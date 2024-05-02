#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    319) Bulb Switcher
    ===========================

    ============
    Description:
    ============

    There are n bulbs that are initially off. You first turn on all the bulbs,
    then you turn off every second bulb.

    On the third round, you toggle every third bulb (turning on if it's off or
    turning off if it's on). For the ith round, you toggle every i bulb. For
    the nth round, you only toggle the last bulb.

    Return the number of bulbs that are on after n rounds.

    ================================
    FUNCTION: int bulbSwitch(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        Round 1)   ON  ON  ON
                    1   2   3

        Round 2)   ON  OFF ON
                    1   2   3

        Round 3)   ON  OFF OFF
                    1   2   3

    Input: n = 3
    Output: 1
    Explanation: At first, the three bulbs are [off, off, off].
    After the first round, the three bulbs are [on, on, on].
    After the second round, the three bulbs are [on, off, on].
    After the third round, the three bulbs are [on, off, off].
    So you should return 1 because there is only one bulb is on.



    --- Example 2 ---
    Input: n = 0
    Output: 0


    --- Example 3 ---
    Input: n = 1
    Output: 1


    *** Constraints ***
    0 <= n <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.46% */
/* Space Beats: 23.40% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int bulbSwitch(int n)
    {
        int sum   = 0;
        int count = 0;

        for(int i = 1; i <= n; i += 2)
        {
            sum = sum + i;

            if(n < sum)
                break;

            count++;
        }

        return count;
    }
};
