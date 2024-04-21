#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    113) Path Sum II
    ===========================

    ============
    Description:
    ============

    Given the root of a binary tree and an integer targetSum, return all
    root-to-leaf paths where the sum of the node values in the path equals
    targetSum. Each path should be returned as a list of the node values, not
    node references.

    A root-to-leaf path is a path starting from the root and ending at any leaf
    node. A leaf is a node with no children.

    =====================================================================
    FUNCTION: vector<vector<int>> pathSum(TreeNode* root, int targetSum);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                                    5
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       4                         8
                     /                         /   \
                    /                         /     \
                   /                         /       \
                  /                         /         \
                 /                         /           \
                11                        13            4
               / \                                     / \
              /   \                                   /   \
             /     \                                 /     \
            7       2                               5       1

    Input:  root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
    Output: [[5,4,11,2],[5,8,4,5]]
    Explanation: There are two paths whose sum equals targetSum:
    5 + 4 + 11 + 2 = 22
    5 + 8 + 4 + 5 = 22



    --- Example 2 ---
                             1
                            / \
                           /   \
                          2     3

    Input: root = [1,2,3], targetSum = 5
    Output: []



    --- Example 3 ---
    Input: root = [1,2], targetSum = 0
    Output: []



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

    One of the most basic uses of DFS. The only thing that you should care
    about here is that we don't need to pass another variable named "curr_sum"
    "dfs" function, we can, instead, simply decrement root->val from the
    targetSum.

    Even if root->val is a negative value, it will still work.

    That way we're conservative with Space.

*/

/* Time  Beats: 31.16% */
/* Space Beats: 21.87% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum)
    {
        if ( ! root)
            return {};

        std::vector<std::vector<int>> results;
        dfs(root, targetSum, {}, results);

        return results;
    }

private:
    void dfs(TreeNode* root,
             int targetSum,
             std::vector<int> curr_path,
             std::vector<std::vector<int>>& results)
    {
        if ( ! root)
        {
            return;
        }
        else if (targetSum - root->val == 0 && !root->left && !root->right)
        {
            curr_path.push_back(root->val);
            results.push_back(curr_path);
            return;
        }

        curr_path.push_back(root->val);
        dfs(root->left,  targetSum - root->val, curr_path, results);
        dfs(root->right, targetSum - root->val, curr_path, results);
    }
};
