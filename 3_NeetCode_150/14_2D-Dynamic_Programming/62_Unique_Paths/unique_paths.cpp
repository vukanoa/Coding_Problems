/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    62) Unique Paths
    ===========================

    ============
    Description:
    ============

    There is a robot on an m x n grid. The robot is initially located at the
    top-left corner(i.e., grid[0][0]). The robot tries to move to the
    bottom-right corner(i.e., grid[m - 1][n - 1]). The robot can only move
    either down or right at any point in time.

    Given the two integers 'm' and 'n', return the number of possible unique
    paths that the robot can take to reach the bottom-right corner.

    The test cases are generated so that the answer will be less than or equal
    to 2 * 10^9

    ========================================
    FUNCTION: int uniquePaths(int m, int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  m = 3, n = 7
    Output: 28

    --- Example 2 ---
    Input:  m = 3, n = 2
    Output: 3

    *** Constraints ***
    1 <= m, n <= 100

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental 2D Top-Down Memoization technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.05% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution_Top_Down__Memoization {
private:
    int memo[101][101];

public:
    int uniquePaths(int m, int n)
    {
        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(m-1, n-1);
    }

private:
    int solve(int row, int col)
    {
        if (row == 0 || col == 0)
            return 1;

        if (memo[row][col] != -1)
            return memo[row][col];

        int up   = solve(row-1, col  );
        int left = solve(row  , col-1);

        return memo[row][col] = up + left;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Fundamental 2D Bottom-Up Tabulation Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  27.65% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M * N) */
class Solution_Bottom_Up__Tabulation {
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 1));

        for (int row = 1; row < m; row++)
        {
            for (int col = 1; col < n; col++)
            {
                dp[row][col] = dp[row-1][col  ] + // From Up
                               dp[row  ][col-1];  // From Left
            }
        }

        return dp[m-1][n-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Further inspecting the above code:
        previous_row[j] is just the current_row[j] before the update.

    So we can further reduce the memory usage to one row.
    
    Note:
        Space Beats on LeetCode shows worse percentage than Solution 2, but
        that depends on LeetCode. Generally, Solution 3 is always preffered.
*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.19% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(N)     */
class Solution_Bottom_Up__Tabulation__Space_Optimized {
public:
    int uniquePaths(int m, int n)
    {
        vector<int> dp(n, 1);

        for (int row = 1; row < m; row++)
        {
            for (int col = 1; col < n; col++)
            {
                dp[col] = dp[col-1] + // From Left
                          dp[col  ];  // From Up
            }
        }

        return dp[n-1];
    }
};
