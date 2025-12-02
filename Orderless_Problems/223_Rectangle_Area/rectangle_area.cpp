/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    223) Rectangle Area
    ===========================

    ============
    Description:
    ============

    Given the coordinates of two rectilinear rectangles in a 2D plane, return
    the total area covered by the two rectangles.

    The first rectangle is defined by its bottom-left corner (ax1, ay1) and its
    top-right corner (ax2, ay2).

    The second rectangle is defined by its bottom-left corner (bx1, by1) and
    its top-right corner (bx2, by2).

    ==================================================================================================
    FUNCTION: int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
    ==================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
    Output: 45

    --- Example 2 ---
    Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
    Output: 16


    *** Constraints ***
    -10^4 <= ax1 <= ax2 <= 10^4
    -10^4 <= ay1 <= ay2 <= 10^4
    -10^4 <= bx1 <= bx2 <= 10^4
    -10^4 <= by1 <= by2 <= 10^4

*/

#include <algorithm>
using namespace std;



/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This is a common trick you should learn)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.44% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int computeArea( int ax1, int ay1, int ax2, int ay2,
                     int bx1, int by1, int bx2, int by2 )
    {
        int area1 = (ax2 - ax1) * (ay2 - ay1);
        int area2 = (bx2 - bx1) * (by2 - by1);

        int overlap_width  = max(0, min(ax2, bx2) - max(ax1, bx1));
        int overlap_height = max(0, min(ay2, by2) - max(ay1, by1));

        int overlap_area = overlap_width * overlap_height;

        int total_area = area1 + area2 - overlap_area;

        return total_area;
    }
};
