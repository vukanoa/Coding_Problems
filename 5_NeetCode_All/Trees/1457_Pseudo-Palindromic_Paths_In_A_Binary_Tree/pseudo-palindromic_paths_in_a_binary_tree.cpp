#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    1457) Pseudo-Palindromic Paths in a Binary-Tree
    ===============================================

    ============
    Description:
    ============

    Given a binary tree where node values are digits from 1 to 9. A path in the
    binary tree is said to be pseudo-palindromic if at least one permutation of
    the node values in the path is a palindrome.

    Return the number of pseudo-palindromic paths going from the root node to
    leaf nodes.

    ======================================================
    FUNCTION: int pseudoPalindromicPaths (TreeNode* root);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [2,3,1,3,1,null,1]
    Output: 2
    Explanation: The figure above represents the given binary tree. There are
                 three paths going from the root node to leaf nodes: the red
                 path [2,3,3], the green path [2,1,1], and the path [2,3,1].
                 Among these paths only red path and green path are
                 pseudo-palindromic paths since the red path [2,3,3] can be
                 rearranged in [3,2,3] (palindrome) and the green path [2,1,1]
                 can be rearranged in [1,2,1] (palindrome).


    --- Example 2 ---
    Input: root = [2,1,1,1,3,null,null,null,null,null,1]
    Output: 1
    Explanation: The figure above represents the given binary tree. There are
                 three paths going from the root node to leaf nodes: the green
                 path [2,1,1], the path [2,1,3,1], and the path [2,1]. Among
                 these paths only the green path is pseudo-palindromic since
                 [2,1,1] can be rearranged in [1,2,1] (palindrome).


    --- Example 3 ---
    Input: root = [9]
    Output: 1



    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^5].
    1 <= Node.val <= 9

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

/* Time  Beats: 83.53% */
/* Space Beats: 29.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int pseudoPalindromicPaths (TreeNode* root)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        unordered_map<int, int> umap;
        int count = 0;
        int odd_freqs = 0;

        dfs(root, umap, count, 0, odd_freqs);

        return count;
    }

private:
    void dfs(TreeNode* root, unordered_map<int, int>& umap, int& count, int level, int& odd_freqs)
    {
        if ( ! root)
            return;

        umap[root->val]++; // Push
        if (umap[root->val] & 1)
            odd_freqs++;
        else
            odd_freqs--;

        if ( !root->left && !root->right )
        {
            if (level & 1) // If it's an Odd level, that means there are Even number of nodes from Leaf to root
            {
                /* If there are EVEN number of nodes that means we can have up to 1 Odd frequency of some node */
                if (odd_freqs <= 1)
                    count++;
            }
            else // Even level with Odd number of nodes
            {
                /* If there are ODD number of nodes that means we can MUST have EXACTLY 1 Odd Frequency of some node */
                if (odd_freqs == 1)
                    count++;
            }
        }

        dfs(root->left,  umap, count, level+1, odd_freqs);
        dfs(root->right, umap, count, level+1, odd_freqs);

        umap[root->val]--; // Pop
        if (umap[root->val] & 1)
            odd_freqs++;
        else
            odd_freqs--;
    }
};
