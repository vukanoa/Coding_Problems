/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    1620) Coordinate with Maximum Network Quality
    =============================================

    ============
    Description:
    ============

    You are given an array of network towers towers, where towers[i] = [xi, yi,
    qi] denotes the ith network tower with location (xi, yi) and quality factor
    qi. All the coordinates are integral coordinates on the X-Y plane, and the
    distance between the two coordinates is the Euclidean distance.

    You are also given an integer radius where a tower is reachable if the
    distance is less than or equal to radius. Outside that distance, the signal
    becomes garbled, and the tower is not reachable.

    The signal quality of the ith tower at a coordinate (x, y) is calculated
    with the formula ⌊qi / (1 + d)⌋, where d is the distance between the tower
    and the coordinate. The network quality at a coordinate is the sum of the
    signal qualities from all the reachable towers.

    Return the array [cx, cy] representing the integral coordinate (cx, cy)
    where the network quality is maximum. If there are multiple coordinates
    with the same network quality, return the lexicographically minimum
    non-negative coordinate.

    =====
    Note:
    =====

    + A coordinate (x1, y1) is lexicographically smaller than (x2, y2) if
      either:
        + x1 < x2, or
        + x1 == x2 and y1 < y2.

    + ⌊val⌋ is the greatest integer less than or equal to val (the floor
      function).

    ==============================================================================
    FUNCTION: vector<int> bestCoordinate(vector<vector<int>>& towers, int radius);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: towers = [[1,2,5],[2,1,7],[3,1,9]], radius = 2
    Output: [2,1]
    Explanation: At coordinate (2, 1) the total quality is 13.
    - Quality of 7 from (2, 1) results in ⌊7 / (1 + sqrt(0)⌋ = ⌊7⌋ = 7
    - Quality of 5 from (1, 2) results in ⌊5 / (1 + sqrt(2)⌋ = ⌊2.07⌋ = 2
    - Quality of 9 from (3, 1) results in ⌊9 / (1 + sqrt(1)⌋ = ⌊4.5⌋ = 4
    No other coordinate has a higher network quality.

    --- Example 2 ---
    Input: towers = [[23,11,21]], radius = 9
    Output: [23,11]
    Explanation: Since there is only one tower, the network quality is highest
                 right at the tower's location.

    --- Example 3 ---
    Input: towers = [[1,2,13],[2,1,7],[0,1,9]], radius = 2
    Output: [1,2]
    Explanation: Coordinate (1, 2) has the highest network quality.


    *** Constraints ***
    1 <= towers.length <= 50
    towers[i].length == 3
    0 <= xi, yi, qi <= 50
    1 <= radius <= 50

*/

#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>> &towers, int radius)
    {
        /* Sort towers by x, then y, then quality */
        sort(towers.begin(), towers.end());

        deque<int> active_tower_ids;

        int tower_idx = 0;
        int best_x = 0;
        int best_y = 0;
        int best_quality = 0;

        int min_x = towers.front()[0];
        int max_x = towers.back()[0];

        for (int curr_x = min_x; curr_x <= max_x; curr_x++)
        {
            while (tower_idx < towers.size() && curr_x + radius >= towers[tower_idx][0])
            {
                active_tower_ids.push_back(tower_idx);
                tower_idx++;
            }

            while ( ! active_tower_ids.empty() &&
                   towers[active_tower_ids.front()][0] < curr_x - radius)
            {
                active_tower_ids.pop_front();
            }

            for (int curr_y = 0; curr_y <= 50; ++curr_y)
            {
                int curr_quality = 0;

                for (int id : active_tower_ids)
                {
                    int tower_x = towers[id][0];
                    int tower_y = towers[id][1];
                    int tower_q = towers[id][2];

                    if (tower_y < curr_y - radius || tower_y > curr_y + radius)
                        continue;

                    int dx = tower_x - curr_x;
                    int dy = tower_y - curr_y;
                    int dist_sq = dx * dx + dy * dy;

                    if (dist_sq <= radius * radius)
                        curr_quality += tower_q / (1 + sqrt(dist_sq));
                }

                if (curr_quality > best_quality)
                {
                    best_quality = curr_quality;
                    best_x = curr_x;
                    best_y = curr_y;
                }
            }
        }

        return {best_x, best_y};
    }
};
