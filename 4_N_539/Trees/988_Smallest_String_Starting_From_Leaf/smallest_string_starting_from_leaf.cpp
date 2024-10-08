#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    988) Smallest String Starting From Leaf
    =======================================

    ============
    Description:
    ============

    You are given the root of a binary tree where each node has a value in the
    range [0, 25] representing the letters 'a' to 'z'.

    Return the lexicographically smallest string that starts at a leaf of this
    tree and ends at the root.

    As a reminder, any shorter prefix of a string is lexicographically smaller.

        For example, "ab" is lexicographically smaller than "aba".

    A leaf of a node is a node that has no children.

    ==================================================
    FUNCTION: string smallestFromLeaf(TreeNode* root); 
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [0,1,2,3,4,3,4]
    Output: "dba"

    --- Example 2 ---
    Input: root = [25,1,3,1,3,0,2]
    Output: "adz"

    --- Example 3 ---
    Input: root = [2,2,1,null,1,0,null,0]
    Output: "abc"


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 8500].
    0 <= Node.val <= 25

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

    TODO

*/

/* Time  Beats: 75.78% */
/* Space Beats: 13.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string smallestFromLeaf(TreeNode* root)
    {
        string result(8501, 'z');

        dfs(root, "", result);

        return result;
    }

private:
    void dfs(TreeNode *root, string curr_str, string& result)
    {
        if ( ! root)
            return;

        char curr_chr = static_cast<char>(root->val+'a');

        if( !root->left && !root->right)
        {
            if ((curr_chr + curr_str) < result)
                result = curr_chr + curr_str;

            return;
        }

        dfs(root->left,  curr_chr + curr_str, result);
        dfs(root->right, curr_chr + curr_str, result);
    }
};
