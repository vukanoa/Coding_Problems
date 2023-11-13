#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    2483) Minimum Penalty For Shop
    ==============================

    ============
    Description:
    ============

    You are given the customer visit log of a shop represented by a 0-indexed string customers consisting only of characters 'N' and 'Y':

        if the ith character is 'Y', it means that customers come at the ith hour
        whereas 'N' indicates that no customers come at the ith hour.

    If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:

        For every hour when the shop is open and no customers come, the penalty increases by 1.
        For every hour when the shop is closed and customers come, the penalty increases by 1.

    Return the earliest hour at which the shop must be closed to incur a minimum penalty.

    Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.

    ================================================
    FUNCTION: int bestClosingTime(string customers);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: customers = "YYNY"
    Output: 2
    Explanation:
    - Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
    - Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
    - Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
    - Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
    - Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
    Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is
    earlier, the optimal closing time is 2.


    --- Example 2 ---
    Input: customers = "NNNNN"
    Output: 0
    Explanation: It is best to close the shop at the 0th hour as no customers
    arrive.


    --- Example 3 ---
    Input: customers = "YYYY"
    Output: 4
    Explanation: It is best to close the shop at the 4th hour as customers
    arrive at each hour.


    *** Constraints ***
    1 <= customers.length <= 10^5
    customers consists only of characters 'Y' and 'N'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    count left N's and right Y's

    Essentially:
        how many N's left  of the current position   NOT  INCLUDING current pos
            +(Plus)
        how many Y's right of the current position INDEED INCLUDING current pos

    That's how we count an incur of penalty if we close at hour of current pos.


    // My own Example
    Y Y N Y Y N N Y
    0 1 2 3 4 5 6 7

    0th -> 5     0N     5Y
    1th -> 4     0N     4Y
    2th -> 3     0N     3Y
    3th -> 4     1N     3Y
    4th -> 3     1N     2Y
    5th -> 2     1N     1Y
    6th -> 3     2N     1Y
    7th -> 4     3N     1Y
    8th -> 3     3N     0Y

    2nd hour is before 4th, 6-th and 8th, therefore we returnd hour 2.



    // Example 1
    Y Y N Y
    0 1 2 3

    0th -> 3     0N     3Y
    1th -> 2     0N     2Y
    2th -> 1     0N     1Y
    3th -> 2     1N     1Y
    4th -> 1     1N     0Y

    2nd hour is before 4th, so we return 2.



    // Example 17
    N Y N N N Y Y N
    0 1 2 3 4 5 6 7

    0th -> 3     0N     3Y
    1th -> 4     1N     3Y
    2th -> 3     1N     2Y
    3th -> 4     2N     2Y
    4th -> 5     3N     2Y
    5th -> 6     4N     2Y
    6th -> 5     4N     1Y
    7th -> 4     4N     0Y

    0th hour is before 2nd hour, therefore we return 0.

*/

/* Time  Beats: 94.90% */
/* Space Beats: 90.65% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int bestClosingTime(string customers)
    {
        int left_N  = 0;
        int right_Y = 0;

        // Count Y's
        for (char& c : customers)
        {
            if (c == 'Y')
                right_Y++;
        }

        int hour = 0;
        int min = left_N + right_Y;

        for (int i = 1; i <= customers.length(); i++)
        {
            if (customers[i-1] == 'Y')
                right_Y--;
            else
                left_N++;

            if ((left_N + right_Y) < min)
            {
                min = left_N + right_Y;
                hour = i;
            }
        }

        return hour;
    }
};
