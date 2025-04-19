/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    3112) Minimum Time to Visit Disappearing Nodes
    ==============================================

    ============
    Description:
    ============

    There is an undirected graph of n nodes. You are given a 2D array edges,
    where edges[i] = [ui, vi, lengthi] describes an edge between node ui and
    node vi with a traversal time of lengthi units.

    Additionally, you are given an array disappear, where disappear[i] denotes
    the time when the node i disappears from the graph and you won't be able to
    visit it.

    Note that the graph might be disconnected and might contain multiple edges.

    Return the array answer, with answer[i] denoting the minimum units of time
    required to reach node i from node 0. If node i is unreachable from node 0
    then answer[i] is -1.

    =============================================================================================
    FUNCTION: vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear);
    =============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,1,5]
    Output: [0,-1,4]
    Explanation:
    We are starting our journey from node 0, and our goal is to find the
    minimum time required to reach each node before it disappears.

        For node 0, we don't need any time as it is our starting point.

        For node 1, we need at least 2 units of time to traverse edges[0].
        Unfortunately, it disappears at that moment, so we won't be able to
        visit it.

        For node 2, we need at least 4 units of time to traverse edges[2].


    --- Example 2 ---
    Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,3,5]
    Output: [0,2,3]
    Explanation:
    We are starting our journey from node 0, and our goal is to find the
    minimum time required to reach each node before it disappears.

        For node 0, we don't need any time as it is the starting point.

        For node 1, we need at least 2 units of time to traverse edges[0].

        For node 2, we need at least 3 units of time to traverse edges[0] and
        edges[1].



    --- Example 3 ---
    Input: n = 2, edges = [[0,1,1]], disappear = [1,1]
    Output: [0,-1]
    Explanation:
    Exactly when we reach node 1, it disappears.


    *** Constraints ***
    1 <= n <= 5 * 10%4
    0 <= edges.length <= 10%5
    edges[i] == [ui, vi, lengthi]
    0 <= ui, vi <= n - 1
    1 <= lengthi <= 10%5
    disappear.length == n
    1 <= disappear[i] <= 10%5

*/

#include <climits>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 21.45% */
/* Space Beats: 10.85% */

/* Time  Complexity: O(E + logV) */
/* Space Complexity: O(E + V)    */
class Solution {
private:
    vector<unordered_map<int, int>> adj_list;

public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear)
    {
        /*Build an Adjacency List */
        adj_list.assign(n, unordered_map<int, int>());

        for (const auto& entry : edges)
        {
            const int u = entry[0];
            const int v = entry[1];
            const int time = entry[2];

            if (u == v)
                continue;

            if (adj_list[u].find(v) != adj_list[u].end())
                adj_list[u][v] = min(adj_list[u][v], time);
            else
                adj_list[u][v] = time;

            if (adj_list[v].find(u) != adj_list[v].end())
                adj_list[v][u] = min(adj_list[v][u], time);
            else
                adj_list[v][u] = time;
        }

        vector<int> answer = dijkstra(0, n, disappear);

        for (int i = 0; i < n; i++)
        {
            if (answer[i] == INT_MAX)
                answer[i] = -1;
        }

        return answer;
    }

private:
    vector<int> dijkstra(int source, int n, vector<int>& disappear)
    {
        vector<int> dist(n, INT_MAX);
        dist[source] = 0;

        /* Comparator: by first INCREASING, by second DECREASING */
        auto comparator = [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first)
                return a.second < b.second;
            return a.first > b.first;
        };

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       decltype(comparator)> min_heap(comparator);


        min_heap.push( {0, source} );

        while ( ! min_heap.empty())
        {
            auto [curr_time, curr_node] = min_heap.top();
            min_heap.pop();

            // So that we do NOT go back to visited nodes
            if (curr_time > dist[curr_node])
                continue;

            for (const auto& [neighbor, time] : adj_list[curr_node])
            {
                int new_time = curr_time + time;

                if (new_time >= disappear[neighbor])
                    continue;

                if (new_time < dist[neighbor])
                {
                    dist[neighbor] = new_time;
                    min_heap.push( {new_time, neighbor} );
                }
            }
        }

        return dist;
    }
};
