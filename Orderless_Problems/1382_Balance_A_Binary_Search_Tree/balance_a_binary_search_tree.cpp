#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    1382) Balance a Binar Search Tree
    =================================

    ============
    Description:
    ============

    Given the root of a binary search tree, return a balanced binary search
    tree with the same node values. If there is more than one answer, return
    any of them.

    A binary search tree is balanced if the depth of the two subtrees of every
    node never differs by more than 1.

    ===============================================
    FUNCTION: TreeNode* balanceBST(TreeNode* root); 
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,2,null,3,null,4,null,null]
    Output: [2,1,3,null,null,null,4]
    Explanation: This is not the only correct answer, [3,1,4,null,2] is also
                 correct.


    --- Example 2 ---
    Input: root = [2,1,3]
    Output: [2,1,3]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    1 <= Node.val <= 10^5

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

/* Time  Beats: 91.52% */
/* Space Beats: 85.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<TreeNode*> sortedArr;

    TreeNode* balanceBST(TreeNode* root)
    {
        inorderTraverse(root);
        return sortedArrayToBST(0, sortedArr.size() - 1);
    }

private:
    void inorderTraverse(TreeNode* root)
    {
        if (root == NULL)
            return;

        inorderTraverse(root->left);
        sortedArr.push_back(root);
        inorderTraverse(root->right);
    }

    TreeNode* sortedArrayToBST(int start, int end)
    {
        if (start > end)
            return NULL;

        int mid = (start + end) / 2;

        TreeNode* root = sortedArr[mid];
        root->left = sortedArrayToBST(start, mid - 1);
        root->right = sortedArrayToBST(mid + 1, end);

        return root;
    }
};
