/*
    ============
    === HARD ===
    ============

    ==================================
    3123) Find Edges in Shortest Paths
    ==================================

    ============
    Description:
    ============

    You are given an undirected weighted graph of n nodes numbered from 0 to
    n - 1.

    The graph consists of m edges represented by a 2D array edges, where
    edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai
    and bi with weight wi.

    Consider all the shortest paths from node 0 to node n - 1 in the graph.

    You need to find a boolean array answer where answer[i] is true if the edge
    edges[i] is part of at least one shortest path. Otherwise, answer[i] is
    false.

    Return the array answer.

    =====
    Note: that the graph may not be connected.
    =====

    =====================================================================
    FUNCTION: vector<bool> findAnswer(int n, vector<vector<int>>& edges);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5,2]]
    Output: [true,true,true,false,true,true,true,false]
    Explanation:
    The following are all the shortest paths between nodes 0 and 5:
        The path 0 -> 1 -> 5: The sum of weights is 4 + 1 = 5.
        The path 0 -> 2 -> 3 -> 5: The sum of weights is 1 + 1 + 3 = 5.
        The path 0 -> 2 -> 3 -> 1 -> 5: The sum of weights is 1 + 1 + 2 + 1 = 5.


    --- Example 2 ---
    Input: n = 4, edges = [[2,0,1],[0,1,1],[0,3,4],[3,2,2]]
    Output: [true,false,false,true]
    Explanation:
    There is one shortest path between nodes 0 and 3, which is the path
    0 -> 2 -> 3 with the sum of weights 1 + 2 = 3.


    *** Constraints ***
    2 <= n <= 5 * 10^4
    m == edges.length
    1 <= m <= min(5 * 104, n * (n - 1) / 2)
    0 <= ai, bi < n
    ai != bi
    1 <= wi <= 10^5
    There are no repeated edges.

*/

#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is much easier than you think, however this Solution is not easy
    to come up with.

    Since we need to know what is the minimum distance between node 0 and n-1
    we use "Dijkstra's Algorithm".

    However, that is not enough, since after we've found that min_dist we need
    to try and proclaim if some edge was participating in our min_dist path.

    If it has, then we need to put "true" for that edge in our "answer" vector
    that we're going to return.

    But how are we going to do that?
    Calculating min_dist alone won't help us.


    I'm going to draw "Example 1" using ASCII characters, so that you can see
    the beauty of this Solution:

            4       3
        0 ----- 1 ----- 4
        |       | \     |
        |       |  \    |
       1|      2|   \1  | 2
        |       |    \  |
        |       |     \ |
        |       |      \|
        2 ----- 3 ----- 5
            1       3


    I'm going to draw "Example 2" using ASCII characters, so that you can see
    the beauty of this Solution:



                            1
                        0 ----- 1
                        |\
                        | \
                        |  \
                       1|   \ 4
                        |    \
                        |     \
                        |      \
                        2 ----- 3
                            2


    If we begin at node 0, we want to see what is the MIN_DIST to get to each
    other connected node.

    Specifically:

        source_dist = [0 1 1 3]
                       0 1 2 3

    This array indicates that:

        a) Starting at "node 0", min_dist to get to "node 0" is 0.
        b) Starting at "node 0", min_dist to get to "node 1" is 1.
        c) Starting at "node 0", min_dist to get to "node 2" is 1.
        d) Starting at "node 0", min_dist to get to "node 3" is 3.

    If you've "memorized" Dijkstra without much thought, then this may get
    over your head.

    Dijkstra can calculate min_dist to ANY(or every) node starting at ANY node.
    This is ABSOLUTELY CRUCIAL!!!


    Only if you understand that you have a chance of coming up with this
    Solution.

    Since we've obtained this:


                             ------- "absolute_min_dist"
                             |
                             v
        source_dist = [0 1 1 3]
                       0 1 2 3

    which represents min_dist to any node STARTING at node 0, how can we know
    if some edge participated in our shortest path?

    Especially since there can be multiple shortest paths as it is the case in
    "Example 1".


    The Solution is the following:

    First, we need to calculate min_dist to every node STARTING AT "node n-1".
    Why?

    You'll se in a bit.

    We are going to iterate through each edge and do this:

        edges = [[2,0,1],  [0,1,1],  [0,3,4],   [3,2,2]]
                    0         1         2          3


                            1
                        0 ----- 1
                        |\
                        | \
                        |  \
                       1|   \ 4
                        |    \
                        |     \
                        |      \
                        2 ----- 3
                            2


    0th edge is this:  [2, 0, 1]   // In form {start_node, end_node, time}

    From 2 to 0, needed time is 1.
    But how do we know if this edge PARTICIPATED INDEED in our Shortest Path?

    if: from time from 2 to 0(i.e. "time 1") + SHORTEST TIME FROM "node n-1" to
    "node 0"(in this case) is EQUAL to "absolute_min_dist".

    Also, since edges are UNDIRECTED, we try:

    if: from time from 0 to 2(i.e. "time 1") + SHORTEST TIME FROM "node n-1" to
    "node 2"(in this case) is EQUAL to "absolute_min_dist".

    If that's the case then we're certain this edge DID INDEED participate in
    our Shortest Path.


    Go through the code once and I'm sure you'll get it.

*/

/* Time  Beats: 52.79% */
/* Space Beats: 22.91% */

/* Time  Complexity: O(E + V * logV) */
/* Space Complexity: O(E + V)        */
class Solution {
private:
    vector<unordered_map<int, int>> adj_list;

public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges)
    {
        vector<bool> answer;

        /*Build an Adjacency List */
        adj_list.assign(n, unordered_map<int, int>());

        for (const auto& entry : edges)
        {
            const int u = entry[0];
            const int v = entry[1];
            const int time = entry[2];

            adj_list[u][v] = time;
            adj_list[v][u] = time;
        }

        vector<int> source_dist = dijkstra(  0, n);
        vector<int> target_dist = dijkstra(n-1, n);

        if (source_dist[n - 1] == INT_MAX) // If we CANNOT reach n-1 from 0
            return vector<bool>(edges.size(), false);

        int min_dist = source_dist[n - 1];

        for (const auto& entry : edges)
        {
            const int u = entry[0];
            const int v = entry[1];
            const int time = entry[2];

            if (
                (
                 source_dist[u] != INT_MAX &&
                 target_dist[v] != INT_MAX &&
                 source_dist[u] + time + target_dist[v] == min_dist
                )
                    ||
                (
                 source_dist[v] != INT_MAX &&
                 target_dist[u] != INT_MAX &&
                 source_dist[v] + time + target_dist[u] == min_dist
                )
               )
            {
                answer.push_back(true);
            }
            else
            {
                answer.push_back(false);
            }
        }

        return answer;
    }

private:
    vector<int> dijkstra(int source, int n)
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
