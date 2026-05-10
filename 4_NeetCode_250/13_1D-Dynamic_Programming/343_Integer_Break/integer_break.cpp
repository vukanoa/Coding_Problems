/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    343) Integer Break
    ===========================

    ============
    Description:
    ============

    Given an integer n, break it into the sum of k positive integers, where k
    >= 2, and maximize the product of those integers.

    Return the maximum product you can get.

    ==================================
    FUNCTION: int integerBreak(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: 1
    Explanation: 2 = 1 + 1, 1 × 1 = 1.


    --- Example 2 ---
    Input: n = 10
    Output: 36
    Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.


    *** Constraints ***
    2 <= n <= 58

*/

#include <cstring>
#include <vector>
using namespace std;


/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up__Tabulation {
public:
    int integerBreak(int n)
    {
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for (int i = 3; i <= n; i++)
        {
            for (int num = 1; num < i; num++)
            {
                dp[i] = max(dp[i], num * max(i - num, dp[i - num]));
            }
        }

        return dp[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same "Dynamic Programming" Solution as above, though implemented using a
    Top-Down approach called "Memoization".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  88.19% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization {
private:
    int memo[59];

public:
    int integerBreak(int n)
    {
        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(n);
    }

private:
    int solve(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1 || n == 2)
            return 1;

        if (memo[n] != -1)
            return memo[n];

        int result = 0;
        for (int num = 1; num < n; num++)
        {
            if (n - num < 0)
                break;

            result = max(result, num * max(n - num, solve(n - num)));
        }

        return memo[n] = result;
    }
};
