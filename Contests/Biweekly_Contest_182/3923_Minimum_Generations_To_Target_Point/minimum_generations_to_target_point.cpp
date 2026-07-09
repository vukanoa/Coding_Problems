/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3923) Minimum generations to Target Point
    =========================================

    ============
    Description:
    ============

    You are given a 2D integer array points where points[i] = [xi, yi, zi]
    represents a point in 3D space, and an integer array target representing a
    target point.

    Define generation 0 as the initial list of points. For each integer k >= 1,
    form generation k as follows:

        + Consider every pair of two distinct points a = [x1, y1, z1] and b =
          [x2, y2, z2] taken from all points produced in generations 0 through
          k - 1.

        + For each such pair, compute c = [floor((x1 + x2) / 2), floor((y1 +
          y2) / 2), floor((z1 + z2) / 2)] and collect every such c into a
          generation k.

        + All points in the generation k are produced simultaneously from
          points in generations 0 through k - 1.

        + After generation k is formed, the points in the generation k are
          considered available for forming later generations.

    Return the smallest integer k such that the target appears in one of the
    generations 0 through k. If the target is already in the initial points,
    return 0. If it is impossible to obtain the target, return -1.

    =====
    Note: floor denotes rounding down to the nearest integer.

          "Two distinct points" means the two chosen points must have different
          (x, y, z) coordinates. A point cannot be paired with itself, and
          pairing two points with identical coordinates is not possible.
    =====

    ===============================================================================
    FUNCTION: int minGenerations(vector<vector<int>>& points, vector<int>& target);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[0,0,0],[6,6,6]], target = [3,3,3]
    Output: 1
    Explanation:
        Generation 0: The initial points = [[0, 0, 0], [6, 6, 6]].
        The target = [3, 3, 3] does not exist in generation 0.
        Generation 1: For each pair of points in generation 0, we create new points.
            Using [0, 0, 0] and [6, 6, 6], we generate [3, 3, 3].
        After generation 1, points = [[0, 0, 0], [6, 6, 6], [3, 3, 3]].
        The target = [3, 3, 3] is found in generation 1, so the smallest k is 1.


    --- Example 2 ---
    Input: points = [[0,0,0],[5,5,5]], target = [1,1,1]
    Output: 2
    Explanation:

        Generation 0: The initial points = [[0, 0, 0], [5, 5, 5]].
        The target = [1, 1, 1] does not exist in generation 0.
        Generation 1: For each pair of points in generation 0, we create new points.
            Using [0, 0, 0] and [5, 5, 5], we generate [2, 2, 2].
        After generation 1, points = [[0, 0, 0], [5, 5, 5], [2, 2, 2]].
        Generation 2: For each pair of points available after generation 1, we create new points.
            Using [0, 0, 0] and [5, 5, 5], we generate [2, 2, 2].
            Using [0, 0, 0] and [2, 2, 2], we generate [1, 1, 1].
            Using [5, 5, 5] and [2, 2, 2], we generate [3, 3, 3].
        After generation 2, points = [[0, 0, 0], [5, 5, 5], [2, 2, 2], [1, 1, 1], [3, 3, 3]].
        The target = [1, 1, 1] is found in generation 2, so the smallest k is 2.


    --- Example 3 ---
    Input: points = [[0,0,0],[2,2,2],[3,3,3]], target = [2,2,2]
    Output: 0
    Explanation:
        Generation 0: The initial points = [[0, 0, 0], [2, 2, 2], [3, 3, 3]].
        The target = [2, 2, 2] already exists in generation 0, so the smallest k is 0.


    --- Example 4 ---
    Input: points = [[1,2,3]], target = [5,5,5]

    Output: -1

    Explanation:

        Only one initial point is available, so no new points can be generated.
        Therefore, the target cannot be obtained, and the answer is -1.


    *** Constraints ***
    1 <= points.length <= 20
    points[i] = [xi, yi, zi]
    0 <= xi, yi, zi <= 6
    target.length == 3
    0 <= target[i] <= 6
    The initial set of points contains no duplicates.

*/

#include <vector>
using namespace std;

/* Time  Beats: 89.80% */
/* Space Beats: 79.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minGenerations(vector<vector<int>>& points, vector<int>& target)
    {
        const int N = points.size();
        int result = 0;

        vector<vector<int>> unique;

        bool present[7][7][7] = {false};
        for (const auto& point : points)
        {
            const int& x = point[0];
            const int& y = point[1];
            const int& z = point[2];

            if (x == target[0] && y == target[1] && z == target[2])
                return 0;

            if ( ! present[x][y][z])
            {
                present[x][y][z] = true;
                unique.push_back( {x, y, z} );
            }
        }

        int k = 1;
        int iteration = 0;
        while (true)
        {
            const int SIZE = unique.size();

            vector<vector<int>> new_points;

            for (int i = 0; i < SIZE; i++)
            {
                for (int j = i + 1; j < SIZE; j++)
                {
                    int new_x = (unique[i][0] + unique[j][0]) / 2;
                    int new_y = (unique[i][1] + unique[j][1]) / 2;
                    int new_z = (unique[i][2] + unique[j][2]) / 2;

                    if (present[new_x][new_y][new_z])
                        continue;

                    present[new_x][new_y][new_z] = true;
                    new_points.push_back( {new_x, new_y, new_z} );
                }
            }

            if (new_points.empty())
                break;

            for (const auto& point : new_points)
            {
                if (point == target)
                    return k;

                unique.push_back(point);
            }

            k++;
        }

        return -1;
    }
};
