/*
    ============
    === EASY ===
    ============

    ===========================
    70) Climbing Stairs
    ===========================

    ============
    Description:
    ============

    You are climbing a staircase. It takes 'n' steps to reach the top.

    Each time you can either climb 1 or 2 steps. In how many disctin ways can
    you climb to the top?

    =================================
    FUNCTION: int climbStairs(int n);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  n = 2
    Output: 2

    --- Example 2 ---
    Input:  n = 3
    Output: 3
    Explanation: There are three ways to climb to the top.
    1) 1 + 1 + 1
    2) 1 + 2
    3) 2 + 1

    --- Example 3 ---
    Input:  n = 4
    Output: 5
    Explanation: There are five ways to climb to the top.
    1) 1 + 1 + 1 + 1
    2) 1 + 1 + 2
    3) 1 + 2 + 1
    4) 2 + 1 + 1
    5) 2 + 2

    --- Example 4 ---
    Input:  n = 5
    Output: 8
    Explanation: There are eight ways to climb to the top.
    1) 1 + 1 + 1 + 1 + 1
    2) 1 + 1 + 1 + 2
    3) 1 + 1 + 2 + 1
    4) 1 + 2 + 1 + 1
    5) 2 + 1 + 1 + 1
    6) 1 + 2 + 2
    7) 2 + 1 + 2
    8) 2 + 2 + 1

    --- Example 5 ---
    Input:  n = 6
    Output: 13
    Explanation: There are thirteen ways to climb to the top.
    1)  1 + 1 + 1 + 1 + 1 + 1
    2)  1 + 1 + 1 + 1 + 2
    3)  1 + 1 + 1 + 2 + 1
    4)  1 + 1 + 2 + 1 + 1
    5)  1 + 2 + 1 + 1 + 1
    6)  2 + 1 + 1 + 1 + 1
    7)  1 + 1 + 2 + 2
    8)  1 + 2 + 1 + 2
    9)  1 + 2 + 2 + 1
    10) 2 + 1 + 2 + 1
    11) 2 + 2 + 1 + 1
    12) 2 + 1 + 1 + 2
    13) 2 + 2 + 2

    *** Constraints ***
    1 <= n <= 45

*/

#include <cstring>

/*
    ------------
    --- IDEA ---
    ------------

    This is the most fundamental "Dynamic Programming" technique that exists.

    If you want to master "Dynamic Programming", this is the necessary first
    step.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.44% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up__1D_DP_Array {
public:
    int climbStairs(int n)
    {
        int dp[n + 1];
        dp[0] = 1;
        dp[1] = 1;

        /* Fibonacci */
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i-2] + dp[i-1];

        return dp[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of using entire "dp" vector, instead we can use only last two
    dp states since that's all we need. Thus we will use only 2 variables
    instead of an entire "dp" vector.

    Reducing Space Complexity from O(N) down to O(1).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int climbStairs(int n)
    {
        int prev_prev = 1;
        int prev      = 1;

        for (int i = 2; i <= n; i++)
        {
            int curr = prev_prev + prev;

            prev_prev = prev;
            prev      = curr;
        }

        return prev;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is written in a specific "Memoization" form. It's important to be
    aware of this "form" if you plan to learn true Memoization technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Memoization {
private:
    int memo[46];

public:
    int climbStairs(int n)
    {
        /* Memset */
        memset(memo, -1, sizeof(memo));

        return memoization(n);
    }

private:
    int memoization(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        
        if (memo[n] != -1)
            return memo[n];
        
        int take_prev_prev = memoization(n-1);
        int take_prev      = memoization(n-2);

        return memo[n] = take_prev_prev + take_prev;
    }
};
