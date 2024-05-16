#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    2331) Boolean Binary Tree
    ===========================

    ============
    Description:
    ============

    You are given the root of a full binary tree with the following properties:

        + Leaf nodes have either the value 0 or 1, where 0 represents False and
          1 represents True.

        + Non-leaf nodes have either the value 2 or 3, where 2 represents the
          boolean OR and 3 represents the boolean AND.

    The evaluation of a node is as follows:

        + If the node is a leaf node, the evaluation is the value of the node,
          i.e. True or False.

        + Otherwise, evaluate the node's two children and apply the boolean
          operation of its value with the children's evaluations.

    Return the boolean result of evaluating the root node.

    A full binary tree is a binary tree where each node has either 0 or 2
    children.

    A leaf node is a node that has zero children.

    ============================================
    FUNCTION: bool evaluateTree(TreeNode* root);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                        OR           ===>          OR         ===>   True
                      /    \                     /    \
                     /      \                   /      \
                    /        \                True    False
                   /          \
                  /            \
                True           AND
                               / \
                              /   \
                             /     \
                          False    True

    Input: root = [2,1,3,null,null,0,1]
    Output: true
    Explanation: The above diagram illustrates the evaluation process.
                 The AND node evaluates to False AND True = False.
                 The OR node evaluates to True OR False = True.
                 The root node evaluates to True, so we return true.


    --- Example 2 ---
    Input: root = [0]
    Output: false
    Explanation: The root node is a leaf node and it evaluates to false, so we
                 return false.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 1000].
    0 <= Node.val <= 3
    Every node has either 0 or 2 children.
    Leaf nodes have a value of 0 or 1.
    Non-leaf nodes have a value of 2 or 3.

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

    A standard DFS for Binary Tree Problem. If you don't get it, make sure you
    solved Problems such as:

    1) 226 Invert Binary Tree
    2) 104 Maximum Depth of Binary Tree
    3) 100 Same Tree
    4) Subtree of Another Tree

    After those, this one will be obvious, plus these four above are essential
    to solving Binary Tree Problems, so it's better to solve it sooner than
    later.

*/

/* Time  Beats: 87.42% */
/* Space Beats: 64.84% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool evaluateTree(TreeNode* root)
    {
        if (!root->left && !root->right)
            return root->val;

        bool left  = evaluateTree(root->left);
        bool right = evaluateTree(root->right);

        if (root->val == 2)
            return left || right;

        return left && right; // if (root->val == 3), but it's implicit
    }
};
