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

#include <bitset>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.06% */
/* Space Beats: 5.01% */

/* Time  Complexity: O(E * logE) */
/* Space Complexity: O(E + V)    */ // Where V <==> n
class Solution {
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
