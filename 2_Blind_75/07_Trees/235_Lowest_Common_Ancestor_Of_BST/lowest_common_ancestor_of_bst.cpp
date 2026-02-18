/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    235) Lower Common Ancestor of BST
    =================================

    ============
    Description:
    ============

    Given a binary search tree (BST), find the lowest common ancestor (LCA)
    node of two given nodes in the BST.

    According to the definition of LCA on Wikipedia: “The lowest common
    ancestor is defined between two nodes p and q as the lowest node in T that
    has both p and q as descendants (where we allow a node to be a descendant
    of itself).”

    ===================================================================================
    FUNCTION: TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    Output: 6
    Explanation: The LCA of nodes 2 and 8 is 6.


    --- Example 2 ---
    Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    Output: 2
    Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a
                 descendant of itself according to the LCA definition.


    --- Example 3 ---
    Input: root = [2,1], p = 2, q = 1
    Output: 2


    *** Constraints ***
    The number of nodes in the tree is in the range [2, 105].
    -109 <= Node.val <= 109
    All Node.val are unique.
    p != q
    p and q will exist in the BST.

*/

#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.59% */
/* Space Beats: 59.75% */

/* Time  Complexity: O(H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(1) */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        TreeNode* curr = root;

        while (curr)
        {
            /* Using the property of the BST */
            if (p->val < curr->val && q->val < curr->val)
            {
                curr = curr->left;
            }
            else if (p->val > curr->val && q->val > curr->val)
            {
                curr = curr->right;
            }
            else
            {
                return curr;
            }
        }

        return nullptr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.39% */
/* Space Beats: 72.79% */

/* Time  Complexity: O(H) */ // Where 'H' is the Height of the Tree
/* Space Complexity: O(H) */
class Solution_2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == p || root == q)
            return root;

        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);

        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though implemented in a slightly different way. Or rather,
    implemented in a slightly different order.

    This one is more explicit, however it does seem to be less elegant and/or
    more messy.

    But it's clear and explicit that if p is less than root and q is greater
    than root or vice versa, that in that case we must return "root".

*/




/*
    ------------
    --- IDEA ---
    ------------

    The most straightforwards and most concise way.

*/

/* Time  Beats: 79.08% */
/* Space Beats:  6.01% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(n)    */
class Solution_4_Concise {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || root == p || root == q)
            return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        return left && right ? root : (left ? left : right);
    }
};
