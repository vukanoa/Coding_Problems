/*
    ============
    === HARD ===
    ============

    ======================================
    329) Longest Increasing Path In Matrix
    ======================================

    ============
    Description:
    ============

    Given an m x n integers matrix, return the length of the longest increasing
    path in matrix.

    From each cell, you can either move in four directions: left, right, up, or
    down. You may not move diagonally or move outside the boundary (i.e.,
    wrap-around is not allowed).

    =================================================================
    FUNCTION: int longestIncreasingPath(vector<vector<int>>& matrix);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[9,9,4],
                     [6,6,8],
                     [2,1,1]]
    Output: 4
    Explanation: The longest increasing path is [1, 2, 6, 9].


    --- Example 2 ---
    Input: matrix = [[3,4,5],
                     [3,2,6],
                     [2,2,1]]
    Output: 4
    Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally
                 is not allowed.


    --- Example 3 ---
    Input: matrix = [[1]]
    Output: 1


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    0 <= matrix[i][j] <= 2^31 - 1

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

/* Time  Beats: 12.80% */
/* Space Beats: 90.04% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Top_Down__Memoization {
private:
    int memo[201][201];

public:
    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();
        int result = 0;

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        for (int row = 0; row < 201; row++)
        {
            for (int col = 0; col < 201; col++)
            {
                result = max(result, solve(row, col, -1, matrix));
            }
        }

        return result;
    }

private:
    int solve(int row, int col, int prev_value, vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return 0;

        if (matrix[row][col] <= prev_value)
            return 0;

        if (memo[row][col] != -1)
            return memo[row][col];


        /* Signing Cross */
        int up    = solve(row-1, col  , matrix[row][col], matrix);
        int down  = solve(row+1, col  , matrix[row][col], matrix);
        int left  = solve(row  , col-1, matrix[row][col], matrix);
        int right = solve(row  , col+1, matrix[row][col], matrix);

        return memo[row][col] = 1 + max( {up, down, left, right} );
    }
};
