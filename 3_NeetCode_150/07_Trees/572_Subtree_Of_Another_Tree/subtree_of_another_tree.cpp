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

    If you don't genuinely understand "Same Tree", make sure to understand that
    one first and then come back. That is an absolutely necessary foundational
    problem for solving THIS problem.


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
        the way up since we have a logical OR between the conditions.

    Now, after you've read this, try reading the code. It is LITERALLY what
    it says up here.

    (See how "SameTree" is absolutely necessary to solve this problem?)

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* Time  Complexity: O(M * N) */ // M = number of nodes in root
/* Space Complexity: O(M + N) */ // N = number of nodes in subRoot
class Solution {
public:
    // O(M * N)
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        if ( ! root && ! subRoot) return true;
        if ( ! root || ! subRoot) return false;

        if (isSameTree(root, subRoot)) // O(N)
            return true;

        // O(M * N)
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

private:
    // O(min(M, N))
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if ( ! p && ! q) return true;
        if ( ! p || ! q) return false;

        if (p->val != q->val)
            return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
