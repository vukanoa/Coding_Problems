/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3650) Minimum Cost Path with Edge Reversals
    ===========================================

    ============
    Description:
    ============

    You are given a directed, weighted graph with n nodes labeled from 0 to
    n - 1, and an array edges where edges[i] = [ui, vi, wi] represents a
    directed edge from node ui to node vi with cost wi.

    Each node ui has a switch that can be used at most once: when you arrive
    at ui and have not yet used its switch, you may activate it on one of its
    incoming edges vi → ui reverse that edge to ui → vi and immediately traverse it.

    The reversal is only valid for that single move, and using a reversed edge
    costs 2 * wi.

    Return the minimum total cost to travel from node 0 to node n - 1. If it
    is not possible, return -1.

    =========================================================
    FUNCTION: int minCost(int n, vector<vector<int>>& edges);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
    Output: 5
    Explanation:
    Use the path 0 → 1 (cost 3).
    At node 1 reverse the original edge 3 → 1 into 1 → 3 and traverse it at
    cost 2 * 1 = 2. Total cost is 3 + 2 = 5.

    --- Example 2 ---
    Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
    Output: 3
    Explanation:
    No reversal is needed. Take the path 0 → 2 (cost 1), then 2 → 1 (cost 1),
    then 1 → 3 (cost 1). Total cost is 1 + 1 + 1 = 3.


    *** Constraints ***
    2 <= n <= 5 * 10^4
    1 <= edges.length <= 10^5
    edges[i] = [ui, vi, wi]
    0 <= ui, vi <= n - 1
    1 <= wi <= 1000

*/

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Classic Dijkstra)

*/

/* Time  Beats: 24.68% */
/* Space Beats: 24.43% */

/* Time  Complexity: O(E * logV) */
/* Space Complexity: O(E + V)    */
class Solution {
private:
    unordered_map<int, vector<pair<int, long long>>> adj_list;

public:
    int minCost(int n, vector<vector<int>>& edges)
    {
        long long result = 0LL;

        // Build
        build_adjacency_list(n, edges);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;
        for (const auto& pair : adj_list[0])
            min_heap.push( {pair.second, pair.first} );

        vector<bool> visited(n, false);
        visited[0] = true;

        // Dijkstra
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            if (top.second == n-1)
                return top.first;

            
            if (visited[top.second])
                continue;

            visited[top.second] = true;

            for (auto& pair : adj_list[top.second])
            {
                pair.second += top.first;
                min_heap.push( {pair.second, pair.first} );
            }
        }

        return -1;
    }

private:
    void build_adjacency_list(int& n, const vector<vector<int>>& edges)
    {
        for (const auto& entry : edges)
        {
            const int u = entry[0];
            const int v = entry[1];
            const int w = entry[2];

            adj_list[u].push_back( {v,   w} );
            adj_list[v].push_back( {u, 2*w} ); // Double the cost for reverse
        }
    }
};
