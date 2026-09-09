/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    3871) Count Commas in Range II
    ==============================

    ============
    Description:
    ============

    You are given an integer n.

    Return the total number of commas used when writing all integers from
    [1, n] (inclusive) in standard number formatting.

    In standard formatting:

        + A comma is inserted after every three digits from the right.
        + Numbers with fewer than 4 digits contain no commas.

    =============================================
    FUNCTION: long long countCommas(long long n);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1002
    Output: 3
    Explanation:
    The numbers "1,000", "1,001", and "1,002" each contain one comma, giving a
    total of 3.

    --- Example 2 ---
    Input: n = 998
    Output: 0
    Explanation:
    All numbers from 1 to 998 have fewer than four digits. Therefore, no commas
    are used.


    *** Constraints ***
    1 <= n <= 10^15

*/

/* Time  Beats: 100.00% */
/* Space Beats:  19.20% */

/* Time  Complexity: O(log10(N)) */
/* Space Complexity: O(1)        */
class Solution {
public:
    long long countCommas(long long n)
    {
        if (n < 1000)
            return 0;

        long long result = 0LL;
        
        int commas = 1;
        int zeroes = 3; // 1000

        long long number_start = 1000LL;
        while (number_start < n)
        {
            commas = zeroes / 3;

            long long number_end = 10 * number_start;
            result += commas * (number_end - number_start);

            ++zeroes;
            number_start = number_end;
        }

        if (number_start == n)
            return result + 1LL * (zeroes / 3); // Since zeroes are INCREMENTED
                                                // and possible (zeroes / 3)
                                                // can now give a higher number
                                                // of commas. Example: n=10^6
                                                //                     n=10^9
                                                //                     n=10^12
                                                //                     n=10^15

        return result - 1LL * (commas * (number_start - (n + 1)));
    }
};
