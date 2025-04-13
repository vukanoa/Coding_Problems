/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1922) Count Good Numbers
    ===========================

    ============
    Description:
    ============

    A digit string is good if the digits (0-indexed) at even indices are even
    and the digits at odd indices are prime (2, 3, 5, or 7).

        For example, "2582" is good because the digits (2 and 8) at even
        positions are even and the digits (5 and 2) at odd positions are prime.

        However, "3245" is not good because 3 is at an even index but is not
        even.

    Given an integer n, return the total number of good digit strings of length
    n. Since the answer may be large, return it modulo 109 + 7.

    A digit string is a string consisting of digits 0 through 9 that may
    contain leading zeros.

    ============================================
    FUNCTION: int countGoodNumbers(long long n);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 5
    Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".

    --- Example 2 ---
    Input: n = 4
    Output: 400

    --- Example 3 ---
    Input: n = 50
    Output: 564908303


    *** Constraints ***
    1 <= n <= 10^15

*/

/*
    ------------
    --- IDEA ---
    ------------

    Crux of this problem is "Fast Exponentiation".

    If you want to find a number:

        base^exponent

    then the easiest way is to solve this problem repetitively multiplying
    "base" "exponent" times.

    It would look something like this:

    // Function to calculate power using brute force approach
    long long find_power(int base, int exponent)
    {
        long long result = 1;

        for (int i = 0; i < exponent; ++i)
            result *= base;

        return result;
    }

    However, the problem with this is that it takes: O(N) Time Complexity.

    Since we're told in the Constraints of this very problem that:

        1 <= n <= 10^15

    we can't use this "Brute Force" approach to calculate the number, it would
    take O(N) which would be O(10^15) and that is too much for LeetCode, we'll
    get TLE.


    So to overcome that we can simply do a "Fast Exponentiation".
    It's literally the same as "find_power", but its Time Complexity is O(logN)
    which is always acceptable.

    long long fast_exponentiation(long long base, long long exponent)
    {
        long long result = 1;
        base %= MOD;

        while (exponent > 0)
        {
            // If the current LSB is set(i.e. 1)
            if (exponent & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;

            // Right Shift
            exponent >>= 1;
        }

        return result;
    }


    Now the remaining part is easy.

    There are exacly:  (N + 1) / 2  EVEN positions
    There are exactly: N / 2        ODD  positions

    At even positions all digits we're allowed to put are: {0, 2, 4, 6, 8}
    At odd  positions all digits we're allowed to put are: {2, 3, 5, 7}


    Therefore:
        + At each of (N+1)/2 positions we can put 5 numbers.
        + At each of N/2     positions we can put 4 numbers.

    We just do fast exponentiation on each and multiple the result of both.
    (Be careful to MOD intermediate results as well since 10^15 is HUGE)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  3.22% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
private:
    const long long MOD = 1e9 + 7;

public:
    int countGoodNumbers(long long n)
    {
        long long even_positions = (n + 1) / 2;
        long long odd_positions  = n / 2;

        long long result = 1;
        result = (result * fast_exponentiation(5LL, even_positions)) % MOD;
        result = (result * fast_exponentiation(4LL, odd_positions))  % MOD;

        return static_cast<int>(result);
    }

private:
    long long fast_exponentiation(long long base, long long exponent)
    {
        long long result = 1;
        base %= MOD;

        while (exponent > 0)
        {
            // If the current LSB is set(i.e. 1)
            if (exponent & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;

            // Right Shift
            exponent >>= 1;
        }

        return result;
    }
};
