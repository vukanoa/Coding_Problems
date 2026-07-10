/*
    ============
    === HARD ===
    ============

    ==========================================
    3534) Path Existence Queries in a Graph II
    ==========================================

    ============
    Description:
    ============

    You are given an integer n representing the number of nodes in a graph,
    labeled from 0 to n - 1.

    You are also given an integer array nums of length n and an integer
    maxDiff.

    An undirected edge exists between nodes i and j if the absolute difference
    between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]|
    <= maxDiff).

    You are also given a 2D integer array queries. For each queries[i] = [ui,
    vi], find the minimum distance between nodes ui and vi. If no path exists
    between the two nodes, return -1 for that query.

    Return an array answer, where answer[i] is the result of the ith query.

    =====
    Note: The edges between the nodes are unweighted. 
    =====

    ================================================================================================================
    FUNCTION: vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries);
    ================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
    Output: [1,1]

    --- Example 2 ---
    Input: n = 5, nums = [5,3,1,9,10], maxDiff = 2, queries = [[0,1],[0,2],[2,3],[4,3]]
    Output: [1,2,-1,1]

    --- Example 3 ---
    Input: n = 3, nums = [3,6,1], maxDiff = 1, queries = [[0,0],[0,1],[1,2]]
    Output: [0,-1,-1]
    Explanation:
    There are no edges between any two nodes because:
        Nodes 0 and 1: |nums[0] - nums[1]| = |3 - 6| = 3 > 1
        Nodes 0 and 2: |nums[0] - nums[2]| = |3 - 1| = 2 > 1
        Nodes 1 and 2: |nums[1] - nums[2]| = |6 - 1| = 5 > 1
    Thus, no node can reach any other node, and the output is [0, -1, -1].


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    0 <= nums[i] <= 10^5
    0 <= maxDiff <= 10^5
    1 <= queries.length <= 10^5
    queries[i] == [ui, vi]
    0 <= ui, vi < n

*/

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Binary Lifting)

*/

/* Time  Beats: 53.95% */
/* Space Beats: 98.68% */

/* Time  Complexity: O(N * logN  +  Q * logN) */
/* Space Complexity: O(N * logN  +  Q       ) */
class Solution {
public:
    static constexpr int LOG = 18;
    static constexpr int MAX_NODES = 1e5;

    int up[LOG][MAX_NODES];
    int sorted_idx[MAX_NODES];

    pair<int, int> pairs_val_and_idx[MAX_NODES];

    // Returns minimum jumps required to reach v from u
    int minimum_jumps_required(int u, int v)
    {
        if (u == v)
            return 0;

        // Reachable in ONE jump
        if (up[0][u] >= v)
            return 1;

        // Unable to reach
        if (up[LOG - 1][u] < v)
            return -1;

        int jumps = 0;

        // Binary Lifting
        for (int j = LOG-1; j >= 0; j--)
        {
            if (up[j][u] < v)
            {
                jumps += (1 << j); // Jump 2^j times
                u = up[j][u];
            }
        }

        return jumps + 1;
    }

    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries)
    {
        const int Q = queries.size();

        // Store value with original index
        for (int i = 0; i < n; i++)
            pairs_val_and_idx[i] = {nums[i], i};

        // Sort by value
        sort(pairs_val_and_idx, pairs_val_and_idx + n);

        // Position of original indices in sorted array
        for (int i = 0; i < n; i++)
            sorted_idx[pairs_val_and_idx[i].second] = i;

        // Sliding Window
        int R = 0;
        for (int L = 0; L < n; L++)
        {
            while (R+1 < n  &&  abs(pairs_val_and_idx[R+1].first - pairs_val_and_idx[L].first) <= maxDiff)
                R++;

            up[0][L] = R;
        }

        // Build Binary Lifting Table
        for (int j = 1; j < LOG; j++) // 2^j ancestor
        {
            for (int v = 0; v < n; v++)
            {
                // 2^jth ancestor of vertex 'v'
                up[j][v] = up[j - 1][ up[j - 1][v] ];
            }
        }

        vector<int> result;
        for (const auto& q : queries)
        {
            int u = sorted_idx[q[0]];
            int v = sorted_idx[q[1]];

            if (u > v)
                swap(u, v);

            result.push_back(minimum_jumps_required(u, v));
        }

        return result;
    }
};
