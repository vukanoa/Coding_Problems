#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    404) Sum Of Left Leaves
    ===========================

    ============
    Description:
    ============

    Given the root of a binary tree, return the sum of all left leaves.

    A leaf is a node with no children. A left leaf is a leaf that is the left
    child of another node.

    ==============================================
    FUNCTION: int sumOfLeftLeaves(TreeNode* root);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,9,20,null,null,15,7]
    Output: 24
    Explanation: There are two left leaves in the binary tree, with values 9
                 and 15 respectively.

    --- Example 2 ---
    Input: root = [1]
    Output: 0


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 1000].
    -1000 <= Node.val <= 1000

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

    One of the most fundamental DFS uses. If you do NOT understand this, please
    learn DFS first and then come back.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root)
    {
        if (!root->left && !root->right)
            return 0;

        int sum = 0;
        dfs(root, false, sum);

        return sum;
    }

private:
    void dfs(TreeNode* root, bool left_node, int& sum)
    {
        if ( ! root)
            return;
        else if (left_node && !root->left && !root->right)
        {
            sum += root->val;
            return;
        }

        dfs(root->left,  true,  sum);
        dfs(root->right, false, sum);
    }
};
