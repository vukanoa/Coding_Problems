#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    257) Binary Tree Paths
    ===========================

    ============
    Description:
    ============

    Given the root of a binary tree, return all root-to-leaf paths in any
    order.

    A leaf is a node with no children.

    =========================================================
    FUNCTION: vector<string> binaryTreePaths(TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,null,5]
    Output: ["1->2->5","1->3"]

    --- Example 2 ---
    Input: root = [1]
    Output: ["1"]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 100].
    -100 <= Node.val <= 100

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

    Basic DFS. The only "problematic" thing is how to construct the string.
    Only the first one should begin with "->", or only the last one shouldn't
    be ending with "->", whichever way makes more sense to you.

    I chose the latter, therefore, before pushing the string "path" to result,
    I am popping last two characers, i.e. '-' and '>'.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  39.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root)
    {
        std::vector<string> result;

        dfs(root, "", result);

        return result;
    }

private:
    void dfs(TreeNode* root, std::string path, std::vector<string>& result)
    {
        if ( ! root)
            return;

        path += std::to_string(root->val) + "->";

        if (!root->left && !root->right)
        {
            path.pop_back(); // '>'
            path.pop_back(); // '-'

            result.push_back(path);
            return;
        }

        dfs(root->left,  path, result);
        dfs(root->right, path, result);
    }
};
