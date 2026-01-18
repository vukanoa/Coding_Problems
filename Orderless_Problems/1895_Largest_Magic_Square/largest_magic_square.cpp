/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1895) Largest Magic Square
    ===========================

    ============
    Description:
    ============

    A A k x k magic square is a k x k grid filled with integers such that every
    row sum, every column sum, and both diagonal sums are all equal. The
    integers in the magic square do not have to be distinct. Every 1 x 1 grid
    is trivially a magic square.

    Given an m x n integer grid, return the size (i.e., the side length k) of
    the largest magic square that can be found within this grid.

    ============================================================
    FUNCTION: int largestMagicSquare(vector<vector<int>>& grid);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
    Output: 3
    Explanation: The largest magic square has a size of 3.
    Every row sum, column sum, and diagonal sum of this magic square is equal
    to 12.
    - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
    - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
    - Diagonal sums: 5+4+3 = 6+4+2 = 12

    --- Example 2 ---
    Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
    Output: 2


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    1 <= grid[i][j] <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.90% */
/* Space Beats: 96.80% */

/* Time  Complexity: O(ROWS * COLS * min(ROWS, COLS)^2) */
/* Space Complexity: O(ROWS * COLS)                     */
class Solution {
private:
    static const int N = 51;

    int row_sum[N][N]; // row <==> ROW
    int col_sum[N][N]; // col <==> COLUMN
    int dia_sum[N][N]; // dia <==> DIAGONAL
    int adi_sum[N][N]; // adi <==> ANTI-diagonal

    int ROWS;
    int COLS;

public:
    int largestMagicSquare(vector<vector<int>>& grid)
    {
        ROWS = grid.size();
        COLS = grid[0].size();

        row_sum[0][0] = 0;
        col_sum[0][0] = 0;
        dia_sum[0][0] = 0;
        adi_sum[0][0] = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                int value = grid[row][col];

                row_sum[row+1][col+1] = row_sum[row+1][col  ] + value;
                col_sum[row+1][col+1] = col_sum[row  ][col+1] + value;
                dia_sum[row+1][col+1] = dia_sum[row  ][col  ] + value;
                adi_sum[row+1][col  ] = adi_sum[row  ][col+1] + value;
            }
        }

        for (int k = min(ROWS, COLS); k >= 2; k--)
        {
            if (is_magic(k))
                return k;
        }

        return 1;
    }

private:
    bool is_magic(int k)
    {
        for (int row = 0; row + k <= ROWS; row++)
        {
            for (int col = 0; col + k <= COLS; col++)
            {
                int main_diag = dia_sum[row+k][col+k] - dia_sum[row][col  ];
                int anti_diag = adi_sum[row+k][col  ] - adi_sum[row][col+k];

                if (main_diag != anti_diag)
                    continue;

                bool match = true;

                for (int offset = 0; offset < k && match; offset++)
                {
                    int curr_row_sum = row_sum[row + offset + 1][col + k] -
                                       row_sum[row + offset + 1][col    ];

                    int curr_col_sum = col_sum[row + k][col + offset + 1] -
                                       col_sum[row    ][col + offset + 1];

                    if (curr_row_sum != main_diag ||
                        curr_col_sum != main_diag)
                    {
                        match = false;
                    }
                }

                if (match)
                    return true;
            }
        }

        return false;
    }
};
