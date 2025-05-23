/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3111) Minimum Rectangles to Cover Points
    ========================================

    ============
    Description:
    ============

    You are given a 2D integer array points, where points[i] = [xi, yi].
    You are also given an integer w. Your task is to cover all the given points
    with rectangles.

    Each rectangle has its lower end at some point (x1, 0) and its upper end at
    some point (x2, y2), where x1 <= x2, y2 >= 0, and the condition
    x2 - x1 <= w must be satisfied for each rectangle.

    A point is considered covered by a rectangle if it lies within or on the
    boundary of the rectangle.

    Return an integer denoting the minimum number of rectangles needed so that
    each point is covered by at least one rectangle.

    =====
    Note: A point may be covered by more than one rectangle.
    =====

    =============================================================================
    FUNCTION: int minRectanglesToCoverPoints(vector<vector<int>>& points, int w);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[2,1],[1,0],[1,4],[1,8],[3,5],[4,6]], w = 1
    Output: 2
    Explanation:
    The image above shows one possible placement of rectangles to cover the points:
        A rectangle with a lower end at (1, 0) and its upper end at (2, 8)
        A rectangle with a lower end at (3, 0) and its upper end at (4, 8)


    --- Example 2 ---
    Input: points = [[0,0],[1,1],[2,2],[3,3],[4,4],[5,5],[6,6]], w = 2
    Output: 3
    Explanation:
    The image above shows one possible placement of rectangles to cover the points:
        A rectangle with a lower end at (0, 0) and its upper end at (2, 2)
        A rectangle with a lower end at (3, 0) and its upper end at (5, 5)
        A rectangle with a lower end at (6, 0) and its upper end at (6, 6)


    --- Example 3 ---
    Input: points = [[2,3],[1,2]], w = 0
    Output: 2
    Explanation:
    The image above shows one possible placement of rectangles to cover the points:
        A rectangle with a lower end at (1, 0) and its upper end at (1, 2)
        A rectangle with a lower end at (2, 0) and its upper end at (2, 3)


    *** Constraints ***
    1 <= points.length <= 10^5
    points[i].length == 2
    0 <= xi == points[i][0] <= 10^9
    0 <= yi == points[i][1] <= 10^9
    0 <= w <= 10^9
    All pairs (xi, yi) are distinct.

*/

#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. It's seems much harder than it actually is.

*/

/* Time  Beats: 17.98% */
/* Space Beats: 13.11% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w)
    {
        const int N = points.size();
        int result = 1;

        unordered_set<int> uset;
        for (const auto& point : points)
            uset.insert(point[0]);

        vector<int> horizontal_points_at(uset.begin(), uset.end());
        sort(horizontal_points_at.begin(), horizontal_points_at.end());

        int start = horizontal_points_at[0];
        for (int i = 1; i < horizontal_points_at.size(); i++)
        {
            if (horizontal_points_at[i] - start > w)
            {
                result++;
                start = horizontal_points_at[i];
            }
        }

        return result;
    }
};
