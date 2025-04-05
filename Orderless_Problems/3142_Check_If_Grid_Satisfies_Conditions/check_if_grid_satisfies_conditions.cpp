/*
    ============
    === EASY ===
    ============

    ========================================
    3142) Check if Grid Satisfies Conditions
    ========================================

    ============
    Description:
    ============

    You are given a 2D matrix grid of size m x n. You need to check if each
    cell grid[i][j] is:

        + Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j]
          (if it exists).

        + Different from the cell to its right, i.e.
          grid[i][j] != grid[i][j + 1]
          (if it exists).

    Return true if all the cells satisfy these conditions, otherwise, return
    false.

    ==============================================================
    FUNCTION: bool satisfiesConditions(vector<vector<int>>& grid);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0,2],[1,0,2]]
    Output: true

    --- Example 2 ---
    Input: grid = [[1,1,1],[0,0,0]]
    Output: false

    --- Example 3 ---
    Input: grid = [[1],[2],[3]]
    Output: false


    *** Constraints ***
    1 <= n, m <= 10
    0 <= grid[i][j] <= 9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.40% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    bool satisfiesConditions(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (row + 1 < ROWS)
                {
                    if (grid[row][col] != grid[row+1][col])
                        return false;
                }

                if (col + 1 < COLS)
                {
                    if (grid[row][col] == grid[row][col+1])
                        return false;
                }
            }
        }

        return true;
    }
};
