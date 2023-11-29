#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    513) Find Bottom Left Tree Value
    ================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the leftmost value in the last row
    of the tree.

    ==================================================
    FUNCTION: int findBottomLeftValue(TreeNode* root);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [2,1,3]
    Output: 1


    --- Example 2 ---
    Input: root = [1,2,3,4,null,5,6,null,null,7]
    Output: 7


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    -2^31 <= Node.val <= 2^31 - 1

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

    The most basic use of BFS on a Binary Tree.

*/

/* Time  Beats: 39.00% */
/* Space Beats: 43.58% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    int findBottomLeftValue(TreeNode* root)
    {
        if (!root->left && !root->right)
            return root->val;
        
        std::queue<TreeNode*> queue;
        queue.push(root);

        int left_most = root->val;

        while (!queue.empty())
        {
            int size = queue.size();

            for (int i = 0; i < size; i++)
            {
                if (i == 0)
                    left_most = queue.front()->val;
                
                TreeNode* curr_node = queue.front();
                queue.pop();

                if (curr_node->left)
                    queue.push(curr_node->left);
                
                if (curr_node->right)
                    queue.push(curr_node->right);
            }
        }

        return left_most;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The most Basic use of DFS in a Binary Tree.

*/

/* Time  Beats: 78.75% */
/* Space Beats: 96.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    int findBottomLeftValue(TreeNode* root)
    {
        if (!root->left && !root->right)
            return root->val;

        int left_most;
        int level = 0;
        int max_level = 0;

        dfs(root, max_level, level+1, left_most);

        return left_most;
    }

private:
    void dfs(TreeNode* root, int& max_level, int curr_level, int& left_most)
    {
        if (!root)
            return;

        if (curr_level > max_level)
        {
            max_level = curr_level;
            left_most = root->val;
        }

        dfs(root->left,  max_level, curr_level+1, left_most);
        dfs(root->right, max_level, curr_level+1, left_most);
    }
};
