#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    785) Is Graph Bipartite
    ===========================

    ============
    Description:
    ============

    There is an undirected graph with n nodes, where each node is numbered
    between 0 and n - 1. You are given a 2D array graph, where graph[u] is an
    array of nodes that node u is adjacent to. More formally, for each v in
    graph[u], there is an undirected edge between node u and node v. The graph
    has the following properties:

        There are no self-edges (graph[u] does not contain u).  There are no
        parallel edges (graph[u] does not contain duplicate values).  If v is
        in graph[u], then u is in graph[v] (the graph is undirected).  The
        graph may not be connected, meaning there may be two nodes u and v such
        that there is no path between them.

    A graph is bipartite if the nodes can be partitioned into two independent
    sets A and B such that every edge in the graph connects a node in set A and
    a node in set B.

    Return true if and only if it is bipartite.

    =======================================================
    FUNCTION: bool isBipartite(vector<vector<int>>& graph);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        0 --------- 1
        | \         |
        |  \        |
        |   \       |
        |    \      |
        |     \     |
        |      \    |
        |       \   |
        |        \  |
        |         \ |
        3 --------- 2

    Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
    Output: false
    Explanation: There is no way to partition the nodes into two independent
    sets such that every edge connects a node in one and a node in the other.


    --- Example 2 ---

        2 --------- 1
        |           |
        |           |
        3 --------- 4

    Input: graph = [[1,3],[0,2],[1,3],[0,2]]
    Output: true
    Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.


    *** Constraints ***
    graph.length == n
    1 <= n <= 100
    0 <= graph[u].length < n
    0 <= graph[u][i] <= n - 1
    graph[u] does not contain u.
    All the values of graph[u] are unique.
    If graph[u] contains v, then graph[v] contains u.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.62% */
/* Space Beats: 35.43% */

/* Time  Complexity: O(E + V) */
/* Space Complexity: O(V) */
class Solution {
public:
    bool isBipartite(std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();

        std::vector<int> color(n, 0); // Green(A) == 1, Red(B) == -1

        for (int i = 0; i < n; i++)
        {
            if (!BFS(graph, color, i))
                return false;
        }

        return true;
    }

private:
    bool BFS(std::vector<std::vector<int>>& graph, std::vector<int>& color, int node)
    {
        if (color[node] != 0) // If either color is already assigned to this node
            return true;

        std::queue<int> queue;
        queue.push(node);
        color[node] = -1; // Red(B) color

        while (!queue.empty())
        {
            node = queue.front();
            queue.pop();

            for (int& neighbor : graph[node])
            {
                if (color[neighbor] == color[node])
                    return false;
                else if (color[neighbor] == 0) // Color not yet assigned
                {
                    queue.push(neighbor);
                    color[neighbor] = -1 * color[node]; // Opposite color of this node
                }
            }
        }

        return true;
    }
};
