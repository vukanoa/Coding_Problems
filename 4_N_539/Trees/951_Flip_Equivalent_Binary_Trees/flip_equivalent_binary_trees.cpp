#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    951) Flip Equivalent Binary Trees
    =================================

    ============
    Description:
    ============

    For a binary tree T, we can define a flip operation as follows: choose any
    node, and swap the left and right child subtrees.

    A binary tree X is flip equivalent to a binary tree Y if and only if we can
    make X equal to Y after some number of flip operations.

    Given the roots of two binary trees root1 and root2, return true if the two
    trees are flip equivalent or false otherwise.

    ===========================================================
    FUNCTION: bool flipEquiv(TreeNode* root1, TreeNode* root2);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root1 = [1,2,3,4,5,6,null,null,null,7,8],
           root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
    Output: true
    Explanation: We flipped at nodes with values 1, 3, and 5.


    --- Example 2 ---
    Input: root1 = [], root2 = []
    Output: true


    --- Example 3 ---
    Input: root1 = [], root2 = [1]
    Output: false


    *** Constraints ***
    The number of nodes in each tree is in the range [0, 100].
    Each tree will have unique node values in the range [0, 99].

*/

/* Time  Beats: 100.00% */
/* Space Beats:  20.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2)
    {
        if(!root1 && !root2)
            return true;
        if(!root1 || !root2 || root1->val != root2->val)
            return false;

        bool left_1, right_1, left_2, right_2;

        left_1  = flipEquiv(root1->left,  root2->left);
        right_1 = flipEquiv(root1->right, root2->right);
        left_2  = flipEquiv(root1->left,  root2->right);
        right_2 = flipEquiv(root1->right, root2->left);

        return ((left_1 && right_1) || (left_2 && right_2));
    }
};
