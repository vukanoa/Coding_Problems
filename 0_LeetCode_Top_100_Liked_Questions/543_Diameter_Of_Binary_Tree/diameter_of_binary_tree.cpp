/*
    ============
    === EASY ===
    ============

    ============================
    543) Diameter of Binary Tree
    ============================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return the length of the diameter of the
    tree.

    The diameter of a binary tree is the length of the longest path between any
    two nodes in a tree. This path may or may not pass through the "root".

    The length of a path between two nodes is represented by the number of
    edges between them.

    ===================================================
    FUNCTION: int diameterOfBinaryTree(TreeNode* root);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [1, 2, 3, 4, 5]
    Output: 3
    Explanation: 3 is the length of the path [4, 2, 1, 3] or [5, 2, 1, 3]

    --- Example 2 ---
    Input:  root = [1, 2]
    Output: 1

    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4]
    -100 <= Node.val <= 100

*/

#include <algorithm>
using namespace std;



// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    First, you MUST solve LeetCode 104. "Maximum Depth of a Binary Tree".

    After that, it's trivial.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  19.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root)
    {
        int result = 0;
        depth(root, result);

        return result;
    }

private:
    int depth(TreeNode* root, int& result)
    {
        if ( ! root)
            return 0;

        int left_depth  = depth(root->left, result);
        int right_depth = depth(root->right, result);

        result = max(result, left_depth + right_depth);

        return 1 + max(left_depth, right_depth);
    }
};
