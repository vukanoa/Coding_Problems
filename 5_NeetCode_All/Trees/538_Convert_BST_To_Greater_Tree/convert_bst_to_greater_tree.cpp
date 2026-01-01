#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    538) Convert BST to Greater Tree
    ================================

    ============
    Description:
    ============

    Given the root of a Binary Search Tree (BST), convert it to a Greater Tree
    such that every key of the original BST is changed to the original key plus
    the sum of all keys greater than the original key in BST.

    As a reminder, a binary search tree is a tree that satisfies these
    constraints:

        The left subtree of a node contains only nodes with keys less than the
        node's key.  The right subtree of a node contains only nodes with keys
        greater than the node's key.  Both the left and right subtrees must
        also be binary search trees.

    =====
    Note: This question is the same as 1038:
          https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
    =====

    ===============================================
    FUNCTION: TreeNode* convertBST(TreeNode* root);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        _______________________4(30)_________________
        ___________1(36)_________________6(21)_______
        _____0(36)_____2(35)_________5(26)_____7(15)_
        ____________________3(33)_________________8(8)

    Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]



    --- Example 2 ---
    Input: root = [0,null,1]
    Output: [1,null,1]



    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^4].
    -10^4 <= Node.val <= 10^4
    All the values in the tree are unique.
    root is guaranteed to be a valid binary search tree.

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

/* Time  Beats:  6.11% */
/* Space Beats: 91.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* convertBST(TreeNode* root)
    {
        int curr_sum = 0;
        reverse_tree(root, curr_sum);

        return root;
    }

private:
    void reverse_tree(TreeNode* root,int &curr_sum)
    {
        if(!root)
            return;

        reverse_tree(root->right, curr_sum);

        curr_sum += root->val;
        root->val = curr_sum;

        reverse_tree(root->left, curr_sum);
    }
};
