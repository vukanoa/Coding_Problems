/*
    ============
    === HARD ===
    ============

    =====================================================
    3924) Minimum Threshold Path With Limited Heavy Edges
    =====================================================

    ============
    Description:
    ============

    There is an undirected weighted graph with n nodes labeled from 0 to n - 1.

    The graph is represented by a 2D integer array edges, where each edge
    edges[i] = [ui, vi, wi] indicates that there is an undirected edge between
    nodes ui and vi with weight wi.

    You are also given integers source, target and k.

    A threshold value determines whether an edge is considered light or heavy:

        + An edge is light if its weight is less than or equal to threshold.
        + An edge is heavy if its weight is greater than threshold.

    A path from source to target is valid if it contains at most k heavy edges.

    Return the minimum integer threshold such that at least one valid path
    exists from source to target. If no such path exists, return -1.

    =================================================================================================
    FUNCTION: int minimumThreshold(int n, vector<vector<int>>& edges, int source, int target, int k);
    =================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, edges = [[0,1,5],[1,2,3],[3,4,4],[4,5,1],[1,4,2]], source = 0, target = 3, k = 1
    Output: 4
    Explanation:
    The minimum threshold such that a path from node 0 to node 3 uses at most 1 heavy edge is 4.
        Light edges: [1, 2, 3], [3, 4, 4], [4, 5, 1], [1, 4, 2]
        Heavy edges: [0, 1, 5]
    A valid path is 0 → 1 → 4 → 3. It uses only 1 heavy edge ([0, 1, 5]), which satisfies the limit k = 1.
    Any smaller threshold would make it impossible to reach node 3 without exceeding 1 heavy edge.


    --- Example 2 ---
    Input: n = 6, edges = [[0,1,3],[1,2,4],[3,4,5],[4,5,6]], source = 0, target = 4, k = 1
    Output: -1
    Explanation:
    There is no path from node 0 to node 4. Since the target cannot be reached,
    the output is -1.


    --- Example 3 ---
    Input: n = 4, edges = [[0,1,2],[1,2,2],[2,3,2],[3,0,2]], source = 0, target = 0, k = 0
    Output: 0
    Explanation:
    The source and target are the same node. No edges need to be traversed, so
    the minimum threshold is 0.


    *** Constraints ***
    1 <= n <= 10^3
    0 <= edges.length <= 10^3
    edges[i] = [ui, vi, wi]
    0 <= ui, vi <= n - 1
    1 <= wi <= 109
    0 <= source, target <= n - 1
    0 <= k <= edges.length

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

    This one is really NOT that compilcated, you just need to know 3
    fundamentals Algorithms by heart.

    1. DSU (Disjoint Set Union, ie.. "Union & Find")
    2. Binary Search on result range
    3. Dijkstra on number of heavy-edges instead of the "distance".

*/

/* Time  Beats: 61.17% */
/* Space Beats: 80.29% */

/* Time  Complexity: O(V  +  E * alpha(V)  +  E  +  log(MAX_WEIGHT) * (E + V)*logV) */
/* Space Complexity: O(E + V)                                                       */
class DSU {
private:
    vector<int> size;
    vector<int> parent;
    int components;

public:
    DSU(int n)
    {
        components = n;

        size.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++) // TC: O(V)
        {
            size[i]   = 1;
            parent[i] = i;
        }
    }

    // TC: O(alpha(V))
    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function, <= 5 for all practical inputs */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    // TC: O(alpha(V))
    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1); // O(alpha(V))
        int root_2 = find_root(node_2); // O(alpha(V))

        if (root_1 == root_2)
            return false; // NOT merged

        if (size[root_1] < size[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        size[root_1]  += size[root_2];

        components--;

        return true; // Merged
    }

    // TC: O(1)
    int number_of_components()
    {
        return components;
    }

    // TC: O(alpha(V))
    int are_connected(int node_1, int node_2)
    {
        int root_1 = find_root(node_1); // O(alpha(V))
        int root_2 = find_root(node_2); // O(alpha(V))

        return root_1 == root_2;
    }
};



class Solution {
private:
    static constexpr int MAX_N = 1e3;

public:
    int minimumThreshold(int n, vector<vector<int>>& edges, int source, int target, int k)
    {
        if (source == target)
            return 0;

        DSU dsu(n); // TC: O(V) for the Constructor

        int heaviest_edge = 0;

        /* Check if source and target are CONNECTED */
        // TC: O(E * alpha(V)) for entire block
        for (const auto& edge : edges) 
        {
            const int u = edge[0];
            const int v = edge[1];
            const int w = edge[2];

            dsu.union_components(u, v);

            heaviest_edge = max(heaviest_edge, w);
        }

        if ( ! dsu.are_connected(source, target)) // TC: O(alpha(V))
            return -1;


        /* Build an Adjacency List */
        unordered_map<int, vector<pair<int,int>>> adj_list;

        // TC: O(E) for entire block
        for (const auto& edge : edges)
        {
            const int u = edge[0];
            const int v = edge[1];
            const int w = edge[2];

            /* Undirected WEIGHTED edges */
            adj_list[u].push_back( {v, w} );
            adj_list[v].push_back( {u, w} );
        }


        /* Binary Search */
        // 
        // TC: O(log(MAX_WEIGHT)) is the "Binary Search" portion
        // 
        int low  = 0;
        int high = heaviest_edge;
        while (low < high)
        {
            int threshold_mid = low + (high - low) / 2; // Prevents OVERFLOW

            // "possible_with" is Dijkstra's Algorithm and its Time Complexity:
            // TC: O((E + V) * logV)
            if (possible_with(threshold_mid, adj_list, k, source, target, n))
                high = threshold_mid;
            else
                low  = threshold_mid + 1;
        }

        return low; // Or high, it does NOT matter
    }

private:
    // TC: O((E + V) * logV)
    bool possible_with(int threshold, unordered_map<int, vector<pair<int,int>>>& adj_list, int k, int source, int target, int n)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;

        vector<int> min_heavy_edges(n, INT_MAX);
        min_heavy_edges[source] = 0;

        min_heap.push( {0, source} );

        /* Dijkstra */
        while ( ! min_heap.empty())
        {
            auto [heavy_edges, node] = min_heap.top();
            min_heap.pop();

            if (heavy_edges > min_heavy_edges[node])
                continue;

            if (node == target)
                return heavy_edges <= k;

            for (auto [neighbor_node, neighbor_weight] : adj_list[node])
            {
                int new_heavy_edges = heavy_edges + (neighbor_weight > threshold);

                if (new_heavy_edges < min_heavy_edges[neighbor_node] && new_heavy_edges <= k)
                {
                    min_heavy_edges[neighbor_node] = new_heavy_edges;
                    min_heap.push( {new_heavy_edges, neighbor_node} );
                }
            }
        }

        return false;
    }
};
