/*
    ============
    === HARD ===
    ============

    =================================================
    2508) Add Edges to Make Degrees of All Nodes Even
    =================================================

    ============
    Description:
    ============

    There is an undirected graph consisting of n nodes numbered from 1 to n.
    You are given the integer n and a 2D array edges where edges[i] = [ai, bi]
    indicates that there is an edge between nodes ai and bi. The graph can be
    disconnected.

    You can add at most two additional edges (possibly none) to this graph so
    that there are no repeated edges and no self-loops.

    Return true if it is possible to make the degree of each node in the graph
    even, otherwise return false.

    The degree of a node is the number of edges connected to it.

    =============================================================
    FUNCTION: bool isPossible(int n, vector<vector<int>>& edges);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
    Output: true
    Explanation: The above diagram shows a valid way of adding an edge.
    Every node in the resulting graph is connected to an even number of edges.

    --- Example 2 ---
    Input: n = 4, edges = [[1,2],[3,4]]
    Output: true
    Explanation: The above diagram shows a valid way of adding two edges.

    --- Example 3 ---
    Input: n = 4, edges = [[1,2],[1,3],[1,4]]
    Output: false
    Explanation: It is not possible to obtain a valid graph with adding at most
    2 edges.


    *** Constraints ***
    3 <= n <= 10^5
    2 <= edges.length <= 10^5
    edges[i].length == 2
    1 <= ai, bi <= n
    ai != bi
    There are no repeated edges.

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 47.25% */
/* Space Beats: 23.78% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges)
    {
        const int V = n;
        const int E = edges.size();

        vector<unordered_set<int>> adj_list(n+1); // node=0 is unusused
        vector<int> degree(n+1, 0);               // node=0 is unusused

        for (const auto& edge : edges)
        {
            const int& one = edge[0];
            const int& two = edge[1];

            // UNDIRECTED edge
            ++degree[one];
            ++degree[two];

            adj_list[one].insert(two);
            adj_list[two].insert(one);
        }

        int a = -1;
        int b = -1;
        int c = -1;
        int d = -1;
        int odd_degree_nodes_count = 0;
        for (int node = 1; node <= n; node++)
        {
            if (degree[node] & 1) // if degree of this node is ODD
            {
                ++odd_degree_nodes_count;

                if (a == -1) a = node;
                else if (b == -1) b = node;
                else if (c == -1) c = node;
                else if (d == -1) d = node;
            }
        }

        if (odd_degree_nodes_count == 0) // Every node already has an EVEN degree
            return true;

        if (odd_degree_nodes_count & 1) // Impossible to fix with
            return false;

        if (odd_degree_nodes_count > 4) // We'd need MORE than 2 new edges, however we're allowed AT MOST 2 new edges
            return false;

        if (odd_degree_nodes_count == 2)
        {
            if (adj_list[a].count(b) == 0) // Connect two nodes with ODD degrees, making both of them with EVEN degrees
                return true;
            
            for (int node = 1; node <= n; node++)
            {
                if (node == a || node == b)
                    continue;
                
                if (adj_list[node].count(a) == 0 &&
                    adj_list[node].count(b) == 0)
                {
                    return true;
                }
            }

            return false;
        }

        // odd_degree_nodes_count == 4
        if (adj_list[a].count(b) == 0 && adj_list[c].count(d) == 0) // Connect (a with b) and (c with d)
            return true;
        
        if (adj_list[a].count(c) == 0 && adj_list[b].count(d) == 0) // Connect (a with c) and (b with d)
            return true;
        
        if (adj_list[a].count(d) == 0 && adj_list[b].count(c) == 0) // Connect (a with d) and (b with c)
            return true;

        return false;
    }
};
