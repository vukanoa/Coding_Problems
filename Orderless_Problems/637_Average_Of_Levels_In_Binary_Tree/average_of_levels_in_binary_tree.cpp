#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === EASY ===
    ============

    =================================
    637) Average Level in Binary Tree
    =================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the average value of the nodes on
    each level in the form of an array. Answers within 10-5 of the actual
    answer will be accepted.

    =========================================================
    FUNCTION: vector<double> averageOfLevels(TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [3,9,20,null,null,15,7]
    Output: [3.00000,14.50000,11.00000]
    Explanation: The average value of nodes on level 0 is 3, on level 1 is
                 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].


    --- Example 2 ---
    Input: root = [3,9,20,15,7]
    Output: [3.00000,14.50000,11.00000]


    *** Constraints ***
    The number of nodes in the tree is in the range [1, 10^4].
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

    Basic BFS(Level-Order) traversal.

    This is a fundamental techique. If you don't understand it, make sure to
    learn it anywhere on the internet or even by watching the code below.

    It's like a "multiplication table". There is no going further without it.

*/

/* Time  Beats: 22.15% */
/* Space Beats: 41.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root)
    {
        vector<double> result;

        /* BFS (Level-Order) */
        queue<TreeNode*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();

            long long sum = 0;
            for (int x = 0; x < size; x++)
            {
                TreeNode* curr_node = queue.front();
                queue.pop();

                sum += curr_node->val;

                if (curr_node->left)
                    queue.push(curr_node->left);

                if (curr_node->right)
                    queue.push(curr_node->right);
            }

            // result.push_back(static_cast<double>(sum / size));
            result.push_back(1.0 *  sum / size);
        }

        return result;
    }
};
