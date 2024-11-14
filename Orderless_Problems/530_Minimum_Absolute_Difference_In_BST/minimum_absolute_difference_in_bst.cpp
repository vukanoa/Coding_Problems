#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =======================================
    530) Minimum Absolute Difference in BST
    =======================================

    ============
    Description:
    ============

    Given the root of a Binary Search Tree (BST), return the minimum absolute
    difference between the values of any two different nodes in the tree.

    =====
    Note: This question is the same as 783:
          https://leetcode.com/problems/minimum-distance-between-bst-nodes/
    =====

    ===================================================
    FUNCTION: int getMinimumDifference(TreeNode* root);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [4,2,6,1,3]
    Output: 1

    --- Example 2 ---
    Input: root = [1,0,48,null,null,12,49]
    Output: 1


    *** Constraints ***
    The number of nodes in the tree is in the range [2, 10^4].
    0 <= Node.val <= 10^5

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

    Inorder traversal traverses the Tree in a Sorted-Way, meaning if you was
    to print all the values as you traverse them, they would be sorted in a
    non-decreasing order.

    Similarly, if you were to push each traverse element into a vector, as you
    traverse, at the end you would have a vector of elements sorted in a
    non-decreasing order.

    At the end, we start from index 1 and not 0 and we check the difference
    between current value and the previous value.

    We return the smallest difference.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int getMinimumDifference(TreeNode* root)
    {
        vector<int> vec;

        inorder(root, vec);

        int result = INT_MAX;
        for (int i = 1; i < vec.size(); i++)
            result = min(result, vec[i] - vec[i-1]);

        return result;
    }

private:
    void inorder(TreeNode* root, vector<int>& vec)
    {
        if ( ! root)
            return;

        inorder(root->left, vec);
        vec.push_back(root->val);
        inorder(root->right, vec);
    }
};
