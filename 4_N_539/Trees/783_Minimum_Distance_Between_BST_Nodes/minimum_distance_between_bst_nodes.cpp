#include <iostream>

/*
    ============
    === EASY ===
    ============

    =======================================
    783) Minimum Distance Between BST Nodes
    =======================================

    ============
    Description:
    ============

    Given the root of a Binary Search Tree (BST), return the minimum difference
    between the values of any two different nodes in the tree.

    =====
    Note: This question is the same as 530:
    =====

    ===========================================
    FUNCTION: int minDiffinBST(TreeNode* root);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [4,2,6,1,3]
    Output: 1

    --- Example 2 ---
    Input: root = [1,0,48,null,null,12,49]
    Output: 1

    *** Constraints ***
    The number of nodes in the tree is in the range [2, 100].
    0 <= Node.val <= 10^5

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

/* Time  Beats:   100% */
/* Space Beats: 56.58% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minDiffInBST(TreeNode* root)
    {
        int min = INT_MAX;

        dfs(root, root->left,  min, nullptr, root   );
        dfs(root, root->right, min, root   , nullptr);

        return min;
    }

private:
    void dfs(TreeNode* parent, TreeNode* root, int& min, TreeNode* left_bound, TreeNode* right_bound)
    {
        if (!root)
            return;

        min = std::min(min, std::abs(parent->val - root->val));

        if (left_bound)
            min = std::min(min, std::abs(left_bound->val - root->val));

        if (right_bound)
            min = std::min(min, std::abs(right_bound->val - root->val));

        dfs(root, root->left,  min, left_bound, root       );
        dfs(root, root->right, min, root,       right_bound);
    }
};