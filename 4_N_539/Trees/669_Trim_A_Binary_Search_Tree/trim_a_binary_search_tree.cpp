#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    669) Trim a Binary Search Tree
    ==============================

    ============
    Description:
    ============

    Given the root of a binary search tree and the lowest and highest
    boundaries as low and high, trim the tree so that all its elements lies in
    [low, high]. Trimming the tree should not change the relative structure of
    the elements that will remain in the tree (i.e., any node's descendant
    should remain a descendant). It can be proven that there is a unique
    answer.

    Return the root of the trimmed binary search tree. Note that the root may
    change depending on the given bounds.

    ===============================================================
    FUNCTION: TreeNode* trimBST(TreeNode* root, int low, int high);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
            _____          _____
            __1__   ===>   __1__
            0___2          ____2

    Input: root = [1,0,2], low = 1, high = 2
    Output: [1,null,2]




    --- Example 2 ---
            _______________________            _______________________
            ___________3___________            ___________3___________
            _____0___________4_____    ===>    _____2_________________
            ________2______________            __1____________________
            ______1________________            _______________________


    Input: root = [3,0,4,null,2,null,null,1], low = 1, high = 3
    Output: [3,2,null,1]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    0 <= Node.val <= 10^4
    The value of each node in the tree is unique.
    root is guaranteed to be a valid binary search tree.
    0 <= low <= high <= 10^4

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

    Very intuitive BST Problem.
    Forget how to code for a second and think how you would solve it, using
    only your own words.

    Then just code that. It's really that simple.

*/

/* Time  Beats: 94.43% */
/* Space Beats: 93.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high)
    {
        if (!root)
            return nullptr;

        root->left  = trimBST(root->left,  low, high);
        root->right = trimBST(root->right, low, high);

        if (root->val < low)
        {
            while (root && root->val < low)
                root = root->right;
        }
        else if (root->val > high)
        {
            while (root && root->val > high)
                root = root->left;
        }

        return root;
    }
};
