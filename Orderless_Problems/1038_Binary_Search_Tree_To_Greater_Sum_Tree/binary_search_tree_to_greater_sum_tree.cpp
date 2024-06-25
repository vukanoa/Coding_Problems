#include <iostream>

/*
    Note: This question is the same as 538:

        https://leetcode.com/problems/convert-bst-to-greater-tree/

*/

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1038) Binary Search Tree To Greater Sum Tree
    ============================================

    ============
    Description:
    ============

    Given the root of a Binary Search Tree (BST), convert it to a Greater Tree
    such that every key of the original BST is changed to the original key plus
    the sum of all keys greater than the original key in BST.

    As a reminder, a binary search tree is a tree that satisfies these
    constraints:

        + The left subtree of a node contains only nodes with keys less than
          the node's key.

        + The right subtree of a node contains only nodes with keys greater
          than the node's key.

        + Both the left and right subtrees must also be binary search trees.


    =============================================
    FUNCTION: TreeNode* bstToGst(TreeNode* root); 
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

    --- Example 2 ---
    Input: root = [0,null,1]
    Output: [1,null,1]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 100].
    0 <= Node.val <= 100
    All the values in the tree are unique.

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

    Inverse Inorder approach.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  12.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int sum = 0;
    TreeNode* bstToGst(TreeNode* root)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        if ( ! root)
            return root;

        bstToGst(root->right);

        sum += root->val;
        root->val = sum;

        bstToGst(root->left);

        return root;
    }
};
