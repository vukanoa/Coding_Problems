/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3558) Number of Ways to Assign Edge Weights I
    =============================================

    ============
    Description:
    ============

    There is an undirected tree with n nodes labeled from 1 to n, rooted at
    node 1. The tree is represented by a 2D integer array edges of length
    n - 1, where edges[i] = [ui, vi] indicates that there is an edge between
    nodes ui and vi.

    Initially, all edges have a weight of 0. You must assign each edge a weight
    of either 1 or 2.

    The cost of a path between any two nodes u and v is the total weight of all
    edges in the path connecting them.

    Select any one node x at the maximum depth. Return the number of ways to
    assign edge weights in the path from node 1 to x such that its total cost
    is odd.

    Since the answer may be large, return it modulo 10^9 + 7.

    =====
    Note: Ignore all edges not in the path from node 1 to x.
    =====

    =============================================================
    FUNCTION:  int assignEdgeWeights(vector<vector<int>>& edges);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[1,2]]
    Output: 1
    Explanation:
        The path from Node 1 to Node 2 consists of one edge (1 → 2).
        Assigning weight 1 makes the cost odd, while 2 makes it even. Thus,
        the number of valid assignments is 1.


    --- Example 2 ---
    Input: edges = [[1,2],[1,3],[3,4],[3,5]]
    Output: 2
    Explanation:
        The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node can be selected for processing.
        For example, the path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4).
        Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i] == [ui, vi]
    1 <= ui, vi <= n
    edges represents a valid tree.

*/

#include <unordered_map>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.18% */
/* Space Beats: 13.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int assignEdgeWeights(vector<vector<int>>& edges)
    {
        const int N = edges.size() + 1;    

        unordered_map<int, vector<int>> adj_list;

        for (auto& entry : edges)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        // Number of edges from 1 to X is "max_depth"
        int max_depth = 0;
        dfs(adj_list, 1, 0, max_depth, -1);

        return modular_exponentiation(2, max_depth - 1);
    }

private:
    void dfs(unordered_map<int, vector<int>>& adj_list, int node, int level, int& max_depth, int parent)
    {
        max_depth = max(max_depth, level);

        for (auto& child : adj_list[node])
        {
            if (child == parent)
                continue;

            dfs(adj_list, child, level+1, max_depth, node);
        }
    }

    // Needed numbers are too large to left shift.
    // It's basiclaly: (base^exp) % mod
    long long modular_exponentiation(long long base, long long exp)
    {
        long long result = 1;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;
            exp /= 2;
        }

        return result;
    }
};
