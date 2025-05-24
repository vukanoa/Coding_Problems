/*
    ============
    === HARD ===
    ============

    ===========================
    3544) Subtree Inversion Sum
    ===========================

    ============
    Description:
    ============

    You are given an undirected tree rooted at node 0, with n nodes numbered
    from 0 to n - 1. The tree is represented by a 2D integer array edges of
    length n - 1, where edges[i] = [ui, vi] indicates an edge between nodes ui
    and vi.

    You are also given an integer array nums of length n, where nums[i]
    represents the value at node i, and an integer k.

    You may perform inversion operations on a subset of nodes subject to the
    following rules:

        + Subtree Inversion Operation:

            + When you invert a node, every value in the

            + rooted at that node is multiplied by -1.

        + Distance Constraint on Inversions:

            + You may only invert a node if it is "sufficiently far" from any
              other inverted node.

            + Specifically, if you invert two nodes a and b such that one is an
              ancestor of the other (i.e., if LCA(a, b) = a or LCA(a, b) = b),
              then the distance (the number of edges on the unique path between
              them) must be at least k.

    Return the maximum possible sum of the tree's node values after applying
    inversion operations.

    ==============================================================================================
    FUNCTION: long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k);
    ==============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], nums = [4,-8,-6,3,7,-2,5], k = 2
    Output: 27
    Explanation:
    Apply inversion operations at nodes 0, 3, 4 and 6.
    The final nums array is [-4, 8, 6, 3, 7, 2, 5], and the total sum is 27.


    --- Example 2 ---
    Input: edges = [[0,1],[1,2],[2,3],[3,4]], nums = [-1,3,-2,4,-5], k = 2
    Output: 9
    Explanation:
        Apply the inversion operation at node 4.
        The final nums array becomes [-1, 3, -2, 4, 5], and the total sum is 9


    --- Example 3 ---
    Input: edges = [[0,1],[0,2]], nums = [0,-1,-2], k = 3
    Output: 3
    Explanation:
    Apply inversion operations at nodes 1 and 2.


    *** Constraints ***
    2 <= n <= 5 * 10^4
    edges.length == n - 1
    edges[i] = [ui, vi]
    0 <= ui, vi < n
    nums.length == n
    -5 * 10^4 <= nums[i] <= 5 * 10^4
    1 <= k <= 50
    The input is generated such that edges represents a valid tree.

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 7.41% */
/* Space Beats: 9.35% */

/* Time  Complexity: O(N * k) */
/* Space Complexity: O(N * k) */
class Solution {
private:
    vector<vector<vector<long long>>> memo;

public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<vector<int>> adj_list(N);
        for (const auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }

        vector<int> parent(N, -1);

        // memo[node][since_last][flip_flag] = result
        memo = vector<vector<vector<long long>>>(N, vector<vector<long long>>(k + 1, vector<long long>(2, LLONG_MIN)));
        // or (both are fine)
        // memo.assign(N, vector<vector<long long>>(k + 1, vector<long long>(2, LLONG_MIN)));

        return dfs(0, k, 0, k, nums, adj_list, parent);
    }

private:
    long long dfs(int curr_node,
                  int since_last,
                  int flip_flag,
                  int max_k,
                  const vector<int>& nums,
                  const vector<vector<int>>& adj_list,
                  vector<int>& parent)
    {
        if (memo[curr_node][since_last][flip_flag] != LLONG_MIN)
            return memo[curr_node][since_last][flip_flag];

        long long no_flip = flip_flag ? -nums[curr_node] : nums[curr_node];
        long long if_flip = -no_flip;

        for (const int& neighbor : adj_list[curr_node])
        {
            if (neighbor == parent[curr_node])
                continue;

            parent[neighbor] = curr_node;
            no_flip += dfs(neighbor, min(since_last + 1, max_k), flip_flag, max_k, nums, adj_list, parent);

            if (since_last == max_k)
            {
                if_flip += dfs(neighbor, 1, !flip_flag, max_k, nums, adj_list, parent);
            }
        }

        if (since_last == max_k)
            memo[curr_node][since_last][flip_flag] = max(no_flip, if_flip);
        else
            memo[curr_node][since_last][flip_flag] = no_flip;

        return memo[curr_node][since_last][flip_flag];
    }
};
