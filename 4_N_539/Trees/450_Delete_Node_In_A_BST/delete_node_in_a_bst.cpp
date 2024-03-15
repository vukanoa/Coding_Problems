#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    450) Delete Node In a BST
    ===========================

    ============
    Description:
    ============

    Given a root node reference of a BST and a key, delete the node with the
    given key in the BST. Return the root node reference (possibly updated) of
    the BST.

    Basically, the deletion can be divided into two stages:

        1. Search for a node to remove.
        2. If the node is found, delete the node.


    Follow up: Could you solve it with time complexity O(height of tree)?

    ========================================================
    FUNCTION: TreeNode* deleteNode(TreeNode* root, int key);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,3,6,2,4,null,7], key = 3
    Output: [5,4,6,2,null,null,7]
    Explanation: Given key to delete is 3. So we find the node with value 3 and
    delete it.  One valid answer is [5,4,6,2,null,null,7], shown in the above
    BST.  Please notice that another valid answer is [5,2,6,null,4,null,7] and
    it's also accepted.


    --- Example 2 ---
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]
    Explanation: The tree does not contain a node with value = 0.


    --- Example 3 ---
    Input: root = [], key = 0
    Output: []


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^4].
    -10^5 <= Node.val <= 10^5
    Each node has a unique value.
    root is a valid binary search tree.
    -10^5 <= key <= 10^5

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

/* Time  Beats: 93.89% */
/* Space Beats: 61.18% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key)
    {
        if (!root)
            return nullptr;

        if (key > root->val)
            root->right = deleteNode(root->right, key);
        else if (key < root->val)
            root->left  = deleteNode(root->left,  key);
        else
        {
            if (!root->left)
                return root->right;
            else if (!root->right)
                return root->left;

            /* Find min from the right Subtree */
            TreeNode* curr = root->right;
            while (curr->left)
                curr = curr->left;

            root->val = curr->val;
            root->right = deleteNode(root->right, root->val);
        }

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Solution is much more lengthy in terms of code, however I strongly
    believe it is much easier to understand, grasp and it's even easier to code
    it up.

    Even if the code is genuinely much longer.

    This is something you could, genuinely, come up with in an 30-minutes
    interview, whereas the above approach is something you almost must know
    beforehand.

*/

/* Time  Beats: 80.98% */
/* Space Beats: 51.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key)
    {
        if (!root)
            return nullptr;
        else if (root->val == key)
            return merge(root->left, root->right);

        find(root, key);

        return root;
    }

private:
    void find(TreeNode* root, int key)
    {
        if (!root)
            return;

        if (root->left && root->left->val == key)
        {
            root->left = merge(root->left->left, root->left->right);
        }
        else if (root->right && root->right->val == key)
        {
            root->right = merge(root->right->left, root->right->right);
        }
        else
        {
            if (key < root->val)
                find(root->left, key);
            else
                find(root->right, key);
        }
    }

    TreeNode* merge(TreeNode* left, TreeNode* right)
    {
        if (!left && !right)
            return nullptr;
        else if (!left && right)
            return right;
        else if (left && !right)
            return left;

        TreeNode* rights_leftmost = leftmost(right);
        rights_leftmost->left = left;

        return right;
    }

    TreeNode* leftmost(TreeNode* root)
    {
        if (!root->left)
            return root;

        return leftmost(root->left);
    }
};
