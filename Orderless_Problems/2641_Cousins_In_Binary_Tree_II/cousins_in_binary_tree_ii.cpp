#include <iostream>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    2641) Cousins in Binary Tree II
    ===============================

    ============
    Description:
    ============

    Given the root of a binary tree, replace the value of each node in the tree
    with the sum of all its cousins' values.

    Two nodes of a binary tree are cousins if they have the same depth with
    different parents.

    Return the root of the modified tree.

    =====
    Note: Note that the depth of a node is the number of edges in the path from the
          root node to it.
    =====

    =======================================================
    FUNCTION: TreeNode* replaceValueInTree(TreeNode* root);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,4,9,1,10,null,7]
    Output: [0,0,0,7,7,null,11]
    Explanation: The diagram above shows the initial binary tree and the binary
    tree after changing the value of each node.
    - Node with value 5 does not have any cousins so its sum is 0.
    - Node with value 4 does not have any cousins so its sum is 0.
    - Node with value 9 does not have any cousins so its sum is 0.
    - Node with value 1 has a cousin with value 7 so its sum is 7.
    - Node with value 10 has a cousin with value 7 so its sum is 7.
    - Node with value 7 has cousins with values 1 and 10 so its sum is 11.

    --- Example 2 ---
    Input: root = [3,1,2]
    Output: [0,0,0]
    Explanation: The diagram above shows the initial binary tree and the binary
    tree after changing the value of each node.
    - Node with value 3 does not have any cousins so its sum is 0.
    - Node with value 1 does not have any cousins so its sum is 0.
    - Node with value 2 does not have any cousins so its sum is 0.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^5].
    1 <= Node.val <= 10^4

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    By the time you finish reading description, you should intuitively know if
    it's possible to solve this problem by DFS or BFS.

    Sometimes it's neither, but one is ALWAYS more likely.

    In this case, since we're dealing with the "same level nodes", it's very
    obvious that BFS is the more likely approach to work. More likely than DFS.

    Maybe not even BFS is going to help us, but we'll see.


    Now, everytime you're dealing with "brothers", "cousins" kind of Tree
    problems, especially where you're asked to change the values of the
    nodes(or pointers or something similar), it's usually easiest to do so
    while you're ON the parent node.

    Meaning - If you want to change the value(or pointer of some kind) of some
    node, it's usually the best to do so by accessing that node through the
    parent, i.e. curr_node->left or curr_node->right.


    Knowing these general-directions, we're almost there.

    When doing Tree Problems, always try at least 4 different Trees:
        1. Empty Tree(If it's possible, check the Constraints)
        2. Single-node Tree
        3. Two  levels Tree(2 or 3 nodes)
        4. Five levels Tree

    First 3 are kind of an edge case, ususally, but you should take care of
    those immediately since you shouldn't be constrained by those by any means.

    Even if you general solution works for every other case besides these first
    three, then you should cover them separately, in if-elseif at the
    beginning.

    Now, let's focus on the "Five levels" tree.

    It's usually the best to go with 5 levels because that's enough nodes and
    levels and branches to cover all possibles scenarios. I'm not sure I
    remember a problem where 5 level wasn't enough to notice something
    important about the problem.

    Height: 5

        _______________________A_______________________  // Level 0
        ___________B_______________________C___________  // Level 1
        _____D___________E___________F___________G_____  // Level 2
        __H_____I_____J_____K_____L_____M_____N_____O__  // Level 3
        P___Q_R___S_T___U_V___W_X___Y_Z___@_#___$_%___&  // Level 4


    Let's consider Level 2.

    We're at node: D

    What are counsins of D's children, i.e. cousins of H and I?
    Nodes at the same level as H and I, but with different parents. They are:

        J, K, L, M, N and O

    Since we're doing a BFS, imagine that in the Queue, we have: D, E, F, G

    We took D and now how can we get the sum of all cousins?
    We'll, we MUST go through all the other nodes on the same level and sum
    their children's values.

    However, if we do that, since they are in the Queue, we are going to empty
    the Queue and therefore will be unable to do the same for those nodes'
    children.

    Solutions - After we "iterate" through those nodes, each time we pop them
    and add their children's values, we are going to push this nodes back.

    Aren't we going to have an infinite loop? No, because we'll pop and
    push(pop and push we'll be done in ONE iteration) exactly size-1 times.

    "size" is the number of nodes in the current level. At level 2, at the
    beginning it's 4(D, E, F and G). However, we do NOT want to count current
    node's children as cousins and besides that we've ALREADY popped current
    node(D, the first one), therefore we have to pop it 4-1 times, i.e. 3 more
    times.

    Therefore we'll pop E, add it's children's sum and push it back at the end.
    Then,     we'll pop F, add it's children's sum and push it back at the end.
    Then,     we'll pop G, add it's children's sum and push it back at the end.

    After we're doing we have "suffix_sum" calculated and the STATE of the
    Queue is the same as before we've calculated "suffix_sum".

    Since it would be VERY inefficient to count all the remaining nodes'
    children values each time, we're going to have this "suffix_sum". However,
    once we get to bet at Node 'E' or 'F', now we NEED D's children values
    because those ARE indeed cousins at to 'E' and 'F'(and will be to 'G').

    But how are we going to calculate them if we've already popped those values
    and we've even changed their initial values?

        Simple - We're going to keep another variable "prefix_sum" which we'll
        add values to right before we change that children's value.

    However, each time(except the first node in the Level) we'll have to
    SUBTRACT current node's children value from "suffix_sum" since individual
    nodes cannot be cousins to themselves or their brothers and also
    "suffix_sum" was calculated BEFORE where it DID include current node's
    children. Now we have to remove them.

    After removal, we say current node's children values are now: prefix_sum +
    suffix_sum.

    That's the entire Solution.

    (There are a few minor temporary variables for prefix_sum, but you'll
     understand that in the code below. The crux is unchanged)

*/

/* Time  Beats: 99.55% */
/* Space Beats: 25.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root)
    {
        root->val = 0;

        queue<TreeNode*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();

            int prefix_sum = 0;
            int suffix_sum = 0;

            for (int i = 0; i < size; i++)
            {
                TreeNode* curr_node = queue.front();
                queue.pop();

                if (i == 0)
                {
                    for (int x = 0; x < size-1; x++)
                    {
                        TreeNode* tmp_node = queue.front();
                        queue.pop();

                        suffix_sum += tmp_node->left  ? tmp_node->left->val  : 0;
                        suffix_sum += tmp_node->right ? tmp_node->right->val : 0;

                        queue.push(tmp_node);
                    }

                    if (curr_node->left)
                    {
                        prefix_sum += curr_node->left->val;
                        curr_node->left->val = suffix_sum;

                        queue.push(curr_node->left);
                    }

                    if (curr_node->right)
                    {
                        prefix_sum += curr_node->right->val;
                        curr_node->right->val = suffix_sum;

                        queue.push(curr_node->right);
                    }
                }
                else
                {
                    int tmp_prefix_sum = prefix_sum;

                    // So that the both, potential, nodes are subtracted before
                    // we use suffix_sum
                    suffix_sum -= curr_node->left  ? curr_node->left->val  : 0;
                    suffix_sum -= curr_node->right ? curr_node->right->val : 0;

                    if (curr_node->left)
                    {
                        tmp_prefix_sum += curr_node->left->val;
                        curr_node->left->val = prefix_sum + suffix_sum;

                        queue.push(curr_node->left);
                    }

                    if (curr_node->right)
                    {
                        tmp_prefix_sum += curr_node->right->val;
                        curr_node->right->val = prefix_sum + suffix_sum;

                        queue.push(curr_node->right);
                    }

                    prefix_sum = tmp_prefix_sum;
                }
            }
        }

        return root;
    }
};
