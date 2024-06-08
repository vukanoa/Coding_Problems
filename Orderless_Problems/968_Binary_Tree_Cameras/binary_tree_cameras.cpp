#include <iostream>

/*
    ============
    === HARD ===
    ============

    ===========================
    968) Binary Tree Cameras
    ===========================

    ============
    Description:
    ============

    You are given the root of a binary tree. We install cameras on the tree
    nodes where each camera at a node can monitor its parent, itself, and its
    immediate children.

    Return the minimum number of cameras needed to monitor all nodes of the
    tree.

    =============================================
    FUNCTION: int minCameraCover(TreeNode* root);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [0,0,null,0,0]
    Output: 1
    Explanation: One camera is enough to monitor all nodes if placed as shown.


    --- Example 2 ---
    Input: root = [0,0,null,0,null,0,null,null,0]
    Output: 2
    Explanation: At least two cameras are needed to monitor all nodes of the
    tree. The above image shows one of the valid configurations of camera
    placement.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 1000].
    Node.val == 0

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

    TODO

*/

/* Time  Beats: 96.39% */
/* Space Beats: 40.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minCameraCover(TreeNode* root)
    {
        if( ! root)
            return 0;

        int cameras = 0;
        if ( ! dfs(root, cameras))
            cameras++;

        return cameras;
    }

private:
    int dfs(TreeNode* root, int& cameras)
    {
        if( ! root)
            return 1;

        int left  = dfs(root->left,  cameras);
        int right = dfs(root->right, cameras);

        if (!left || !right)
        {
            cameras++;
            return 2;
        }

        return std::max(left, right) - 1;
    }
};
