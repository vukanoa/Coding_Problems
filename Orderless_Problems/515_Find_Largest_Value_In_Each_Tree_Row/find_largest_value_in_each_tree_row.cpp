#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    515) Find Largest Value in Each Tree Row
    ========================================

    ============
    Description:
    ============

    Given the root of a binary tree, return an array of the largest value in
    each row of the tree (0-indexed).

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                                    1
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             3             2
                            / \             \
                           /   \             \
                          /     \             \
                         5       3             9

    Input: root = [1,3,2,5,3,null,9]
    Output: [1,3,9]




    --- Example 2 ---
                             1
                            / \
                           /   \
                          2     3

    Input: root = [1,2,3]
    Output: [1,3]




    *** Constraints ***
    The number of nodes in the tree will be in the range [0, 10^4].
    -2^31 <= Node.val <= 2^31 - 1

*/

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

    Classic BFS problem. Nothing special.

*/

/* Time  Beats: 77.21% */
/* Space Beats: 92.23% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> largestValues(TreeNode* root)
    {
        if ( ! root)
            return {};

        std::vector<int> results; // Maxes in every level

        std::queue<TreeNode*> queue;
        queue.push(root);

        int level = 0;

        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            results.push_back(INT_MIN); // Add INT_MIN as max for this level

            for (int i = 0; i < size; i++)
            {
                TreeNode* curr = queue.front();
                queue.pop();

                results[level] = std::max(results[level], curr->val);

                if (curr->left)
                    queue.push(curr->left);

                if (curr->right)
                    queue.push(curr->right);
            }

            level++;
        }

        return results;
    }
};
