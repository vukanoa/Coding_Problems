#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2458) Height_Of_Binary_Tree_After_Subtree_Removal_Queries
    =========================================================

    ============
    Description:
    ============


    You are given the root of a binary tree with n nodes. Each node is assigned
    a unique value from 1 to n. You are also given an array queries of size m.

    You have to perform m independent queries on the tree where in the ith
    query you do the following:

        Remove the subtree rooted at the node with the value queries[i] from
        the tree. It is guaranteed that queries[i] will not be equal to the
        value of the root.

    Return an array answer of size m where answer[i] is the height of the tree
    after performing the ith query.

    =====
    Note: The queries are independent, so the tree returns to its initial state
          after each query.

          The height of a tree is the number of edges in the longest simple
          path from the root to some node in the tree.
    =====

    ========================================================================
    FUNCTION: vector<int> treeQueries(TreeNode* root, vector<int>& queries);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================


    --- Example 1 ---
    Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
    Output: [2]
    Explanation: The diagram above shows the tree after removing the subtree
                 rooted at node with value 4. The height of the tree is 2 (The
                 path 1 -> 3 -> 2).


    --- Example 2 ---
    Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
    Output: [3,2,3,2]
    Explanation: We have the following queries:
    - Removing the subtree rooted at node with value 3. The height of the tree becomes 3 (The path 5 -> 8 -> 2 -> 4).
    - Removing the subtree rooted at node with value 2. The height of the tree becomes 2 (The path 5 -> 8 -> 1).
    - Removing the subtree rooted at node with value 4. The height of the tree becomes 3 (The path 5 -> 8 -> 2 -> 6).
    - Removing the subtree rooted at node with value 8. The height of the tree becomes 2 (The path 5 -> 9 -> 3).


    *** Constraints ***
    The number of nodes in the tree is n.
    2 <= n <= 10^5
    1 <= Node.val <= n
    All the values in the tree are unique.
    m == queries.length
    1 <= m <= min(n, 10^4)
    1 <= queries[i] <= n
    queries[i] != root.val

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

    TODO

*/

/* Time  Beats: 59.79% */
/* Space Beats: 33.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int total_nodes; // total nodes in the tree
    vector<vector<int>> level_heights; // stores maximum heights at each level, with up to 2 nodes per level
    vector<int> node_levels;           // stores the level of each node
    vector<int> node_heights;          // stores the height of each node

    // Recursive function to initialize the vectors
    int traverse(TreeNode* root, int level)
    {
        if (root == NULL)
            return 0;

        // Update total_nodes to reflect the highest node value
        total_nodes = max(total_nodes, root->val);

        // Store the level of the current node
        node_levels[root->val] = level;

        // Recursively calculate left and right subtree heights
        int left_height  = traverse(root->left,  level + 1);
        int right_height = traverse(root->right, level + 1);

        // Store the height of the current node as a root node
        node_heights[root->val] = max(left_height, right_height);

        // Add this node's height to its level's list
        level_heights[level].push_back(node_heights[root->val]);
        
        // Keep only the two largest heights at this level
        if (level_heights[level].size() == 3)
        {
            int min_height = min({level_heights[level][0], level_heights[level][1], level_heights[level][2]});

            if (level_heights[level][0] == min_height)
            {
                swap(level_heights[level][2], level_heights[level][0]);
            }
            else if (level_heights[level][1] == min_height)
            {
                swap(level_heights[level][2], level_heights[level][1]);
            }

            level_heights[level].pop_back();
        }

        return node_heights[root->val] + 1;
    }

    vector<int> treeQueries(TreeNode* root, vector<int>& queries)
    {
        // Initialize sizes of vectors
        level_heights.resize(1e5);
        node_heights.resize(1e5 + 1, 0);
        node_levels.resize(1e5 + 1, 0);

        // Store the total number of nodes
        total_nodes = 0;
        node_heights[0] = -1;
        traverse(root, 0); // Fill all vectors

        vector<int> heights_with_node_removed(total_nodes + 1, 0); // Store heights if each node is removed once
        vector<int> result(queries.size(), 0);
        
        for (int i = 1; i <= total_nodes; i++)
        {
            if (node_levels[i] == 0)
                continue; // Skip root node

            int new_max_height = -1; // Find the new maximum height after node removal
            bool count_once = true;  // Flag to count only one occurrence of the same height

            // Traverse nodes at the same level as the current node
            for (int height : level_heights[node_levels[i]])
            {
                if (height == node_heights[i] && count_once)
                {
                    count_once = false;
                    continue;
                }

                new_max_height = max(new_max_height, height);
            }

            // If no other node at this level, the tree height depends only on the level of this node
            heights_with_node_removed[i] = new_max_height == -1 ? node_levels[i] - 1 : node_levels[i] + new_max_height;
        }

        // Populate result for each query
        for (int i = 0; i < queries.size(); i++)
            result[i] = heights_with_node_removed[queries[i]];

        return result;
    }
};
