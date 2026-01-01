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

#include <cstdlib>
#include <vector>
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

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
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
        if (!root || !balanced)
            return 0;

        int left  = depth(root->left, balanced);
        int right = depth(root->right, balanced);

        if (std::abs(left - right) > 1)
            balanced = false;

        return 1 + std::max(left, right);
    }
};



class Solution_2 {
public:
    bool isBalanced(TreeNode* root)
    {
        return dfs(root)[0];
    }

private:
    vector<int> dfs(TreeNode* root)
    {
        if ( ! root)
            return {1, 0};

        vector<int> left  = dfs(root->left);
        vector<int> right = dfs(root->right);

        int balanced = left[0] && right[0] && abs(left[1] - right[1]) <= 1;

        return {balanced, 1 + max(left[1], right[1])};
    }
};
