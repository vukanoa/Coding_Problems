/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2443) Sum of Numbers and ITs Reverse
    ====================================

    ============
    Description:
    ============

    Given a non-negative integer num, return true if num can be expressed as
    the sum of any non-negative integer and its reverse, or false otherwise.

    ==============================================
    FUNCTION: bool sumOfNumberAndReverse(int num);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 443
    Output: true
    Explanation: 172 + 271 = 443 so we return true.

    --- Example 2 ---
    Input: num = 63
    Output: false
    Explanation: 63 cannot be expressed as the sum of a non-negative integer
                 and its reverse so we return false.

    --- Example 3 ---
    Input: num = 181
    Output: true
    Explanation: 140 + 041 = 181 so we return true. Note that when a number is
                 reversed, there may be leading zeros.


    *** Constraints ***
    0 <= num <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.86% */
/* Space Beats: 71.40% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool sumOfNumberAndReverse(int num)
    {
        for (int first_number = num / 2; first_number <= num; first_number++)
        {
            if (first_number + reverse_number(first_number) == num)
                return true;
        }

        return false;
    }

private:
    int reverse_number(int number)
    {
        int reversed = 0;

        while (number > 0)
        {
            int digit = number % 10;
            reversed = reversed * 10 + digit;

            number /= 10;
        }

        return reversed;
    }
};
