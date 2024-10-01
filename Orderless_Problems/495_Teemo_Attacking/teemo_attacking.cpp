#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    495) Teemo Attacking
    ===========================

    ============
    Description:
    ============

    Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo
    attacks Ashe, Ashe gets poisoned for a exactly duration seconds. More
    formally, an attack at second t will mean Ashe is poisoned during the
    inclusive time interval [t, t + duration - 1]. If Teemo attacks again
    before the poison effect ends, the timer for it is reset, and the poison
    effect will end duration seconds after the new attack.

    You are given a non-decreasing integer array timeSeries, where
    timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and
    an integer duration.

    Return the total number of seconds that Ashe is poisoned.

    ==========================================================================
    FUNCTION: int findPoisonedDuration(vector<int>& timeSeries, int duration);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: timeSeries = [1,4], duration = 2
    Output: 4
    Explanation: Teemo's attacks on Ashe go as follows:
    - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
    - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
    Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.


    --- Example 2 ---
    Input: timeSeries = [1,2], duration = 2
    Output: 3
    Explanation: Teemo's attacks on Ashe go as follows:
    - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
    - At second 2 however, Teemo attacks again and resets the poison timer.
      Ashe is poisoned for seconds 2 and 3.

    Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.


    *** Constraints ***
    1 <= timeSeries.length <= 10%4
    0 <= timeSeries[i], duration <= 10^7
    timeSeries is sorted in non-decreasing order.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.70% */
/* Space Beats: 67.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration)
    {
        const int n = timeSeries.size();
        int result = 0;

        for (int i = 0; i < n;)
        {
            int start = timeSeries[i];
            int end = start + duration - 1;

            int j = i+1;

            while (j < n && timeSeries[j] <= end)
            {
                end = timeSeries[j] + duration - 1;
                j++;
            }

            i = j;
            result += (end - start +1);
        }

        return result;
    }
};
