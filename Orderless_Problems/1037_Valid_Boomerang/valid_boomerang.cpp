/*
    ============
    === EASY ===
    ============

    ===========================
    1037) Valid Boomerang
    ===========================

    ============
    Description:
    ============

    Given an array points where points[i] = [xi, yi] represents a point on the
    X-Y plane, return true if these points are a boomerang.

    A boomerang is a set of three points that are all distinct and not in a
    straight line.

    ========================================================
    FUNCTION: bool isBoomerang(vector<vector<int>>& points);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,1],[2,3],[3,2]]
    Output: true

    --- Example 2 ---
    Input: points = [[1,1],[2,2],[3,3]]
    Output: false


    *** Constraints ***
    points.length == 3
    points[i].length == 2
    0 <= xi, yi <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.85% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points)
    {
        int x1 = points[0][0];
        int y1 = points[0][1];

        int x2 = points[1][0];
        int y2 = points[1][1];

        int x3 = points[2][0];
        int y3 = points[2][1];

        return (x1 - x2) * (y1 - y3) != (x1 - x3) * (y1 - y2);
    }
};
