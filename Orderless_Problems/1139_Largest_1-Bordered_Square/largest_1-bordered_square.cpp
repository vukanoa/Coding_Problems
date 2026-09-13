/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    1139) Largest 1-Border Square
    =============================

    ============
    Description:
    ============

    Given a 2D grid of 0s and 1s, return the number of elements in the largest
    square subgrid that has all 1s on its border, or 0 if such a subgrid
    doesn't exist in the grid.

    ================================================================
    FUNCTION: int largest1BorderedSquare(vector<vector<int>>& grid);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
    Output: 9

    --- Example 2 ---
    Input: grid = [[1,1,0,0]]
    Output: 1


    *** Constraints ***
    1 <= grid.length <= 100
    1 <= grid[0].length <= 100
    grid[i][j] is 0 or 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 71.26% */
/* Space Beats: 62.76% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> row_prefix(ROWS, vector<int>(COLS));
        vector<vector<int>> col_prefix(ROWS, vector<int>(COLS));

        /* Calculate PREFIX SUMS */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    row_prefix[row][col] = 1 + (col > 0 ? row_prefix[row  ][col-1] : 0);
                    col_prefix[row][col] = 1 + (row > 0 ? col_prefix[row-1][col  ] : 0);
                }
            }
        }

        int max_side = 0;

        /* Try every cell as BOTTOM-RIGHT corner */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                int bottom = row_prefix[row][col];
                int right  = col_prefix[row][col];

                int side = min(bottom, right);

                while (side > max_side)
                {
                    int top   = row_prefix[row-side+1][col       ];
                    int left  = col_prefix[row       ][col-side+1];

                    if (top >= side && left >= side)
                    {
                        max_side = side;
                        break;
                    }

                    --side;
                }
            }
        }

        return max_side * max_side;
    }
};
