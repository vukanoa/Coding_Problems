#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1129) Shortest Path with Alternating Colors
    ===========================================

    ============
    Description:
    ============

    You are given an integer n, the number of nodes in a directed graph where
    the nodes are labeled from 0 to n - 1. Each edge is red or blue in this
    graph, and there could be self-edges and parallel edges.

    You are given two arrays redEdges and blueEdges where:

        redEdges[i] = [ai, bi] indicates that there is a directed red edge from
        node ai to node bi in the graph, and blueEdges[j] = [uj, vj] indicates
        that there is a directed blue edge from node uj to node vj in the
        graph.

    Return an array answer of length n, where each answer[x] is the length of
    the shortest path from node 0 to node x such that the edge colors alternate
    along the path, or -1 if such a path does not exist.

    =====================================================================================================================
    FUNCTION: vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges);
    =====================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
    Output: [0,1,-1]

    --- Example 2 ---
    Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
    Output: [0,1,-1]


    *** Constraints ***
    1 <= n <= 100
    0 <= redEdges.length, blueEdges.length <= 400
    redEdges[i].length == blueEdges[j].length == 2
    0 <= ai, bi, uj, vj < n

*/


/*
    ------------
    --- IDEA ---
    ------------

    This example is better:

    n = 7
    redEdges  = [[0,3],[0,6],[1,2],[2,3],[4,5],[5,6]]   // Designated by '***'
    blueEdges = [[0,1],[1,2],[2,2],[3,4],[5,5],[6,5]]   // Designated by '---'


    ****************************
    *                          *                    -----
    *                          *                     \  |
    *                          v                      \ v
    0 --------> 1              3 ----------> 4 *******> 5 <------
    *           \ *            ^                        *      /
    *            \ ******      *                        *     /
    *             ------ *     *                        *    /
    *                   \ *    *                        *   /
    *                    \ *   *                        *  /
    *                     V    *                        v /
    *                     2 ****          ************> 6 ****
    *                     ^ \             *             ^    *
    *                     |  \            *             *    *
    *                     ----            *             ******
    *                                     *
    ***************************************


    In the Adjacency list, redEdges will be denoted by a positive number of
    the node they are pointing to. On the other blueEdges will be denoted by
    negative values.

    Adjacency list RED:
    0: 3, 6
    1: 2
    2: 3
    3: /
    4: 5
    5: 6
    6: 6

    Adjacency list BLUE:
    0: 1
    1: 2
    2: 2
    3: 4
    4: /
    5: 5
    6: 5

    answer = [0, 1, 2, 1, 2, 2, 1]
              0  1  2  3  4  5  6


    BFS with another property(Color)

*/

/* Time  Beats: 77.02% */
/* Space Beats: 49.87% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> shortestAlternatingPaths(int n, std::vector<std::vector<int>>& redEdges, std::vector<std::vector<int>>& blueEdges)
    {
        std::vector<int> answer(n, -1);

        std::unordered_map<int, std::vector<int>> adj_red;
        std::unordered_map<int, std::vector<int>> adj_blue;

        for (auto& pair : redEdges)
            adj_red[pair[0]].push_back(pair[1]);

        for (auto& pair : blueEdges)
            adj_blue[pair[0]].push_back(pair[1]);


        std::vector<bool> visited_red (n, false);
        std::vector<bool> visited_blue(n, false);

        std::queue<std::vector<int>> queue;
        // prev_edge_color is 0(i.e NEITHER) at the beginning
        queue.push({0, 0, 0}); // {node, length, prev_edge_color}

        while (!queue.empty())
        {
            std::vector<int> vec = queue.front();
            queue.pop();

            int node       = vec[0];
            int length     = vec[1];
            int edge_color = vec[2]; // 0 == NEITHER, 1 == RED, 2 == BLUE

            if (answer[node] == -1)
                answer[node] = length;

            if (edge_color != 1) // != RED
            {
                for (auto& neighbor : adj_red[node])
                {
                    if (!visited_red[neighbor])
                    {
                        visited_red[neighbor] = true;
                        queue.push({neighbor, length + 1, 1});
                    }
                }
            }

            if (edge_color != 2) // != BLUE
            {
                for (auto& neighbor : adj_blue[node])
                {
                    if (!visited_blue[neighbor])
                    {
                        visited_blue[neighbor] = true;
                        queue.push({neighbor, length + 1, 2});
                    }
                }
            }
        }

        return answer;
    }
};
