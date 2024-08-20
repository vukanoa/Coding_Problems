#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    872) Leaf-Similar Trees
    ===========================

    ============
    Description:
    ============

    Consider all the leaves of a binary tree, from left to right order, the
    values of those leaves form a leaf value sequence.

                                    3
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       5                         1
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                6             2           9             8
                             / \
                            /   \
                           /     \
                          7       4

    For example, in the given tree above, the leaf value sequence is

        (6, 7, 4, 9, 8).

    Two binary trees are considered leaf-similar if their leaf value sequence
    is the same.

    Return true if and only if the two given trees with head nodes root1 and
    root2 are leaf-similar.


    =============================================================
    FUNCTION: bool leafSimilar(TreeNode* root1, TreeNode* root2);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root1 = [3,5,1,6,2,9,8,null,null,7,4],
           root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
    Output: true


    --- Example 2 ---
    Input: root1 = [1,2,3], root2 = [1,3,2]
    Output: false


    *** Constraints ***
    The number of nodes in each tree will be in the range [1, 200].
    Both of the given trees will have values in the range [0, 200].

*/

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

/*
    ------------
    --- IDEA ---
    ------------

    Foundational Binary Tree problem.

*/

/* Time  Beats: 100,00% */
/* Space Beats:  17.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2)
    {
        vector<int> leaf_seq_1;
        vector<int> leaf_seq_2;

        dfs(root1, leaf_seq_1);
        dfs(root2, leaf_seq_2);

        return leaf_seq_1 == leaf_seq_2;
    }

private:
    void dfs(TreeNode* root, vector<int>& leaf_seq)
    {
        if ( ! root)
            return;

        if ( !root->left && !root->right )
            leaf_seq.push_back(root->val);
        else
        {
            dfs(root->left,  leaf_seq);
            dfs(root->right, leaf_seq);
        }
    }
};
