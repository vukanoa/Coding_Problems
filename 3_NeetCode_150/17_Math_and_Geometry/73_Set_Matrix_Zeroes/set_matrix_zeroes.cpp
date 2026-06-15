/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    73) Set Matrix Zeroes
    ===========================

    ============
    Description:
    ============

    Given an "m x n" integer matrix "matrix", if an element is 0, set its
    entire row and column to 0's.

    =====
    Node: You must do it in place.
    =====

    ======================================================
    FUNCTION: void setZeroes(vector<vector<int>>& matrix);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  matrix = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
    Output: [[1, 0, 1], [0, 0, 0], [1, 0, 1]]

    --- Example 2 ---
    Input:  matrix = [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]]
    Output: [[0, 0, 0, 0], [0, 4, 5, 0], [0, 3, 1, 0]]

    *** Constraints ***
    m == matrix.lenght
    n == matrix[0].length
    1 <= m, n <= 200
    -2^31 <= matrix[i][j] <= 2^31 - 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we should be doing it in place, another-matrix-solution is out.

    Idea is that if we find out that, for example, matrix[4][3] == 0, then that
    means we should be nullifying entire row[4] as well as entire column[3];

    So what we do is we just remember row index in 0th row and we remember
    column index in 0th column.
    Afterwards we're going to nullify entire rows and columns based on those
    indicators in 0th row and 0th column.

    First we iterate through 0th(first) row. If we find that there is a 0
    somewhere in it, we remember that in variable "nullify_row_zero".
    We only need to know if there is any zero in 0th row(without matrix[0][0]).

    Then we iterate through 0th(first) column. If we find that there is a 0
    somewhere in it, we remember that in variable "nullify_col_zero".
    We only need to know if there is any zero in 0th col(without matrix[0][0]).

    It's important to note that in both iterations we're iterating starting
    from index 1 and not 0.

    Why?

    Because at the very end we will just check if that element is 0, if it is
    we don't care about these 2 boolean values since we are going to nullify
    both first row and first column.

    After that we just set 0's in 0th row and column based on values in our
    submatrix matrix[1][1] - matrix[m][n].

    Then iterate through the 0th row (from index 1 again) and if we find a 0
    value, nullify that entire column.

    Then iterate through the 0th col (from index 1 again) and if we find a 0
    value, nullify that entire ow.

    After we finish that, now we check if matrix[0][0] == 0. If it is then
    nullify both 0th row and 0th column.

    If it is not, then our "nullify_row_zero" and "nullify_col_zero" boolean
    variables come in play.

    We nullify 0th row if "nullify_row_zero" is true.
    We nullify 0th col if "nullify_col_zero" is true.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.74% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        if (ROWS == 1 && COLS == 1)
            return;

        bool nullify_col_zero = false;
        for (int row = 0; row < ROWS; row++)
        {
            if (matrix[row][0] == 0)
            {
                nullify_col_zero = true;
                break;
            }
        }

        bool nullify_row_zero = false;
        for (int col = 0; col < COLS; col++)
        {
            if (matrix[0][col] == 0)
            {
                nullify_row_zero = true;
                break;
            }
        }

        // Check the Submatrix from matrix[1][1] to matrix[ROWS-1][COLS-1] incl
        for (int row = 1; row < ROWS; row++)
        {
            for (int col = 1; col < COLS; col++)
            {
                if (matrix[row][col] == 0)
                {
                    matrix[ 0 ][col] = 0; // Mark
                    matrix[row][ 0 ] = 0; // Mark
                }
            }
        }

        // Nullify corresponding ROWS
        for (int col = 1; col < COLS; col++)
        {
            if (matrix[0][col] == 0)
                nullify_col(col, matrix);
        }

        // Nullify corresponding COLS
        for (int row = 1; row < ROWS; row++)
        {
            if (matrix[row][0] == 0)
                nullify_row(row, matrix);
        }

        if (nullify_row_zero) nullify_row(0, matrix);
        if (nullify_col_zero) nullify_col(0, matrix);
    }

private:
    void nullify_col(int col, vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();

        for (int row = 0; row < ROWS; row++)
            matrix[row][col] = 0;
    }

    void nullify_row(int row, vector<vector<int>>& matrix)
    {
        const int COLS = matrix[0].size();

        for (int col = 0; col < COLS; col++)
            matrix[row][col] = 0;
    }
};
