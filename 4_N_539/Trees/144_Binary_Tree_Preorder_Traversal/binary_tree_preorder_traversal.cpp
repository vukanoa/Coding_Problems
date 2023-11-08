#include <iostream>
#include <vector>
#include <stack>

/*
    ============
    === EASY ===
    ============

    ===================================
    144) Binary Tree Preorder Traversal
    ===================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the preorder traversal of its
    nodes' values.

    Follow up: Recursive solution is trivial, could you do it iteratively?

    ========================================================
    FUNCTION: vector<int> preorderTraversal(TreeNode* root);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,2,3]
    Output: [1,2,3]

    --- Example 2 ---
    Input: root = []
    Output: []

    --- Example 3 ---
    Input: root = [1]
    Output: [1]


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 100].
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

/* Time  Beats: 100.00% */
/* Space Beats:  48.84% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursive {
public:
    std::vector<int> preorderTraversal(TreeNode* root)
    {
        std::vector<int> result;
        preorder(root, result);

        return result;
    }

private:
    void preorder(TreeNode* root, std::vector<int>& result)
    {
        if (!root)
            return;

        result.push_back(root->val);
        preorder(root->left,  result);
        preorder(root->right, result);
    }
};




/* Time  Beats: 100.00% */
/* Space Beats: 48.84% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Iterative {
public:
    std::vector<int> preorderTraversal(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        std::stack<TreeNode*> stack;
        stack.push(root);

        while (!stack.empty())
        {
            root = stack.top();
            stack.pop();

            result.push_back(root->val);

            if (root->right)
                stack.push(root->right);

            if (root->left)
                stack.push(root->left);
        }

        return result;
    }
};
