/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    743) Network Delay Time
    ===========================

    ============
    Description:
    ============

    You are given a network of n nodes, labeled from 1 to n. You are also given
    times, a list of travel times as directed edges times[i] = (ui, vi, wi),
    where ui is the source node, vi is the target node, and wi is the time it
    takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the minimum time it takes
    for all the n nodes to receive the signal. If it is impossible for all the
    n nodes to receive the signal, return -1.

    =========================================================================
    FUNCTION: int networkDelayTime(vector<vector<int>>& times, int n, int k);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                  1
         1 <-------------- 2
                           |
                           |
                           | 1
                           |
                           |
                   1       v
         4 <-------------- 3


    Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    Output: 2




    --- Example 2 ---
    Input: times = [[1,2,1]], n = 2, k = 1
    Output: 1



    --- Example 3 ---
    Input: times = [[1,2,1]], n = 2, k = 2
    Output: -1


    *** Constraints ***
    1 <= k <= n <= 100
    1 <= times.length <= 6000
    times[i].length == 3
    1 <= ui, vi <= n
    ui != vi
    0 <= wi <= 100
    All the pairs (ui, vi) are unique. (i.e., no multiple edges.)

*/

#include <algorithm>
#include <bitset>
#include <climits>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    (Brute Force)

    We need to calculate how long does it take for a signal to reach each node
    stratin from the node k.

    Here we're using a DFS and we simply try all of the possible paths from k
    and we keep track of the best(i.e. MINIMUM) time needed to reach that node.

    If we reach some node and the current time is BETTER(i.e. smaller) than the
    current minimum---We update it.

    If the current time is already worse or requal than a current minimium, we
    stop going down this path, i.e. we're doing "prunning".

    After we go through each and every path(i.e. each and every EDGE) the
    result is the maximum among all nodes, i.e. the last one to receive the
    signal.

    However it can happen that some(or more than one) node is unreachable, i.e.
    its "best" time is INT_MAX. If that's the case, we simply return -1.

*/

/* Time  Beats:  5.02% */
/* Space Beats: 68.88% */

/* Time  Complexity: O(V * E) */
/* Space Complexity: O(V + E) */
class Solution_DFS {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        unordered_map<int, vector<pair<int, int>>> adj_list;

        /* Create an Adjacency List */
        for (const auto& edge : times)
        {
            const int& u = edge[0];
            const int& v = edge[1];
            const int& t = edge[2];

            adj_list[u].push_back( {v, t} );
        }

        vector<int> dist(n + 1, INT_MAX);

        /* DFS */
        dfs(k, 0, dist, adj_list);

        // +1 because nodes are from [1, n], inclusivelly
        int result = *max_element(dist.begin() + 1, dist.end());

        return result == INT_MAX ? -1 : result;
    }

