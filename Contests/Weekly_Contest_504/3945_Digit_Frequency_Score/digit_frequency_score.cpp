/*
    ============
    === EASY ===
    ============

    ===========================
    3945) Digit Frequency Score
    ===========================

    ============
    Description:
    ============

    You are given an integer n.

    The score of n is defined as the sum of d * freq(d) over all distinct
    digits d, where freq(d) denotes the number of times the digit d appears in
    n.

    Return an integer denoting the score of n.

    =========================================
    FUNCTION: int digitFrequencyScore(int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 122
    Output: 5
    Explanation:
        The digit 1 appears 1 time, contributing 1 * 1 = 1.
        The digit 2 appears 2 times, contributing 2 * 2 = 4.
        Thus, the score of n is 1 + 4 = 5.

    --- Example 2 ---
    Input: n = 101
    Output: 2
    Explanation:
        The digit 0 appears 1 time, contributing 0 * 1 = 0.
        The digit 1 appears 2 times, contributing 1 * 2 = 2.
        Thus, the score of n is 2.


    *** Constraints ***
    1 <= n <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  64.42% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int digitFrequencyScore(int n)
    {
        int result = 0;

        int freq[10] = {0};
        while (n > 0)
        {
            int digit = n % 10;
            freq[digit]++;

            n /= 10;
        }

        for (int d = 0; d < 10; d++)
            result += d * freq[d];

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If you look closely it's actually just a simple digit-sum, nothing special
    about it.

    We don't have to count frequencies of each digit and process those after
    we're done with everything else. Instead, we cam simply sum each digit as
    we go, turning this Solution to a simple "Digit sum" problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  81.09% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_Actually_Just_Digit_SUm {
public:
    int digitFrequencyScore(int n)
    {
        int sum = 0;

        while (n > 0)
        {
            int digit = n % 10;
            sum += digit;

            n /= 10;
        }

        return sum;
    }
};
