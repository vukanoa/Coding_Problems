#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1110) Delete Nodes and Return Forest
    ====================================

    ============
    Description:
    ============

    Given the root of a binary tree, each node in the tree has a distinct
    value.

    After deleting all nodes with a value in to_delete, we are left with a
    forest (a disjoint union of trees).

    Return the roots of the trees in the remaining forest. You may return the
    result in any order.

    =============================================================================
    FUNCTION: vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete);  
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
    Output: [[1,2,null,4],[6],[7]]

    --- Example 2 ---
    Input: root = [1,2,4,null,3], to_delete = [3]
    Output: [[1,2,4]]


    *** Constraints ***
    The number of nodes in the given tree is at most 1000.
    Each node has a distinct value between 1 and 1000.
    to_delete.length <= 1000
    to_delete contains distinct values between 1 and 1000.

*/

using namespace std;

/* Time  Beats: 45.72% */
/* Space Beats: 18.42% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete)
    {
        vector<TreeNode*> result;

        vector<bool> set(1000, false);
        for (const int& num : to_delete)
            set[num] = true;

        dfs(root, set, true, result);

        return result;
    }

private:
    void dfs(TreeNode* &root, vector<bool>& set, bool flag, vector<TreeNode*>& result)
    {
        if (root == nullptr)
            return;

        dfs(root->left,  set, set[root->val], result);
        dfs(root->right, set, set[root->val], result);

        if ( ! set[root->val] && flag)
            result.push_back(root);

        if (set[root->val])
            root = nullptr;
    }
};