#include <iostream>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    117) Populating Next Right Pointers in Each Node II
    ===================================================

    ============
    Description:
    ============

    Given a binary tree

    struct Node {
      int val;
      Node *left;
      Node *right;
      Node *next;
    }

    Populate each next pointer to point to its next right node. If there is no
    next right node, the next pointer should be set to NULL.

    Initially, all next pointers are set to NULL.

    Follow up:
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
    Input: root = [1,2,3,4,5,null,7]
    Output: [1,#,2,3,#,4,5,7,#]
    Explanation: Given the above binary tree (Figure A), your function should
                 populate each next pointer to point to its next right node,
                 just like in Figure B. The serialized output is in level order
                 as connected by the next pointers, with '#' signifying the end
                 of each level.


    --- Example 2 ---
    Input: root = []
    Output: []


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 6000].
    -100 <= Node.val <= 100

*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

/* Time  Beats: 84.30% */
/* Space Beats: 32.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    Node* connect(Node* root)
    {
        if ( ! root)
            return nullptr;

        std::queue<Node*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                Node* curr = queue.front();
                queue.pop();

                if (curr->left)
                    queue.push(curr->left);

                if (curr->right)
                    queue.push(curr->right);

                // Only the rightmost's next doesn't need to be updated
                if (x < size-1)
                    curr->next = queue.front();
            }
        }

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The crux of this problem is that we're doing a DFS but in an unusual way.
    The "traditional" way of writing a DFS is - Go all the way to the left and
    once you cannot go left anymore, start going right.

    However, since here we're populating "next" pointers, meaning nodes on the
    left side are going to be pointing to the nodes on the right side in that
    same level, we MUST MUST MUST first go "all the way to the right and once
    we cannot go right anymore, we start going left".

    In other words, we must solve this problem by going to right nodes first.
    And only when we're done doing that, we can go to the left.

    Why?

    Because we need ALL of the next pointers of the level above the current one
    to be solved.

    And why do we need that?

    Consider these two examples:

First:
[2,1,3,0,7,9,1,2,null,1,0,null,null,8,8,null,null,null,null,7]

                                    2
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       1                         3
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                0             7           9             1
               /             / \                       / \
              /             /   \                     /   \
             /             /     \                   /     \
            2             1       0                 8       8
                                 /
                                /
                               7



Second:
[5,2,-2,4,-4,-8,2,7,2,null,-9,1,null,null,3,null,8,null,null,null,null,null,null,null,6]

                                    5
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       2                        -2
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                4            -4          -8             2
               / \             \         /               \
              /   \             \       /                 \
             /     \             \     /                   \
      ----> 7       2            -9   1                     3
      |      \                                               \
      |       \                                               \
      |        8                                               6
      |
      |
      |___________
                 |
                 |
                 |
    When we are here, and we want to populate 7's Right's next, i.e. 8's next,
    then we MUST have all the next pointers in current level of the root(in
    this moment the root is the pointed node 7). Meaning, we MUST already have
    correct populated "next" pointers at that level so that we can iterate
    through all of the next pointers and reach the first one with a non-null
    left or right node, respectively.
    (We ALWAYS are checking to see if there is a left node of some root->next,
     if it's not, then and only then we check if there is root->next's right)


    Therefore we must have this situation:
                                    5  ===> NULL
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       2 =====================> -2 ===> NULL
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                4 =========> -4 =======> -8 ==========> 2 ===> NULL
               / \             \         /               \
              /   \             \       /                 \
             /     \             \     /                   \
      ----> 7 ====> 2 ========> -9 => 1 ==================> 3 ===> NULL
      |      \                                               \
      |       \                                               \
      |        8 ===> NULL                                     6 ===> NULL
      |
      |
      |____________
                  |
                  |
                  |
     The current root

     Now, from this curren root, we're trying to populate root->right->next.

     To do that, we are checking is root->next exists. Since it does then we
     are iterating through the linked list whose head is pointed by root->next.

     If at any point we find out that some root->next is NOT NULL and that
     there is either root->next->left or root->next->right, we assign the first
     of those two to our root->right->next and we break the "while loop".

     However, since we cannot iterate with our "root" pointer, we will make
     a tempoerary pointer called "curr" which we'll use to iterate over root's
     next pointers.

     Once "curr" becomes node 1 in the current root's level list, we'll ask:
     if curr->next->left or curr->next->right exist and we'll assign that
     non-null node to the root->right->next(8's next in this case).

     It's important to emphasize that once the "curr" points to 1 in the Linked
     List and once we say "curr->next", we don't mean node 1, but node 3, since
     "curr" is node 1 and "curr->next" node 1's next, which is node 3.

     Then 3's left is NULL, but 3's right is NOT NULL, therefore we assign:

        root->right->next = curr->next->right;

         (7->right->next) =  (1->next->right)
                (8->next) =  (3->right)
                (8->next) =  (node 6)

*/

/* Time  Beats: 84.30% */
/* Space Beats: 87.77% */

/*
    Time  Complexity: O(n)
*/
/*
    Space Complexity: O(1)
    They told us in the Description that:

    "You may only use constant extra space.  The recursive approach is
     fine. You may assume implicit stack space does not count as extra space
     for this problem."

    Thus, this Solution can be considered as O(1) Space Complexity.
*/
class Solution_Efficient {
public:
    Node* connect(Node* root)
    {
        if ( ! root)
            return nullptr;

        /* Left's Next */
        if (root->left && root->right)
        {
            root->left->next = root->right;
        }
        else if (root->left && root->next)
        {
            Node* curr = root;
            while (curr->next)
            {
                if (curr->next->left)
                {
                    root->left->next = curr->next->left;
                    break;
                }
                else if (curr->next->right)
                {
                    root->left->next = curr->next->right;
                    break;
                }

                curr = curr->next;
            }
        }

        /* Right's Next */
        if (root->right && root->next)
        {
            Node* curr = root;
            while (curr->next)
            {
                if (curr->next->left)
                {
                    root->right->next = curr->next->left;
                    break;
                }
                else if (curr->next->right)
                {
                    root->right->next = curr->next->right;
                    break;
                }

                curr = curr->next;
            }
        }

        connect(root->right); // We MUST MUST MUST do the right subtree first!
        connect(root->left);

        return root;
    }
};
