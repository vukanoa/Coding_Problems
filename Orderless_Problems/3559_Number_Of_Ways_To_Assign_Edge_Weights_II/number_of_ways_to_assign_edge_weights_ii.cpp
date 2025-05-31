/*
    ============
    === HARD ===
    ============

    ==============================================
    3559) Number of Ways to Assign Edge Weights II
    ==============================================

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

    You are given a 2D integer array queries. For each queries[i] = [ui, vi],
    determine the number of ways to assign weights to edges in the path such
    that the cost of the path between ui and vi is odd.

    Return an array answer, where answer[i] is the number of valid assignments
    for queries[i].

    Since the answer may be large, apply modulo 109 + 7 to each answer[i].

    =====
    Note: For each query, disregard all edges not in the path between node ui
          and vi.
    =====

    ==================================================================================================
    FUNCTION: vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries);
    ==================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[1,2]], queries = [[1,1],[1,2]]
    Output: [0,1]
    Explanation:
        Query [1,1]: The path from Node 1 to itself consists of no edges, so
                     the cost is 0. Thus, the number of valid assignments is 0.
        Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2).
                     Assigning weight 1 makes the cost odd, while 2 makes it
                     even. Thus, the number of valid assignments is 1.


    --- Example 2 ---
    Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]
    Output: [2,1,4]
    Explanation:
        Query [1,4]: The path from Node 1 to Node 4 consists of two edges
                     (1 → 3 and 3 → 4). Assigning weights (1,2) or (2,1)
                     results in an odd cost. Thus, the number of valid
                     assignments is 2.

        Query [3,4]: The path from Node 3 to Node 4 consists of one edge
                     (3 → 4). Assigning weight 1 makes the cost odd, while 2
                     makes it even. Thus, the number of valid assignments is 1.

        Query [2,5]: The path from Node 2 to Node 5 consists of three edges
                     (2 → 1, 1 → 3, and 3 → 5). Assigning (1,2,2), (2,1,2),
                     (2,2,1), or (1,1,1) makes the cost odd. Thus, the number
                     of valid assignments is 4.


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i] == [ui, vi]
    1 <= queries.length <= 10^5
    queries[i] == [ui, vi]
    1 <= ui, vi <= n
    edges represents a valid tree.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.04% */
/* Space Beats: 42.54% */

/* Time  Complexity: O((N + Q) * logN) */
/* Space Complexity: O(N * logN)       */
class Solution {
public:
    const int MOD = 1e9 + 7;
    const int MAX_BITS = 21;

    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries)
    {
        const int N = edges.size() + 1;
        const int QUERIES_SIZE = queries.size();

        vector<vector<int>> adj_list(N + 1);
        for (auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }

        vector<int> depths(N + 1, 0);
        vector<vector<int>> dp(N + 1, vector<int>(MAX_BITS, 0));

        dfs(1, -1, depths, dp, adj_list);

        vector<int> answer;
        for (int i = 0; i < QUERIES_SIZE; i++)
        {
            int u = queries[i][0];
            int v = queries[i][1];

            if (u == v)
            {
                answer.push_back(0);
            }
            else
            {
                int dist = find_distance(u, v, depths, dp);

                answer.push_back(modular_exponentiation(2, dist - 1));
            }
        }

        return answer;
    }

private:
    long long modular_exponentiation(long long base, long long exp)
    {
        long long result = 1;
        while (exp > 0)
        {
            if (exp & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;
            exp /= 2;
        }

        return result;
    }

    void dfs(int curr_node, int parent, vector<int>& depth, vector<vector<int>>& dp, vector<vector<int>>& adj)
    {
        depth[curr_node] = 1 + (parent == -1 ? 0 : depth[parent]);

        if (parent != -1)
            dp[curr_node][0] = parent;

        for (int j = 1; j < MAX_BITS; j++)
        {
            dp[curr_node][j] = dp[dp[curr_node][j - 1]][j - 1];
        }

        for (auto& child : adj[curr_node])
        {
            if (child != parent)
            {
                dfs(child, curr_node, depth, dp, adj);
            }
        }
    }

    int find_distance(int x, int y, vector<int>& depth, vector<vector<int>>& dp)
    {
        int lca = find_LCA(x, y, depth, dp);
        return depth[x] + depth[y] - 2 * depth[lca];
    }

    int find_LCA(int x, int y, vector<int>& depth, vector<vector<int>>& dp)
    {
        if (depth[x] > depth[y])
            swap(x, y); // So that x is ALWAYS SMALLER OR EQUAL to y

        int diff = depth[y] - depth[x];
        for (int i = 0; i < MAX_BITS; i++)
        {
            if (diff & (1 << i))
                y = dp[y][i];
        }

        if (x == y)
            return x;

        for (int i = MAX_BITS-1; i >= 0; i--)
        {
            if (dp[x][i] != dp[y][i])
            {
                x = dp[x][i];
                y = dp[y][i];
            }
        }

        return dp[x][0];
    }
};
