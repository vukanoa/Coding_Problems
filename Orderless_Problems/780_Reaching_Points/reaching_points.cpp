#include <iostream>

/*
    ============
    === HARD ===
    ============

    ===========================
    780) Reaching Points
    ===========================

    ============
    Description:
    ============

    Given four integers sx, sy, tx, and ty, return true if it is possible to
    convert the point (sx, sy) to the point (tx, ty) through some operations,
    or false otherwise.

    The allowed operation on some point (x, y) is to convert it to either (x, x
    + y) or (x + y, y).

    ==============================================================
    FUNCTION: bool reachingPoints(int sx, int sy, int tx, int ty);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sx = 1, sy = 1, tx = 3, ty = 5
    Output: true
    Explanation:
    One series of moves that transforms the starting point to the target is:
    (1, 1) -> (1, 2)
    (1, 2) -> (3, 2)
    (3, 2) -> (3, 5)


    --- Example 2 ---
    Input: sx = 1, sy = 1, tx = 2, ty = 2
    Output: false


    --- Example 3 ---
    Input: sx = 1, sy = 1, tx = 1, ty = 1
    Output: true


    *** Constraints ***
    1 <= sx, sy, tx, ty <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.07% */
/* Space Beats: 49.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty)
    {
        while (tx >= sx && ty >= sy)
        {
            if (tx == sx)
                return (ty - sy) % tx == 0;

            if (ty == sy)
                return (tx - sx) % ty == 0;

            if (ty > tx)
                ty = ty % tx;
            else
                tx = tx % ty;
        }

        return false;
    }
};
