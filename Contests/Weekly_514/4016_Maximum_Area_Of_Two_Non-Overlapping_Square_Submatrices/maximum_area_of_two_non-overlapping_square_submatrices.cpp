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

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.30% */
/* Space Beats: 97.72% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
class Solution {
private:
    int memo[501][501];
    int max_row_size[502];
    int max_col_size[502];

    int ROWS;
    int COLS;

public:
    int maxArea(vector<vector<int>>& mat)
    {
        ROWS = mat.size();
        COLS = mat[0].size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo)); // 0xff is -1 in "2's complement"
        memset(max_row_size, 0, sizeof(max_row_size));
        memset(max_col_size, 0, sizeof(max_col_size));

        /* Populate "memo" */
        solve(0, 0, mat);

        /* Get Maximum Square Size Per Row */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                max_row_size[row] = max(max_row_size[row], memo[row][col]);
                max_col_size[col] = max(max_col_size[col], memo[row][col]);
            }
        }

        /* Suffix Maximums */
        for (int row = ROWS - 1; row >= 0; row--)
            max_row_size[row] = max(max_row_size[row], max_row_size[row+1]);

        for (int col = COLS - 1; col >= 0; col--)
            max_col_size[col] = max(max_col_size[col], max_col_size[col+1]);

        /* Binary Search */
        int start = 1;
        int end   = min(ROWS, COLS);
        int result = 0;

        while (start <= end)
        {
            int k = start + (end - start) / 2;
            bool found = false;

            for (int row = 0; row < ROWS && !found; row++)
            {
                for (int col = 0; col < COLS; col++)
                {
                    if (memo[row][col] < k)
                        continue;

                    if ((row + k < ROWS && max_row_size[row+k] >= k) ||
                        (col + k < COLS && max_col_size[col+k] >= k))
                    {
                        found = true;
                        break;
                    }
                }
            }

            if (found)
            {
                result = k * k;
                start  = k + 1;
            }
            else
                end = k - 1;
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
