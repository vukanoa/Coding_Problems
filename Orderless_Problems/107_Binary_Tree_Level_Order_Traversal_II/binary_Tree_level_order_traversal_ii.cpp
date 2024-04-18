#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    107) Binary Tree Level Order Traversal II
    =========================================

    ============
    Description:
    ============

    Given the root of a binary tree, return the bottom-up level order traversal
    of its nodes' values. (i.e., from left to right, level by level from leaf
    to root).

    ===============================================================
    FUNCTION: vector<vector<int>> levelOrderBottom(TreeNode* root);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                                    3
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             9            20
                                          / \
                                         /   \
                                        /     \
                                       15      7

    Input: root = [3,9,20,null,null,15,7]
    Output: [[15,7],[9,20],[3]]

    --- Example 2 ---
    Input: root = [1]
    Output: [[1]]

    --- Example 3 ---
    Input: root = []
    Output: []


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 2000].
    -1000 <= Node.val <= 1000

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

    Basic Level-order(i.e. BFS traversal) + std::reverse "results" at the end.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  50.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root)
    {
        if ( ! root)
            return {};

        std::vector<std::vector<int>> results;

        std::queue<TreeNode*> queue;
        queue.push(root);

        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();
            std::vector<int> level;

            for (int x = 0; x < size; x++)
            {
                TreeNode* node = queue.front();
                queue.pop();

                level.push_back(node->val);

                if (node->left)
                    queue.push(node->left);

                if (node->right)
                    queue.push(node->right);
            }

            results.push_back(level);
        }

        std::reverse(results.begin(), results.end());

        return results;
    }
};
