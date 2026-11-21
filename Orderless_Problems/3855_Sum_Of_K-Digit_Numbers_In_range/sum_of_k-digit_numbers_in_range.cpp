/*
    ============
    === HARD ===
    ============

    =====================================
    3855) Sum of K-Digit Numbers in Range
    =====================================

    ============
    Description:
    ============

    You are given three integers l, r, and k.

    Consider all possible integers consisting of exactly k digits, where each
    digit is chosen independently from the integer range [l, r] (inclusive). If
    0 is included in the range, leading zeros are allowed.

    Return an integer representing the sum of all such numbers. Since the
    answer may be very large, return it modulo 109 + 7.

    ================================================
    FUNCTION: int sumOfNumbers(int l, int r, int k);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: l = 1, r = 2, k = 2
    Output: 66
    Explanation:
        All numbers formed using k = 2 digits in the range [1, 2] are 11, 12,
        21, 22.
        The total sum is 11 + 12 + 21 + 22 = 66.

    --- Example 2 ---
    Input: l = 0, r = 1, k = 3
    Output: 444
    Explanation:
        All numbers formed using k = 3 digits in the range [0, 1] are 000, 001,
        010, 011, 100, 101, 110, 111.
        These numbers without leading zeros are 0, 1, 10, 11, 100, 101, 110,
        111.
        The total sum is 444.

    --- Example 3 ---
    Input: l = 5, r = 5, k = 10
    Output: 555555520
    Explanation:
        5555555555 is the only valid number consisting of k = 10 digits in the
        range [5, 5]. The total sum is 5555555555 % (109 + 7) = 555555520.



    *** Constraints ***
    0 <= l <= r <= 9
    1 <= k <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 63.44% */
/* Space Beats: 35.48% */

/* Time  Complexity: O(logK) */
/* Space Complexity: O(1)    */
class Solution {
    const long long MOD = 1e9+7;

public:
    int sumOfNumbers(int l, int r, int k)
    {
        long long digit_count = r - l + 1;
        
        long long avg_digit_sum = ((digit_count * (l + r)) / 2) % MOD;

        long long remaining_combinations = modular_exponentiation(digit_count, k-1);
        long long ten_to_k               = modular_exponentiation(10         , k  );
        
        long long inverse_nine     = modular_exponentiation(9, MOD-2);
        long long geometric_factor = ((ten_to_k-1 + MOD) % MOD * inverse_nine) % MOD;

        long long result = avg_digit_sum;

        result = (result * remaining_combinations) % MOD;
        result = (result * geometric_factor      ) % MOD;

        return result;
        
    }

    long long modular_exponentiation(long long base, long long exp)
    {
        base %= MOD; // Just in case
        long long result = 1LL;

        while (exp > 0) // 19 = 1 + 2 + 16
        {
            if (exp & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;
            exp >>= 1;
        }

        return result;
    }
};
