#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    1463) Cherry Pickup II
    ===========================

    ============
    Description:
    ============


    You are given a rows x cols matrix grid representing a field of cherries
    where grid[i][j] represents the number of cherries that you can collect
    from the (i, j) cell.

    You have two robots that can collect cherries for you:

        Robot #1 is located at the top-left corner (0, 0), and
        Robot #2 is located at the top-right corner (0, cols - 1).

    Return the maximum number of cherries collection using both robots by
    following the rules below:

        + From a cell (i, j), robots can move to cell:
            (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).

        + When any robot passes through a cell, It picks up all cherries, and
          the cell becomes an empty cell.

        + When both robots stay in the same cell, only one takes the cherries.

        + Both robots cannot move outside of the grid at any moment.

        + Both robots should reach the bottom row in grid.

    ======================================================
    FUNCTION: int cherryPickup(vector<vector<int>>& grid);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
    Output: 24
    Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
    Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
    Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
    Total of cherries: 12 + 12 = 24.

    --- Example 2 ---
    Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
    Output: 28
    Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
    Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
    Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
    Total of cherries: 17 + 11 = 28.


    *** Constraints ***
    rows == grid.length
    cols == grid[i].length
    2 <= rows, cols <= 70
    0 <= grid[i][j] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.18% */
/* Space Beats: 25.87% */

/* Time  Complexity: O(ROWS * COLS^2) */
/* Space Complexity: O(ROWS * COLS^2) */
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid)
    {
        int ROWS = grid.size();
        int COLS = grid[0].size();

        vector<vector<vector<int>>> dp(ROWS, vector<vector<int>>(COLS, vector<int>(COLS, -1)));
        dp[0][0][COLS - 1] = grid[0][0] + grid[0][COLS - 1];

        int max_cherries = 0;
        for (int row = 1; row < ROWS; row++)
        {
            for (int col_a = 0; col_a < COLS; ++col_a) // robot A's column
            {
                for (int col_b = col_a + 1; col_b < COLS; col_b++) // robot B's column
                {
                    for (int delta_a = -1; delta_a <= 1; delta_a++) // move robot A
                    {
                        for (int delta_b = -1; delta_b <= 1; delta_b++) // move robot B
                        {
                            int new_col_a = col_a + delta_a;
                            int new_col_b = col_b + delta_b;

                            if (new_col_a >= 0 && new_col_a < COLS && new_col_b >= 0 && new_col_b < COLS)
                            {
                                int previous_cherries = dp[row - 1][new_col_a][new_col_b];

                                if (previous_cherries != -1)
                                    dp[row][col_a][col_b] = max(dp[row][col_a][col_b], previous_cherries + grid[row][col_a] + (col_a != col_b ? grid[row][col_b] : 0));
                            }
                        }
                    }

                    if (max_cherries < dp[row][col_a][col_b])
                        max_cherries = dp[row][col_a][col_b];
                }
            }
        }

        return max_cherries;
    }
};
