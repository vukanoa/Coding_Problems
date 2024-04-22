#include <iostream>

/*
    ============
    === EASY ===
    ============

    ==============================
    222) Count Complete Tree Nodes
    ==============================

    ============
    Description:
    ============

    Given the root of a complete binary tree, return the number of the nodes in
    the tree.

    According to Wikipedia, every level, except possibly the last, is
    completely filled in a complete binary tree, and all nodes in the last
    level are as far left as possible. It can have between 1 and 2h nodes
    inclusive at the last level h.

    Design an algorithm that runs in less than O(n) time comple

    =========================================
    FUNCTION: int countNodes(TreeNode* root);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,4,5,6]
    Output: 6

    --- Example 2 ---
    Input: root = []
    Output: 0

    --- Example 3 ---
    Input: root = [1]
    Output: 1


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 5 * 10^4].
    0 <= Node.val <= 5 * 10^4
    The tree is guaranteed to be complete.

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

    The height of a tree can be found by just going left. Let a single node
    tree have height 0. Find the height h of the whole tree. If the whole tree
    is empty, i.e. has height -1, there are 0 nodes.

    Otherwise check whether the height of the right subtree is just one less
    than that of the whole tree, meaning left and right subtree have the same
    height.

    If yes, then the last node on the last tree row is in the right subtree and
    the left subtree is a full tree of height h-1. So we take the 2^h-1 nodes
    of the left subtree plus the 1 root node plus recursively the number of
    nodes in the right subtree.

    If no, then the last node on the last tree row is in the left subtree and
    the right subtree is a full tree of height h-2. So we take the 2^(h-1)-1
    nodes of the right subtree plus the 1 root node plus recursively the number
    of nodes in the left subtree.

    Since we halve the tree in every recursive step, we have: O(log(n)) steps.

    Finding a height costs O(log(n)).
    Therefore,  overall O(log(n)^2).

*/

/* Time  Beats: 88.00% */
/* Space Beats: 43.42% */

/* Time  Complexity: O(log(n)^2) */
/* Space Complexity: O(log(n))   */
class Solution {
public:
    int countNodes(TreeNode* root)
    {
        int h = height(root);

        if (h < 0)
            return 0;

        if (height(root->right) == h-1)
            return (1 << h)   + countNodes(root->right);
        else
            return (1 << h-1) + countNodes(root->left);
    }

private:
    int height(TreeNode* root)
    {
        return root == nullptr ? -1 : 1+height(root->left);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent to the one above, however this one is implemented
    differently.

*/

/* Time  Beats: 24.03% */
/* Space Beats: 78.63% */

/* Time  Complexity: O(log(n)^2) */
/* Space Complexity: O(log(n))   */
class Solution_Ternary {
public:
    int countNodes(TreeNode* root)
    {
        int h = height(root);

        return h < 0 ? 0 : (height(root->right) == h-1 ? (1 << h)   + countNodes(root->right)
                                                       : (1 << h-1) + countNodes(root->left));
    }

private:
    int height(TreeNode* root)
    {
        return root == nullptr ? -1 : 1+height(root->left);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

   Here's an iterative version as well, with the benefit that we don't
   recompute h in every step.

*/

/* Time  Beats: 63.32% */
/* Space Beats: 78.63% */

/* Time  Complexity: O(log(n)^2) */
/* Space Complexity: O(log(n))   */
class Solution_Iterative {
public:
    int countNodes(TreeNode* root)
    {
        int nodes = 0;
        int h = height(root);

        while (root)
        {
            if (height(root->right) == h - 1)
            {
                nodes += 1 << h;
                root = root->right;
            }
            else
            {
                nodes += 1 << (h-1);
                root = root->left;
            }

            h--;
        }

        return nodes;
    }

private:
    int height(TreeNode* root)
    {
        return root == nullptr ? -1 : 1+height(root->left);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A combination of Iterative and Recursive Solutoins above. It seems as if
    this runs fastest on LeetCode for some reason.

*/

/* Time  Beats: 94.34% */
/* Space Beats: 12.85% */

/* Time  Complexity: O(log(n)^2) */
/* Space Complexity: O(log(n))   */
class Solution_Efficient {
public:
    int countNodes(TreeNode* root)
    {
        if ( ! root)
            return 0;

        TreeNode* left  = root;
        TreeNode* right = root;
        int height = 0;

        while (right)
        {
            left  = left->left;
            right = right->right;
            height++;
        }

        if ( ! left)
            return (1 << height) - 1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Concise way of solving. It is not the most Time efficient, but it does the
    job.

*/

/* Time  Beats: 54.04% */
/* Space Beats: 78.63% */

/* Time  Complexity: O(log(n)^2) */
/* Space Complexity: O(log(n))   */
class Solution_Concise {
public:
    int countNodes(TreeNode* root)
    {
        if ( ! root)
            return 0;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
