/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1680) Concatenation of Consectuive Binary Numbers
    =================================================

    ============
    Description:
    ============

    Given an integer n, return the decimal value of the binary string formed by
    concatenating the binary representations of 1 to n in order, modulo 109 +
    7.

    ========================================
    FUNCTION: int concatenatedBinary(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: 1
    Explanation: "1" in binary corresponds to the decimal value 1.

    --- Example 2 ---
    Input: n = 3
    Output: 27
    Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
                 After concatenating them, we have "11011", which corresponds
                 to the decimal value 27.

    --- Example 3 ---
    Input: n = 12
    Output: 505379714
    Explanation: The concatenation results in
                 "1101110010111011110001001101010111100". The decimal value of
                 that is 118505380540. After modulo 109 + 7, the result is
                 505379714.


    *** Constraints ***
    1 <= n <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.55% */
/* Space Beats: 69.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solutions {
public:
    int concatenatedBinary(int n)
    {
        const int MOD = 1e9 + 7;
        long long result = 0;

        int bits = 0;
        for (int num = 1; num <= n; num++)
        {
            if ((num & (num-1)) == 0)
                bits++;

            result = ((result << bits) | num) % MOD;
        }

        return static_cast<int>(result);
    }
};
