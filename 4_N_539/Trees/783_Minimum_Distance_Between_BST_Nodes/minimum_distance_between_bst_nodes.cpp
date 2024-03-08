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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.14% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int minDiffInBST(TreeNode* root)
    {
        int result = INT_MAX;
        dfs(root, result);

        return result;
    }

private:
    std::pair<int, int> dfs(TreeNode* root, int& result)
    {
        if (!root->left && !root->right)
            return {root->val, root->val};

        std::pair<int, int> left;
        std::pair<int, int> right;

        if (root->left)
        {
            left = dfs(root->left, result);
            result = std::min(result, root->val - left.second);
        }

        if (root->right)
        {
            right = dfs(root->right, result);
            result = std::min(result, right.first - root->val);
        }

        /* Current Node has only Left Child */
        if (root->left && !root->right)
            return {left.first, root->val};

        /* Current Node has only Right Child */
        if (!root->left && root->right)
            return {root->val, right.second};

        /* Current Node has both Left and Right Child */
        return {left.first, right.second};
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.14% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    int minDiffInBST(TreeNode* root)
    {
        int result = INT_MAX;

        std::vector<int> vec;
        dfs(root, vec);

        for (int i = 0; i < vec.size() - 1; i++)
            result = std::min(result, vec[i+1] - vec[i]);

        return result;
    }

private:
    void dfs(TreeNode* root, std::vector<int>& vec)
    {
        if (!root)
            return;

        dfs(root->left, vec);
        vec.push_back(root->val);
        dfs(root->right, vec);
    }
};
