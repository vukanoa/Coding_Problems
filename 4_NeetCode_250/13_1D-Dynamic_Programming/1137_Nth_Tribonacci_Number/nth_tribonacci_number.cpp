/*
    ============
    === EASY ===
    ============

    ============================
    1137) N-th Tribonacci Number
    ============================

    ============
    Description:
    ============

    The Tribonacci sequence Tn is defined as follows:

    T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

    Given n, return the value of Tn.

    ================================
    FUNCTION: int tribonacci(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: 4
    Explanation:
    T_3 = 0 + 1 + 1 = 2
    T_4 = 1 + 1 + 2 = 4


    --- Example 2 ---
    Input: n = 25
    Output: 1389537


    *** Constraints ***
    0 <= n <= 37
    The answer is guaranteed to fit within a 32-bit integer, i.e.
    answer <= 2^31 - 1.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Top-Down Memiozation technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Top_Down__Memoization {
private:
    int memo[38];

public:
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1 || n == 2)
            return 1;

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(n);
    }

private:
    int solve(int target)
    {
        if (target == 0)
            return 0;

        if (target == 1 || target == 2)
            return 1;

        if (memo[target] != -1)
            return memo[target];

        int result = solve(target - 3) + solve(target - 2) + solve(target - 1);

        return memo[target] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Bottom-Up(Tabulation) Dynamic Problem Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.43% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Bottom_Up__Tabulation {
public:
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1 || n == 2)
            return 1;

        vector<int> dp(n+1, 0);
        
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for (int i = 3; i <= n; i++)
            dp[i] = dp[i-3] + dp[i-2] + dp[i-1];

        return dp[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Space-Optimized Bottom-Up(Tabulation) Dynamic Problem Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  47.27% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    int tribonacci(int n)
    {
        if (n == 0)
            return 0;
        
        int prev_prev_prev = 0;
        int prev_prev      = 1;
        int prev           = 1;

        for (int i = 3; i <= n; i++)
        {
            int curr = prev_prev_prev + prev_prev + prev;

            prev_prev_prev = prev_prev;
            prev_prev      = prev;
            prev           = curr;
        }

        return prev;
    }
};
