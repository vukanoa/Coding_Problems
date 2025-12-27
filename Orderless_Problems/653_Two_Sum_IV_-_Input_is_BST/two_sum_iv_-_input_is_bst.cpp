/*
    ============
    === EASY ===
    ============

    ================================
    653) Two Sum IV - Input is a BST
    ================================

    ============
    Description:
    ============

    Given the root of a binary search tree and an integer k, return true if
    there exist two elements in the BST such that their sum is equal to k, or
    false otherwise.

    =================================================
    FUNCTION: bool findTarget(TreeNode* root, int k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [5,3,6,2,4,null,7], k = 9
    Output: true

    --- Example 2 ---
    Input: root = [5,3,6,2,4,null,7], k = 28
    Output: false


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    -10^4 <= Node.val <= 10^4
    root is guaranteed to be a valid binary search tree.
    -10^5 <= k <= 10^5

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

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Recursive {
public:
    TreeNode* root = nullptr;

    bool findTarget(TreeNode* node, int k)
    {
        if ( ! root)
            root = node;

        if ( ! node)
            return false;

        if (dfs_search(node, k - node->val))
            return true;

        return findTarget(node->left, k) || findTarget(node->right, k);
    }

private:
    bool dfs_search(TreeNode* node, int target)
    {
        TreeNode* current = root;

        while (current)
        {
            if (target == current->val)
                return current != node;

            if (target > current->val)
            {
                current = current->right;
            }
            else // if (target < current->val)
            {
                current = current->left;
            }
        }

        return false;
    }
};
