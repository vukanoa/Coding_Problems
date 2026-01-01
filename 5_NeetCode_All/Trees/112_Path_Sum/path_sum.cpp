#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    112) Path Sum
    ===========================

    ============
    Description:
    ============

    Given the root of a binary tree and an integer targetSum, return true if
    the tree has a root-to-leaf path such that adding up all the values along
    the path equals targetSum.

    A leaf is a node with no children.

    =========================================================
    FUNCTION: bool hasPathSum(TreeNode* root, int targetSum);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
    Output: true
    Explanation: The root-to-leaf path with the target sum is shown.


    --- Example 2 ---
    Input: root = [1,2,3], targetSum = 5
    Output: false
    Explanation: There two root-to-leaf paths in the tree:
    (1 --> 2): The sum is 3.
    (1 --> 3): The sum is 4.
    There is no root-to-leaf path with sum = 5.


    --- Example 3 ---
    Input: root = [], targetSum = 0
    Output: false
    Explanation: Since the tree is empty, there are no root-to-leaf paths.


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 5000].
    -1000 <= Node.val <= 1000
    -1000 <= targetSum <= 1000

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

    One of the fundamental techniques - DFS. It's nothing tricky of fancy or
    advanced.

    If you know how DFS works and if you know how to implement it recursively,
    you should be able to solve this.

    If not, make sure to figure out DFS first, that is definitely a
    prerequisite for this problem.

*/

/* Time  Beats: 96.44% */
/* Space Beats: 89.80% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum)
    {
        return dfs(root, targetSum, 0);
    }

private:
    bool dfs(TreeNode* root, int& targetSum, int currSum)
    {
        if (!root)
            return false;

        if (!root->left && !root->right)
            return (currSum + root->val) == targetSum;

        return dfs(root->left,  targetSum, currSum + root->val) ||
               dfs(root->right, targetSum, currSum + root->val);
    }
};
