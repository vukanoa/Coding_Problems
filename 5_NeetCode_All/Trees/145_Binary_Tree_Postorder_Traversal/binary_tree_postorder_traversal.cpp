#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    145) Binary Tree Postorder Traversal
    ====================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the postorder traversal of its
    nodes' values.

    Follow up: Recursive solution is trivial, could you do it iteratively?

    =========================================================
    FUNCTION: vector<int> postorderTraversal(TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,2,3]
    Output: [3,2,1]

    --- Example 2 ---
    Input: root = []
    Output: []

    --- Example 3 ---
    Input: root = [1]
    Output: [1]

    *** Constraints ***
    The number of the nodes in the tree is in the range [0, 100].
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

/* Time  Beats:   100% */
/* Space Beats: 67.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> postorderTraversal(TreeNode* root)
    {
        std::vector<int> result;
        postorder(root, result);

        return result;
    }

private:
    void postorder(TreeNode* root, std::vector<int>& result)
    {
        if (!root)
            return;

        postorder(root->left, result);
        postorder(root->right, result);
        result.push_back(root->val);
    }
};




/* Time  Beats:   100% */
/* Space Beats: 67.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Iterative_2_Stacks {
public:
    std::vector<int> postorderTraversal(TreeNode* root)
    {
        if (!root)
            return {};

        std::stack<TreeNode*> s1;
        std::stack<TreeNode*> s2;

        s1.push(root);
        while (!s1.empty())
        {
            root = s1.top();
            s1.pop();

            s2.push(root);

            if (root->left)
                s1.push(root->left);

            if (root->right)
                s1.push(root->right);
        }

        std::vector<int> result;
        while (!s2.empty())
        {
            result.push_back(s2.top()->val);
            s2.pop();
        }

        return result;
    }
};




/* Time  Beats:   100% */
/* Space Beats: 67.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Iterative_A_Single_Stack {
public:
    std::vector<int> postorderTraversal(TreeNode* root)
    {
        std::vector<int> result;
        std::stack<TreeNode*> stack;

        TreeNode* current = root;

        while (current || !stack.empty())
        {
            if (current)
            {
                stack.push(current);
                current = current->left;
            }
            else
            {
                TreeNode* tmp = stack.top()->right;

                if (!tmp)
                {
                    tmp = stack.top();
                    stack.pop();

                    result.push_back(tmp->val);

                    while (!stack.empty() && tmp == stack.top()->right)
                    {
                        tmp = stack.top();
                        stack.pop();

                        result.push_back(tmp->val);
                    }
                }
                else
                    current = tmp;
            }
        }

        return result;
    }
};
