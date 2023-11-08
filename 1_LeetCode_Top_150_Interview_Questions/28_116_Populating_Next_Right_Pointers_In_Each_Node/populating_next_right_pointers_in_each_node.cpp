#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    116) Populating Next Right Pointers in Each Node
    ================================================

    ============
    Description:
    ============

    You are given a perfect binary tree where all leaves are on the same level,
    and every parent has two children. The binary tree has the following
    definition:

    struct Node {
        int val;
        Node *left;
        Node *right;
        Node *next;
    }

    Populate each next pointer to point to its next right node. If there is no
    next right node, the next pointer should be set to NULL.

    Initially, all next pointers are set to NULL.



    Follow-up:

    You may only use constant extra space.
    The recursive approach is fine. You may assume implicit stack space does
    not count as extra space for this problem.

    ====================================
    FUNCTION: Node* connect(Node* root);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

           1                                    1 -----------> NULL
     2           3                        2 --------> 3 -----> NULL
  4     5     6     7                  4 --> 5 --> 6 --> 7 --> NULL

    Input: root = [1,2,3,4,5,6,7]
    Output: [1,#,2,3,#,4,5,6,7,#]
    Explanation: Given the above perfect binary tree (Figure A), your function
    should populate each next pointer to point to its next right node, just
    like in Figure B. The serialized output is in level order as connected by
    the next pointers, with '#' signifying the end of each level.

    --- Example 2 ---
    Input: root = []
    Output: []

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 2^12 - 1].
    -1000 <= Node.val <= 1000

*/


/*
    ------------
    --- IDEA ---
    ------------

    At the beginning all of the next pointers are pointing to NULL.
    So, we don't have to worry about that.

                           1 -------------------------> NULL
               2                       3 -------------> NULL
         3           4           6           7 -------> NULL
      8     9     10   11     12   13     14    15 ---> NULL

    The idea is simpler than you think.

    You can see that in order to link Node 2 and Node 3, you have to be on
    Node 1.

    So basically just do a DFS and link children. However that would get us in
    this position:

    From this:
                           1 -------------------------> NULL
               2                       3 -------------> NULL
         3           4           6           7 -------> NULL
      8     9     10   11     12   13     14    15 ---> NULL


    To this:
                           1 -------------------------> NULL
               2 --------------------> 3 -------------> NULL
         3 --------> 4           6 --------> 7 -------> NULL
      8 --> 9     10 ->11     12 ->13     14 -> 15 ---> NULL


    But what about these in the middle?
    9  doesn't point to 10
    11 doesn't point to 12
    13 doesn't point to 14
    4  doesn't point to 6

    How can we link those?

    The idea is unbelievably simple. It's much much more simple than you think.
    At least it's a lot simpler than I thought.

    Since we're linking the nodes from the parent to the children, say:
    from Node 2, we linked 3 and 4.

    So when we're at the Node 3, how are we going to link Node 9 and Node 10?

    It seems kind of impossible right?

    Just look at what we have been doing up to this point?
    We were linking children's NEXT pointers.

    When we are at, say, Node 3, it's NEXT pointer already points to Node 4.
    So now, to link Node 9 to Node 10, we have to use that NEXT pointer.

    We are at the Node 3:

         3 --------> 4
      8 --> 9     10 ->11

    To link 9 to 10, we only have to do:
    3->right      // Which is 9

    3->next->left // Which is 10

    3->right = 3->next->left;

    And Voila!

    That's the crux of this Solution.

*/

/* Time  Beats: 81.54% */
/* Space Beats: 94.90% */

/* Time  Complexity: O(n) */
/*
    Space Complexity: O(1)
    In description we're told that Recursion doesn't count as additional memory
    in this problem.
*/
class Solution_Recursive_1 {
public:
    Node* connect(Node* root)
    {
        dfs(root);

        return root;
    }

private:
    void dfs(Node* root)
    {
        if (root == nullptr)
            return;

        if (root->left != nullptr)
        {
            root->left->next = root->right;

            if (root->next != nullptr)
                root->right->next = root->next->left;
        }

        dfs(root->left);
        dfs(root->right);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it in a recursive fashion.

*/

/* Time  Beats: 84.28% */
/* Space Beats: 88.95% */

/* Time  Complexity: O(n) */
/*
    Space Complexity: O(1)
    In description we're told that Recursion doesn't count as additional memory
    in this problem.
*/
class Solution_Recursive_2 {
public:
    Node* connect(Node* root)
    {
        if (!root || !root->left)
            return root;

        populate(root->left,  root, true);
        populate(root->right, root, false);

        return root;
    }

private:
    void populate(Node* root, Node* parent, bool left_side)
    {
        if (!root) // If we're below the leaf
            return;

        if (left_side)
        {
            root->next = parent->right;

            populate(root->left,  root, true);
            populate(root->right, root, false);
        }
        else
        {
            if (parent->next)
                root->next = parent->next->left;

            populate(root->left,  root, true);
            populate(root->right, root, false);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's a similar Approach. The main thing, again, is to make use of the NEXT
    pointer.

    However, here, instead of doing a DFS, we're kind of doing a BFS approach.
    Though a BFS in O(1).

    How's that possible?

    Well, instead of putting the elements of every level in a Queue, we will
    make use of our NEXT pointers.

    Simulation:


               curr
         next    |
           |     v
           v     1 -----------> NULL
           2           3 -----> NULL
        4     5     6     7 --> NULL


         curr
      next |
        |  |
        |  v     1 -----------> NULL
        v  2 --------> 3 -----> NULL
        4     5     6     7 --> NULL


        Now since curr->next != nullptr, we shift curr not to "next" but to
        curr->next. Now we're in this situation.


                     curr
      next             |
        |              |
        |        1 ----v------> NULL
        v  2 --------> 3 -----> NULL
        4 --> 5 --> 6 --> 7 --> NULL


        Now, again, curr->next == nullptr, so we move "next" to next->left.
        Since that is NULL, that's how we know we're done with the algorithm.


                     curr
      next             |
        |              |
        |        1 ----v------> NULL
        v  2 --------> 3 -----> NULL
        4 --> 5 --> 6 --> 7 --> NULL
*/


/* Time  Beats: 85.43% */
/* Space Beats: 79.58% */

/* Time  Complexity: O(n) */
/*
    Space Complexity: O(1)
    This is true O(1).
*/
class Solution_True_Constant_Space {
public:
    Node* connect(Node* root)
    {
        Node* curr = root;
        Node* next;

        if (root != nullptr)
            next = root->left;

        while (curr != nullptr && next != nullptr)
        {
            curr->left->next = curr->right;

            if (curr->next)
                curr->right->next = curr->next->left;

            curr = curr->next;

            if (curr == nullptr)
            {
                curr = next;
                next = curr->left;
            }
        }

        return root;
    }
};
