/*
    ============
    === HARD ===
    ============

    ======================================================================
    1489) Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
    ======================================================================

    ============
    Description:
    ============

    Given a weighted undirected connected graph with n vertices numbered from 0
    to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents
    a bidirectional and weighted edge between nodes ai and bi. A minimum
    spanning tree (MST) is a subset of the graph's edges that connects all
    vertices without cycles and with the minimum possible total edge weight.

    Find all the critical and pseudo-critical edges in the given graph's
    minimum spanning tree (MST). An MST edge whose deletion from the graph
    would cause the MST weight to increase is called a critical edge. On the
    other hand, a pseudo-critical edge is that which can appear in some MSTs
    but not all.

    =====
    Note: Note that you can return the indices of the edges in any order.
    =====

    ====================================================================================================
    FUNCTION: vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges);
    ====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
    Output: [[0,1],[2,3,4,5]]
    Explanation: The figure above describes the graph.
    The following figure shows all the possible MSTs:

    Notice that the two edges 0 and 1 appear in all MSTs, therefore they are
    critical edges, so we return them in the first list of the output.
    The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are
    considered pseudo-critical edges. We add them to the second list of the
    output.



    --- Example 2 ---
    Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
    Output: [[],[0,1,2,3]]
    Explanation: We can observe that since all 4 edges have equal weight,
                 choosing any 3 edges from the given 4 will yield an MST.
                 Therefore all 4 edges are pseudo-critical.




    *** Constraints ***
    2 <= n <= 100
    1 <= edges.length <= min(200, n * (n - 1) / 2)
    edges[i].length == 3
    0 <= ai < bi < n
    1 <= weighti <= 1000
    All pairs (ai, bi) are distinct.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.31% */
/* Space Beats: 42.19% */

/* Time  Complexity: O(E^2 * alpha(V)) */// E^2 dominates over O(E * logE)
/* Space Complexity: O(V + E)          */// O(V) for DSU, O(E) for sorted_edges
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU (int n)
    {
        rank.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function, for all practical inputs: <= O(5) */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }

    bool connected(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        return root_1 == root_2;
    }

    int max_component_size()
    {
        return *max_element(rank.begin(), rank.end());
    }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges)
    {
        const int V = n;
        const int E = edges.size();
        vector<int> critical;
        vector<int> pseudo_critical;

        vector<vector<int>> sorted_edges; // {weight, u, v, original_idx}
        sorted_edges.reserve(E);          // To prevent reallocations

        for (int i = 0; i < E; i++)
        {
            const int& u = edges[i][0];
            const int& v = edges[i][1];
            const int& w = edges[i][2];

            sorted_edges.push_back( {w, u, v, i} );
        }

        /* Sort */
        sort(sorted_edges.begin(), sorted_edges.end()); // O(E * logE)

        DSU dsu_global(V);
        int global_MST_weight = 0;

        /* Kruskal's Algorithm */
        // O(E * alpha(V)) (entire block)
        for (const auto& edge : sorted_edges) // O(E)
        {
            const int& w = edge[0]; // Weight
            const int& u = edge[1]; // node_1
            const int& v = edge[2]; // node_2
            const int& i = edge[3]; // orig idx

            if (dsu_global.union_components(u, v)) // (alpha(V))
                global_MST_weight += w;
        }

        /* Find all Critical and Pseudo-Critical edges */
        // O(E^2 * alpha(V)) (entire block)
        for (const auto& candidate_edge : sorted_edges) // O(E)
        {
            const int& candidate_w   = candidate_edge[0]; // candidate weight
            const int& candidate_u   = candidate_edge[1]; // candidate node_1
            const int& candidate_v   = candidate_edge[2]; // candidate node_2
            const int& candidate_idx = candidate_edge[3]; // candidate orig idx

            DSU dsu_without_candidate(V);

            // local <==> without the CURRENT edge
            int local_MST_weight = 0;

            /**************************/
            /* Check if it's CRITICAL */
            /**************************/
            for (const auto& iter_edge : sorted_edges) // O(E)
            {
                const int& edge_w   = iter_edge[0]; // edge weight
                const int& edge_u   = iter_edge[1]; // edge node_1
                const int& edge_v   = iter_edge[2]; // edge node_2
                const int& edge_idx = iter_edge[3]; // edge orig idx

                if (candidate_idx == edge_idx)
                    continue;

                // O(alpha(V))
                if (dsu_without_candidate.union_components(edge_u, edge_v))
                    local_MST_weight += edge_w;
            }

            bool graph_fully_connected = dsu_without_candidate.max_component_size() == V;
            if ( ! graph_fully_connected || local_MST_weight > global_MST_weight)
            {
                critical.push_back(candidate_idx);
                continue;
            }

            /*********************************/
            /* Check if it's PSEUDO-CRITICAL */
            /*********************************/
            DSU dsu_with_candidate(V);

            // Force this candidate-edge into the Graph
            dsu_with_candidate.union_components(candidate_u, candidate_v);
            local_MST_weight = candidate_w;

            for (const auto& iter_edge : sorted_edges) // O(E)
            {
                const int& edge_w   = iter_edge[0]; // edge weight
                const int& edge_u   = iter_edge[1]; // edge node_1
                const int& edge_v   = iter_edge[2]; // edge node_2
                const int& edge_idx = iter_edge[3]; // edge orig idx

                // O(alpha(V))
                if (dsu_with_candidate.union_components(edge_u, edge_v))
                    local_MST_weight += edge_w;
            }

            if (local_MST_weight == global_MST_weight)
                pseudo_critical.push_back(candidate_idx);
        }

        return {critical, pseudo_critical};
    }
};
