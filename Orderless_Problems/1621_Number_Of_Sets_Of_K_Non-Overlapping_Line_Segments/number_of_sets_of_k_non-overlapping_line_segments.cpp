/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    1621) Number of Sets of K Non-Overlapping Line Segments
    =======================================================

    ============
    Description:
    ============

    Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x
    = i, find the number of ways we can draw exactly k non-overlapping line
    segments such that each segment covers two or more points. The endpoints of
    each segment must have integral coordinates. The k line segments do not
    have to cover all n points, and they are allowed to share endpoints.

    Return the number of ways we can draw k non-overlapping line segments.
    Since this number can be huge, return it modulo 10^9 + 7.

    =========================================
    FUNCTION: int numberOfSets(int n, int k);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, k = 2
    Output: 5
    Explanation: The two line segments are shown in red and blue.
    The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)},
    {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.

    --- Example 2 ---
    Input: n = 3, k = 1
    Output: 3
    Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.

    --- Example 3 ---
    Input: n = 30, k = 7
    Output: 796297179
    Explanation: The total number of possible ways to draw 7 line segments is
                 3796297200. Taking this number modulo 109 + 7 gives us
                 796297179.


    *** Constraints ***
    2 <= n <= 1000
    1 <= k <= n-1

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.13% */

/* Time  Complexity: O(k + log(MOD)) */
/* Space Complexity: O(1)            */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int numberOfSets(int n, int k)
    {
        // We need C(n + k - 1, 2k), i.e. "(n + k -1) choose 2*k"
        int a = n + k - 1;
        int b = 2 * k;

        long long numerator   = 1; // Numerator
        long long denominator = 1; // Denominator

        // Numerator   = a * (a - 1) * ... * (a - b + 1)
        // Denominator = b!
        for (int i = 1; i <= 2*k; i++)
        {
            numerator   = 1LL * numerator   * a % MOD;
            --a;

            denominator = 1LL * denominator * b % MOD;
            --b;
        }

        // Modular division:
        //
        //     numerator / denominator = numerator * inverse(denominator)
        //
        // inverse(denominator) = denominator^(MOD-2) % MOD
        long long result = 1LL * numerator * binary_exponentiation(denominator, MOD - 2) % MOD;

        return static_cast<int>(result);
    }

private:
    long long binary_exponentiation(long long base, long long exp)
    {
        base %= MOD;
        long long result = 1LL;

        while (exp > 0)
        {
            if (exp & 1)
                result = (result * base) % MOD; 

            base = (base * base) % MOD;
            exp >>= 1;
        }

        return result;
    }
};
