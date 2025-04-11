/*
    ============
    === EASY ===
    ============

    ==============================
    2843) Count Symmetric Integers
    ==============================

    ============
    Description:
    ============

    You are given two positive integers low and high.

    An integer x consisting of 2 * n digits is symmetric if the sum of the
    first n digits of x is equal to the sum of the last n digits of x.

    Numbers with an odd number of digits are never symmetric.

    Return the number of symmetric integers in the range [low, high].

    ========================================================
    FUNCTION: int countSymmetricIntegers(int low, int high);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: low = 1, high = 100
    Output: 9
    Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33,
                 44, 55, 66, 77, 88, and 99.

    --- Example 2 ---
    Input: low = 1200, high = 1230
    Output: 4
    Explanation: There are 4 symmetric integers between 1200 and 1230: 1203,
                 1212, 1221, and 1230.


    *** Constraints ***
    1 <= low <= high <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    Very specific problem, so there's this Brute-Force like Solution since it
    is allowed by the Constraints.

*/

/* Time  Beats: 89.06% */
/* Space Beats: 96.76% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countSymmetricIntegers(int low, int high)
    {
        int count = 0;

        for (int num = low; num <= high; num++)
        {
            int tmp = num;

            if (tmp < 10)
            {
                num = 10 - 1;
                continue;
            }

            if (tmp >= 100 && tmp < 1000)
            {
                num = 999;
                continue;
            }

            if (tmp == 1e4)
                continue;

            if (tmp >= 10 && tmp < 100)
            {
                int R = tmp % 10;
                int L = tmp / 10;

                if (L == R)
                    count++;
            }
            else // tmp >= 1000 && tmp < 1e4
            {
                int R = tmp % 10;
                tmp /= 10;
                R += tmp % 10;
                tmp /= 10;

                int L = tmp % 10;
                tmp /= 10;
                L += tmp % 10;
                tmp /= 10;

                if (L == R)
                    count++;
            }
        }

        return count;
    }
};