private:
    void dfs(int node, int time, vector<int>& dist, unordered_map<int, vector<pair<int, int>>>& adj_list)
    {
        if (time >= dist[node])
            return;

        dist[node] = time;

        for (const auto& [neighbor, w] : adj_list[node])
        {
            dfs(neighbor, time + w, dist, adj_list);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------


    We need to calculate how long does it take for a signal to reach each node
    stratin from the node k.


    Bellman ford is:

        Shortest path from ONE node to ALL nodes, where NEGATIVE edges ARE
        INDEED allowed.

        (In this problem there are no negative edges, but in general, Bellman
        Ford works with negative edges as well)


    How does it work?
    The point is in "Relaxation".

    What's that?
    It's updating the current best time(i.e. min time) in "dist" vector.

    We're "relaxing" EDGES, not nodes. And we do that repeatedly.
    Each "relaxation" tries to improve the shortest distance(i.e. minimum time)
    to some node by using an additional edge, through node 'u'.

    After n-1 "rounds", all shortest paths(i.e. minimum times) are GUARANTEED
    to be found because the longest simple path has AT MOST n-1 edges.

    After we're done with that, the result is the maximum among all nodes, i.e.
    the last one to receive the signal.

    However it can happen that some(or more than one) node is unreachable, i.e.
    its "best" time is INT_MAX. If that's the case, we simply return -1.

*/

/* Time  Beats: 14.63% */
/* Space Beats: 97.81% */

/* Time  Complexity: O(V * E) */
/* Space Complexity: O(V)     */
class Solution_Bellman_Ford {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;

        // O(V * E) (entire block)
        for (int i = 1; i < n; i++) // O(V)
        {
            for (const auto& edge : times) // O(E)
            {
                const int& src = edge[0];
                const int& dst = edge[1];
                const int& w   = edge[2];

                if (dist[src] != INT_MAX && (dist[src] + w) < dist[dst])
                    dist[dst] = dist[src] + w;
            }
        }

        int result = 0;
        for (int i = 1; i < n+1; i++)
        {
            if (dist[i] == INT_MAX)
                return -1;

            result = max(result, dist[i]);
        }

        return result;
    }
};






/*
    ------------
    --- IDEA ---
    ------------

    TODO
    There is a better way to implement Dijkstra's Algorithm for this Solution.
    Check out the other "Optimal_Dijkstra" Solution down below in this file.

*/

/* Time  Beats: 5.06% */
/* Space Beats: 5.01% */

/* Time  Complexity: O(E * logE) */
/* Space Complexity: O(E + V)    */ // Where V <==> n
class Solution_Dijkstra {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        const int E = times.size();
        int result = 0;

        unordered_map<int, vector<vector<int>>> adj_list;

        /* Create an Adjacency List */
        // O(E) (enire block)
        for (const auto& edge : times)
        {
            const int& u = edge[0];
            const int& v = edge[1];
            const int& t = edge[2];

            adj_list[u].push_back( {t, v} );
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push( {0, k} );

        bitset<101> received_signal = 0;

        // O(N) (entire block)
        bitset<101> mask; // "All received" mask
        for (int i = 1; i < n+1; i++) // Starting from 1, not 0.
            mask.set(i);

        /* Dijkstra's Algorithm */
        // O (E * logE) (entire block)
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop(); // O(logE) because there are duplicates

            const int& curr_time = top[0];
            const int& curr_node = top[1];

            // O(V / 64) because bitset is implemented using 8 Bytes words
            if (received_signal.test(curr_node)) // Already received the signal
                continue;

            received_signal.set(curr_node); // Mark that it received the signal

            if ((received_signal & mask) == mask)
                return curr_time;

            // O(E) (entire block) in total for entire while-loop
            for (auto& neighbor : adj_list[curr_node])
            {
                const int& neighbor_time = neighbor[0];
                const int& neighbor_node = neighbor[1];

                /* Min time for this "neighbor_node" to receive the signal */
                int new_time = curr_time + neighbor_time;

                min_heap.push( {new_time, neighbor_node} );
            }
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a better implementation and a more optimal way of writing Dijkstra
    for this problem.

    It's always beneficial to see multiple different implementations of the
    same technique. It makes you appreciate the subtleties that are actually
    important and vastly improve the efficiency of the program.

*/

/* Time  Beats: 48.41% */
/* Space Beats: 68.88% */

/* Time  Complexity: O(E * logV) */
/* Space Complexity: O(E + V)    */
class Solution_Optimal_Dijkstra {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        const int E = times.size();

        unordered_map<int, vector<pair<int,int>>> adj_list;

        /* Create an Adjacency List */
        for (const auto& edge : times)
        {
            const int& u = edge[0];
            const int& v = edge[1];
            const int& t = edge[2];

            adj_list[u].push_back({v, t});
        }

        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;
        min_heap.push( {0, k} );

        /* Dijkstra's Algorithm */
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            const int& curr_time = top.first;
            const int& curr_node = top.second;

            if (curr_time > dist[curr_node])
                continue;

            for (const auto& neighbor : adj_list[curr_node])
            {
                const int& neighbor_node = neighbor.first;
                const int& neighbor_time = neighbor.second;

                int new_time = curr_time + neighbor_time;

                if (new_time < dist[neighbor_node])
                {
                    dist[neighbor_node] = new_time;
                    min_heap.push({new_time, neighbor_node});
                }
            }
        }

        int result = 0;
        for (int i = 1; i < n+1; i++)
        {
            if (dist[i] == INT_MAX) // We have NOT found a path from k to i
                return -1;

            result = max(result, dist[i]);
        }

        return result;
    }
};
