#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    652) Find Duplicate Subtrees
    ============================

    ============
    Description:
    ============

    Given the root of a binary tree, return all duplicate subtrees.

    For each kind of duplicate subtrees, you only need to return the root node
    of any one of them.

    Two trees are duplicate if they have the same structure with the same node
    values.

    ==================================================================
    FUNCTION: vector<TreeNode*> findDuplicateSubtrees(TreeNode* root);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,4,null,2,4,null,null,4]
    Output: [[2,4],[4]]

    --- Example 2 ---
    Input: root = [2,1,1]
    Output: [[1]]

    --- Example 3 ---
    Input: root = [2,2,2,3,null,3,null]
    Output: [[2,3],[3]]


    *** Constraints ***
    The number of the nodes in the tree will be in the range [1, 5000]
    -200 <= Node.val <= 200

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

/* Time  Beats: 25.71% */
/* Space Beats: 31.78% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:

    std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
    {
        std::vector<TreeNode*> result;
        unordered_map<std::string, int> umap;

        preorder_dfs(root, umap, result);

        return result;
    }

private:
    std::string preorder_dfs(TreeNode* root,
                             std::unordered_map<std::string, int>& umap,
                             std::vector<TreeNode*>& result)
    {
        if(!root)
            return "";

        std::string left  = preorder_dfs(root->left,  umap, result);
        std::string right = preorder_dfs(root->right, umap, result);

        std::string str = "(" + left + std::to_string(root -> val) + right + ")";

        if(umap[str] == 1)
            result.push_back(root);

        umap[str]++;

        return str;
    }
};
