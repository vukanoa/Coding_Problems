#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================================
    106) Construct Binary Tree From Inorder and Postorder Traversal
    ===============================================================

    ============
    Description:
    ============

    Given two integer arrays inorder and postorder where inorder is the inorder
    traversal of a binary tree and postorder is the postorder traversal of the
    same tree, construct and return the binary tree.

    ============================================================================
    FUNCTION: TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                                    3
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             9            20
                                          / \
                                         /   \
                                        /     \
                                       15      7

    Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
    Output: [3,9,20,null,null,15,7]

    --- Example 2 ---
    Input: inorder = [-1], postorder = [-1]
    Output: [-1]


    *** Constraints ***
    1 <= inorder.length <= 3000
    postorder.length == inorder.length
    -3000 <= inorder[i], postorder[i] <= 3000
    inorder and postorder consist of unique values.
    Each value of postorder also appears in inorder.
    inorder is guaranteed to be the inorder traversal of the tree.
    postorder is guaranteed to be the postorder traversal of the tree.

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

    The main part of this problem is to realize that we're going to use the 2nd
    vector, i.e. "postorder" only to retrieve the current root at every level
    of recursion.

    Once you realize that, the remaining part is only how to separate left and
    right subtree from "inorder" vector.

    Try to simulate this Example with the code down below. Once you go through
    the code once, it will be crystal clear, I promise.

    Input: inorder = [1,9,2,3,15,20,7], postorder = [1,2,9,15,7,20,3]
                      0 1 2 3 4  5  6                0 1 2 3  4 5  6


                                    3
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             9            20
                            / \           / \
                           /   \         /   \
                          /     \       /     \
                         1       2     15      7


*/

/* Time  Beats: 76.32% */
/* Space Beats: 98.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder)
    {
        const int n = inorder.size();

        TreeNode* root = new TreeNode(postorder.back());
        postorder.pop_back();

        int i;
        for (i = 0; i < n; i++)
        {
            if (inorder[i] == root->val)
                break;
        }

        root->right = construct(inorder, postorder, i+1, n-1, 0, n-2);
        root->left  = construct(inorder, postorder, 0  , i-1, 0, n-2);

        return root;
    }

private:
    TreeNode* construct(std::vector<int>& inorder,
                       std::vector<int>& postorder,
                       int beg_inorder,
                       int end_inorder,
                       int beg_postorder,
                       int end_postorder)
    {
        if (beg_inorder > end_inorder)
            return nullptr;

        TreeNode* root = new TreeNode(postorder.back());
        postorder.pop_back();

        int i;
        for (i = beg_inorder; i <= end_inorder; i++)
        {
            if (inorder[i] == root->val)
                break;
        }

        root->right = construct(inorder, postorder,      i+1   , end_inorder, 0, end_postorder-1);
        root->left  = construct(inorder, postorder, beg_inorder,     i-1    , 0, end_postorder-1);

        return root;
    }
};
