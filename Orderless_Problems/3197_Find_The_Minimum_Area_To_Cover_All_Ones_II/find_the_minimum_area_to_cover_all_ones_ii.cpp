/*
    ============
    === HARD ===
    ============

    ================================================
    3197) Find the Minimum Area to Cover All Ones II
    ================================================

    ============
    Description:
    ============

    You are given a 2D binary array grid. You need to find 3 non-overlapping
    rectangles having non-zero areas with horizontal and vertical sides such
    that all the 1's in grid lie inside these rectangles.

    Return the minimum possible sum of the area of these rectangles.

    =====
    Note: that the rectangles are allowed to touch.
    =====

    ====================================================
    FUNCTION: int minimumSum(vector<vector<int>>& grid);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0,1],[1,1,1]]
    Output: 5

    --- Example 2 ---
    Input: grid = [[1,0,1,0],[0,1,0,1]]
    Output: 5


    *** Constraints ***
    1 <= grid.length, grid[i].length <= 30
    grid[i][j] is either 0 or 1.
    The input is generated such that there are at least three 1's in grid.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since the Constraints are extremely small, we can Brute-Force it.

    However, even with the Brute-Force, it's still not easy to come up with it.

    There are exactly 6(six) possible cases. We are just going through them.

*/

/* Time  Beats: 82.00% */
/* Space Beats: 74.00% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int minimumSum(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 1e9;

        int one;
        int two;
        int three;

        int row;
        int col;

        /*
        -------------
        |    (1)    |
        |           |
        -------------
        | (2) | (3) |
        |     |     |
        -------------
        */
        for (row = 0; row < ROWS; row++)
        {
            one = minimum_area(grid, 0, row, 0, COLS - 1);

            for (col = 0; col < COLS; col++)
            {
                two    = minimum_area(grid, row+1, ROWS-1,   0  , col   );
                three  = minimum_area(grid, row+1, ROWS-1, col+1, COLS-1);

                result = min(result, one + two + three);
            }
        }

        /*
        -------------
        |     | (2) |
        |     |     |
          (1) -------
        |     |     |
        |     | (3) |
        -------------
        */
        for (col = 0; col < COLS; col++)
        {
            one = minimum_area(grid, 0, ROWS-1, 0, col);

            for (row = 0; row < ROWS; row++)
            {
                two    = minimum_area(grid,   0  , row   , col+1, COLS-1);
                three  = minimum_area(grid, row+1, ROWS-1, col+1, COLS-1);

                result = min(result, one + two + three);
            }
        }

        /*
        -------------
        |     |     |
        | (2) |     |
        ------- (1) |
        |     |     |
        | (3) |     |
        -------------
        */
        for (col = COLS-1; col >= 0; col--)
        {
            one = minimum_area(grid, 0, ROWS-1, col+1, COLS-1);

            for (row = 0; row < ROWS; row++)
            {
                two    = minimum_area(grid,    0 , row   , 0, col);
                three  = minimum_area(grid, row+1, ROWS-1, 0, col);

                result = min(result, one + two + three);
            }
        }


        /*
        -------------
        | (2) | (3) |
        |     |     |
        ------------
        |           |
        |    (1)    |
        -------------
        */
        for ( row = ROWS-1; row >= 0; row--)
        {
            one = minimum_area(grid, row+1, ROWS-1, 0, COLS - 1);

            for (col = 0; col < COLS; col++)
            {
                two    = minimum_area(grid, 0, row,  0,    col   );
                three  = minimum_area(grid, 0, row, col+1, COLS-1);

                result = min(result, one + two + three);
            }
        }

        /*
        -------------
        |    (1)    |
        -------------
        |    (2)    |
        -------------
        |    (3)    |
        -------------
        */
        for (row = 0; row < ROWS; row++)
        {
            for (col = row+1; col < ROWS; col++)
            {
                one    = minimum_area(grid,  0   , row   , 0, COLS-1);
                two    = minimum_area(grid, row+1, col   , 0, COLS-1);
                three  = minimum_area(grid, col+1, ROWS-1, 0, COLS-1);

                result = min(result, one + two + three);
            }
        }

         /*
        -------------
        |   |   |   |
        |   |   |   |
        |(1)|(2)|(3)|
        |   |   |   |
        |   |   |   |
        -------------
        */
        for (row = 0; row < COLS; row++)
        {
            for (col = row+1; col < COLS; col++)
            {
                one    = minimum_area(grid, 0, ROWS-1,  0   , row   );
                two    = minimum_area(grid, 0, ROWS-1, row+1, col   );
                three  = minimum_area(grid, 0, ROWS-1, col+1, COLS-1);

                result = min(result, one + two + three);
            }
        }

        return result;
    }

private:
    // Function to calculate the minimum area of rectangle enclosing all ones in a submatrix
    int minimum_area(vector<vector<int>>& grid, int starting_row, int ending_row, int starting_col, int ending_col)
    {
        int start_row = 1e9;
        int end_row   = -1;

        int start_col = 1e9;
        int end_col   = -1;

        int found = 0;

        for (int row = starting_row; row <= ending_row; row++)
        {
            for (int col = starting_col; col <= ending_col; col++)
            {
                if (grid[row][col])
                {
                    start_row = min(start_row, row);
                    end_row   = max(end_row, row);

                    start_col = min(start_col, col);
                    end_col   = max(end_col, col);

                    found = 1;
                }
            }
        }

        return found ? ((end_row - start_row + 1) * (end_col - start_col + 1)) : 0;
    }
};
