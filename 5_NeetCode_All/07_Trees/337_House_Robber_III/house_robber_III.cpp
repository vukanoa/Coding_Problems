/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    337) House Robber III
    ===========================

    ============
    Description:
    ============

    The thief has found himself a new place for his thievery again. There is
    only one entrance to this area, called root.

    Besides the root, each house has one and only one parent house. After a
    tour, the smart thief realized that all houses in this place form a binary
    tree. It will automatically contact the police if two directly-linked
    houses were broken into on the same night.

    Given the root of the binary tree, return the maximum amount of money the
    thief can rob without alerting the police.

    ==================================
    FUNCTION: int rob(TreeNode* root);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,2,3,null,3,null,1]
    Output: 7
    Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

    --- Example 2 ---
    Input: root = [3,4,5,1,3,null,1]
    Output: 9
    Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
    0 <= Node.val <= 10^4

*/

#include <algorithm>
#include <utility>
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

    The only important part here to "notice"(but they tell you this) is that
    if you take the root node of certain subtree, then you are NOT allowed to
    take its immediate children into account.

    However, if you decide not to take the root node of the certain subtree,
    then you are indeed allowed to take its immediate children into account.

    There is only one problem, or "edge case" that you need to be aware of.

    Look at this example:

        ___________4___________
        _____6_________________
        __3____________________
        5______________________

    If you only consider "root->val + left_without_root + right_without_root"
    then you'd get a result of 9, which isn't the maximum.

    The maximum is 6 + 5 = 11;

    The main thing is to realize that for "with_root" value, it may be better
    to take:
        left_with_root + right_with_root

            instead of

        left_without_root + right_without_root + root->val

    It's the same thing as with the classical "house robber" problem.

        nums = [2,1,2,3,5,4,3,1]
                0 1 2 3 4 5 6 7

    int prev = 0;
    int curr = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        int tmp = std::max(curr, prev + nums[i]);

        prev = curr;
        curr = tmp;
    }

    return curr;

    At each position you can either:
        1. Take the current house plus max amount of money if you include to
           rob the 2nd house to the left of the current one.

            or

        2. Take the max amount of money if you include to rob the 1st house to
           the left of the current one.



    That's why we have this line in our code:
        return {without_root, max(without_root, with_root)};

    That's the equivalent of:
        int tmp = std::max(curr, prev + nums[i]);

    in the classical House Robber problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.32% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int rob(TreeNode* root)
    {
        auto [without_root, with_root] = dfs(root);

        return max(without_root, with_root);
    }

private:
    pair<int, int> dfs(TreeNode* root)
    {
        if ( ! root)
            return {0, 0};

        auto [left_max,   left_max_with_neighbor] = dfs(root->left);
        auto [right_max, right_max_with_neighbor] = dfs(root->right);

        int without_root = left_max_with_neighbor + right_max_with_neighbor;
        int with_root    = left_max               + right_max                + root->val;

        return {without_root, max(without_root, with_root)};
    }
};
