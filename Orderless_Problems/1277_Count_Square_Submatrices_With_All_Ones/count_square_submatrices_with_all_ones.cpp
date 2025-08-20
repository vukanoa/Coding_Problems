/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1277) Count Square Submatrices with All Ones
    ============================================

    ============
    Description:
    ============

    Given a m * n matrix of ones and zeros, return how many square submatrices
    have all ones.

    ========================================================
    FUNCTION: int countSquares(vector<vector<int>>& matrix);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix =
    [
      [0,1,1,1],
      [1,1,1,1],
      [0,1,1,1]
    ]
    Output: 15
    Explanation:
    There are 10 squares of side 1.
    There are 4 squares of side 2.
    There is  1 square of side 3.
    Total number of squares = 10 + 4 + 1 = 15.

    --- Example 2 ---
    Input: matrix =
    [
      [1,0,1],
      [1,1,0],
      [1,1,0]
    ]
    Output: 7
    Explanation:
    There are 6 squares of side 1.
    There is 1 square of side 2.
    Total number of squares = 6 + 1 = 7.


    *** Constraints ***
    1 <= arr.length <= 300
    1 <= arr[0].length <= 300
    0 <= arr[i][j] <= 1

*/

#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.85% */
/* Space Beats: 56.40% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix)
    {
        int ROWS = matrix.size();
        int COLS = matrix[0].size();
        int result = 0;

        vector<vector<int>> dp(ROWS, vector<int>(COLS, 0));

        for (int i = 0; i < ROWS; i++)
        {
            dp[i][0] = matrix[i][0];
            result += dp[i][0];
        }

        for (int j = 1; j < COLS; j++)
        {
            dp[0][j] = matrix[0][j];
            result += dp[0][j];
        }

        // Solve
        for (int i = 1; i < ROWS; i++)
        {
            for (int j = 1; j < COLS; j++)
            {
                if (matrix[i][j] == 1)
                {
                    dp[i][j] = 1 + min( {dp[i-1][j  ],    // Top
                                         dp[i  ][j-1],    // Left
                                         dp[i-1][j-1]} ); // Top-Left(diagonal)
                }

                result += dp[i][j];
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    (Classic Memoization)
    TODO

*/

/* Time  Beats:  6.21% */
/* Space Beats: 85.80% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Memoization {
private:
        int memo[301][301];

public:
    int countSquares(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        /* Initialize */
        memset(memo, -1, sizeof(memo));

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                result += solve(i, j, grid);
            }
        }

        return result;
    }

private:
    int solve(int i, int j, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (i >= ROWS || j >= COLS)
            return 0;

        if (grid[i][j] == 0)
            return 0;

        if (memo[i][j] != -1)
            return memo[i][j];

        int below    = solve(i+1, j  , grid);
        int right    = solve(i  , j+1, grid);
        int diagonal = solve(i+1, j+1, grid);

        return memo[i][j] = 1 + min( {below, right, diagonal} );
    }
};
