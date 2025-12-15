/*
    ============
    === HARD ===
    ============

    =====================================
    3715) Sum of Perfect Square Ancestors
    =====================================

    ============
    Description:
    ============


    You are given an integer n and an undirected tree rooted at node 0 with n
    nodes numbered from 0 to n - 1. This is represented by a 2D array edges of
    length n - 1, where edges[i] = [ui, vi] indicates an undirected edge
    between nodes ui and vi.

    You are also given an integer array nums, where nums[i] is the positive
    integer assigned to node i.

    Define a value ti as the number of ancestors of node i such that the
    product nums[i] * nums[ancestor] is a perfect square.

    Return the sum of all ti values for all nodes i in range [1, n - 1].

    =====
    Note: In a rooted tree, the ancestors of node i are all nodes on the path 
          from node i to the root node 0, excluding i itself.
    =====

    =========================================================================================
    FUNCTION: long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums);
    =========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2]], nums = [2,8,2]
    Output: 3

    --- Example 2 ---
    Thus, the total number of valid ancestor pairs across all non-root nodes is 1 + 2 = 3.

    --- Example 3 ---
    Input: n = 3, edges = [[0,1],[0,2]], nums = [1,2,4]
    Output: 1

    --- Example 4 ---
    Input: n = 4, edges = [[0,1],[0,2],[1,3]], nums = [1,2,9,4]
    Output: 2


    *** Constraints ***
    1 <= n <= 10^5
    edges.length == n - 1
    edges[i] = [ui, vi]
    0 <= ui, vi <= n - 1
    nums.length == n
    1 <= nums[i] <= 10^5
    The input is generated such that edges represents a valid tree.

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

/* Time  Beats: 51.95% */
/* Space Beats: 44.92% */

/* Time  Complexity: O(N * sqrt(M)) */
/* Space Complexity: O(N + M)       */
class Solution {
public:
    const int MAX = 1e5;

    long long sumOfAncestors(int n,
                             vector<vector<int>>& edges,
                             vector<int>& nums)
    {
        vector<vector<int>> adj_list(n);
        /* Undirected Edges */
        for (const auto& e : edges)
        {
            adj_list[e[0]].push_back(e[1]);
            adj_list[e[1]].push_back(e[0]);
        }

        // Compute square-free version of each number
        vector<long long> dp(MAX + 1);
        for (int i = 1; i <= MAX; i++)
            dp[i] = i;

        for (int i = 2; i * i <= MAX; i++)
        {
            long long sq = 1LL * i * i;
            for (int j = sq; j <= MAX; j += sq)
            {
                while (dp[j] % sq == 0)
                    dp[j] /= sq;
            }
        }

        vector<long long> square_free_val(n);
        for (int i = 0; i < n; i++)
            square_free_val[i] = dp[nums[i]];

        long long result = 0;
        unordered_map<long long, int> freq;

        dfs(0, -1, result, square_free_val, adj_list, freq);

        return result;
    }

private:
    void dfs(int node,
             int parent,
             long long& result,
             vector<long long>& square_free_val,
             vector<vector<int>>& adj_list,
             unordered_map<long long, int>& freq)
    {
        if (node != 0) 
            result += freq[square_free_val[node]];

        freq[square_free_val[node]]++;

        for (int neighbor : adj_list[node])
        {
            if (neighbor == parent)
                continue;

            dfs(neighbor, node, result, square_free_val, adj_list, freq);
        }

        freq[square_free_val[node]]--;
    }
};
