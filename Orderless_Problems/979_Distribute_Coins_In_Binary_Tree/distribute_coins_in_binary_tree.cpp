#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    979) Distribute Coins in Binary Tree
    ====================================

    ============
    Description:
    ============

    You are given the root of a binary tree with n nodes where each node in the
    tree has node.val coins. There are n coins in total throughout the whole
    tree.

    In one move, we may choose two adjacent nodes and move one coin from one
    node to another. A move may be from parent to child, or from child to
    parent.

    Return the minimum number of moves required to make every node have exactly
    one coin.

    ==============================================
    FUNCTION: int distributeCoins(TreeNode* root);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,0,0]
    Output: 2
    Explanation: From the root of the tree, we move one coin to its left child,
                 and one coin to its right child.


    --- Example 2 ---
    Input: root = [0,3,0]
    Output: 3
    Explanation: From the left child of the root, we move two coins to the root
                 [taking two moves]. Then, we move one coin from the root of
                 the tree to the right child.


    *** Constraints ***
    The number of nodes in the tree is n.
    1 <= n <= 100
    0 <= Node.val <= n
    The sum of all Node.val is n.

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

/* Time  Beats: 100.00% */
/* Space Beats:  22.37% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int distributeCoins(TreeNode* root)
    {
        return dfs(root, nullptr);
    }

private:
    int dfs(TreeNode* root, TreeNode* parent) // Postorder DFS
    {
        if ( ! root)
            return 0;

        int moves = dfs(root->left, root) + dfs(root->right, root);
        int excess_coins = root->val - 1; // Give excess_coins to parent node

        if (parent)
            parent->val += excess_coins; // Now parent's coins

        moves += std::abs(excess_coins);

        return moves;
    }
};
