/*
    ============
    === HARD ===
    ============

    ========================================================
    3530) Maximum Profit from Valid Topological Order in DAG
    ========================================================

    ============
    Description:
    ============

    You are given a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to
    n - 1, represented by a 2D array edges, where edges[i] = [ui, vi] indicates
    a directed edge from node ui to vi. Each node has an associated score given
    in an array score, where score[i] represents the score of node i.

    You must process the nodes in a valid topological order. Each node is
    assigned a 1-based position in the processing order.

    The profit is calculated by summing up the product of each node's score and
    its position in the ordering.

    Return the maximum possible profit achievable with an optimal topological
    order.

    A topological order of a DAG is a linear ordering of its nodes such that
    for every directed edge u → v, node u comes before v in the ordering.

    ===============================================================================
    FUNCTION: int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, edges = [[0,1]], score = [2,3]
    Output: 8

    --- Example 2 ---
    Input: n = 3, edges = [[0,1],[0,2]], score = [1,6,3]
    Output: 25


    *** Constraints ***
    1 <= n == score.length <= 22
    1 <= score[i] <= 10^5
    0 <= edges.length <= n * (n - 1) / 2
    edges[i] == [ui, vi] denotes a directed edge from ui to vi.
    0 <= ui, vi < n
    ui != vi
    The input graph is guaranteed to be a DAG.
    There are no duplicate edges.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.33% */
/* Space Beats: 16.67% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N)       */
class Solution_Memo {
private:
    vector<int> need;
    vector<int> memo;

    vector<int> score;
    int n;

public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score)
    {
        need.assign(n, 0);
        memo.assign(1 << n, -1);

        this->score = score;
        this->n = n;

        for (auto& e : edges)
        {
            int src = e[0];
            int dst = e[1];

            need[dst] |= (1 << src);
        }

        // memo[5] represents: memo[000..00101]
        // I.e. when node_2 and node_0 are the only processed, max score is: X
        return solve(0);
    }

private:
    int solve(int mask)
    {
        if (memo[mask] != -1)
            return memo[mask];

        memo[mask] = 0;

        // "position in the processing order"
        int position = (__builtin_popcount(mask) + 1);

        for (int i = 0; i < n; i++)
        {
            if (((mask >> i) & 1) == 0 && (need[i] & mask) == need[i])
            {
                int new_mask = mask | (1 << i);
                int gain     = score[i] * position;

                int total    = gain + solve(new_mask);

                memo[mask] = max(memo[mask], total);
            }
        }

        return memo[mask];
    }
};
