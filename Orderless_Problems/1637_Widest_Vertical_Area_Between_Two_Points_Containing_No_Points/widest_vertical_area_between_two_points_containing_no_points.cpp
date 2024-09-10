#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ==================================================================
    1637) Widest Vertical Area Between Two Points Containing No Points
    ==================================================================

    ============
    Description:
    ============

    Given n points on a 2D plane where points[i] = [xi, yi], Return the widest
    vertical area between two points such that no points are inside the area.

    A vertical area is an area of fixed-width extending infinitely along the
    y-axis (i.e., infinite height). The widest vertical area is the one with
    the maximum width.

    Note that points on the edge of a vertical area are not considered included
    in the area.

    ==================================================================
    FUNCTION: int maxWidthOfVerticalArea(vector<vector<int>>& points);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[8,7],[9,9],[7,4],[9,7]]
    Output: 1
    Explanation: Both the red and the blue area are optimal.

    --- Example 2 ---
    Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
    Output: 3


    *** Constraints ***
    n == points.length
    2 <= n <= 10^5
    points[i].length == 2
    0 <= xi, yi <= 10^9

*/


/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points)
    {
        const int n = points.size();

        // Sort the array on the first value in ascending order.
        sort(points.begin(), points.end());

        // Calculating Area between each points and maintining that in maxArea
        int max_area = 0;
        for (int i = 1; i < n; i++)
        {
            int currArea = points[i][0] - points[i-1][0];
            max_area = max(max_area, currArea);
        }

        return max_area;
    }
};
