/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3613) Minimize Maximum Component Cost
    =====================================

    ============
    Description:
    ============

    You are given an undirected connected graph with n nodes labeled from 0 to
    n - 1 and a 2D integer array edges where edges[i] = [ui, vi, wi] denotes an
    undirected edge between node ui and node vi with weight wi, and an integer
    k.

    You are allowed to remove any number of edges from the graph such that the
    resulting graph has at most k connected components.

    The cost of a component is defined as the maximum edge weight in that
    component. If a component has no edges, its cost is 0.

    Return the minimum possible value of the maximum cost among all components
    after such removals.

    ================================================================
    FUNCTION: int minCost(int n, vector<vector<int>>& edges, int k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, edges = [[0,1,4],[1,2,3],[1,3,2],[3,4,6]], k = 2
    Output: 4
    Explanation:
    Remove the edge between nodes 3 and 4 (weight 6).
    The resulting components have costs of 0 and 4, so the overall maximum cost
    is 4.

    --- Example 2 ---
    Input: n = 4, edges = [[0,1,5],[1,2,5],[2,3,5]], k = 1
    Output: 5
    Explanation:
    No edge can be removed, since allowing only one component (k = 1) requires
    the graph to stay fully connected. That single component’s cost equals its
    largest edge weight, which is 5.


    *** Constraints ***
    1 <= n <= 5 * 10^4
    0 <= edges.length <= 10^5
    edges[i].length == 3
    0 <= ui, vi < n
    1 <= wi <= 10^6
    1 <= k <= n
    The input graph is connected.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Sort edges by their weights in ASCENDING order, then realize that at the
    beginning you have 'n' components, since at the beginning we consider each
    node separated from the rest.

    Then we want to start Unioning nodes, but we want to union edges that have
    the lowest weights first.

    Each time we Union two COMPONENTS(their respective "root nodes" differ) we
    DECREMENT the number of components we have and we update "result" as the
    maximum edge among all of the components.

    Also if at ANY point we stumble upon an edge that has the SAME "root node"
    we do NOT want to connect that edge.

    Why?
    Because it potentially the HIGHEST weight edge, however we know that we do
    NOT need it since by connecting those two edges we will NOT reduce the
    number of COMPONENTS we have in the graph.


    We are doing this until we have MORE components than k. As soon as we have
    exactly K components, we STOP and return result.


    Actually pretty easy if you know DSU(Disjoint Set Union).

*/

/* Time  Beats: 99.02% */
/* Space Beats: 87.58% */

/* Time  Complexity: O(E * logE) */ // Where 'E' is the number of edges
/* Space Complexity: O(N)        */
class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n)
    {
        rank.assign(n, 1);
        parent.resize(n);

        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find_root_node(int node)
    {
        // Get root parent
        while (node != parent[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node1, int node2)
    {
        int root1 = find_root_node(node1);
        int root2 = find_root_node(node2);

        if (root1 == root2)
            return false;

        if (rank[root1] < rank[root2])
            swap(root1, root2);

        // Make sure that to merge TOWARDS the smaller node, i.e. root1
        parent[root2] = root1;
        rank[root1] += rank[root2];

        return true;
    }
};

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges, int k)
    {
        if (k == n)
            return 0;

        int result = 0;

        // Sort in ASCENDING order by weights
        sort(edges.begin(), edges.end(), [](const vector<int>& a,
                                            const vector<int>& b)
                                         {
                                             return a[2] < b[2];
                                         });

        // Create DSU object
        DSU dsu(n);

        int idx = 0;
        int components = n;
        while (components > k)
        {
            if (dsu.union_components(edges[idx][0], edges[idx][1]))
            {
                components--;
                result = max(result, edges[idx][2]);
            }

            idx++;
        }

        return result;
    }
};
