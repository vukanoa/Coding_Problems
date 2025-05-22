/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3543) Maximum Weighted K-Edge Path
    ==================================

    ============
    Description:
    ============

    You are given an integer n and a Directed Acyclic Graph (DAG) with n nodes
    labeled from 0 to n - 1. This is represented by a 2D array edges, where
    edges[i] = [ui, vi, wi] indicates a directed edge from node ui to vi with
    weight wi.

    You are also given two integers, k and t.

    Your task is to determine the maximum possible sum of edge weights for any
    path in the graph such that:

        + The path contains exactly k edges.

        + The total sum of edge weights in the path is strictly less than t.

    Return the maximum possible sum of weights for such a path. If no such path
    exists, return -1.

    =========================================================================
    FUNCTION: int maxWeight(int n, vector<vector<int>>& edges, int k, int t);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1,1],[1,2,2]], k = 2, t = 4
    Output: 3
    Explanation:
    The only path with k = 2 edges is 0 -> 1 -> 2 with weight 1 + 2 = 3 < t.
    Thus, the maximum possible sum of weights less than t is 3.


    --- Example 2 ---
    Input: n = 3, edges = [[0,1,2],[0,2,3]], k = 1, t = 3
    Output: 2
    Explanation:
    There are two paths with k = 1 edge:
        0 -> 1 with weight 2 < t.
        0 -> 2 with weight 3 = t, which is not strictly less than t.
    Thus, the maximum possible sum of weights less than t is 2.


    --- Example 3 ---
    Input: n = 3, edges = [[0,1,6],[1,2,8]], k = 1, t = 6
    Output: -1
    Explanation:
    There are two paths with k = 1 edge:
        0 -> 1 with weight 6 = t, which is not strictly less than t.
        1 -> 2 with weight 8 > t, which is not strictly less than t.
    Since there is no path with sum of weights strictly less than t, the answer
    is -1.


    *** Constraints ***
    1 <= n <= 300
    0 <= edges.length <= 300
    edges[i] = [ui, vi, wi]
    0 <= ui, vi < n
    ui != vi
    1 <= wi <= 10
    0 <= k <= 300
    1 <= t <= 600
    The input graph is guaranteed to be a DAG.
    There are no duplicate edges.

*/

#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 62.50% */
/* Space Beats: 26.82% */

/* Time  Complexity: O(n * k * t) */
/* Space Complexity: O(n * k * t) */
class Solution {
private:
    vector<unordered_map<int, int>> adj_list;
    vector<vector<unordered_map<int, int>>> memo;

public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t)
    {
        build_adjacency_list(edges, n);

        memo.assign(n, vector<unordered_map<int, int>>(k + 1));

        int result = -1;
        for (int vertex = 0; vertex < n; vertex++)
        {
            result = max(result, solve(vertex, k, 0, t));
        }

        return result;
    }

private:
    int solve(int vertex, int k, int sum, int t)
    {
        if (k == 0)
            return sum < t ? sum : -1;

        if (memo[vertex][k].count(sum))
            return memo[vertex][k][sum];

        int max_sum = -1;
        for (const auto& [neighbor, weight] : adj_list[vertex])
        {
            int new_sum = sum + weight;

            if (new_sum >= t)
                continue;

            int result = solve(neighbor, k - 1, new_sum, t);
            if (result != -1)
                max_sum = max(max_sum, result);
        }

        return memo[vertex][k][sum] = max_sum;
    }

    void build_adjacency_list(const vector<vector<int>>& edges, int n)
    {
        adj_list.assign(n, unordered_map<int, int>());

        for (const auto& entry : edges)
        {
            int u = entry[0];
            int v = entry[1];
            int w = entry[2];

            adj_list[u][v] = w;
        }
    }
};
