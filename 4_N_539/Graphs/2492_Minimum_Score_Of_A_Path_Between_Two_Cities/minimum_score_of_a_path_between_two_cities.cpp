#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    2492) Minimum Score Of A Path Between Two Cities
    ================================================

    ============
    Description:
    ============

    You are given a positive integer n representing n cities numbered from 1 to
    n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei]
    indicates that there is a bidirectional road between cities ai and bi with
    a distance equal to distancei. The cities graph is not necessarily
    connected.

    The score of a path between two cities is defined as the minimum distance
    of a road in this path.

    Return the minimum possible score of a path between cities 1 and n.

    Note:
        + A path is a sequence of roads between two cities.

        + It is allowed for a path to contain the same road multiple times, and
          you can visit cities 1 and n multiple times along the path.

        + The test cases are generated such that there is at least one path
          between 1 and n.

    ==========================================================
    FUNCTION: int minScore(int n, vector<vector<int>>& roads);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

                                   1
                                  / \
                                 /   \
                               7/     \9
                               /       \
                              4 ------- 2
                                   5   /
                                      /6
                                     /
                                    3

    Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
    Output: 5
    Explanation: The path from city 1 to 4 with the minimum score is:
                     1 -> 2 -> 4
                 The score of this path is min(9,5) = 5.  It can be shown that
                 no other path has less score.




    --- Example 2 ---
                                   1
                                  / \
                                 /   \
                               4/     \2
                               /       \
                              3         2
                               \
                                \
                                7\
                                  \
                                   4

    Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
    Output: 2
    Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 ->
                     1 -> 3 -> 4
                 The score of this path is min(2,2,4,7) = 2.


    *** Constraints ***
    2 <= n <= 10^5
    1 <= roads.length <= 10^5
    roads[i].length == 3
    1 <= ai, bi <= n
    ai != bi
    1 <= distancei <= 10^4
    There are no repeated edges.
    There is at least one path between 1 and n.

*/

/*
    ------------
    --- IDEA ---
    ------------

    I firmly believe that once you see(down below in this IDEA):

        + "My First  Example" and
        + "My Second Example"

    everything will be clear and obvious at that point.


    ************************************************************
    *** TWO IMPORTANT PIECES OF INFORMATION FROM DESCRIPTION ***
    ************************************************************

    However, there are two VERY important thing they've told us but that is
    easy to forget or miss while reading. They have said:

    1)

        "The cities graph is not necessarily connected."

        What that means is - You cannot just take the minimum distance (third
        value, i.e. index 2 from every road in "roads", i.e. distance_i from:

                            road_i:  [a_i, b_i, distance_i])
                           indices:    0    1       2

                           road_i[2] = distance_i;

        from the "roads" and return as a result because maybe that distance
        path is between some two cities which are completely disconnected from
        node_1 and, by extension, node_n.

        (Realize that if any node is in any direct or INDIRECT way connected to
        node_1 and MUST be true that it is also connected to node_n in some
        way)


    2)
        "The test cases are generated such that there is at least one path
         between 1 and n."

         Which means that there is certain SOME path(at least one) that
         connects node_1 and node_n.


    After noticing these two important pieces of information and once you take
    a look at "My First Example" and "My Second Example" everything should be
    clear:


    --- My First Example ---

                   5 -------- 4
                        1      \
                                \2
                                 \
                                  \
                                   1
                                  / \
                                 /   \
                               7/     \9
                               /       \
                              6 ------- 2
                                   5   /
                                      /6
                                     /
                                    3

    Input: n = 6, roads = [[1,2,9],[2,3,6],[2,6,5],[1,6,7],[1,4,2],[4,5,1]]]
    Output: 1
    Explanation: The path from city 1 to 4 with the minimum score is:
                     1 -> 4 -> 5 -> 4 -> 1 -> 6
                 The score of this path is min(1,2,7,9,5,6) = 5.
                 In other words, take into account every "distance_i" that is
                 in some way connected to node_1 and node_n.
                 (By definition if any node is connected to node_1 it must be
                  also connected to node_n and vice versa)


    --- My Second Example ---



               (This one is DISCONNECTED from node_1 and, by extension, node_n)
                   5 -------- 4
                        1
                                   1
                                  / \
                                 /   \
                               7/     \9
                               /       \
                              6 ------- 2
                                   5   /
                                      /6
                                     /
                                    3

    Input: n = 6, roads = [[1,2,9],[2,3,6],[2,6,5],[1,6,7],[4,5,1]]]
    OUtput: 5
    Explanation: The path from city 1 to 4 with the minimum score is:
                     1 -> 2 - > 6
                 The score of this path is min(7,9,5,6) = 5.
                 Since node_4 and node_5 AREN'T connected to node_1 and node_n
                 in any, even indirect, way, then we DO NOT count its score as
                 "one of the scores along the path".


    Precisely because cities are not necessarily connected, we ONLY care about
    the connected ones, i.e. the ones that are connected to node_1 and node_n
    in any direct or indirect way.

    To make sure we only visit those connected nodes, we're going to start at
    node_1 and simply do a BFS until we have traversed the entire graph. The
    minimum path(i.e. minimum edge) in the entire graph is our desired result.

*/

/* Time  Beats: 61.36% */
/* Space Beats: 55.52% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    int minScore(int n, vector<vector<int>>& roads)
    {
        int min_score = INT_MAX;
        std::vector<bool> visited(n+1, false);
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj_list;

        for (const auto& road : roads)
        {
            adj_list[road[0]].push_back({road[1], road[2]});
            adj_list[road[1]].push_back({road[0], road[2]});
        }

        std::queue<int> queue;
        visited[1] = true;
        queue.push(1);

        /* BFS */
        while (!queue.empty())
        {
            int size = queue.size();

            for (int i = 0; i < size; i++)
            {
                int city = queue.front();
                queue.pop();

                for (const auto& neighbor : adj_list[city])
                {
                    int neighbor_city     = neighbor.first;
                    int neighbor_distance = neighbor.second;

                    min_score = std::min(min_score, neighbor_distance);

                    if (visited[neighbor_city])
                        continue;

                    visited[neighbor_city] = true;
                    queue.push(neighbor_city);
                }
            }
        }

        return min_score;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's the same IDEA as above, however instead of using a BFS to find a
    minimum score(i.e. minimum edge) in a graph connected to node_1 and node_n
    in any direct or indirect way, we use a DFS here to accomplish the same
    thing.

*/

/* Time  Beats: 37.54% */
/* Space Beats: 51.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    int minScore(int n, vector<vector<int>>& roads)
    {
        int min_score = INT_MAX;
        std::vector<bool> visited(n+1, false);
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj_list;

        for (const auto& road : roads)
        {
            adj_list[road[0]].push_back({road[1], road[2]});
            adj_list[road[1]].push_back({road[0], road[2]});
        }

        dfs(adj_list, visited, min_score, 1);

        return min_score;
    }

private:
    void dfs(std::unordered_map<int, std::vector<std::pair<int,int>>>& adj_list,
             std::vector<bool>& visited,
             int& min_score,
             int city)
    {
        if (visited[city])
            return;

        visited[city] = true;

        for (const auto& neighbor : adj_list[city])
        {
            int neighbor_city     = neighbor.first;
            int neighbor_distance = neighbor.second;

            min_score = std::min(min_score, neighbor_distance);
            dfs(adj_list, visited, min_score, neighbor_city);
        }
    }
};
