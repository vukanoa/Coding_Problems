#include <iostream>
#include <vector>
#include <algorithm>

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

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This requires serious explanation)

*/

/* Time  Beats: 91.98% */
/* Space Beats: 56.96% */

/* Time  Complexity: O(E2logE+ElogE+E⋅α(N)) */
/* Space Complexity: O(N+E)O(N+E)           */
class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges)
    {
        for (int i = 0; i < edges.size(); ++i)
            edges[i].push_back(i); // [v1, v2, weight, original_index]

        sort(edges.begin(), edges.end(), [](const vector<int>& e1, const vector<int>& e2) {
            return e1[2] < e2[2];
        });

        int mst_weight = 0;
        UnionFind uf(n);
        for (auto& edge : edges)
        {
            if (uf.unionSets(edge[0], edge[1]))
            {
                mst_weight += edge[2];
            }
        }

        vector<int> critical, pseudo;

        for (auto& edge : edges)
        {
            int i = edge[3];

            // Try without the current edge
            int weight = 0;
            UnionFind uf_no_edge(n);

            for (auto& e : edges)
            {
                if (i != e[3] && uf_no_edge.unionSets(e[0], e[1]))
                    weight += e[2];
            }

            if (*max_element(uf_no_edge.rank.begin(), uf_no_edge.rank.end()) != n || weight > mst_weight)
            {
                critical.push_back(i);
                continue;
            }

            // Try with the current edge
            UnionFind uf_with_edge(n);
            uf_with_edge.unionSets(edge[0], edge[1]);
            weight = edge[2];

            for (auto& e : edges)
            {
                if (uf_with_edge.unionSets(e[0], e[1]))
                    weight += e[2];
            }

            if (weight == mst_weight)
            {
                pseudo.push_back(i);
            }
        }

        return {critical, pseudo};
    }
};
