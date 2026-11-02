/*
    ============
    === HARD ===
    ============

    ============================================
    4100) Minimum Cost Path With Even XOR Parity
    ============================================

    ============
    Description:
    ============

    You are given a tree with n nodes numbered from 0 to n - 1, represented by
    a 2D integer array edges. Each edges[i] = [ui, vi, ci] represents an edge
    between nodes ui and vi with cost ci.

    You are also given an integer array values of length n, where values[i] is
    the value of node i.

    A path between two distinct nodes is Balanced-XOR if the bitwise XOR of the
    values of all nodes on the path, including both endpoints, has an even
    number of set bits.

    The cost of a path is the sum of its edge costs.

    Return the minimum cost of a Balanced-XOR path. If no such path exists,
    return -1.

    The number 0 has zero set bits.

    =================================================================================
    FUNCTION: int minActivationCost(vector<vector<int>>& edges, vector<int>& values);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1,4],[0,2,6],[0,3,3],[3,4,5]], values = [3,1,7,1,3]
    Output: 7
    Explanation:
    Balanced-XOR Path       XOR Value               Total Cost
    1 - 0 - 2            1 XOR 3 XOR 7       = 5    4 + 6 = 10
    1 - 0 - 3            1 XOR 3 XOR 1       = 3    4 + 3 = 7
    1 - 0 - 3 - 4        1 XOR 3 XOR 1 XOR 3 = 0    4 + 3 + 5 = 12
    2 - 0 - 3            7 XOR 3 XOR 1       = 5    6 + 3 = 9
    2 - 0 - 3 - 4        7 XOR 3 XOR 1 XOR 3 = 6    6 + 3 + 5 = 14

    The minimum cost is 7, achieved by the path 1 - 0 - 3. Thus, the answer is 7.


    --- Example 2 ---
    Input: edges = [[0,1,5],[1,2,10]], values = [1,7,3]
    Output: 5
    Explanation:
    Balanced-XOR Path    XOR Value           Total Cost
    0 - 1               1 XOR 7       = 6    5
    0 - 1 - 2           1 XOR 7 XOR 3 = 5    5 + 10 = 15

    The minimum cost is 5, achieved by the path 0 - 1. Thus, the answer is 5.


    --- Example 3 ---
    Input: edges = [[0,1,5],[0,2,7],[0,3,9]], values = [1,3,5,9]
    Output: -1
    Explanation:
        Every path between two distinct nodes has an XOR value with an odd
        number of set bits. Therefore, no Balanced-XOR path exists, so the
        answer is -1.


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i] = [ui, vi, ci]
        0 <= ui, vi <= n - 1
        1 <= ci <= 10^9
    values.length == n
    1 <= values[i] <= 10^9
    edges represents a valid tree.

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minActivationCost(vector<vector<int>>& edges, vector<int>& values)
    {
        const int n = values.size();
        long long result = INT_MAX;

        // min 0-1 edge starting at each node with 0 parity
        vector<long long> best_from(n, INT_MAX);

        for (const auto& edge : edges)
        {
            long long u = edge[0];
            long long v = edge[1];
            long long w = edge[2];

            int parity_u = __builtin_parity(values[u]);
            int parity_v = __builtin_parity(values[v]);

            if (parity_u == parity_v)
            {
                result = min(result, w);
            }
            else
            {
                int zero_node = (parity_u == 0) ? u : v;

                //                   1   ---   0   ---   1
                //                   ^         ^^^^^^^^^^^
                //                   |              |     
                //                   w    +     best_from[zero_node]
                result = min(result, w + best_from[zero_node]);


                best_from[zero_node] = min(best_from[zero_node], w);
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};
