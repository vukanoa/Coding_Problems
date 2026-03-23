/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    1594) Maximum Non Negative Product in a Matrix
    ==============================================

    ============
    Description:
    ============

    You are given a m x n matrix grid. Initially, you are located at the
    top-left corner (0, 0), and in each step, you can only move right or down
    in the matrix.

    Among all possible paths starting from the top-left corner (0, 0) and
    ending in the bottom-right corner (m - 1, n - 1), find the path with the
    maximum non-negative product. The product of a path is the product of all
    integers in the grid cells visited along the path.

    Return the maximum non-negative product modulo 109 + 7. If the maximum
    product is negative, return -1.

    Notice that the modulo is performed after getting the maximum product.

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
    Output: -1
    Explanation: It is not possible to get non-negative product in the path
                 from (0, 0) to (2, 2), so return -1.

    --- Example 2 ---
    Input: grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
    Output: 8
    Explanation: Maximum non-negative product is shown (1 * 1 * -2 * -4 * 1=8)

    --- Example 3 ---
    Input: grid = [[1,3],[0,-4]]
    Output: 0
    Explanation: Maximum non-negative product is shown (1 * 0 * -4 = 0).


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 15
    -4 <= grid[i][j] <= 4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Classic 3D DP problem. Nothing fancy about it. As fundamental as it gets
    for a 3D DP.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.15% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int MOD = 1e9 + 7;

        long long dp[15][15][2]; // [2] is for {MAX, MIN}
        dp[ROWS-1][COLS-1][0] = 1LL * grid[ROWS-1][COLS-1];
        dp[ROWS-1][COLS-1][1] = 1LL * grid[ROWS-1][COLS-1];

        /* Precompute last ROW */
        for (int col = COLS-2; col >= 0; col--)
        {
            if (grid[ROWS-1][col] >= 0)
            {
                dp[ROWS-1][col][0] = 1LL * grid[ROWS-1][col] * dp[ROWS-1][col+1][0];
                dp[ROWS-1][col][1] = 1LL * grid[ROWS-1][col] * dp[ROWS-1][col+1][1];
            }
            else // grid[ROWS-1][col] < 0
            {
                dp[ROWS-1][col][0] = 1LL * grid[ROWS-1][col] * dp[ROWS-1][col+1][1];
                dp[ROWS-1][col][1] = 1LL * grid[ROWS-1][col] * dp[ROWS-1][col+1][0];
            }
        }

        /* Precompute last COL */
        for (int row = ROWS-2; row >= 0; row--)
        {
            if (grid[row][COLS-1] >= 0)
            {
                dp[row][COLS-1][0] = 1LL * grid[row][COLS-1] * dp[row+1][COLS-1][1];
                dp[row][COLS-1][1] = 1LL * grid[row][COLS-1] * dp[row+1][COLS-1][0];
            }
            else // grid[ROWS-1][col] < 0
            {
                dp[row][COLS-1][1] = 1LL * grid[row][COLS-1] * dp[row+1][COLS-1][0];
                dp[row][COLS-1][0] = 1LL * grid[row][COLS-1] * dp[row+1][COLS-1][1];
            }
        }

        /* Solve */
        for (int row = ROWS-2; row >= 0; row--)
        {
            for (int col = COLS-2; col >= 0; col--)
            {
                if (grid[row][col] >= 0)
                {
                    dp[row][col][0] = max(1LL * grid[row][col] * dp[row  ][col+1][0],  // Right
                                          1LL * grid[row][col] * dp[row+1][col  ][0]); // Down

                    dp[row][col][1] = min(1LL * grid[row][col] * dp[row  ][col+1][1],  // Right
                                          1LL * grid[row][col] * dp[row+1][col  ][1]); // Down
                }
                else // dp[row][col].first < 0)
                {
                    dp[row][col][0] = max(1LL * grid[row][col] * dp[row  ][col+1][1],  // Right
                                          1LL * grid[row][col] * dp[row+1][col  ][1]); // Down

                    dp[row][col][1] = min(1LL * grid[row][col] * dp[row  ][col+1][0],  // Right
                                          1LL * grid[row][col] * dp[row+1][col  ][0]); // Down

                }
            }
        }

        return dp[0][0][0] >= 0 ? static_cast<int>(dp[0][0][0] % MOD): -1;
    }
};
