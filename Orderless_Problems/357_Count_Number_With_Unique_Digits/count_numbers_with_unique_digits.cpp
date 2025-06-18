/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    357) Count Numbers with Unique Digits
    =====================================

    ============
    Description:
    ============

    Given an integer n, return the count of all numbers with unique digits, x,
    where 0 <= x < 10n.

    ==================================================
    FUNCTION: int countNumbersWithUniqueDigits(int n);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: 91
    Explanation: The answer should be the total numbers in the range of
                 0 <= x < 100, excluding 11,22,33,44,55,66,77,88,99

    --- Example 2 ---
    Input: n = 0
    Output: 1


    *** Constraints ***
    0 <= n <= 8

*/

/*
    ------------
    --- IDEA ---
    ------------

    Following the hint. Let f(n) = count of number with unique digits of length n.

    f(1) = 10. (0, 1, 2, 3, ...., 9)

    f(2) = 9 * 9.
    Because for each number i from 1 ... 9, we can pick j to form a 2-digit
    number ij and there are 9 numbers that are different from i for j to choose
    from.

    f(3) = f(2) * 8 = 9 * 9 * 8.
    Because for each number with unique digits of length 2, say ij, we can pick
    k to form a 3 digit number ijk and there are 8 numbers that are different
    from i and j for k to choose from.

    Similarly f(4) = f(3) * 7 = 9 * 9 * 8 * 7....

    ...

    f(10) = 9 * 9 * 8 * 7 * 6 * ... * 1

    f(11) = 0 = f(12) = f(13)....

    Any number with length > 10 couldn't be unique digits number.

    The problem is asking for numbers from 0 to 10^n.
    Hence return f(1) + f(2) + .. + f(n)

    There are only 11 different asnwers, therefore you can create a lookup
    table for it. This problem is O(1) in essence.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.26% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countNumbersWithUniqueDigits(int n)
    {
        if (n == 0)
            return 1;

        int result = 10; // First 10 numbers fulfill the criterion

        int unique_digits = 9;
        int available_numbers = 9;
        while (n-- > 1 && available_numbers > 0)
        {
            unique_digits = unique_digits * available_numbers;
            result += unique_digits;

            available_numbers--;
        }

        return result;
    }
};
