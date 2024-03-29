#include <iostream>

/*
    ============
    === EASY ===
    ============

    ======================================
    606) Construct String From Binary Tree
    ======================================

    ============
    Description:
    ============

    Given the root of a binary tree, construct a string consisting of
    parenthesis and integers from a binary tree with the preorder traversal
    way, and return it.

    Omit all the empty parenthesis pairs that do not affect the one-to-one
    mapping relationship between the string and the original binary tree.

    ==========================================
    FUNCTION: string tree2str(TreeNode* root);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,4]
    Output: "1(2(4))(3)"
    Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need to
                 omit all the unnecessary empty parenthesis pairs. And it will
                 be "1(2(4))(3)"


    --- Example 2 ---
    Input: root = [1,2,3,null,4]
    Output: "1(2()(4))(3)"
    Explanation: Almost the same as the first example, except we cannot omit
                 the first parenthesis pair to break the one-to-one mapping
                 relationship between the input and the output.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
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

/* Time  Beats: 85.14% */
/* Space Beats: 97.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string tree2str(TreeNode* root)
    {
        std::ostringstream out;
        preorder(root, out);

        return out.str();
    }

private:
    void preorder(TreeNode* root, std::ostringstream& out)
    {
        if (!root)
            return;

        /* Root itself */
        out << root->val;

        /* Left Subtree */
        if (root->left || root->right)
            out << "(";

        preorder(root->left, out);

        if (root->left || root->right)
            out << ")";

        /* Right Subtree */
        if (root->right)
            out << "(";

        preorder(root->right, out);

        if (root->right)
            out << ")";
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of impementing it.

*/

/* Time  Beats: 76.35% */
/* Space Beats: 97.60% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    string tree2str(TreeNode* root)
    {
        std::ostringstream out;
        dfs(root, out);

        return out.str();
    }

private:
    void dfs(TreeNode* root, std::ostringstream& out)
    {
        if (!root)
            return;

        /* Root itself */
        out << root->val;

        if (!root->left && !root->right)
            return;

        /* Left Subtree */
        out << "(";
        dfs(root->left, out);
        out << ")";

        /* Right Subtree */
        if (root->right)
        {
            out << "(";
            dfs(root->right, out);
            out << ")";
        }
    }
};
