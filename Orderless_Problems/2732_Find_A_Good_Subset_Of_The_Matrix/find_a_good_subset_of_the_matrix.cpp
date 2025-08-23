/*
    ============
    === HARD ===
    ============

    ======================================
    2732) Find a Good Subset of the Matrix
    ======================================

    ============
    Description:
    ============

    You are given a 0-indexed m x n binary matrix grid.

    Let us call a non-empty subset of rows good if the sum of each column of
    the subset is at most half of the length of the subset.

    More formally, if the length of the chosen subset of rows is k, then the
    sum of each column should be at most floor(k / 2).

    Return an integer array that contains row indices of a good subset sorted
    in ascending order.

    If there are multiple good subsets, you can return any of them. If there
    are no good subsets, return an empty array.

    A subset of rows of the matrix grid is any matrix that can be obtained by
    deleting some (possibly none or all) rows from grid.

    ==========================================================================
    FUNCTION: vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,1,0],[0,0,0,1],[1,1,1,1]]
    Output: [0,1]
    Explanation: We can choose the 0th and 1st rows to create a good subset of rows.
    The length of the chosen subset is 2.
    - The sum of the 0th column is 0 + 0 = 0, which is at most half of the length of the subset.
    - The sum of the 1st column is 1 + 0 = 1, which is at most half of the length of the subset.
    - The sum of the 2nd column is 1 + 0 = 1, which is at most half of the length of the subset.
    - The sum of the 3rd column is 0 + 1 = 1, which is at most half of the length of the subset.

    --- Example 2 ---
    Input: grid = [[0]]
    Output: [0]
    Explanation: We can choose the 0th row to create a good subset of rows.
    The length of the chosen subset is 1.
    - The sum of the 0th column is 0, which is at most half of the length of the subset.

    --- Example 3 ---
    Input: grid = [[1,1,1],[1,1,1]]
    Output: []
    Explanation: It is impossible to choose any subset of rows to create a good subset.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m <= 10^4
    1 <= n <= 5
    grid[i][j] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is MUCH easier than you'd think.

    First, it's important to be VERY careful how you read the problem. They are
    NOT(!!!) asking us to give the LONGEST subset of rows that satisfy the
    condition, rather they are just asking for ANY subset that satisfy the
    condition.

    Once you realize this, it becomes substantially easier.


    Second, this is the only part that is difficult and not intuitive, but once
    you realize it -- You're done.

    Solution is either:

        1. A single all 0s row
        2. Any TWO rows that have a "bitwise AND" equal to 0.

    It's NOT intuitive to realize the 2nd option. If we're NOT able to find any
    two rows that have "bitwise AND" result of 0, then there is simply no
    solution at all.

    However, once you realize these above things -- You're literally done. The
    implementation is trivial now.

*/

/* Time  Beats: 66.67% */
/* Space Beats: 62.74% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS)        */
class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // At most 32 possible bitmasks since: COLS == 5
        const int max_mask = 1 << COLS;

        // Store first index where each mask appears
        vector<int> first_occurrence(max_mask, -1);

        for (int row = 0; row < ROWS; row++)
        {
            int mask_value = 0;
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                    mask_value |= (1 << col);
            }

            if (mask_value == 0)
                return {row}; // single row with all zeros is valid

            if (first_occurrence[mask_value] == -1)
                first_occurrence[mask_value] = row;
        }

        // Check all pairs of masks (only up to 32 * 32)
        for (int mask1 = 0; mask1 < max_mask; mask1++)
        {
            if (first_occurrence[mask1] == -1)
                continue;

            for (int mask2 = mask1 + 1; mask2 < max_mask; mask2++)
            {
                if (first_occurrence[mask2] == -1)
                    continue;

                if ((mask1 & mask2) == 0)
                {
                    int row1 = first_occurrence[mask1];
                    int row2 = first_occurrence[mask2];

                    if (row1 > row2)
                        swap(row1, row2);

                    return {row1, row2};
                }
            }
        }

        return {};
    }
};
