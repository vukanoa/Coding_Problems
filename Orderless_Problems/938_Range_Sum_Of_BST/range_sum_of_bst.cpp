#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    938) Range Sum of BST
    ===========================

    ============
    Description:
    ============

    Given the root node of a binary search tree and two integers low and high,
    return the sum of values of all nodes with a value in the inclusive range
    [low, high].

    =============================================================
    FUNCTION: int rangeSumBST(TreeNode* root, int low, int high);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
    Output: 32
    Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.

    --- Example 2 ---
    Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
    Output: 23
    Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 2 * 10^4].
    1 <= Node.val <= 10^5
    1 <= low <= high <= 10^5
    All Node.val are unique.

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

    Self-explanatory.

*/

/* Time  Beats: 60.57% */
/* Space Beats: 21.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high)
    {
        if ( ! root)
            return 0;

        int curr = 0;
        if (root->val >= low && root->val <= high)
            curr += root->val;

        return rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high) + curr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 83.02% */
/* Space Beats: 59.18% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int rangeSumBST(TreeNode* root, int low, int high)
    {
        if ( ! root)
            return 0;

        if (root->val < low)
            return rangeSumBST(root->right, low, high);

        if (root->val > high)
            return rangeSumBST(root->left, low, high);

        return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }
};
