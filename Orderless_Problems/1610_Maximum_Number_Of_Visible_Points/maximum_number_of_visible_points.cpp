/*
    ============
    === HARD ===
    ============

    ======================================
    1610) Maximum Number of Visible Points
    ======================================

    ============
    Description:
    ============

    You are given an array points, an integer angle, and your location, where
    location = [posx, posy] and points[i] = [xi, yi] both denote integral
    coordinates on the X-Y plane.

    Initially, you are facing directly east from your position. You cannot move
    from your position, but you can rotate. In other words, posx and posy
    cannot be changed. Your field of view in degrees is represented by angle,
    determining how wide you can see from any given view direction. Let d be
    the amount in degrees that you rotate counterclockwise. Then, your field of
    view is the inclusive range of angles [d - angle/2, d + angle/2].

    ===========================================================================================
    FUNCTION: int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
    Output: 3
    Explanation: The shaded region represents your field of view. All points
    can be made visible in your field of view, including [3,3] even though
    [2,2] is in front and in the same line of sight.

    --- Example 2 ---
    Input: points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
    Output: 4
    Explanation: All points can be made visible in your field of view,
    including the one at your location.

    --- Example 3 ---
    Input: points = [[1,0],[2,1]], angle = 13, location = [1,1]
    Output: 1
    Explanation: You can only see one of the two points, as shown above.


    *** Constraints ***
    1 <= points.length <= 10^5
    points[i].length == 2
    location.length == 2
    0 <= angle < 360
    0 <= posx, posy, xi, yi <= 100

*/

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.36% */
/* Space Beats: 38.78% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location)
    {
        int result = 0;

        vector<double> viewing_angles;
        int points_at_location = 0;

        for (const auto& point : points)
        {
            if (point[0] == location[0] && point[1] == location[1])
            {
                ++points_at_location;
            }
            else
            {
                double angle = atan2(point[1] - location[1], point[0] - location[0]) * 180.0 / M_PI;

                if (angle < 0)
                    angle += 360;

                viewing_angles.push_back(angle);
            }
        }

        /* Sort Viewing Angles */
        sort(viewing_angles.begin(), viewing_angles.end());

        const int N = viewing_angles.size();
        int L = 0;

        /* Duplicate Angles to Handle Circular Range */
        for (int i = 0; i < N; i++)
            viewing_angles.push_back(viewing_angles[i] + 360);

        /* Sliding Window */
        for (int R = 0; R < 2*N; R++)
        {
            while ((viewing_angles[R] - viewing_angles[L]) > angle + 1e-9)
                ++L;

            result = max(result, R - L + 1);
        }

        return result + points_at_location;
    }
};
