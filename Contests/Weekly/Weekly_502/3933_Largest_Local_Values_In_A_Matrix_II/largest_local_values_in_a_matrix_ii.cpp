/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3933) Largest Local Values in a Matrix II
    =========================================

    ============
    Description:
    ============

    You are given an n x m integer matrix matrix containing non-negative
    integers.

    A non-zero cell (row, col) checks the cells near it as follows:

        + Let x = matrix[row][col].

        + Consider every cell within x rows and x columns of (row, col).

        + Ignore cells that are outside the matrix.

        + Ignore the cells where both the row distance and column distance are
          exactly x.

    The cell (row, col) is a local maximum if it is non-zero and no considered
    cell has a value greater than x.

    Return an integer denoting the number of local maximums in matrix.

    ==============================================================
    FUNCTION: int countLocalMaximums(vector<vector<int>>& matrix);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<vector<vector<int>>> prefix_sum;

public:
    int countLocalMaximums(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        int result = 0;

        prefix_sum.resize(201, vector<vector<int>>(ROWS + 1, vector<int>(COLS + 1)));

        for (int value = 0; value <= 200; value++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                int row_sum = 0;

                for (int col = 0; col < COLS; col++)
                {
                    if (matrix[row][col] > value)
                        row_sum++;

                    prefix_sum[value][row + 1][col + 1] = row_sum + prefix_sum[value][row][col + 1];
                }
            }
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (matrix[row][col] == 0)
                    continue;

                if (is_local_maximum(row, col, matrix))
                    result++;
            }
        }

        return result;
    }

private:
    bool is_local_maximum(int row, int col, vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        const int value = matrix[row][col];

        const int top_row    = max(0       , row - value);
        const int bottom_row = min(ROWS - 1, row + value);
        const int left_col   = max(0       , col - value);
        const int right_col  = min(COLS - 1, col + value);

        int greater_elements = prefix_sum[value][bottom_row + 1][right_col + 1] -
                               prefix_sum[value][top_row       ][right_col + 1] -
                               prefix_sum[value][bottom_row + 1][left_col     ] +
                               prefix_sum[value][top_row       ][left_col     ];

        const int row_offset[] = {-value, -value, value, value};
        const int col_offset[] = {-value, value, -value, value};

        for (int direction = 0; direction < 4; direction++)
        {
            const int next_row = row + row_offset[direction];
            const int next_col = col + col_offset[direction];

            if (next_row >= 0 &&
                next_row < ROWS &&
                next_col >= 0 &&
                next_col < COLS &&
                matrix[next_row][next_col] > value)
            {
                greater_elements--;
            }
        }

        return greater_elements == 0;
    }
};



/* Time  Beats: 48.33% */
/* Space Beats: 37.66% */
class Solution_2 {
private:
    vector<int> log_value;

    vector<vector<vector<vector<int>>>> sparse_table;

    void build_sparse_table(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        log_value.resize(max(ROWS, COLS) + 1);

        for (int i = 2; i < (int)log_value.size(); i++)
        {
            log_value[i] = log_value[i / 2] + 1;
        }

        const int ROW_LEVELS = log_value[ROWS] + 1;
        const int COL_LEVELS = log_value[COLS] + 1;

        sparse_table.assign(ROW_LEVELS, vector<vector<vector<int>>>(COL_LEVELS, vector<vector<int>>(ROWS, vector<int>(COLS))));

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                sparse_table[0][0][row][col] = matrix[row][col];
            }
        }

        for (int col_level = 1; col_level < COL_LEVELS; col_level++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                for (int col = 0; col + (1 << col_level) <= COLS; col++)
                {
                    sparse_table[0][col_level][row][col] = max(sparse_table[0][col_level - 1][row][col],
                                                               sparse_table[0][col_level - 1][row][col + (1 << (col_level - 1))]);
                }
            }
        }

        for (int row_level = 1; row_level < ROW_LEVELS; row_level++)
        {
            for (int col_level = 0; col_level < COL_LEVELS; col_level++)
            {
                for (int row = 0; row + (1 << row_level) <= ROWS; row++)
                {
                    for (int col = 0; col + (1 << col_level) <= COLS; col++)
                    {
                        sparse_table[row_level][col_level][row][col] = max(sparse_table[row_level - 1][col_level][row][col],
                                                                           sparse_table[row_level - 1][col_level][row + (1 << (row_level - 1))][col]);
                    }
                }
            }
        }
    }

    int query_max(int row_1, int col_1, int row_2, int col_2)
    {
        if (row_1 > row_2 || col_1 > col_2)
            return INT_MIN;

        const int row_level = log_value[row_2 - row_1 + 1];
        const int col_level = log_value[col_2 - col_1 + 1];

        const int row_offset = row_2 - (1 << row_level) + 1;
        const int col_offset = col_2 - (1 << col_level) + 1;

        return max({
            sparse_table[row_level][col_level][row_1     ][col_1     ],
            sparse_table[row_level][col_level][row_offset][col_1     ],
            sparse_table[row_level][col_level][row_1     ][col_offset],
            sparse_table[row_level][col_level][row_offset][col_offset]
        });
    }

public:
    int countLocalMaximums(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        build_sparse_table(matrix);

        int result = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                const int value = matrix[row][col];

                if (value == 0)
                    continue;

                const int row_min = max(0       , row - value);
                const int row_max = min(ROWS - 1, row + value);
                const int col_min = max(0       , col - value);
                const int col_max = min(COLS - 1, col + value);

                bool is_local_max = true;

                const int inner_max = query_max(
                    row_min + 1,
                    col_min + 1,
                    row_max - 1,
                    col_max - 1
                );

                if (inner_max > value)
                    is_local_max = false;

                if (is_local_max)
                {
                    for (int col_idx = col_min; col_idx <= col_max; col_idx++)
                    {
                        if ( ! (abs(row_min - row) == value && abs(col_idx - col) == value))
                        {
                            if (matrix[row_min][col_idx] > value)
                            {
                                is_local_max = false;
                                break;
                            }
                        }

                        if (row_max != row_min &&
                            ! (abs(row_max - row) == value && abs(col_idx - col) == value))
                        {
                            if (matrix[row_max][col_idx] > value)
                            {
                                is_local_max = false;
                                break;
                            }
                        }
                    }
                }

                if (is_local_max)
                {
                    for (int row_idx = row_min + 1; row_idx < row_max; row_idx++)
                    {
                        if (matrix[row_idx][col_min] > value)
                        {
                            is_local_max = false;
                            break;
                        }

                        if (col_min != col_max &&
                            matrix[row_idx][col_max] > value)
                        {
                            is_local_max = false;
                            break;
                        }
                    }
                }

                if (is_local_max)
                    result++;
            }
        }

        return result;
    }
};
