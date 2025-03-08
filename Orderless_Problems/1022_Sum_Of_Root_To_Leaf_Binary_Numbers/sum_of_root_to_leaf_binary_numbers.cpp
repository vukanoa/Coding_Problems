/*
    ============
    === EASY ===
    ============

    ========================================
    1022) Sum of Root To Leaf Binary Numbers
    ========================================

    ============
    Description:
    ============

    You are given the root of a binary tree where each node has a value 0 or 1.
    Each root-to-leaf path represents a binary number starting with the most significant bit.

        For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could
        represent 01101 in binary, which is 13.

    For all leaves in the tree, consider the numbers represented by the path
    from the root to that leaf. Return the sum of these numbers.

    The test cases are generated so that the answer fits in a 32-bits integer.

    ============================================
    FUNCTION: int sumRootToLeaf(TreeNode* root);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,0,1,0,1,0,1]
    Output: 22
    Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

    --- Example 2 ---
    Input: root = [0]
    Output: 0


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 1000].
    Node.val is 0 or 1.

*/

#include <string>
using namespace std;

/**
 * Definition for a binary tree node.
 */
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

    Basic DFS and a bit of String Manipulation.
    Cool tricks to know in C++.

*/

/* Time  Beats: 17.78% */
/* Space Beats: 15.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int sumRootToLeaf(TreeNode* root)
    {
        int sum = 0;
        dfs(root, "", sum);

        return sum;
    }

private:
    void dfs(TreeNode* root, string bin_str, int& sum)
    {
        if ( ! root)
            return;

        bin_str += to_string(root->val);

        if ( ! root->left && ! root->right) // Leaf Node
        {
            int idx = bin_str.find('1');
            string bin_str_without_leading_zeroes = idx != string::npos ? bin_str.substr(idx) : "";

            int integer = bin_str_without_leading_zeroes.empty() ? 0 : stoi(bin_str_without_leading_zeroes, nullptr, 2);

            sum += integer;
        }
        else
        {
            dfs(root->left,  bin_str, sum);
            dfs(root->right, bin_str, sum);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is much more concise and straightforward. However, it is useful to
    see the above "String manipulation". That one is very handy.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Concise {
public:
    int sumRootToLeaf(TreeNode* root, int val = 0)
    {
        if ( ! root)
            return 0;

        val = (val * 2 + root->val);

        if ( ! root->left && ! root->right)
            return val;

        return sumRootToLeaf(root->left, val) + sumRootToLeaf(root->right, val);
    }
};
