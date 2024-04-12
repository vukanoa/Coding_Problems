#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    Fibonacci sequence using memoization. This is the most fundamental "Dynamic
    Programming" technique that exists.

    If you want to master "Dynamic Programming", this is the necessary first
    step.

*/

/* Time  Beats: 100%   */
/* Space Beats: 77.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int climbStairs(int n)
    {
        int dp[n + 1];
        dp[0] = 1;
        dp[1] = 1;

        /* Fibonacci */
        for (int i = 2; i < n + 1; i++)
            dp[i] = dp[i - 1] + dp[i - 2];

        return dp[n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, though this one doesn't use any extra space. Sinc we
    don't need more than last two elements of array "dp", then instead of
    keeping track of the array, we keep track only of the last two elements.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.58% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int climbStairs(int n)
    {
        int dp_2 = 0;
        int dp_1 = 1;

        for (int i = 2; i <= n; i++)
        {
            int tmp = dp_1;
            dp_1 = dp_2 + dp_1;
            dp_2 = tmp;
        }

        return dp_2 + dp_1;
    }
};


void
print_stairs(int n)
{
    std::cout << "\n\tStairs:\n";
    for (int i = n-1; i >= 0; i--)
    {
        // Horizontal part
        std::cout << "\t";
        int tmp = i;
        while (tmp--)
            std::cout << "   ";

        std::cout << "---\n";

        // Vertical part
        std::cout << "\t";
        tmp = i;
        while (tmp--)
            std::cout << "   ";

        std::cout << "|\n";
    }
    std::cout << "\n";
}


int
main()
{
    Solution           sol;
    Solution_Efficient sol_eff;

    /* Example 1 */
    // int n = 2;

    /* Example 2 */
    int n = 3;

    /* Example 3 */
    // int n = 4;

    /* Example 4 */
    // int n = 5;

    /* Example 5 */
    // int n = 6;

    /* Example 6 */
    // int n = 1;

    /* Example 7 */
    // int n = 45;

    std::cout << "\n\t=======================";
    std::cout << "\n\t=== CLIMBING STAIRS ===";
    std::cout << "\n\t=======================\n";

    /* Write Input */
    std::cout << "\n\tN = " << n << "\n";
    print_stairs(n);


    /* Solution */
    // int ways = sol.climbStairs(n);
    int ways = sol.climbStairs(n);


    /* Write Output */
    std::cout << "\n\tTotal ways: " << ways << "\n\n";


    return 0;
}
