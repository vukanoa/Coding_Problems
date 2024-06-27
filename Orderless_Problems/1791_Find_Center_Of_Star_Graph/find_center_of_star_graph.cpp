#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===============================
    1791) Find Center of Star Graph
    ===============================

    ============
    Description:
    ============

    There is an undirected star graph consisting of n nodes labeled from 1 to
    n. A star graph is a graph where there is one center node and exactly n - 1
    edges that connect the center node with every other node.

    You are given a 2D integer array edges where each edges[i] = [ui, vi]
    indicates that there is an edge between the nodes ui and vi. Return the
    center of the given star graph.

    =====================================================
    FUNCTION: int findCenter(vector<vector<int>>& edges);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[1,2],[2,3],[4,2]]
    Output: 2
    Explanation: As shown in the figure above, node 2 is connected to every
                 other node, so 2 is the center.

    --- Example 2 ---
    Input: edges = [[1,2],[5,1],[1,3],[1,4]]
    Output: 1


    *** Constraints ***
    3 <= n <= 10^5
    edges.length == n - 1
    edges[i].length == 2
    1 <= ui, vi <= n
    ui != vi
    The given edges represent a valid star graph.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Create an unordered map and counter frequencies of all the nodes that are
    appearing in "edges" matrix.

    The one that appears the most is certainly the center. It's logically not
    possible to be otherwise.

    Therefore, after we've created an unordered map, just go through it and
    find the node that corresponds to the greatest frequency in the matrix
    "edges".

*/

/* Time  Beats: 21.23% */
/* Space Beats: 26.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int findCenter(std::vector<std::vector<int>>& edges)
    {
        std::unordered_map<int, int> umap;
        for (auto& edge : edges)
        {
            umap[edge[0]]++;
            umap[edge[1]]++;
        }

        int max_elem = INT_MIN;
        int result;

        for (auto& pair : umap)
        {
            if (max_elem < pair.second)
            {
                max_elem = pair.second;
                result   = pair.first;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.21% */
/* Space Beats: 40.94% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int findCenter(std::vector<std::vector<int>>& edges)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        std::bitset<100000> visited = 0;

        for(auto& edge: edges)
        {
            if (visited[edge[0]])
                return edge[0];

            if (visited[edge[1]])
                return edge[1];

            visited[edge[0]] = visited[edge[1]] = 1;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.51% */
/* Space Beats: 77.19% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findCenter(std::vector<std::vector<int>>& edges)
    {
        return edges[0][0] == edges[1][0] ? edges[0][0] : (edges[0][0]==edges[1][1] ? edges[0][0] : edges[0][1]);
    }
};
