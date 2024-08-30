#include <iostream>
#include <vector>
#include <map>

/*
    ============
    === HARD ===
    ============

    ===========================
    149) Max Points on a Line
    ===========================

    ============
    Description:
    ============

    Given an array of points where points[i] = [xi, yi] represents a point on
    the X-Y plane, return the maximum number of points that lie on the same
    straight line.

    =====================================================
    FUNCTION: int maxPoints(vector<vector<int>>& points);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,1],[2,2],[3,3]]
    Output: 3

    --- Example 2 ---
    Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    Output: 4


    *** Constraints ***
    1 <= points.length <= 300
    points[i].length == 2
    -10^4 <= xi, yi <= 10^4
    All the points are unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.44% */
/* Space Beats: 66.36% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points)
    {
        double slope;
        int n = points.size();
        int result = 0;

        for(int i = 0; i < n; i++)
        {
            map<double, int> map;
            double x;
            double y;

            int max_points_on_line = 0;
            int same = 1;

            for (int j = i + 1; j < n; j++)
            {
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1])
                {
                    same++;
                    continue;
                }

                x = points[i][0] - points[j][0];
                y = points[i][1] - points[j][1];

                if (x == 0)
                    slope = INT_MAX;
                else
                    slope = y / x;

                map[slope] = map[slope] + 1;

                if (map[slope] > max_points_on_line)
                    max_points_on_line = map[slope];
            }

            result = max(max_points_on_line + same, result);
        }

        return result;
    }
};
