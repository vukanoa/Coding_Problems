/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2249) Count a Lattice Points inside a Circle
    ============================================

    ============
    Description:
    ============


    Given a 2D integer array circles where circles[i] = [xi, yi, ri] represents
    the center (xi, yi) and radius ri of the ith circle drawn on a grid, return
    the number of lattice points that are present inside at least one circle.

    Note:

        + A lattice point is a point with integer coordinates.

        + Points that lie on the circumference of a circle are also considered
          to be inside it.

    ===============================================================
    FUNCTION: int countLatticePoints(vector<vector<int>>& circles);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: circles = [[2,2,1]]
    Output: 5
    Explanation:
    The figure above shows the given circle.
    The lattice points present inside the circle are (1, 2), (2, 1), (2, 2),
    (2, 3), and (3, 2) and are shown in green. Other points such as (1, 1) and
    (1, 3), which are shown in red, are not considered inside the circle.
    Hence, the number of lattice points present inside at least one circle is
    5.

    --- Example 2 ---
    Input: circles = [[2,2,2],[3,4,1]]
    Output: 16
    Explanation:
    The figure above shows the given circles.
    There are exactly 16 lattice points which are present inside at least one
    circle. Some of them are (0, 2), (2, 0), (2, 4), (3, 2), and (4, 4).

    *** Constraints ***
    1 <= circles.length <= 200
    circles[i].length == 3
    1 <= xi, yi <= 100
    1 <= ri <= min(xi, yi)

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 62.03% */
/* Space Beats: 59.02% */

/* Time  Complexity: O(N * r^2) */
/* Space Complexity: O(N + r^2) */
class Solution {
public:
    int countLatticePoints(vector<vector<int>> circles)
    {
        unordered_set<int> result;

        for (const auto& circle : circles)
        {
            const auto& x = circle[0];
            const auto& y = circle[1];
            const auto& r = circle[2];

            for (int row_offset = -r; row_offset <= r; row_offset++)
            {
                for (int col_offset = -r; col_offset <= r; col_offset++)
                {
                    if (row_offset * row_offset + col_offset * col_offset <= r * r)
                        result.insert((circle[0] + row_offset) * 1000 + circle[1] + col_offset);
                }
            }
        }

        return result.size();
    }
};
