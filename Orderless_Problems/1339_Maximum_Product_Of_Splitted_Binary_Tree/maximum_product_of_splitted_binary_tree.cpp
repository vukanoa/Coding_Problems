/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    1339) Maximum Product of Splitted Binary Tree
    =============================================

    ============
    Description:
    ============

    Given the root of a binary tree, split the binary tree into two subtrees by
    removing one edge such that the product of the sums of the subtrees is
    maximized.

    Return the maximum product of the sums of the two subtrees. Since the
    answer may be too large, return it modulo 109 + 7.

    =====
    Note: that you need to maximize the answer before taking the mod and not
          after taking it. 
    =====

    =========================================
    FUNCTION: int maxProduct(TreeNode* root);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,4,5,6]
    Output: 110
    Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10.
                 Their product is 110 (11*10)

    --- Example 2 ---
    Input: root = [1,null,2,3,4,null,null,5,6]
    Output: 90
    Explanation: Remove the red edge and get 2 binary trees with sum 15 and
                 6.Their product is 90 (15*6)


    *** Constraints ***
    The number of nodes in the tree is in the range [2, 5 * 10^4].
    1 <= Node.val <= 10^4

*/

#include <algorithm>
using namespace std;

// * Definition for a binary tree node.
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

    Classic DFS with total_sum minus subtree_sum

*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxProduct(TreeNode* root)
    {
        const int MOD = 1e9 + 7;
        unsigned long long result = 0ULL;

        unsigned long long total_sum = 0ULL;
        sum(total_sum, root);
        dfs(total_sum, root, result);

        return result % MOD;
    }

private:
    void sum(unsigned long long& total_sum, TreeNode* root)
    {
        if ( ! root)
            return;

        total_sum += root->val;
        sum(total_sum, root->left);
        sum(total_sum, root->right);
    }

    int dfs(unsigned long long& total_sum, TreeNode* root, unsigned long long& result)
    {
        if ( ! root)
            return 0;

        int left_subtree_sum  = dfs(total_sum, root->left,  result);
        int right_subtree_sum = dfs(total_sum, root->right, result);

        if (left_subtree_sum > 0)
        {
            result = max(result, static_cast<unsigned long long>(left_subtree_sum * (total_sum - left_subtree_sum)));
        }
        
        if (right_subtree_sum > 0)
        {
            result = max(result, static_cast<unsigned long long>(right_subtree_sum * (total_sum - right_subtree_sum)));
        }

        return root->val + left_subtree_sum + right_subtree_sum;
    }
};
