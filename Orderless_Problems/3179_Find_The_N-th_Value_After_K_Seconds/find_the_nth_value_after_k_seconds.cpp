/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3179) Find the N-th Value After K Seconds
    =========================================

    ============
    Description:
    ============

    You are given two integers n and k.

    Initially, you start with an array a of n integers where a[i] = 1 for all
    0 <= i <= n - 1. After each second, you simultaneously update each element
    to be the sum of all its preceding elements plus the element itself.

    For example, after one second:
        a[0] remains the same,
        a[1] becomes a[0] + a[1],
        a[2] becomes a[0] + a[1] + a[2], and so on.

    Return the value of a[n - 1] after k seconds.

    Since the answer may be very large, return it modulo 10^9 + 7.

    ===============================================
    FUNCTION: int valueAfterKSeconds(int n, int k);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, k = 5
    Output: 56

    --- Example 2 ---
    Input: n = 5, k = 3
    Output: 35


    *** Constraints ***
    1 <= n, k <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pascal's Triangle.

*/

/* Time  Beats: 18.08% */
/* Space Beats: 43.29% */

/* Time  Complexity: O(N * K) */
/* Space Complexity: O(N)     */
class Solution {
public:
    int valueAfterKSeconds(int n, int k)
    {
        const int MOD = 1e9+7;

        vector<long long> dp(n, 1LL);

        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[j] = (dp[j-1] % MOD + dp[j] % MOD) % MOD;
            }
        }

        return dp[n-1] % MOD;
    }
};
