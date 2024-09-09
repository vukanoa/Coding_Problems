#include <iostream>

/*
    ============
    === EASY ===
    ============

    ============================
    572) Subtree of Another Tree
    ============================

    ============
    Description:
    ============

    Given the roots of two binary trees root and subRoot, return true if there
    is a subtree of root with the same structure and node values of subRoot and
    false otherwise.

    A subtree of a binary tree tree is a tree that consists of a node in tree
    and all of this node's descendants. The tree tree could also be considered
    as a subtree of itself.

    ============================================================
    FUNCTION: boll isSubtree(TreeNode* root, TreeNode* subRoot);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,4,5,1,2], subRoot = [4,1,2]
    Output: true

    --- Example 2 ---
    Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
    Output: false


    *** Constraints ***
    The number of nodes in the root tree is in the range [1, 2000].
    The number of nodes in the subRoot tree is in the range [1, 1000].
    -10^4 <= root.val <= 10^4
    -10^4 <= subRoot.val <= 10^4

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

    First, you MUST do LeetCode 100 "Same Tree".

    If you don't genuinely understand "SameTree", make sure to understand that
    one first and then come back. That is an absolutely necessary foundation
    for solving this problem.


    Let's read the problem CAREFULLY:
        "Given the roots of two binary trees root and subRoot, return true if
         there is a subtree of root with the same structure and node values of
         subRoot and false otherwise."

    There lays a Solution. We literally have to do what we are told.
    At EACH node in the original Tree we have to check if by starting at that
    node and starting from the root of the subRoot Tree, they are the same.

    If they are the same:
        we IMMEDIATELY return "true".

    If the are NOT the same:
        we try by starting with:
            1. current's left node or
            2. current's right node.

        If any of those two get to return "true", we'll propagate "true" all
        the way up independently of other return values we get or already got
        along the way to the top in this recursion.


    Now, after you've read this, try reading the code. It is LITERALLY what
    it says up here.

    (See how "SameTree" is absolutely necessary to solve this problem?)

*/

/* Time  Beats: 67.05% */
/* Space Beats: 99.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        if (!root && !subRoot) return true;
        if (!root || !subRoot) return false;

        if (sameTree(root, subRoot))
            return true;

        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

private:
    bool sameTree(TreeNode* p, TreeNode* q)
    {
        if (!p && !q) return true;
        if (!p || !q) return false;

        if (p->val != q->val)
            return false;

        return sameTree(p->left, q->left) && sameTree(p->right, q->right);
    }
};
