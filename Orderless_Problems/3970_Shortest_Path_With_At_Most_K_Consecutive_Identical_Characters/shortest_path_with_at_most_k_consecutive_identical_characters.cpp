/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3970) Shortest Path With At Most K Consecutive Identical Characters
    ===================================================================

    ============
    Description:
    ============

    You are given an integer n representing the number of nodes in a directed
    weighted graph, numbered from 0 to n - 1. This is represented by a 2D
    integer array edges, where edges[i] = [ui, vi, wi] represents a directed
    edge from node ui to node vi with weight wi.

    You are also given a string labels of length n, where labels[i] is the
    character assigned to node i, and an integer k.

    Return the minimum total edge weight of a path from node 0 to node n - 1
    such that the concatenation of the labels of the nodes along the path
    contains at most k consecutive identical characters. If no valid path
    exists, return -1.

    ====================================================================================
    FUNCTION: int shortestPath(int n, vector<vector<int>>& edges, string labels, int k);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

#include <climits>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's a Dijkstra with Extra State. Nothing special if you already know
    Dijkstra.

*/

/* Time  Beats: 46.71% */
/* Space Beats: 20.41% */

/* Time  Complexity: O((V * k + E * k) log(V * k)) */
/* Space Complexity: O(V * k + E)                  */
class Solution {
private:
    vector<vector<pair<int, int>>> adj_list;

    using ll = long long;

public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k)
    {
        long long result = INT_MAX;

        /* Build an Adjacency List */
        build_adjacency_list(edges, n);

        priority_queue<vector<ll>, vector<vector<ll>>, greater<>> min_heap;

        vector<vector<long long>> min_dist(n, vector<long long>(k+1, INT_MAX));

        min_dist[0][1] = 0;
        min_heap.push( {0, 0, 1} );// {distance, source_node, consecutive_chrs}

        while ( ! min_heap.empty())
        {
            auto vec = min_heap.top();
            min_heap.pop();

            long long curr_dist               = vec[0];
            long long src                     = vec[1];
            long long consecutive_ending_chrs = vec[2];

            if (curr_dist != min_dist[src][consecutive_ending_chrs])
                continue;

            for (const auto& [dst, weight] : adj_list[src])
            {
                int next_consecutive = 1;

                if (labels[src] == labels[dst])
                {
                    next_consecutive = consecutive_ending_chrs + 1;

                    if (next_consecutive > k)
                        continue;
                }

                if (curr_dist + weight >= min_dist[dst][next_consecutive])
                    continue;

                min_dist[dst][next_consecutive] = curr_dist + weight;
                min_heap.push( {curr_dist + weight, dst, next_consecutive} );
            }
        }

        for (int consecutive = 1; consecutive <= k; consecutive++)
            result = min(result, min_dist[n - 1][consecutive]);

        return result == INT_MAX ? -1 : result;
    }

private:
    void build_adjacency_list(const vector<vector<int>>& edges, int n)
    {
        adj_list.assign(n, {});

        for (const auto& edge : edges)
        {
            const int src    = edge[0];
            const int dst    = edge[1];
            const int weight = edge[2];

            adj_list[src].push_back( {dst, weight} );
        }
    }
};
