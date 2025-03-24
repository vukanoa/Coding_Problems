/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    1976) Number of Ways to Arrive at Destination
    =============================================

    ============
    Description:
    ============

    You are in a city that consists of n intersections numbered from 0 to n - 1
    with bi-directional roads between some intersections. The inputs are
    generated such that you can reach any intersection from any other
    intersection and that there is at most one road between any two
    intersections.

    You are given an integer n and a 2D integer array roads where
    roads[i] = [ui, vi, timei] means that there is a road between
    intersections ui and vi that takes timei minutes to travel.

    You want to know in how many ways you can travel from intersection 0 to
    intersection n - 1 in the shortest amount of time.

    Return the number of ways you can arrive at your destination in the
    shortest amount of time. Since the answer may be large, return it modulo
    10^9 + 7.

    ============================================================
    FUNCTION: int countPaths(int n, vector<vector<int>>& roads);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
    Output: 4
    Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
    The four ways to get there in 7 minutes are:
    - 0 ➝ 6
    - 0 ➝ 4 ➝ 6
    - 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
    - 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6

    Example 2:

    Input: n = 2, roads = [[1,0,10]]
    Output: 1
    Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.



    --- Example 2 ---
    Input: n = 2, roads = [[1,0,10]]
    Output: 1
    Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.



    *** Constraints ***
    1 <= n <= 200
    n - 1 <= roads.length <= n * (n - 1) / 2
    roads[i].length == 3
    0 <= ui, vi <= n - 1
    1 <= timei <= 10^9
    ui != vi
    There is at most one road connecting any two intersections.
    You can reach any intersection from any other intersection.

*/

#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    First, you absolutely MUST always look at the Constraints. This thing:

        1 <= timei <= 10^9

    is VERY VERY important.

    Edge cases are always difficult if you don't see such details. You'll get
    an Overflow.


    Other than that this is a pretty standard Dijkstra algorithm, however since
    we need to return the number of ways of reaching the destination, i.e. n-1
    node in shortest_time, we need to modify is a little bit.

    We'll keep two additional vectors of size n:

        1. shortest_time
        2. path_count

    It's important to note that we'll initialize "shortest_path" vector with
    LLONG_MAX, i.e. maximum values. (That's one of the reasons it was important
    to look at the Constraints of this problem)

    Each time we reach a node, we'll ask if the current time is LESS than the
    time we needed so far(if it was reached already).

    If it wasn't reached already, then the shortest_time will be LLONG_MAX,
    which is certainly more than the current time.


    Anyhow, if we are CHANGING the shortest_time for some node, how can we know
    what is the number of ways we can reach it in that time?

    It's actually pretty easy if you think about it.

    Since reaching this node with a new shortest_time is found, we can reach it
    as many time as we can the node we're coming from.
    (Read that again, slowly)

    For example:

             -- 0 ---
            /  / \   \
           /  /   \   \
          /  |    |    \
         /   |    |     \
        /    |    |     |
        1    2    3     4
        |    |    |     |
         \   |    |    /
          \ / \  /    /
           5   6  ----
           |   |
            \ /
             7


    Let's say that we've read 7 with shortest_time 12, coming from node 6.

    In how many ways can we reach 7 with time 12?

    In as many ways as we can reach node 6, that we're coming from!


    This piece of code is the absolute CRUX of this Solution:

        path_count[neighbor] = path_count[curr_node]; // Crux

    If you got that, you're done.

*/

/* Time  Beats: 86.38% */
/* Space Beats: 78.75% */

