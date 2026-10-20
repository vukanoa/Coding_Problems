/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    221) Maximal Square
    ===========================

    ============
    Description:
    ============

    Given an m x n binary matrix filled with 0's and 1's, find the largest
    square containing only 1's and return its area.

    ==========================================================
    FUNCTION: int maximalSquare(vector<vector<char>>& matrix);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  1  |  0  |  0  |
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+
    |  1  |  1  |  1  |  1  |  1  |
    +-----+-----+-----+-----+-----+
    |  1  |  0  |  0  |  1  |  0  |
    +-----+-----+-----+-----+-----+

    Input: matrix =
    [["1","0","1","0","0"],
     ["1","0","1","1","1"],
     ["1","1","1","1","1"],
     ["1","0","0","1","0"]]
    Output: 4


    --- Example 2 ---
    +-----+-----+
    |  0  |  1  |
    +-----+-----+
    |  1  |  0  |
    +-----+-----+
    Input: matrix = [["0","1"],["1","0"]]
    Output: 1


    --- Example 3 ---
    Input: matrix = [["0"]]
    Output: 0


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is '0' or '1'.

*/

#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.44% */
/* Space Beats: 82.54% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
private:
    int memo[501][501];

    int ROWS;
    int COLS;

public:
    int maximalSquare(vector<vector<char>> matrix)
    {
        ROWS = matrix.size();
        COLS = matrix[0].size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // 0xff is -1 in "Two's complement"

        /* Solve */
        solve(0, 0, matrix);

        /* Get Result */
        int max_side = 0;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
                max_side = max(max_side, memo[row][col]);
        }

        return max_side * max_side;
    }

private:
    int solve(int row, int col, vector<vector<char>>& matrix)
    {
        if (row >= ROWS || col >= COLS)
            return 0;

        if (memo[row][col] != -1)
            return memo[row][col];

        int down     = solve(row+1, col  , matrix);
        int right    = solve(row  , col+1, matrix);
        int diagonal = solve(row+1, col+1, matrix);

        memo[row][col] = 0;

        if (matrix[row][col] == '1')
            memo[row][col] = 1 + min( {down, right, diagonal} );

        return memo[row][col];
    }
};
