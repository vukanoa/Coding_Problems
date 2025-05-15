/*
    ============
    === EASY ===
    ============

    ===================================
    1971) Find If Paths Exists in Graph
    ===================================

    ============
    Description:
    ============

    There is a bi-directional graph with n vertices, where each vertex is
    labeled from 0 to n - 1 (inclusive). The edges in the graph are represented
    as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a
    bi-directional edge between vertex ui and vertex vi. Every vertex pair is
    connected by at most one edge, and no vertex has an edge to itself.

    You want to determine if there is a valid path that exists from vertex
    source to vertex destination.

    Given edges and the integers n, source, and destination, return true if
    there is a valid path from source to destination, or false otherwise.

    =========================================================================================
    FUNCTION: bool validPath(int n, vector<vector<int>>& edges, int source, int destination);
    =========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
    Output: true
    Explanation: There are two paths from vertex 0 to vertex 2:
    - 0 → 1 → 2
    - 0 → 2


    --- Example 2 ---
    Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
    Output: false
    Explanation: There is no path from vertex 0 to vertex 5.


    *** Constraints ***
    1 <= n <= 2 * 10^5
    0 <= edges.length <= 2 * 10^5
    edges[i].length == 2
    0 <= ui, vi <= n - 1
    ui != vi
    0 <= source, destination <= n - 1
    There are no duplicate edges.
    There are no self edges.

*/

#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Union-Find(Disjoint Set) Problem.

*/

/* Time  Beats: 98.22% */
/* Space Beats: 95.42% */

/*
    Time  Complexity: O(E * α(n))

    What is α(n), Really?

        α(n) is the inverse Ackermann function.

        It grows slower than any practical function — so slow that:

        For all real-world values of n
        (like up to the number of atoms in the universe), α(n) ≤ 5.

    So while it's not technically constant, it is so tiny that we can treat it
    as constant time for all practical inputs.

*/
/*
    Space Complexity: O(N)
*/
class Solution_Union_Find {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination)
    {
        vector<int> rank(n, 1);

        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        for (const auto& edge : edges)
            Union(edge[0], edge[1], parent, rank);

        return Find(source, parent) == Find(destination, parent);
    }

private:

    int Find(int node, vector<int>& parent)
    {
        while (node != parent[node])
        {
            node = parent[parent[node]]; // Reverse Acerkman function ~O(1)
        }

        return node;
    }

    void Union(int node1, int node2, vector<int>& parent, vector<int>& rank)
    {
        int p1 = Find(node1, parent);
        int p2 = Find(node2, parent);

        if (p1 == p2)
            return;

        if (rank[p1] >= rank[p2])
        {
            parent[p2] = p1;
            rank[p1] += rank[p2];
        }
        else
        {
            parent[p1] = p2;
            rank[p2] += rank[p1];
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Fundamental DFS.

*/

/* Time  Beats: 28.92% */
/* Space Beats: 24.44% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination)
    {
        unordered_map<int, vector<int>> adj_list;

        for (auto& entry : edges)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        vector<bool> visited(n, false);

        return dfs(source, destination, adj_list, visited);
    }

    bool dfs(int node, int& destination, unordered_map<int, vector<int>>& adj_list, vector<bool>& visited)
    {
        if (node == destination)
            return true;

        visited[node] = true;

        for (const auto& neighbor : adj_list[node])
        {
            if (visited[neighbor])
                continue;

            if (dfs(neighbor, destination, adj_list, visited))
                return true;
        }

        // visited[node] = false;

        return false;
    }
};
