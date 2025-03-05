/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    2579) Count Total Number of Colored Cells
    =========================================

    ============
    Description:
    ============

    There exists an infinitely large two-dimensional grid of uncolored unit
    cells. You are given a positive integer n, indicating that you must do the
    following routine for n minutes:

        + At the first minute, color any arbitrary unit cell blue.

        + Every minute thereafter, color blue every uncolored cell that touches
          a blue cell.

    Below is a pictorial representation of the state of the grid after minutes
    1, 2, and 3.

                                     O
                      O             OOO
        O     -->    OOO    -->    OOOOO
                      O             OOO
                                     O

       n=1           n=2            n=3

    Return the number of colored cells at the end of n minutes.

    ========================================
    FUNCTION: long long coloredCells(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 1
    Explanation: After 1 minute, there is only 1 blue cell, so we return 1.

    --- Example 2 ---
    Input: n = 2
    Output: 5
    Explanation: After 2 minutes, there are 4 colored cells on the boundary
    and 1 in the center, so we return 5.


    *** Constraints ***
    1 <= n <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    n=1 and n=2 are unique cases, treat them separately.

    After that you can add additoinal:

        n=3)  3 * 2 + 2
        n=4)  5 * 2 + 2
        n=5)  7 * 2 + 2
        n=6)  9 * 2 + 2
        n=7) 11 * 2 + 2
        ...

    Why are we multiplying by 2 and why are we adding 2 afterwards?

    Consider this FOUNDATIONAL construction:

             O
            OOO
             O

    We can add, on TWO sides: one on top and two on the sides:

             X
            XOX
            OOO
            XOX
             X

    But we aren't done. We didn't add Xs on each side's "peak". That's why + 2.

             X
            XOX
           XOOOX
            XOX
             X

    And this is the n=3. From n=2 to n=3 we've added: 3 * 2 + 2.

    However, for n=4 we're going to add: 5 * 2 + 2.
    Look:

             _
            _X_
           _XOX_
          _XOOOX_
           _XOX_
            _X_
             _

    The pattern goes like this:

        n=3)  3 * 2 + 2
        n=4)  5 * 2 + 2
        n=5)  7 * 2 + 2
        n=6)  9 * 2 + 2
        n=7) 11 * 2 + 2
        ...

    Simple start at i=3 and go to our given Input n and add accordingly.
    Look at the code and it'll be clear.

    base is 3, because the difference between current i and base is our "step".

    Step is this
              |
              |
              v
        n=3)  3 * 2 + 2
        n=4)  5 * 2 + 2
        n=5)  7 * 2 + 2
        n=6)  9 * 2 + 2
        n=7) 11 * 2 + 2
        ...

    For example for n=7, step is:((7 - base) * 2)  * 2 + 2.

    But we can't just use this formula since we need all of the additions along
    the way. That's why we must iterate.

*/

/* Time  Beats: 20.68% */
/* Space Beats: 31.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long coloredCells(int n)
    {
        if (n == 1) return 1;
        if (n == 2) return 5;

        const long long FOUNDATION = 5;
        long long result = FOUNDATION;

        int base = 3;
        for (int i = 3; i <= n; i++)
        {
            int diff = i - base;
            result += (base + 2 * diff) * 2 + 2;
        }

        return result;
    }
};
