/*
    ============
    === HARD ===
    ============

    ================================================
    2642) Design Graph With Shortest Path Calculator
    ================================================

    ============
    Description:
    ============


    There is a directed weighted graph that consists of n nodes numbered from
    0 to n - 1. The edges of the graph are initially represented by the given
    array edges where edges[i] = [fromi, toi, edgeCosti] meaning that there is
    an edge from fromi to toi with the cost edgeCosti.

    Implement the Graph class:

        + Graph(int n, int[][] edges) initializes the object with n nodes and
          the given edges.

        + addEdge(int[] edge) adds an edge to the list of edges where
          edge = [from, to, edgeCost]. It is guaranteed that there is no edge
          between the two nodes before adding this one.

        + int shortestPath(int node1, int node2) returns the minimum cost of a
          path from node1 to node2. If no path exists, return -1. The cost of a
          path is the sum of the costs of the edges in the path.

    ===============================
    CLASS:
    class Graph {
    public:
        Graph(int n, vector<vector<int>>& edges)
        {

        }

        void addEdge(vector<int> edge)
        {

        }

        int shortestPath(int node1, int node2)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
    [[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
    Output
    [null, 6, -1, null, 6]

    Explanation
    Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
    g.shortestPath(3, 2); // return 6. The shortest path from 3 to 2 in the
    first diagram above is 3 -> 0 -> 1 -> 2 with a total cost of 3 + 2 + 1 = 6.
    g.shortestPath(0, 3); // return -1. There is no path from 0 to 3.
    g.addEdge([1, 3, 4]); // We add an edge from node 1 to node 3, and we get
    the second diagram above.
    g.shortestPath(0, 3); // return 6. The shortest path from 0 to 3 now is
    0 -> 1 -> 3 with a total cost of 2 + 4 = 6.


    *** Constraints ***
    1 <= n <= 100
    0 <= edges.length <= n * (n - 1)
    edges[i].length == edge.length == 3
    0 <= fromi, toi, from, to, node1, node2 <= n - 1
    1 <= edgeCosti, edgeCost <= 106
    There are no repeated edges and no self-loops in the graph at any point.
    At most 100 calls will be made for addEdge.
    At most 100 calls will be made for shortestPath.

*/

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A standard Dijkstra. Nothing special. This should be MEDIUM.

    However, the only "annoying" part is that in shortestPath function, node1
    can be equal to node2.

    It's not specifically forbidden in Constraints, but it's not something
    you'd expect, so you may give yourself a penalty if you don't take care of
    this case.

    It's "annoying" because you don't expect and it's difficult to spot.

    Other than that, it's a pretty straightforward Dijkstra's algorithm.

*/

/* Time  Beats: 8.97% */
/* Space Beats: 5.15% */

/* Time  Complexity: O((V + E) * logV) */
/* Space Complexity: O(V + E)          */
class Graph {
private:
    vector<unordered_map<int, int>> adj_list;

public:
    Graph(int n, vector<vector<int>>& edges)
    {
        build_adjacency_list(n, edges);
    }

    void addEdge(vector<int> edge)
    {
        const int from = edge[0];
        const int to   = edge[1];
        const int cost = edge[2];

        adj_list[from][to] = cost;
    }

    int shortestPath(int node1, int node2)
    {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;

        if (node1 == node2)
            return 0;

        // Initial
        for (const auto& entry : adj_list[node1])
            min_heap.push( {entry.second, entry.first} ); // {cost, to_node}

        unordered_set<int> visited = {node1};

        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            auto& cost    = top[0];
            auto& to_node = top[1];

            if (to_node == node2)
                return cost;

            if (visited.count(to_node))
                continue;

            for (const auto& entry : adj_list[to_node])
                min_heap.push( {cost + entry.second, entry.first} );

            visited.insert(to_node);
        }

        return -1;
    }

private:
    void build_adjacency_list(int n, const vector<vector<int>>& edges)
    {
        adj_list.assign(n, unordered_map<int, int>());

        for (const auto& entry : edges)
        {
            const int& from = entry[0];
            const int& to   = entry[1];
            const int& cost = entry[2];

            adj_list[from][to] = cost;
        }
    }
};
