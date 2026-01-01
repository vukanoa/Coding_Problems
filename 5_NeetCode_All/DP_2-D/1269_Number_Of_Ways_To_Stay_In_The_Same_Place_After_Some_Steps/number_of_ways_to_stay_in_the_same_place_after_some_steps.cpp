#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================================
    1269) Number of Ways to Stay in the Same Place After Some Steps
    ===============================================================

    ============
    Description:
    ============

    You have a pointer at index 0 in an array of size arrLen. At each step, you
    can move 1 position to the left, 1 position to the right in the array, or
    stay in the same place (The pointer should not be placed outside the array
    at any time).

    Given two integers steps and arrLen, return the number of ways such that
    your pointer is still at index 0 after exactly steps steps. Since the
    answer may be too large, return it modulo 109 + 7.

    =============================================
    FUNCTION: int numWays(int steps, int arrLen);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: steps = 3, arrLen = 2
    Output: 4
    Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
    Right, Left, Stay
    Stay, Right, Left
    Right, Stay, Left
    Stay, Stay, Stay

    --- Example 2 ---
    Input: steps = 2, arrLen = 4
    Output: 2
    Explanation: There are 2 differents ways to stay at index 0 after 2 steps
    Right, Left
    Stay, Stay

    --- Example 3 ---
    Input: steps = 4, arrLen = 2
    Output: 8

    *** Constraints ***
    1 <= steps <= 500
    1 <= arrLen <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 86.03% */
/* Space Beats: 99.83% */

/* Time  Complexity: O(steps * n) */
/* Space Complexity: O(n)         */
class Solution {
public:
    const int mod = 1e9 + 7;

    int numWays(int steps, int arrLen)
    {
        int n = min(steps/2+1, arrLen); // Maximial reachable position

        // Create a 2D vector dp to store the dynamic programming values
        // (remaining moves, index)

        vector<vector<int>> dp(2, vector<int>(n+1, 0));
        dp[0][0] = 1; // Set the base case 1 way to start at position 0

        for (int mv = 1; mv <= steps; mv++)
        {
            for (int i = 0; i <= n; i++)
            {
                // Compute the number of ways to reach the current position
                long long result = dp[(mv-1)  & 1][i];
                if (i < n-1)
                    result = (result + dp[(mv-1) & 1][i+1]) % mod;

                if (i > 0)
                    result = (result + dp[(mv-1) & 1][i-1]) % mod;

                dp[mv & 1][i] = result;
            }
        }

        return dp[steps & 1][0];
    }
};