/* Time  Complexity: O((V + E) * logV) */
/* Space Complexity: O(V + E)          */
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int MOD = 1e9 + 7;
        int result = 0;


        /* Build an Adjacency List */
        unordered_map<int, vector<pair<int,int>>> adj_list;

        for (const auto& entry : roads)
        {
            const int u    = entry[0];
            const int v    = entry[1];
            const int time = entry[2];

            adj_list[u].push_back( {v, time} );
            adj_list[v].push_back( {u, time} );
        }

        /* Comparator: by first INCREASING, by second DECREASING */
        auto comparator = [](const pair<long long,int>& a, const pair<long long,int>& b)
        {
            if (a.first == b.first)
                return a.second < b.second; // Decreasing by the second

            return a.first > b.first; // Increasing by the first
        };

        priority_queue<pair<long long,int>,
                       vector<pair<long long,int>>,
                       decltype(comparator)> min_heap(comparator);

        min_heap.push( {0,0} );

        vector<long long> shortest_time(n, LLONG_MAX);
        vector<int> path_count(n, 0);

        shortest_time[0] = 0;
        path_count[0] = 1;

        bool found_min_distance = false;
        int min_dist = INT_MAX;

        /* Dijkstra */
        while ( ! min_heap.empty())
        {
            auto pair = min_heap.top();
            min_heap.pop();

            long long curr_time = pair.first;
            int       curr_node = pair.second;

            for (auto& [neighbor, time] : adj_list[curr_node])
            {
                long long new_time = curr_time + time;

                if (new_time < shortest_time[neighbor])
                {
                    shortest_time[neighbor] = curr_time + time;
                    path_count[neighbor] = path_count[curr_node]; // Crux

                    min_heap.push( {shortest_time[neighbor], neighbor} );
                }
                else if (curr_time + time == shortest_time[neighbor])
                {
                    path_count[neighbor] = (path_count[neighbor] + path_count[curr_node]) % MOD;
                }
            }
        }

        return path_count[n - 1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Somewhat unusual Floyd-Warshall in the same way that up above we have an
    unusual Dijkstra.

    Weirdness comes form the fact we need to return all the WAYS that we can
    arrive at our destination in shortest amount of time.

    Instead of the usual: Return the Shortest amount of time to reach X.

*/

/* Time  Beats: 5.34% */
/* Space Beats: 5.61% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^3) */
class Solution_Floyd_Warshall {
public:
    int countPaths(int n, vector<vector<int>>& roads)
    {
        const int MOD = 1e9 + 7;

        /*
            dp[src][dest][0] stores the minimum time between src and dest

            dp[src][dest][1] stores the num of ways to reach dest from src with
                             the minimum time
        */
        vector<vector<vector<long long >>> dp(n, vector<vector<long long>>(n, vector<long long>(2, 0LL)));

        // Initialize the dp table
        for (long long src = 0; src < n; src++)
        {
            for (long long dest = 0; dest < n; dest++)
            {
                if (src != dest)
                {
                    // Set a large initial time
                    dp[src][dest][0] = 1e12;

                    // No paths yet
                    dp[src][dest][1] = 0;
                }
                else
                {
                    // Distance from a node to itself is 0
                    dp[src][dest][0] = 0;

                    // Only one trivial way (staying at the node)
                    dp[src][dest][1] = 1;
                }
            }
        }

        // Initialize direct roads from the input
        for (auto& road : roads)
        {
            long long start_node  = road[0];
            long long end_node    = road[1];
            long long travel_time = road[2];

            dp[start_node][end_node][0] = travel_time;
            dp[end_node][start_node][0] = travel_time;

            // There is one direct path
            dp[start_node][end_node][1] = 1;

            // Since the roads are bidirectional
            dp[end_node][start_node][1] = 1;
        }


        /****************************************************************/
        /* Apply the Floyd-Warshall algorithm to compute shortest paths */
        /****************************************************************/

        for (long long  mid = 0; mid < n; mid++) // Intermediate node
        {
            for (long long  src = 0; src < n; src++) // Starting node
            {
                for (long long  dest = 0; dest < n; dest++) // Destination node
                {
                    // Avoid self-loops
                    if (src != mid && dest != mid)
                    {
                        long long  new_time = dp[src][mid][0] + dp[mid][dest][0];

                        if (new_time < dp[src][dest][0]) // Found a shorter time path
                        {
                            dp[src][dest][0] = new_time;
                            dp[src][dest][1] = (dp[src][mid][1] * dp[mid][dest][1]) % MOD;
                        }
                        else if (new_time == dp[src][dest][0]) // Another way to achieve the same shortest time
                        {
                            dp[src][dest][1] = (dp[src][dest][1] + dp[src][mid][1] * dp[mid][dest][1]) % MOD;
                        }
                    }
                }
            }
        }

        // Return the number of shortest paths from node (n-1) to node 0
        return dp[n - 1][0][1];
    }
};
