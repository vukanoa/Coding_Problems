/*
    ============
    === HARD ===
    ============

    ===============================
    2608) Shortest Cycle in a Graph
    ===============================

    ============
    Description:
    ============

    There is a bi-directional graph with n vertices, where each vertex is
    labeled from 0 to n - 1. The edges in the graph are represented by a given
    2D integer array edges, where edges[i] = [ui, vi] denotes an edge between
    vertex ui and vertex vi. Every vertex pair is connected by at most one
    edge, and no vertex has an edge to itself.

    Return the length of the shortest cycle in the graph. If no cycle exists,
    return -1.

    A cycle is a path that starts and ends at the same node, and each edge in
    the path is used only once.

    ===================================================================
    FUNCTION: int findShortestCycle(int n, vector<vector<int>>& edges);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
    Output: 3
    Explanation: The cycle with the smallest length is : 0 -> 1 -> 2 -> 0

    --- Example 2 ---
    Input: n = 4, edges = [[0,1],[0,2]]
    Output: -1
    Explanation: There are no cycles in this graph.


    *** Constraints ***
    2 <= n <= 1000
    1 <= edges.length <= 1000
    edges[i].length == 2
    0 <= ui, vi < n
    ui != vi
    There are no repeated edges.

*/

#include <climits>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

                        (dist = 0)
                      ____ 0_ ___
                     /           \
                    /             \
                   /               \
       (dist = 1) 7                 2 (dist = 1)
                   \               /
                    \             /
                     \           /
           (dist = 2) 3         4 (dist = 2)
      (number of edges          (number of edges
       from 0 to 3)              from 0 to 4)




    If there is a COMMON edge between the two edges with the SAME distance(both
    edges MUST be different and they must not be the parent of the other)

    If that's the case -- We've found a loop!

    Now just perform a basic BFS and we're done.

*/

/* Time  Beats: 30.67% */
/* Space Beats: 20.10% */

/* Time  Complexity: O(V * (E + V)) */
/* Space Complexity: O(E + V)       */
class Solution {
private:
    unordered_map<int, vector<int>> adj_list;
    int result = INT_MAX;

public:
    int findShortestCycle(int n, vector<vector<int>>& edges)
    {
        /* Build an Adjacency List */
        for (auto& entry : edges)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        for (int i = 0; i < n; i++)
            bfs(i, n);

        return result == INT_MAX ? -1 : result;
    }

private:
    void bfs(int src, int n)
    {
        vector<int> distance(n, INT_MAX);
        vector<int> parent(n, -1);

        queue<int> queue;
        queue.push(src);
        distance[src] = 0;

        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                int node = queue.front();
                queue.pop();

                for (const auto& neighbor : adj_list[node])
                {
                    if (distance[neighbor] == INT_MAX)
                    {
                        distance[neighbor] = 1 + distance[node];
                        parent[neighbor] = node;
                        queue.push(neighbor);
                    }
                    else if (parent[node] != neighbor && parent[neighbor] != node)
                    {
                        result = min(result, distance[neighbor] + distance[node] + 1);
                    }
                }
            }
        }
    }
};
