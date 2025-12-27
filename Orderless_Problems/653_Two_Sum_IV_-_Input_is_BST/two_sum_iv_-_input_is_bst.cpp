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

/* Time  Beats: 100.00% */
/* Space Beats:  98.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Call stack
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




/* Time  Beats: 100.00% */
/* Space Beats:  99.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Iterative {
public:
    bool findTarget(TreeNode* root, int k)
    {
        if ( ! root)
            return false;

        TreeNode* start = root;
        TreeNode* end   = root;

        while (start->left)
            start = start->left;

        while (end->right)
            end = end->right;

        while (start != end)
        {
            int sum = start->val + end->val;

            if (sum == k)
                return true;

            if (sum > k)
            {
                end = find_predecessor(root, end);
            }
            else // if (sum < k)
            {
                start = find_successor(root, start);
            }
        }

        return false;
    }

private:
    TreeNode* find_predecessor(TreeNode* root, TreeNode* node)
    {
        TreeNode* predecessor = nullptr;
        TreeNode* curr = root;

        while (curr)
        {
            if (curr->val < node->val)
            {
                predecessor = curr;
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }

        return predecessor;
    }

    TreeNode* find_successor(TreeNode* root, TreeNode* node)
    {
        TreeNode* successor = nullptr;
        TreeNode* curr = root;

        while (curr)
        {
            if (curr->val > node->val)
            {
                successor = curr;
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }

        return successor;
    }
};
