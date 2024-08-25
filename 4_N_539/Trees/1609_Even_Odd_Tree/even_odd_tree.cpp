#include <iostream>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1609) Even Odd Tree
    ===========================

    ============
    Description:
    ============

    A binary tree is named Even-Odd if it meets the following conditions:

        + The root of the binary tree is at level index 0, its children are at
          level index 1, their children are at level index 2, etc.

        + For every even-indexed level, all nodes at the level have odd integer
          values in strictly increasing order (from left to right).

        + For every odd-indexed level, all nodes at the level have even integer
          values in strictly decreasing order (from left to right).

    Given the root of a binary tree, return true if the binary tree is
    Even-Odd, otherwise return false.

    =============================================
    FUNCTION: bool isEvenOddTree(TreeNode* root);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

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

/* Time  Beats: 61.25% */
/* Space Beats: 72.39% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isEvenOddTree(TreeNode* root)
    {
        if (!root->left && !root->right)
            return root->val & 1; // If it's an even number at the root

        queue<TreeNode*> queue;
        queue.push(root);

        int level = -1;
        while ( ! queue.empty())
        {
            int size = queue.size();
            level++;

            unsigned int prev = (level & 1) ? INT_MAX : 0;

            for (int i = 0; i < size; i++)
            {
                TreeNode* node = queue.front();
                queue.pop();

                if (level & 1) // Odd level (Must be Even integers, STRICTLY DECREASING order from left-to-right)
                {
                    if (node->val % 2 == 1 || prev <= node->val)
                        return false;

                }
                else // Even level (Must be in Odd integers, STRICTLY INCREASING order from left-to-right)
                {
                    if (node->val % 2 == 0 || prev >= node->val)
                        return false;
                }

                prev = node->val;

                if (node->left)
                    queue.push(node->left);

                if (node->right)
                    queue.push(node->right);
            }
        }

        return true;
    }
};
