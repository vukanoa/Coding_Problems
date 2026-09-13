/*
    ============
    === HARD ===
    ============

    ===========================
    850) Rectangle Area II
    ===========================

    ============
    Description:
    ============

    You are given a 2D array of axis-aligned rectangles. Each rectangle[i] =
    [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the
    coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates
    of the top-right corner.

    Calculate the total area covered by all rectangles in the plane. Any area
    covered by two or more rectangles should only be counted once.

    Return the total area. Since the answer may be too large, return it modulo
    10^9 + 7.

    =============================================================
    FUNCTION: int rectangleArea(vector<vector<int>>& rectangles);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
    Output: 6
    Explanation: A total area of 6 is covered by all three rectangles, as
    illustrated in the picture.
    From (1,1) to (2,2), the green and red rectangles overlap.
    From (1,0) to (2,3), all three rectangles overlap.

    --- Example 2 ---
    Input: rectangles = [[0,0,1000000000,1000000000]]
    Output: 49
    Explanation: The answer is 1018 modulo (109 + 7), which is 49.


    *** Constraints ***
    1 <= rectangles.length <= 200
    rectanges[i].length == 4
    0 <= xi1, yi1, xi2, yi2 <= 10^9
    xi1 <= xi2
    yi1 <= yi2
    All rectangles have non zero area.

*/

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.44% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles)
    {
        const int MOD = 1e9 + 7;

        set<int> y_coordinates; // SORTED in ASCENDING order by 'y' coordinates
        for (const auto& rect: rectangles)
        {
            const int& x1 = rect[0];
            const int& y1 = rect[1];

            const int& x2 = rect[2];
            const int& y2 = rect[3];

            /* Insert */
            y_coordinates.insert(y1);
            y_coordinates.insert(y2);
        }

        // Sort rectangle in ASCENDING order by x1
        sort(rectangles.begin(), rectangles.end(), [](const auto& r1, const auto& r2) {
            return r1[0] < r2[0];
        });
        
        /* Sweep Line from BOTTOM to TOP */
        int prev_y = *y_coordinates.begin();

        long long result = 0;
        for (const auto& curr_y : y_coordinates)
        {
            long long height  = curr_y - prev_y;

            long long x_start = rectangles.front()[0];
            long long x_end   = x_start;

            for (const auto& rect : rectangles)
            {
                const int& x1 = rect[0];
                const int& y1 = rect[1];

                const int& x2 = rect[2];
                const int& y2 = rect[3];

                if (y1 <= prev_y && curr_y <= y2)
                {
                    if (x1 > x_end)
                    {
                        result  += height * (x_end - x_start) % MOD;
                        x_start  = x1;
                    }

                    if (x2 > x_end)
                    {
                        x_end = x2;
                    }
                }
            }

            result += height * (x_end - x_start) % MOD;
            prev_y  = curr_y;
        }
        
        return result % MOD;
    }
};
