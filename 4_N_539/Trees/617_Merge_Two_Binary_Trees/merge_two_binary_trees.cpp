#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    617) Merge Two Binary Trees
    ===========================

    ============
    Description:
    ============

    You are given two binary trees root1 and root2.

    Imagine that when you put one of them to cover the other, some nodes of the
    two trees are overlapped while the others are not. You need to merge the
    two trees into a new binary tree. The merge rule is that if two nodes
    overlap, then sum node values up as the new value of the merged node.
    Otherwise, the NOT null node will be used as the node of the new tree.

    Return the merged tree.

    Note: The merging process must start from the root nodes of both trees.

    =================================================================
    FUNCTION: TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
    Output: [3,4,5,5,4,null,7]

    --- Example 2 ---
    Input: root1 = [1], root2 = [1,2]
    Output: [2,2]


    *** Constraints ***
    The number of nodes in both trees is in the range [0, 2000].
    -10^4 <= Node.val <= 10^4

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




/* Time  Beats: 75.62% */
/* Space Beats:  7.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
    {
        if (!root1 && !root2)
            return nullptr;

        TreeNode* root = new TreeNode();

        root->val += root1 ? root1->val : 0;
        root->val += root2 ? root2->val : 0;

        root->left  = mergeTrees(root1 ? root1->left  : nullptr, root2 ? root2->left  : nullptr);
        root->right = mergeTrees(root1 ? root1->right : nullptr, root2 ? root2->right : nullptr);

        return root;
    }
};





/* Time  Beats: 96.08% */
/* Space Beats: 54.94% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
    {
        if(!root1 || !root2)
            return root1 ? root1 : root2;

        root1->val += root2->val;

        root1->left  = mergeTrees(root1->left,  root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        return root1;
    }
};
