#include <iostream>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ==================================
    2543) Check if Points is Reachable
    ==================================

    ============
    Description:
    ============

    There exists an infinitely large grid. You are currently at point (1, 1),
    and you need to reach the point (targetX, targetY) using a finite number of
    steps.

    In one step, you can move from point (x, y) to any one of the following
    points:

        (x, y - x)
        (x - y, y)
        (2 * x, y)
        (x, 2 * y)

    Given two integers targetX and targetY representing the X-coordinate and
    Y-coordinate of your final position, return true if you can reach the point
    from (1, 1) using some number of steps, and false otherwise.

    =========================================
    FUNCTION: bool isReachable(int x, int y);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: targetX = 6, targetY = 9
    Output: false
    Explanation: It is impossible to reach (6,9) from (1,1) using any sequence
                 of moves, so false is returned.

    --- Example 2 ---
    Input: targetX = 4, targetY = 7
    Output: true
    Explanation: You can follow the path (1,1) -> (1,2) -> (1,4) -> (1,8) ->
                 (1,7) -> (2,7) -> (4,7).


    *** Constraints ***
    1 <= targetX, targetY <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Greatest Common Divisor.
    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 51.35%  */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution {
public:
    bool isReachable(int x, int y)
    {
        int g = __gcd(x, y);

        while(g % 2 == 0)
            g /= 2;

        return g == 1;
    }
};