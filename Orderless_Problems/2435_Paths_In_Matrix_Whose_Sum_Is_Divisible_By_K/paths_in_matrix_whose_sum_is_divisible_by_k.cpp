/*
    ============
    === HARD ===
    ============

    =================================================
    2435) Paths in Matrix Whose Sum Is Divisible by K
    =================================================

    ============
    Description:
    ============

    You are given a 0-indexed m x n integer matrix grid and an integer k. You
    are currently at position (0, 0) and you want to reach position (m - 1, n -
    1) moving only down or right.

    Return the number of paths where the sum of the elements on the path is
    divisible by k. Since the answer may be very large, return it modulo 109 +
    7.

    ==============================================================
    FUNCTION: int numberOfPaths(vector<vector<int>>& grid, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
    Output: 2
    Explanation: There are two paths where the sum of the elements on the path
    is divisible by k.
    The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which
    is divisible by 3.
    The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15
    which is divisible by 3.

    --- Example 2 ---
    Input: grid = [[0,0]], k = 5
    Output: 1
    Explanation: The path highlighted in red has a sum of 0 + 0 = 0 which is
                 divisible by 5.

    --- Example 3 ---
    Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
    Output: 10
    Explanation: Every integer is divisible by 1 so the sum of the elements on
                 every possible path is divisible by k.

    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 5 * 10^4
    1 <= m * n <= 5 * 10^4
    0 <= grid[i][j] <= 100
    1 <= k <= 50

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.17% */
/* Space Beats: 5.18% */

/* Time  Complexity: O(ROWS * COLS * K) */
/* Space Complexity: O(ROWS * COLS * K) */
class Solution_Bottom_Up {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        const int MOD = 1e9 + 7;

        vector<vector<vector<unsigned long long>>> dp(ROWS+1, vector<vector<unsigned long long>>(COLS+1, vector<unsigned long long>(51, 0)));
        dp[ROWS-1][COLS-1][grid[ROWS-1][COLS-1] % k] = 1;


        // Last Row
        for (int col = COLS-2; col >= 0; col--)
        {
            for (int i = 0; i <= 50; i++)
            {
                int curr_val = grid[ROWS-1][col];

                dp[ROWS-1][col][(i + curr_val) % k] += dp[ROWS-1][col+1][i];
                dp[ROWS-1][col][(i + curr_val) % k] %= MOD;
            }
        }

        // Last Col
        for (int row = ROWS-2; row >= 0; row--)
        {
            for (int i = 0; i <= 50; i++)
            {
                int curr_val = grid[row][COLS-1];

                dp[row][COLS-1][(i + curr_val) % k] += dp[row+1][COLS-1][i];
                dp[row][COLS-1][(i + curr_val) % k] %= MOD;
            }
        }

        /* Solve starting at [ROWS-2][COLS-2] and traverse back */
        for (int row = ROWS-2; row >= 0; row--)
        {
            for (int col = COLS-2; col >= 0; col--)
            {
                int curr_val = grid[row][col];

                for (int i = 0; i <= 50; i++)
                {
                    // Right
                    dp[row][col][(i + curr_val) % k] += dp[row][col+1][i];
                    dp[row][col][(i + curr_val) % k] %= MOD;

                    // Down
                    dp[row][col][(i + curr_val) % k] += dp[row+1][col][i];
                    dp[row][col][(i + curr_val) % k] %= MOD;
                }
            }
        }

        unsigned long long result = 0;
        for (int i = 0; i <= 50; i++)
        {
            if (i % k == 0)
            {
                result += dp[0][0][i];
                result %= MOD;
            }
        }

        return static_cast<int>(result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Memoization version of the above code. It's a bit less straightforward in
    my opinion.

*/

/* Time  Beats: 5.17% */
/* Space Beats: 5.18% */

/* Time  Complexity: O(ROWS * COLS * K) */
/* Space Complexity: O(ROWS * COLS * K) */
class Solution_Memoization {
private:
    const int MOD = 1e9 + 7;

public:
    int numberOfPaths(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<vector<unsigned long long>>> memo(ROWS+1, vector<vector<unsigned long long>>(COLS+1, vector<unsigned long long>(51, 0)));

        /* Solve */
        memo[0][0] = solve(0, 0, grid, k, memo);

        unsigned long long result = 0;
        for (int i = 0; i <= 50; i++)
        {
            if (i % k == 0)
            {
                result += memo[0][0][i];
                result %= MOD;
            }
        }

        return static_cast<int>(result);
    }

private:
    vector<unsigned long long> solve(int row, int col, vector<vector<int>>& grid, int& k, vector<vector<vector<unsigned long long >>>& memo)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Target, Finish, cell
        if (row == ROWS-1 && col == COLS-1)
        {
            vector<unsigned long long> vec(51, 0ULL);
            vec[grid[row][col] % k] = 1;

            return vec;
        }

        // Out-of-Bounds
        if (row >= ROWS || col >= COLS)
            return vector<unsigned long long>(51, 0ULL);


        if (memo[row][col] != vector<unsigned long long>(51, 0))
            return memo[row][col];

        vector<unsigned long long> right = solve(row  , col+1, grid, k, memo);
        vector<unsigned long long> down  = solve(row+1, col  , grid, k, memo);

        vector<unsigned long long> curr_vec(51, 0);
        int curr_val = grid[row][col];

        for (int i = 0; i <= 50; i++)
        {
            // Right
            curr_vec[(i + curr_val) % k] += right[i];
            curr_vec[(i + curr_val) % k] %= MOD;

            // Down
            curr_vec[(i + curr_val) % k] += down[i];
            curr_vec[(i + curr_val) % k] %= MOD;
        }

        return memo[row][col] = curr_vec;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    However, implementing Memoization this way is much much easier.

    But, it's a bit more difficult to think about it like this if you're not
    very well versed with Memoization.

    If you were, then this is the most straightforward Solution.

*/

/* Time  Beats: 17.65% */
/* Space Beats:  9.88% */

/* Time  Complexity: O(ROWS * COLS * K) */
/* Space Complexity: O(ROWS * COLS * K) */
class Solution_Memoization_Optimized {
private:
    const int MOD = 1e9 + 7;

public:
    int numberOfPaths(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        auto memo = vector(ROWS, vector(COLS, vector<long long>(k, -1)));

        return solve(0, 0, 0, grid, k, memo);
    }

private:
    long long solve(int row, int col, int curr_rem, vector<vector<int>>& grid, int& k, vector<vector<vector<long long>>>& memo)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row >= ROWS || col >= COLS)
            return 0LL;

        if (row == ROWS-1 && col == COLS-1)
            return (grid[row][col] % k == curr_rem ? 1LL : 0LL);

        if (memo[row][col][curr_rem] != -1)
            return memo[row][col][curr_rem];

        int val_rem  = grid[row][col] % k;
        int prev_rem = (curr_rem - val_rem + k) % k;

        long long down  = solve(row+1, col  , prev_rem, grid, k, memo);
        long long right = solve(row  , col+1, prev_rem, grid, k, memo);

        return memo[row][col][curr_rem] = (down + right) % MOD;
    }
};
