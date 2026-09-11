/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    2662) Minimum Cost of a Path With Special Roads
    ===============================================

    ============
    Description:
    ============

    You are given an array start where start = [startX, startY] represents your
    initial position (startX, startY) in a 2D space. You are also given the
    array target where target = [targetX, targetY] represents your target
    position (targetX, targetY).

    The cost of going from a position (x1, y1) to any other position in the
    space (x2, y2) is |x2 - x1| + |y2 - y1|.

    There are also some special roads. You are given a 2D array specialRoads
    where specialRoads[i] = [x1i, y1i, x2i, y2i, costi] indicates that the ith
    special road goes in one direction from (x1i, y1i) to (x2i, y2i) with a
    cost equal to costi. You can use each special road any number of times.

    Return the minimum cost required to go from (startX, startY) to (targetX,
    targetY).

    ======================================================================================================
    FUNCTION: int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads);
    ======================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]]
    Output: 5
    Explanation:
        (1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
        (1,2) to (3,3). Use specialRoads[0] with the cost 2.
        (3,3) to (3,4) with a cost of |3 - 3| + |4 - 3| = 1.
        (3,4) to (4,5). Use specialRoads[1] with the cost 1.
    So the total cost is 1 + 2 + 1 + 1 = 5.


    --- Example 2 ---
    Input: start = [3,2], target = [5,7], specialRoads = [[5,7,3,2,1],[3,2,3,4,4],[3,3,5,5,5],[3,4,5,6,6]]
    Output: 7
    Explanation:
    It is optimal not to use any special edges and go directly from the
    starting to the ending position with a cost |5 - 3| + |7 - 2| = 7.
    Note that the specialRoads[0] is directed from (5,7) to (3,2).


    --- Example 3 ---
    Input: start = [1,1], target = [10,4], specialRoads = [[4,2,1,1,3],[1,2,7,4,4],[10,3,6,1,2],[6,1,1,2,3]]
    Output: 8
    Explanation:
        1. (1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
        2. (1,2) to (7,4). Use specialRoads[1] with the cost 4.
        3. (7,4) to (10,4) with a cost of |10 - 7| + |4 - 4| = 3.



    *** Constraints ***
    start.length == target.length == 2
    1 <= startX <= targetX <= 10^5
    1 <= startY <= targetY <= 10^5
    1 <= specialRoads.length <= 200
    specialRoads[i].length == 5
    startX <= x1i, x2i <= targetX
    startY <= y1i, y2i <= targetY
    1 <= costi <= 10^5

*/

#include <climits>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.69% */
/* Space Beats: 64.60% */

/* Time  Complexity: O(N^2 * logN) */
/* Space Complexity: O(N)          */
class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads)
    {
        const int N = specialRoads.size();

        vector<pair<int,int>> coordinates;
        coordinates.push_back( {start[0],  start[1]}  ); // Push SOURCE
        coordinates.push_back( {target[0], target[1]} ); // Push TARGET

        for (const vector<int>& road : specialRoads)
        {
            coordinates.push_back( {road[0], road[1]} );
            coordinates.push_back( {road[2], road[3]} );
        }

        const int TOTAL_NODES = coordinates.size();

        vector<int> distance(TOTAL_NODES, INT_MAX);
        distance[0] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;
        min_heap.push( {0, 0} );

        /* Dijkstra's Algorithm */
        while ( ! min_heap.empty())
        {
            auto [dist, node] = min_heap.top();
            min_heap.pop();

            if (dist > distance[node])
                continue;

            if (node == 1)
                break;

            const int& x1 = coordinates[node].first;
            const int& y1 = coordinates[node].second;

            /* Normal Manhattan Distance */
            for (int neighbor = 0; neighbor < TOTAL_NODES; neighbor++)
            {
                if (neighbor == node)
                    continue;

                const int& x2 = coordinates[neighbor].first;
                const int& y2 = coordinates[neighbor].second;

                int new_distance = dist + abs(x2 - x1) +
                                          abs(y2 - y1);

                if (new_distance < distance[neighbor])
                {
                    distance[neighbor] = new_distance;
                    min_heap.push( {new_distance, neighbor} );
                }
            }

            /* Special Road */
            for (int neighbor = 0; neighbor < N; neighbor++)
            {
                int source_node = 2*neighbor + 2;

                const int& x2 = coordinates[source_node].first;
                const int& y2 = coordinates[source_node].second;

                if (x1 == x2 && y1 == y2)
                {
                    int target_node = source_node + 1;
                    int cost        = specialRoads[neighbor][4];

                    int new_distance = dist + cost;

                    if (new_distance < distance[target_node])
                    {
                        distance[target_node] = new_distance;         // Relax
                        min_heap.push( {new_distance, target_node} ); // Push
                    }
                }
            }
        }

        return distance[1];
    }
};
