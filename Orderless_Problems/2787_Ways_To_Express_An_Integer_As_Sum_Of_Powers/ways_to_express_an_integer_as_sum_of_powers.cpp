/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    2787) Ways to Express an Integer as Sum of Powers
    =================================================

    ============
    Description:
    ============

    Given two positive integers n and x.

    Return the number of ways n can be expressed as the sum of the xth power of
    unique positive integers, in other words, the number of sets of unique
    integers [n1, n2, ..., nk] where n = n1x + n2x + ... + nkx.

    Since the result can be very large, return it modulo 10^9 + 7.

    For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53

    =========================================
    FUNCTION: int numberOfWays(int n, int x);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10, x = 2
    Output: 1
    Explanation: We can express n as the following: n = 32 + 12 = 10.
    It can be shown that it is the only way to express 10 as the sum of the
    2nd power of unique integers.

    --- Example 2 ---
    Input: n = 4, x = 1
    Output: 2
    Explanation: We can express n in the following ways:
    - n = 41 = 4.
    - n = 31 + 11 = 4.


    *** Constraints ***
    1 <= n <= 300
    1 <= x <= 5

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental "Take-Skip" Memoizaiton problem.

*/

/* Time  Beats: 59.48% */
/* Space Beats: 58.60% */

/* Time  Complexity: O(powers.size() * N) */ // powers.size() <= N
/* Space Complexity: O(powers.size() * N) */
class Solution {
private:
    int const MOD = 1e9 + 7;
    vector<vector<int>> memo;
    vector<int> power; // Store precomputed powers

public:
    int numberOfWays(int n, int x)
    {
        // Precompute powers
        for (int i = 1; pow(i, x) <= n; i++)
            power.push_back(static_cast<int>(pow(i, x)));

        memo.assign(power.size(), vector<int>(n + 1, -1));

        return solve(0, 0, n, x);
    }

private:
    int solve(int idx, int sum, int n, int x)
    {
        if (sum == n)
            return 1;

        if (sum > n)
            return 0;

        if (idx >= power.size())
            return 0;

        if (memo[idx][sum] != -1)
            return memo[idx][sum];

        int take = 0;
        if (sum + power[idx] <= n)
            take = solve(idx + 1, sum + power[idx], n, x);

        int skip = solve(idx + 1, sum +    0      , n, x);

        return memo[idx][sum] = (take + skip) % MOD;
    }
};
