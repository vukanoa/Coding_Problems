/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3608) Minimum Time for K Connected Components
    =============================================

    ============
    Description:
    ============

    You are given an integer n and an undirected graph with n nodes labeled
    from 0 to n - 1. This is represented by a 2D array edges, where edges[i] =
    [ui, vi, timei] indicates an undirected edge between nodes ui and vi that
    can be removed at timei.

    You are also given an integer k.

    Initially, the graph may be connected or disconnected. Your task is to find
    the minimum time t such that after removing all edges with time <= t, the
    graph contains at least k connected components.

    Return the minimum time t.

    A connected component is a subgraph of a graph in which there exists a path
    between any two vertices, and no vertex of the subgraph shares an edge with
    a vertex outside of the subgraph.

    ================================================================
    FUNCTION: int minTime(int n, vector<vector<int>>& edges, int k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, edges = [[0,1,3]], k = 2
    Output: 3
    Explanation:
        Initially, there is one connected component {0, 1}.
        At time = 1 or 2, the graph remains unchanged.
        At time = 3, edge [0, 1] is removed, resulting in k = 2 connected
        components {0}, {1}. Thus, the answer is 3.


    --- Example 2 ---
    Input: n = 3, edges = [[0,1,2],[1,2,4]], k = 3
    Output: 4
    Explanation:
        Initially, there is one connected component {0, 1, 2}.
        At time = 2, edge [0, 1] is removed, resulting in two connected components {0}, {1, 2}.
        At time = 4, edge [1, 2] is removed, resulting in k = 3 connected components {0}, {1}, {2}. Thus, the answer is 4.


    --- Example 3 ---
    Input: n = 3, edges = [[0,2,5]], k = 2
    Output: 0
    Explanation:
        Since there are already k = 2 disconnected components {1}, {0, 2}, no
        edge removal is needed. Thus, the answer is 0.


    *** Constraints ***
    1 <= n <= 10^5
    0 <= edges.length <= 10^5
    edges[i] = [ui, vi, timei]
    0 <= ui, vi < n
    ui != vi
    1 <= timei <= 10^9
    1 <= k <= n
    There are no duplicate edges.

*/

#include <algorithm>
#include <climits>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since DSU is done in O(N) Time and O(N) Space, and additionaly we know
    there are both minimum-possible time and maximum-possible time, and since
    that is a range--We can simply do a Binary Search on that range while
    doing DSU each time since it only takes O(N).

    Making it O(N * logN) which is acceptable given the constraints.

*/

/* Time  Beats: 8.33% */
/* Space Beats: 8.33% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, int k)
    {
        if (edges.empty())
            return 0;

        int result = INT_MAX;

        vector<vector<int>> reordered_edges;

        for (auto& entry : edges)
        {
            int node1 = entry[0];
            int node2 = entry[1];
            int time  = entry[2];

            reordered_edges.push_back( {time, node1, node2} );
        }

        /* Sort in ASCENDING order */
        sort(reordered_edges.begin(), reordered_edges.end());

        int max_time = reordered_edges.back()[0];

        int L = 0;
        int R = max_time;

        while (L <= R)
        {
            int mid = L + (R - L) / 2;

            auto iter = upper_bound(reordered_edges.begin(), reordered_edges.end(), mid, [](int value, const vector<int>& curr_edge) {
                return value < curr_edge[0];
            });

            int idx_of_iter = iter - reordered_edges.begin();

            vector<vector<int>> subarray_of_reordered_edges;
            for (int i = idx_of_iter; i < reordered_edges.size(); i++)
            {
                subarray_of_reordered_edges.push_back( {reordered_edges[i][1], reordered_edges[i][2]} );
            }

            int components = countComponents(n, subarray_of_reordered_edges);

            if (components >= k)
            {
                R = mid - 1;
                result = min(result, mid);
            }
            else
                L = mid + 1;
        }

        return result;
    }


private:
    int countComponents(int n, vector<vector<int>>& edges)
    {
        if (edges.empty())
            return n;

        vector<int> parent(n);
        vector<int> rank(n, 1);

        // Vector parent = [0, 1, 2, ..., n-1]
        iota(parent.begin(), parent.end(), 0);
        /*
           Iota equivalent to this:

           for (int i = 0; i < n; i++)
               parent.push_back(i);
        */

        int components = n;
        for (const auto& edge : edges)
        {
            int node_1 = edge[0];
            int node_2 = edge[1];

            if (union_components(node_1, node_2, parent, rank))
                components--;
        }

        return components;
    }

    int find_root(int node, vector<int>& parent)
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

    bool union_components(int node_1, int node_2, vector<int>& parent, vector<int>& rank)
    {
        int root1 = find_root(node_1, parent);
        int root2 = find_root(node_2, parent);

        if (root1 == root2)
            return false;

        if (rank[root1] < rank[root2])
            swap(root1, root2);

        // Union component rooted in root2 with component rooted in root1
        parent[root2] = root1;
        rank[root1]  += rank[root2];

        return true;
    }
};
