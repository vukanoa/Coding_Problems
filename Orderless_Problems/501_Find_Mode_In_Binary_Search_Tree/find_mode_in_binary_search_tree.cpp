#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ====================================
    501) Find Mode in Binary Search Tree
    ====================================

    ============
    Description:
    ============

    Given the root of a binary search tree (BST) with duplicates, return all
    the mode(s) (i.e., the most frequently occurred element) in it.

    If the tree has more than one mode, return them in any order.

    Assume a BST is defined as follows:

        + The left subtree of a node contains only nodes with keys less than or
          equal to the node's key.

        + The right subtree of a node contains only nodes with keys greater
          than or equal to the node's key.

        + Both the left and right subtrees must also be binary search trees.

    ===============================================
    FUNCTION: vector<int> findMode(TreeNode* root);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,2,2]
    Output: [2]

    --- Example 2 ---
    Input: root = [0]
    Output: [0]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    -10^5 <= Node.val <= 10^5

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

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.38% */
/* Space Beats: 68.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> result;
    int prev = 0;
    int counter = 0;
    int maxi = 0;

    void inorder(TreeNode* root)
    {
        if ( ! root) return;

        inorder(root->left);

        if (prev == root->val)
            counter++;
        else
            counter = 1;

        if(counter == maxi)
           result.push_back(root->val);

        else if (counter > maxi)
        {
            maxi = max(maxi, counter);
            result = {root->val};
        }

        prev = root->val;
        inorder(root->right);
    }

    vector<int> findMode(TreeNode* root)
    {
        inorder(root);

        return result;
    }
};
