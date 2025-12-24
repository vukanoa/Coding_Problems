/*
    ============
    === HARD ===
    ============

    ==============================
    2360) Longest Cycle in a Graph
    ==============================

    ============
    Description:
    ============

    You are given a directed graph of n nodes numbered from 0 to n - 1, where
    each node has at most one outgoing edge.

    The graph is represented with a given 0-indexed array edges of size n,
    indicating that there is a directed edge from node i to node edges[i]. If
    there is no outgoing edge from node i, then edges[i] == -1.

    Return the length of the longest cycle in the graph. If no cycle exists,
    return -1.

    A cycle is a path that starts and ends at the same node.

    ===============================================
    FUNCTION: int longestCycle(vector<int>& edges);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [3,3,4,2,3]
    Output: 3
    Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
    The length of this cycle is 3, so 3 is returned.

    --- Example 2 ---
    Input: edges = [2,-1,3,1]
    Output: -1
    Explanation: There are no cycles in this graph.


    *** Constraints ***
    n == edges.length
    2 <= n <= 10^5
    -1 <= edges[i] < n
    edges[i] != i

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.58% */
/* Space Beats: 96.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int longestCycle(vector<int>& edges)
    {
        const int node_count = edges.size();

        int longest_cycle_length = -1;  // Initialize the answer to -1
        int timestamp = 1;               // Global timestamp for visit order
        vector<int> visited_timestamp(node_count, 0);

        for (int start_node = 0; start_node < node_count; start_node++)
        {
            if (visited_timestamp[start_node] != 0)
                continue;

            int start_time_for_traversal = timestamp;
            int curr_node = start_node;

            while (curr_node != -1 && visited_timestamp[curr_node] == 0)
            {
                visited_timestamp[curr_node] = timestamp++;
                curr_node = edges[curr_node];
            }

            // If a cycle is found that includes nodes in this traversal
            if (curr_node != -1 && visited_timestamp[curr_node] >= start_time_for_traversal)
            {
                int cycle_length = timestamp - visited_timestamp[curr_node];
                longest_cycle_length = max(longest_cycle_length, cycle_length);
            }
        }

        return longest_cycle_length;
    }
};
