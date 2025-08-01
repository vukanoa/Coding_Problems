/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    429) N-ary Tree Level Order Traversal
    =====================================

    ============
    Description:
    ============

    Given an n-ary tree, return the level order traversal of its nodes' values.

    Nary-Tree input serialization is represented in their level order
    traversal, each group of children is separated by the null value
    (See examples).

    =====================================================
    FUNCTION: vector<vector<int>> levelOrder(Node* root);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: root = [1,null,3,2,4,null,5,6]
    Output: [[1],[3,2,4],[5,6]]

    --- Example 2 ---
    Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
    Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]


    *** Constraints ***
    The height of the n-ary tree is less than or equal to 1000
    The total number of nodes is between [0, 10^4]

*/

#include <queue>
#include <vector>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    Classic "BFS"(Breadth First Search) on a Graph.

*/

/* Time  Beats: 73.84% */
/* Space Beats: 46.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root)
    {
        if ( ! root)
            return {};

        vector<vector<int>> result;

        queue<Node*> queue;
        queue.push(root);

        while ( ! queue.empty())
        {
            int size = queue.size();
            vector<int> level;

            for (int x = 0; x < size; x++)
            {
                Node* curr_node = queue.front();
                queue.pop();

                level.push_back(curr_node->val);

                /* Push all of its children to the queue */
                for (Node* child : curr_node->children)
                    queue.push(child);
            }

            result.push_back(level);
        }

        return result;
    }
};
