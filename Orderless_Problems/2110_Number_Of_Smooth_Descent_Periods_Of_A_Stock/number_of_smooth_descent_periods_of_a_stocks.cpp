/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    2110) Number of Smooth Descent Periods of a Stock
    =================================================

    ============
    Description:
    ============

    You are given an integer array prices representing the daily price history
    of a stock, where prices[i] is the stock price on the ith day.

    A smooth descent period of a stock consists of one or more contiguous days
    such that the price on each day is lower than the price on the preceding
    day by exactly 1. The first day of the period is exempted from this rule.

    Return the number of smooth descent periods.

    ===========================================================
    FUNCTION: long long getDescentPeriods(vector<int>& prices);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prices = [3,2,1,4]
    Output: 7
    Explanation: There are 7 smooth descent periods:
    [3], [2], [1], [4], [3,2], [2,1], and [3,2,1]
    Note that a period with one day is a smooth descent period by the
    definition.

    --- Example 2 ---
    Input: prices = [8,6,7,7]
    Output: 4
    Explanation: There are 4 smooth descent periods: [8], [6], [7], and [7]
    Note that [8,6] is not a smooth descent period as 8 - 6 ≠ 1.

    --- Example 3 ---
    Input: prices = [1]
    Output: 1
    Explanation: There is 1 smooth descent period: [1]


    *** Constraints ***
    1 <= prices.length <= 10^5
    1 <= prices[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  24.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices)
    {
        const int N = prices.size();
        long long result = 0;
        long long count = 0;

        for (int i = 0; i < N; i++)
        {
            if (i == 0 || (prices[i-1] - 1) != prices[i])
                count = 1; // Start new descent period
            else
                count++;   // Extend current descent period

            result += count;
        }

        return result;
    }
};
