/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    102) Binary Tree Level Order Traversal
    ======================================

    ============
    Description:
    ============

    Given the "root" of a binary tree, return the level ordder traversal of its
    nodes' values. (i.e., from left to right, level by level).

    =========================================================
    FUNCTION: vector<vector<int>> levelOrder(TreeNode* root);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  root = [3, 9, 20, null, null, 15, 7]
    Output: [[3], [9, 20], [15, 7]]

    --- Example 2 ---
    Input:  root = [1]
    Output: [[1]]

    --- Example 3 ---
    Input:  root = []
    Output: []

    *** Constraints ***
    The number of nodes in the tree is in the range [0, 2000]
    -1000 <= Node.val <= 1000

*/

#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node.
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

    It's just BFS. The only "tricky" part is to know when the current level
    ends and the next one begins.

    We do that but calculating the number of nodes in the queue before we enter
    the "for" loop.

    We don't push null nodes in the queue.

    Also, if we push empty vector in "result", nothing will happen. At least
    that's how it is in C++.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        if ( ! root)
            return {};

        vector<vector<int>> result;

        queue<TreeNode*> queue;
        queue.push(root);

        /* BFS */
        while ( ! queue.empty())
        {
            int size = queue.size();

            vector<int> current_level;
            while (size > 0)
            {
                TreeNode* node = queue.front();
                queue.pop();

                current_level.push_back(node->val);

                if (node->left)
                    queue.push(node->left);

                if (node->right)
                    queue.push(node->right);

                // Decrement
                size--;
            }

            result.push_back(current_level);
        }

        return result;
    }
};
