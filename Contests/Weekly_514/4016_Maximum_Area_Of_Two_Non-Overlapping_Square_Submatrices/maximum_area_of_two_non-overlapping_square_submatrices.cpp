/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    4016) Maximum Area of Two Non-Overlapping Square Submatrices
    ============================================================

    ============
    Description:
    ============

    You are given a 2D integer matrix mat of size m × n, where:

        + mat[r][c] == 1 means the cell at row r and column c is usable.
        + mat[r][c] == 0 means it is not usable.

    Your task is to find two submatrices that satisfy the following conditions:

        + Both submatrices must be squares of the same side length k.
        + The two submatrices must not share any cell.
        + Each submatrix can only cover cells where mat[r][c] == 1.

    Return the maximum possible area of each of the two squares. If it is not
    possible to choose two such squares, return 0.

    ================================================
    FUNCTION: int maxArea(vector<vector<int>>& mat);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,1,1,0],[1,1,1,1],[0,0,1,1]]
    Output: 4
    Explanation:
    The largest equal non-overlapping squares have side length k = 2 with area 4.
        First square starts at top-left (0, 0) and covers cells (0, 0), (0, 1), (1, 0), and (1, 1).
        Second square starts at top-left (1, 2) and covers cells (1, 2), (1, 3), (2, 2), and (2, 3).
    Thus, the answer is 4.

    --- Example 2 ---
    Input: mat = [[0,1],[1,0]]
    Output: 1
    Explanation:
    The largest equal non-overlapping squares have side length k = 1 with area 1.
        First square starts at top-left (0, 1) and covers cell (0, 1).
        Second square starts at top-left (1, 0) and covers cell (1, 0).
    Thus, the answer is 1.

    --- Example 3 ---
    Input: mat = [[0,0],[0,1]]
    Output: 0
    Explanation:
    There is only one usable cell, so it is impossible to choose two
    non-overlapping squares. Thus, the answer is 0.


    *** Constraints ***
    mat.length == m
    mat[i].length == n
    1 <= m, n <= 500
    mat[i][j] is either 0 or 1.

*/

#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 35.36% */
/* Space Beats: 96.01% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
private:
    int memo    [501][501];
    int max_side[501][501];

    int ROWS;
    int COLS;

public:
    int maxArea(vector<vector<int>>& mat)
    {
        ROWS = mat.size();
        COLS = mat[0].size();
        int result = 0;

        /* Memset */
        memset(memo,     0xff, sizeof(memo));      // 0xff is -1 in "2's compl"
        memset(max_side, 0x00, sizeof(max_side));

        /* Populate "memo" */
        solve(0, 0, mat);

        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                max_side[row][col] = max( {    memo[row  ][col  ],
                                           max_side[row+1][col  ],
                                           max_side[row  ][col+1],
                                           max_side[row+1][col+1]} );
            }
        }

        /* Find Result */
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                int k = memo[row][col];

                if (k == 0)
                    continue;

                if (row+k < ROWS)
                {
                    int side_len = min(k, max_side[row+k][0]);

                    result= max(result, side_len * side_len);
                }

                if (col+k < COLS)
                {
                    int side_len = min(k, max_side[0][col+k]);

                    result= max(result, side_len * side_len);
                }
            }
        }

        return result;
    }

private:
    int solve(int row, int col, vector<vector<int>>& mat)
    {
        if (row >= ROWS || col >= COLS)
            return 0;

        if (memo[row][col] != -1)
            return memo[row][col];

        int down     = solve(row+1, col  , mat);
        int right    = solve(row  , col+1, mat);
        int diagonal = solve(row+1, col+1, mat);

        memo[row][col] = 0;

        if (mat[row][col] == 1)
            memo[row][col] = 1 + min( min(down, right), diagonal );

        return memo[row][col];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though written in an Bottom-Up way.

*/

/* Time  Beats: 68.46% */
/* Space Beats: 38.65% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Bottom_Up__Tabulation {
public:
    int maxArea(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();
        int result = 0;

        vector<vector<int>> dp      (ROWS+1, vector<int>(COLS+1, 0));
        vector<vector<int>> max_side(ROWS+1, vector<int>(COLS+1, 0));

        /* Populate "memo" */
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                if (mat[row][col] == 0)
                    continue;

                int down     = row+1 < ROWS                 ? dp[row+1][col  ] : 0;
                int right    = col+1 < COLS                 ? dp[row  ][col+1] : 0;
                int diagonal = row+1 < ROWS && col+1 < COLS ? dp[row+1][col+1] : 0;

                dp[row][col] = 1 + min( min(down, right), diagonal );
            }
        }

        /* Populate "max_side" */
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                max_side[row][col] = max( {      dp[row  ][col  ],
                                           max_side[row+1][col  ],
                                           max_side[row  ][col+1],
                                           max_side[row+1][col+1]} );
            }
        }

        /* Find Result */
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                int k = dp[row][col];

                if (k == 0)
                    continue;

                if (row+k < ROWS)
                {
                    int side_len = min(k, max_side[row+k][0]);

                    result = max(result, side_len * side_len);
                }

                if (col+k < COLS)
                {
                    int side_len = min(k, max_side[0][col+k]);

                    result = max(result, side_len * side_len);
                }
            }
        }

        return result;
    }
};
