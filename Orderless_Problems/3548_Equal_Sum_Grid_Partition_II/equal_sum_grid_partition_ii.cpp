/*
    ============
    === HARD ===
    ============

    =================================
    3548) Equal Sum Grid Partition II
    =================================

    ============
    Description:
    ============

    You are given an m x n matrix grid of positive integers. Your task is to
    determine if it is possible to make either one horizontal or one vertical
    cut on the grid such that:

        + Each of the two resulting sections formed by the cut is non-empty.

        + The sum of elements in both sections is equal, or can be made equal
          by discounting at most one single cell in total(from either section).

        + If a cell is discounted, the rest of the section must remain
          connected.

    Return true if such a partition exists; otherwise, return false.

    =====
    Note: A section is connected if every cell in it can be reached from any
          other cell by moving up, down, left, or right through other cells in
          the section.
    =====

    ===========================================================
    FUNCTION: bool canPartitionGrid(vector<vector<int>>& grid);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,4],[2,3]]
    Output: true
    Explanation: A horizontal cut after the first row gives sums 1 + 4 = 5 and
                 2 + 3 = 5, which are equal. Thus, the answer is true.

    --- Example 2 ---
    Input: grid = [[1,2],[3,4]]
    Output: true
    Explanation:
    A vertical cut after the first column gives sums 1 + 3 = 4 and 2 + 4 = 6.
    By discounting 2 from the right section (6 - 2 = 4), both sections have
    equal sums and remain connected. Thus, the answer is true.

    --- Example 3 ---
    Input: grid = [[1,2,4],[2,3,5]]
    Output: false
    Explanation:
    A horizontal cut after the first row gives 1 + 2 + 4 = 7 and 2 + 3 + 5 = 10
    By discounting 3 from the bottom section (10 - 3 = 7), both sections have
    equal sums, but they do not remain connected as it splits the bottom
    section into two parts ([2] and [5]). Thus, the answer is false.


    --- Example 4 ---
    Input: grid = [[4,1,8],[3,2,6]]
    Output: false
    Explanation: No valid cut exists, so the answer is false.


    *** Constraints ***
    1 <= m == grid.length <= 10^5
    1 <= n == grid[i].length <= 10^5
    2 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^5

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.30% */
/* Space Beats: 94.91% */

/* Time  Complexity: O(ROWS * COLS)             */
/* Space Complexity: O(ROWS + COLS + MAX_VALUE) */
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();

        const int MAX_VALUE = 100000;
        long long total_row_sum = 0LL;
        long long total_col_sum = 0LL;
        vector<long long> prefix_row_wise(ROWS, 0LL);
        vector<long long> prefix_col_wise(COLS, 0LL);

        int min_row[MAX_VALUE + 1];
        int max_row[MAX_VALUE + 1];
        int min_col[MAX_VALUE + 1];
        int max_col[MAX_VALUE + 1];

        fill(min_row, min_row + MAX_VALUE + 1, -1);
        fill(max_row, max_row + MAX_VALUE + 1, -1);
        fill(min_col, min_col + MAX_VALUE + 1, -1);
        fill(max_col, max_col + MAX_VALUE + 1, -1);

        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                int val = grid[row][col];

                prefix_row_wise[row] += 1LL * val;
                prefix_col_wise[col] += 1LL * val;

                if (min_row[val] == -1)
                {
                    min_row[val] = max_row[val] = row;
                    min_col[val] = max_col[val] = col;
                }
                else
                {
                    min_row[val] = min(min_row[val], row);
                    max_row[val] = max(max_row[val], row);
                    min_col[val] = min(min_col[val], col);
                    max_col[val] = max(max_col[val], col);
                }
            }
        }

        for (auto r : prefix_row_wise)
            total_row_sum += r;

        total_col_sum = total_row_sum;

        long long curr_row_upper_sum = 0;
        for (int row = 0; row < ROWS - 1; row++)
        {
            curr_row_upper_sum += prefix_row_wise[row];

            long long lower_segment_sum = total_row_sum - curr_row_upper_sum;

            if (curr_row_upper_sum == lower_segment_sum)
                return true;

            if (curr_row_upper_sum > lower_segment_sum)
            {
                long long diff = curr_row_upper_sum - lower_segment_sum;

                if (diff <= MAX_VALUE && min_row[diff] != -1)
                {
                    if (row == 0 || COLS == 1)
                    {
                        if (diff == grid[0][0]        ||
                            diff == grid[0][COLS - 1] ||
                            diff == grid[row][0])
                        {
                            return true;
                        }
                    }
                    else if (min_row[diff] <= row)
                    {
                        return true;
                    }
                }
            }
            else
            {
                long long diff = lower_segment_sum - curr_row_upper_sum;

                if (diff <= MAX_VALUE && max_row[diff] != -1)
                {
                    if (row == ROWS - 2 || COLS == 1)
                    {
                        if (diff == grid[row + 1][0]        ||
                            diff == grid[row + 1][COLS - 1] ||
                            diff == grid[ROWS - 1][0])
                        {
                            return true;
                        }
                    }
                    else if (max_row[diff] > row)
                    {
                        return true;
                    }
                }
            }
        }

        long long curr_col_left_sum = 0;
        for (int col = 0; col < COLS - 1; col++)
        {
            curr_col_left_sum += prefix_col_wise[col];

            long long right_segment_sum = total_col_sum - curr_col_left_sum;

            if (curr_col_left_sum == right_segment_sum)
                return true;

            if (curr_col_left_sum > right_segment_sum)
            {
                long long diff = curr_col_left_sum - right_segment_sum;

                if (diff <= MAX_VALUE && min_col[diff] != -1)
                {
                    if (col == 0 || ROWS == 1)
                    {
                        if (diff == grid[0][0]        ||
                            diff == grid[ROWS - 1][0] ||
                            diff == grid[0][col])
                        {
                            return true;

                        }
                    }
                    else if (min_col[diff] <= col)
                    {
                        return true;
                    }
                }
            }
            else
            {
                long long diff = right_segment_sum - curr_col_left_sum;

                if (diff <= MAX_VALUE && max_col[diff] != -1)
                {
                    if (col == COLS - 2 || ROWS == 1)
                    {
                        if (diff == grid[0][col + 1]        ||
                            diff == grid[ROWS - 1][col + 1] ||
                            diff == grid[0][COLS - 1])
                        {
                            return true;
                        }
                    }
                    else if (max_col[diff] > col)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};
