/*
    ============
    === EASY ===
    ============

    =========================
    110) Balanced Binary Tree
    =========================

    ============
    Description:
    ============

    Given a binary tree, determine if it is height-balanced.

    (A height-balanced binary tree is a binary tree in which the depth of the
    two subtrees of every node never differs by more than one)

    ==========================================
    FUNCTION: bool isBalanced(TreeNode* root);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        ___________
        _____3_____
        __9____20__
        _____15___7

    Input: root = [3,9,20,null,null,15,7]
    Output: true



    --- Example 2 ---
        _______________________
        ___________1___________
        _____2___________2_____
        __3_____3______________
        4___4__________________

    Input: root = [1,2,2,3,3,null,null,4,4]
    Output: false


    --- Example 3 ---
    Input: root = []
    Output: true


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 5000].
    -10^4 <= Node.val <= 10^4

*/

#include <algorithm>
#include <cstdlib>
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

    First, you MUST do LeetCode 104. "Maximum Depth of a Binary Tree".
    After that, it's trivial.

    The only thing which is a "nice optimization", is this:

        if (!root || !balanced)
            return 0;

    If we ever find out that any node's left and right subtrees differ by more
    than 1, then we proclaim "balanced" to be false.

    If "balanced" is false, we don't care what we return, we just want to get
    out of the "depth" function as quickly as possible. This helps.

*/

/* Time  Beats: 93.27% */
/* Space Beats: 13.98% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isBalanced(TreeNode* root)
    {
        bool balanced = true;
        depth(root, balanced);

        return balanced;
    }

private:
    int depth(TreeNode* root, bool& balanced)
    {
        if ( ! root || ! balanced)
            return 0;

        int left  = depth(root->left, balanced);
        int right = depth(root->right, balanced);

        if (abs(left - right) > 1)
            balanced = false;

        return 1 + max(left, right);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another implementation.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    bool isBalanced(TreeNode* root)
    {
        auto [balanced, depth] = dfs(root);

        return balanced;
    }

    pair<bool, int> dfs(TreeNode* root)
    {
        if ( ! root)
            return {true, 0};

        auto [left_balanced,  left_depth]  = dfs(root->left);
        auto [right_balanced, right_depth] = dfs(root->right);

        if ( ! left_balanced)  return {false, -1};
        if ( ! right_balanced) return {false, -1};

        return {abs(left_depth - right_depth) <= 1, 1 + max(left_depth, right_depth)};
    }
};
