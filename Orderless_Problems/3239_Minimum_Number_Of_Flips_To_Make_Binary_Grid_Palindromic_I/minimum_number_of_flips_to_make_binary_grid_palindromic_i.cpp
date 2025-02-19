/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================================
    3239) Minimum Number of Flips to Make Binary Grid Palindromic I
    ===============================================================

    ============
    Description:
    ============

    You are given an m x n binary matrix grid.

    A row or column is considered palindromic if its values read the same
    forward and backward.

    You can flip any number of cells in grid from 0 to 1, or from 1 to 0.

    Return the minimum number of cells that need to be flipped to make either
    all rows palindromic or all columns palindromic.

    ==================================================
    FUNCTION: int minFlips(vector<vector<int>>& grid);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
    Output: 2

    --- Example 2 ---
    Input: grid = [[0,1],[0,1],[0,0]]
    Output: 1

    --- Example 3 ---
    Input: grid = [[1],[0]]
    Output: 0
    Explanation:
    All rows are already palindromic.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m * n <= 2 * 10^5
    0 <= grid[i][j] <= 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Count how many would you need to flip in order to make all rows to be
    palindromic.

    Do the same but for columns.

    Take the less one as a result.

*/

/* Time  Beats: 34.88% */
/* Space Beats: 41.34% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int minFlips(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        if (ROWS == 1 || COLS == 1)
            return 0;

        int row_diff = 0;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS/2; col++)
            {
                if (grid[row][col] != grid[row][COLS-1 - col])
                    row_diff++;
            }
        }

        int col_diff = 0;
        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS/2; row++)
            {
                if (grid[row][col] != grid[ROWS-1 - row][col])
                    col_diff++;
            }
        }

        return min(row_diff, col_diff);
    }
};
