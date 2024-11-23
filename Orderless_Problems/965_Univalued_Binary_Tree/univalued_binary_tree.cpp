#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    965) Univalued Binary Tree
    ===========================

    ============
    Description:
    ============

    A binary tree is uni-valued if every node in the tree has the same value.

    Given the root of a binary tree, return true if the given tree is
    uni-valued, or false otherwise.

    ============================================
    FUNCTION: bool isUnivalTree(TreeNode* root);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,1,1,1,1,null,1]
    Output: true

    --- Example 2 ---
    Input: root = [2,2,2,5,2]
    Output: false

    *** Constraints ***
    The number of nodes in the tree is in the range [1, 100].
    0 <= Node.val < 100

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

    The most fundamental DFS implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    bool isUnivalTree(TreeNode* root)
    {
        int uni_value = root->val;
        return dfs(root, uni_value);
    }

private:
    bool dfs(TreeNode* root, int& uni_value)
    {
        if ( ! root)
            return true;

        if (root->val != uni_value)
            return false;

        return dfs(root->left, uni_value) && dfs(root->right, uni_value);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The most fundamental BFS implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   8.90% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    bool isUnivalTree(TreeNode* root)
    {
        int uni_value = root->val;

        queue<TreeNode*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                TreeNode* curr_node = queue.front();
                queue.pop();

                if (curr_node->val != uni_value)
                    return false;

                if (curr_node->left)
                    queue.push(curr_node->left);

                if (curr_node->right)
                    queue.push(curr_node->right);
            }
        }

        return true;
    }
};
