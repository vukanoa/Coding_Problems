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

#include <vector>
#include <unordered_map>
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

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions)
    {
        const int N = descriptions.size();

        unordered_map<int, TreeNode*> umap;
        unordered_map<int, int> indegree;

        for (const vector<int>& description : descriptions)
        {
            const int& parent = description[0];
            const int& child  = description[1];
            const int& isLeft = description[2];

            TreeNode* parent_node;
            if (umap.find(parent) == umap.end()) // does NOT exist yet
            {
                parent_node = new TreeNode(parent);
                umap.insert ( {parent, parent_node} );
            }
            else
            {
                parent_node = umap[parent];
            }

            TreeNode* child_node;
            if (umap.find(child) == umap.end())
            {
                child_node = new TreeNode(child);
                umap.insert( {child, child_node} );
            }
            else
            {
                child_node = umap[child];
            }

            if (isLeft)
                parent_node->left = child_node;
            else
                parent_node->right = child_node;


            indegree.try_emplace(parent, 0); // C++17
            // if ( ! indegree.count(parent))
            //     indegree[parent] = 0;

            indegree[child]++;
        }

        TreeNode* root = nullptr;
        for (const auto& [node_val, indegree_val] : indegree)
        {
            if (indegree_val == 0)
            {
                root = umap[node_val];
                break;
            }
        }

        return root;
    }
};
