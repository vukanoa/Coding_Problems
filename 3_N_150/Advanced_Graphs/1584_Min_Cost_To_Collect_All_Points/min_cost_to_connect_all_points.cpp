#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1584) Min Cost to Connect All Points
    ====================================

    ============
    Description:
    ============

    You are given an array points representing integer coordinates of some
    points on a 2D-plane, where points[i] = [xi, yi].

    The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan
    distance between them: |xi - xj| + |yi - yj|, where |val| denotes the
    absolute value of val.

    Return the minimum cost to make all points connected. All points are
    connected if there is exactly one simple path between any two points.

    ================================================================
    FUNCTION: int minCostConnectPoints(vector<vector<int>>& points);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

      ^
 10 __|       X
  9 __|
  8 __|
  7 __|
  6 __|
  5 __|
  4 __|
  3 __|
  2 __|    X        X
  1 __|
      |
      X-|--|--|--|--|--|--X--|--|--|----->
        1  2  3  4  5  6  7  8  9  10
    Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
    Output: 20
    Explanation:

      ^
 10 __|    ## X
  9 __|    #
  8 __|    #
  7 __|    #
  6 __|    #
  5 __|    #
  4 __|    #
  3 __|    #
  2 __#### X ###### X #####
  1 __#                   #
      #                   #
      X-|--|--|--|--|--|--X--|--|--|----->
        1  2  3  4  5  6  7  8  9  10

    We can connect the points as shown above to get the minimum cost of 20.
    Notice that there is a unique path between every pair of points.




    --- Example 2 ---
    Input: points = [[3,12],[-2,5],[-4,1]]
    Output: 18


    *** Constraints ***
    1 <= points.length <= 1000
    -10^6 <= xi, yi <= 10^6
    All pairs (xi, yi) are distinct.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Consider Example 1:
        points = [[0,0],[2,2],[3,10],[5,2],[7,0]]


    Convert "points" to adj_list:


         Hash Map

    |  Key  :             Values             | // Values = {cost, node}
    +----------------------------------------+
    |   0   :  {4,1}, {13,2},  {7,3},  {7,4} |
    +----------------------------------------+
    |   1   :  {4,0},  {9,2},  {3,3},  {7,4} |
    +----------------------------------------+
    |   2   : {13,0},  {9,1}, {10,3}, {14,4} |
    +----------------------------------------+
    |   3   :  {7,0},  {3,1}, {10,2},  {4,4} |
    +----------------------------------------+
    |   4   :  {7,0},  {7,1}, {14,2},  {4,3} |
    +----------------------------------------+

    After that, do a TEXTBOOK Prims' Algorithm.
    There isn't much explanation other than that.

    The only difference is that the "distance" part(i.e. the first value in
    pair) is the Manhattan distance and not the weight of the edge given
    beforehand.

    If you don't know about Prim's Algorithm, here is an explanation in a
    nutshell:

    We'll have:
        1. An Unordered Set called "visited"
        2. A Min Heap

    The use of an Unordered Set "visited" is to prevent cycles in our graph
    connecting endeavor.

    They have explicitly told us:
        "Return the minimum cost to make all points connected. All points are
         connected if there is exactly one simple path between any two points."

    That means that there are NO CYCLES in that one single path.
    No cycles and one path indicates that this will be a:
        MST - Minimum Spanning Tree

    Since this is a Minimum Spanning Tree, we know we can use a Prim's Algo for
    a MST.

    Actually, what is required of us is literally an example of one use-case of
    Prim's Algorithm.

    Prim's Algorithm works as following:
        1. Before we begin, pick any node and insert it in "visited".
        2. Also push all of the edges of that picked node to min_heap as pair:
           {distance, node_it_connects}

           Now we begin the main part of Prim's Algorithm

        3. Since pairs are "sorted" in min_heap by the first value(i.e. dist),
           at each iteration, we are popping the top pair from that min_heap
           and we check if the "node_it_connects" is present in Set "visited".

           If it is present, then we don't want to create that edge since we
           are NOT allowed to have cycles. Pop that one out and try with the
           new pair at the top of the min_heap.

           Do that until you find one "node_it_connects"(i.e. second value)
           that ISN'T present in the min_heap.

        4. At that "node_it_connects"(i.e. second value from the pair) and
           insert it in a Set "visited".

        5. Add the "dist"(i.e. manhattan distance, i.e. first value from the
           pair) to our final result called "cost".

        6. Push all the edges of the "node_it_connect"(aka the "node" in the
           while loop) that DO connect all the nodes that are NOT yet visited.

        7. Do steps from [3, 6] inclusively, until visited.size() becomes N.

        8. At the end just return "cost".

*/

/* Time  Beats: 73.46% */
/* Space Beats: 36.85% */

/* Time  Complexity: O(n^2 * logn) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points)
    {
        const int N = points.size();
        std::vector<std::vector<std::pair<int,int>>> adj_list(N, std::vector<std::pair<int,int>>());

        // Create an Adjacency List
        for (int i = 0; i < N-1; i++)
        {
            int x1 = points[i][0];
            int y1 = points[i][1];

            for (int j = i+1; j < N; j++)
            {
                int x2 = points[j][0];
                int y2 = points[j][1];

                int distance = std::abs(x1 - x2) + std::abs(y1 - y2);

                adj_list[i].push_back( {distance, j} );
                adj_list[j].push_back( {distance, i} );
            }
        }

        /*** Prim's Algorithm ***/
        std::unordered_set<int> visited;

        std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>> min_heap;


        // Initial state before starting Prim's Algorithm
        visited.insert(0);
        for (int i = 0; i < adj_list[0].size(); i++)
            min_heap.push(adj_list[0][i]);

        int cost = 0;
        while (visited.size() < N)
        {
            int dist = min_heap.top().first;
            int node = min_heap.top().second;
            min_heap.pop(); // O(logn)

            if (visited.count(node)) // If "node" is already visited
                continue;

            visited.insert(node);
            cost += dist;

            for (int i = 0; i < adj_list[node].size(); i++)
            {
                if (visited.count(adj_list[node][i].second) == 0)
                    min_heap.push(adj_list[node][i]);
            }
        }

        return cost;
    }
};
