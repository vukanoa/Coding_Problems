/*
    ============
    === HARD ===
    ============

    ======================================
    3772) Maximum Subgraph Score in a Tree
    ======================================

    ============
    Description:
    ============

    You are given an undirected tree with n nodes, numbered from 0 to n - 1. It
    is represented by a 2D integer array edges of length n - 1, where edges[i]
    = [ai, bi] indicates that there is an edge between nodes ai and bi in the
    tree.

    You are also given an integer array good of length n, where good[i] is 1 if
    the ith node is good, and 0 if it is bad.

    Define the score of a subgraph as the number of good nodes minus the number
    of bad nodes in that subgraph.

    For each node i, find the maximum possible score among all connected
    subgraphs that contain node i.

    Return an array of n integers where the ith element is the maximum score
    for node i.

    A subgraph is a graph whose vertices and edges are subsets of the original
    graph.

    A connected subgraph is a subgraph in which every pair of its vertices is
    reachable from one another using only its edges.

    =============================================================================================
    FUNCTION: vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good);
    =============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2]], good = [1,0,1]
    Output: [1,1,1]
    Explanation:
        + Green nodes are good and red nodes are bad.
        + For each node, the best connected subgraph containing it is the whole
          tree, which has 2 good nodes and 1 bad node, resulting in a score of
          1.
        + Other connected subgraphs containing a node may have the same score.


    --- Example 2 ---
    Input: n = 5, edges = [[1,0],[1,2],[1,3],[3,4]], good = [0,1,0,1,1]
    Output: [2,3,2,3,3]
    Explanation:
        + Node  0          : The best connected subgraph consists of nodes 0, 1, 3, 4, which has 3 good nodes and 1 bad node, resulting in a score of 3 - 1 = 2.
        + Nodes 1, 3, and 4: The best connected subgraph consists of nodes 1, 3, 4, which has 3 good nodes, resulting in a score of 3.
        + Node  2          : The best connected subgraph consists of nodes 1, 2, 3, 4, which has 3 good nodes and 1 bad node, resulting in a score of 3 - 1 = 2.


    --- Example 3 ---
    Input: n = 2, edges = [[0,1]], good = [0,0]
    Output: [-1,-1]
    Explanation:
    For each node, including the other node only adds another bad node, so the
    best score for both nodes is -1.


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i] = [ai, bi]
    0 <= ai, bi < n
    good.length == n
    0 <= good[i] <= 1
    The input is generated such that edges represents a valid tree.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 63.04% */
/* Space Beats: 39.86% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good)
    {
        /* Build an Adjacency List */
        vector<vector<int>> adj_list(n);
        for (const auto& edge : edges)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            // Undirected edge
            adj_list[a].push_back(b);
            adj_list[b].push_back(a);
        }

        vector<int> parent_of(n, -1);

        vector<int> traversal_order;
        traversal_order.reserve(n);

        traversal_order.push_back(0); // We're rooting the tree at node 0
        for (unsigned idx = 0; idx < traversal_order.size(); idx++)
        {
            int curr_node = traversal_order[idx];

            for (const int& neighbor : adj_list[curr_node])
            {
                if (neighbor == parent_of[curr_node]) // neighbor is ABOVE curr_node
                    continue;

                // neighbor is a CHILD of curr_node
                parent_of[neighbor] = curr_node;
                traversal_order.push_back(neighbor);
            }
        }

        // down_score_including[curr_node] = BEST connected subtree inside subtree where curr_node is
        //                         the root of that subtree
        vector<int> down_score_including(n, 0);
        for (int curr_node = 0; curr_node < n; curr_node++)
        {
            down_score_including[curr_node] = good[curr_node] == 1 ? +1 : -1;
        }

        // We're processing in REVERSE order, from children upwards
        for (int idx = n-1; idx >= 1; idx--)
        {
            int curr_node = traversal_order[idx];

            if (down_score_including[curr_node] > 0)
                down_score_including[ parent_of[curr_node] ] += down_score_including[curr_node];
        }

        vector<int> answer(n, 0);
        answer[0] = down_score_including[0];

        // Here we're processing nodes in a standard FORWARD order,
        // i.e. first parents then children
        vector<int> up_score_excluding(n, 0);
        for (int idx = 0; idx < n; idx++)
        {
            int curr_node = traversal_order[idx];

            for (const int& neighbor : adj_list[curr_node])
            {
                if (curr_node != parent_of[neighbor])
                    continue;

                // Here neighbor is CERTAINLY a CHILD of curr_node
                // curr_node <==> parent
                // neighbor  <==> child
                int best_score_without = answer[curr_node] - max(0, down_score_including[neighbor]);

                up_score_excluding[neighbor] = max(0, best_score_without);

                answer[neighbor] =   up_score_excluding[neighbor] +
                                   down_score_including[neighbor];
            }
        }

        return answer;
    }
};
