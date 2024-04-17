#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    111) Minimum Death of Binary Tree
    =================================

    ============
    Description:
    ============

    Given a binary tree, find its minimum depth.

    The minimum depth is the number of nodes along the shortest path from the
    root node down to the nearest leaf node.

    Note: A leaf is a node with no children.

    =======================================
    FUNCTION: int minDepth(TreeNode* root);
    =======================================

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
                                      15       7

    Input: root = [3,9,20,null,null,15,7]
    Output: 2


    --- Example 2 ---
    Input: root = [2,null,3,null,4,null,5,null,6]
    Output: 5


    *** Constraints ***
    The number of nodes in the tree is in the range [0, 10^5].
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

    Self-Explnatory. This is one of the most fundamental techniques. It uses
    the most basic form of DFS traversal along with findind the minimum within
    the function of DFS.

    That's it.

*/

/* Time  Beats: 82.02% */
/* Space Beats: 93.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    int minDepth(TreeNode* root)
    {
        int min_depth = INT_MAX;
        dfs(root, 1, min_depth);

        return min_depth == INT_MAX ? 0 : min_depth;
    }

private:
    void dfs(TreeNode* root, int curr_depth, int& min_depth)
    {
        if (!root)
            return;

        if (!root->left && !root->right)
        {
            min_depth = std::min(min_depth, curr_depth);
            return;
        }

        dfs(root->left,  curr_depth+1, min_depth);
        dfs(root->right, curr_depth+1, min_depth);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Again, this is a fundamental technique, however this time it's a BFS.

    These two techniques are ABSOLUTELY FUNDAMENTAL to any Graph/Tree problem.

*/

/* Time  Beats: 79.72% */
/* Space Beats: 34.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    int minDepth(TreeNode* root)
    {
        if (!root)
            return 0;

        int min_depth = INT_MAX;
        std::queue<TreeNode*> queue;
        queue.push(root);

        int depth = 1;
        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                TreeNode* curr = queue.front();
                queue.pop();

                if (!curr->left && !curr->right)
                    return depth;

                if (curr->left)
                    queue.push(curr->left);

                if (curr->right)
                    queue.push(curr->right);
            }

            depth++;
        }

        return -1; // This will never be returned
    }
};
