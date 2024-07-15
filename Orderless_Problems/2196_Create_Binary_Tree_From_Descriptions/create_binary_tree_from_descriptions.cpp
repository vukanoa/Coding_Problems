#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    2196) Create Binary Tree From Descriptions
    ==========================================

    ============
    Description:
    ============

    You are given a 2D integer array descriptions where descriptions[i] =
    [parenti, childi, isLefti] indicates that parenti is the parent of childi
    in a binary tree of unique values. Furthermore,

        If isLefti == 1, then childi is the left child of parenti.
        If isLefti == 0, then childi is the right child of parenti.

    Construct the binary tree described by descriptions and return its root.

    The test cases will be generated such that the binary tree is valid.

    ========================================================================
    FUNCTION: TreeNode* createBinaryTree(vector<vector<int>>& descriptions);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
    Output: [50,20,80,15,17,19]
    Explanation: The root node is the node with value 50 since it has no parent.
    The resulting binary tree is shown in the diagram.

    --- Example 2 ---
    Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
    Output: [1,2,null,null,3,4]
    Explanation: The root node is the node with value 1 since it has no parent.
    The resulting binary tree is shown in the diagram.


    *** Constraints ***
    1 <= descriptions.length <= 10^4
    descriptions[i].length == 3
    1 <= parenti, childi <= 10^5
    0 <= isLefti <= 1
    The binary tree described by descriptions is valid.

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
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.47% */
/* Space Beats: 98.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = 100001;

        bitset<N> seen = 0;
        int root = -1;
        int parent[N] = {0};           // parent val
        TreeNode* node[N] = {nullptr}; // array for TreeNode*

        for (auto& d : descriptions)
        {
            int x = d[0], y = d[1], l = d[2];

            if (!seen[x])
            {
                node[x] = new TreeNode(x);
                seen[x] = 1;

                if (parent[x] == 0)
                    root = x;
            }

            if (!seen[y])
            {
                node[y] = new TreeNode(y);
                seen[y] = 1;
            }

            parent[y] = x;

            if (l)
                node[x]->left  = node[y];
            else
                node[x]->right = node[y];
        }

        while (parent[root] != 0) // Find real root
            root = parent[root];

        return node[root];
    }
};
