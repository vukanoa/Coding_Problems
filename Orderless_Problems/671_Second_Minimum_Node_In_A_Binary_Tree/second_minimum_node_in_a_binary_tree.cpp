/*
    ============
    === EASY ===
    ============

    =========================================
    671) Second Minimum Node in a Binary Tree
    =========================================

    ============
    Description:
    ============

    Given a non-empty special binary tree consisting of nodes with the
    non-negative value, where each node in this tree has exactly two or zero
    sub-node. If the node has two sub-nodes, then this node's value is the
    smaller value among its two sub-nodes. More formally, the property
    root.val = min(root.left.val, root.right.val) always holds.

    Given such a binary tree, you need to output the second minimum value in
    the set made of all the nodes' value in the whole tree.

    If no such second minimum value exists, output -1 instead.

    =====================================================
    FUNCTION: int findSecondMinimumValue(TreeNode* root);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [2,2,5,null,null,5,7]
    Output: 5
    Explanation: The smallest value is 2, the second smallest value is 5.

    --- Example 2 ---
    Input: root = [2,2,2]
    Output: -1
    Explanation: The smallest value is 2, but there isn't any second smallest value.


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 25].
    1 <= Node.val <= 2^31 - 1
    root.val == min(root.left.val, root.right.val) for each internal node of the tree.

*/

#include <climits>
#include <unordered_set>
using namespace std;

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

#include <climits>
#include <unordered_set>
#include <vector>
#include <algorithm>
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

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  49.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root)
    {
        unordered_set<int> unique_values;
        dfs(root, unique_values);

        if (unique_values.size() < 2)
            return -1;

        vector<int> sorted_values(unique_values.begin(), unique_values.end());
        sort(sorted_values.begin(), sorted_values.end());

        return sorted_values[1];
    }

private:
    void dfs(TreeNode* node, unordered_set<int>& uset)
    {
        if (node == nullptr)
            return;

        uset.insert(node->val);

        dfs(node->left, uset);
        dfs(node->right, uset);
    }
};
