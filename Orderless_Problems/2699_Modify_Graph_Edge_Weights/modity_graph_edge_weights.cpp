#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ===============================
    2699) Modify Graph Edge Weights
    ===============================

    ============
    Description:
    ============

    You are given an undirected weighted connected graph containing n nodes
    labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai,
    bi, wi] indicates that there is an edge between nodes ai and bi with weight
    wi.

    Some edges have a weight of -1 (wi = -1), while others have a positive
    weight (wi > 0).

    Your task is to modify all edges with a weight of -1 by assigning them
    positive integer values in the range [1, 2 * 109] so that the shortest
    distance between the nodes source and destination becomes equal to an
    integer target. If there are multiple modifications that make the shortest
    distance between source and destination equal to target, any of them will
    be considered correct.

    Return an array containing all edges (even unmodified ones) in any order if
    it is possible to make the shortest distance from source to destination
    equal to target, or an empty array if it's impossible.

    Note:

    =====
    Note: You are not allowed to modify the weights of edges with initial
          positive weights.
    =====

    =============================================================================================================================
    FUNCTION: vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target);
    =============================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
    Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
    Explanation: The graph above shows a possible modification to the edges,
                 making the distance from 0 to 1 equal to 5.


    --- Example 2 ---
    Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2, target = 6
    Output: []
    Explanation: The graph above contains the initial edges. It is not possible
                 to make the distance from 0 to 2 equal to 6 by modifying the
                 edge with weight -1. So, an empty array is returned.


    --- Example 3 ---
    Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0, destination = 2, target = 6
    Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
    Explanation: The graph above shows a modified graph having the shortest
                 distance from 0 to 2 as 6.


    *** Constraints ***
    1 <= n <= 100
    1 <= edges.length <= n * (n - 1) / 2
    edges[i].length == 3
    0 <= ai, bi < n
    wi = -1 or 1 <= wi <= 107
    ai != bi
    0 <= source, destination < n
    source != destination
    1 <= target <= 109
    The graph is connected, and there are no self-loops or repeated edges

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Dijkstra)

*/

/* Time  Beats: 94.85% */
/* Space Beats: 91.42% */

/* Time  Complexity: O((E + V) * logV) */
/* Space Complexity: O(E + V)          */
class Solution_Dijkstra {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target)
    {
        vector<vector<pair<int, int>>> adj_list(n);

        for (int i = 0; i < edges.size(); i++)
        {
            int node_a = edges[i][0];
            int node_b = edges[i][1];
            adj_list[node_a].emplace_back(node_b, i);
            adj_list[node_b].emplace_back(node_a, i);
        }

        vector<vector<int>> distances(n, vector<int>(2, INT_MAX));
        distances[source][0] = distances[source][1] = 0;

        run_dijkstra(adj_list, edges, distances, source, 0, 0);
        int difference = target - distances[destination][0];

        if (difference < 0)
            return {};

        run_dijkstra(adj_list, edges, distances, source, difference, 1);

        if (distances[destination][1] < target)
            return {};

        for (auto& edge : edges)
        {
            if (edge[2] == -1)
                edge[2] = 1;
        }

        return edges;
    }

private:
    void run_dijkstra(const vector<vector<pair<int, int>>>& adj_list, vector<vector<int>>& edges, vector<vector<int>>& distances, int source, int difference, int run)
    {
        const int n = adj_list.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> min_heap;
        min_heap.push({0, source});
        distances[source][run] = 0;

        while ( ! min_heap.empty())
        {
            auto [currentDistance, currentNode] = min_heap.top();
            min_heap.pop();

            if (currentDistance > distances[currentNode][run])
                continue;

            for (auto& neighbor : adj_list[currentNode])
            {
                int next_node = neighbor.first;
                int edge_idx  = neighbor.second;

                int weight = edges[edge_idx][2];

                if (weight == -1) weight = 1;

                if (run == 1 && edges[edge_idx][2] == -1)
                {
                    int newWeight = difference + distances[next_node][0] - distances[currentNode][1];
                    if (newWeight > weight)
                        edges[edge_idx][2] = weight = newWeight;
                }

                if (distances[next_node][run] > distances[currentNode][run] + weight)
                {
                    distances[next_node][run] = distances[currentNode][run] + weight;
                    min_heap.push({distances[next_node][run], next_node});
                }
            }
        }
    }
};
