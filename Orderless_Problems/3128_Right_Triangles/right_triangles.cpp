/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3128) Right Triangles
    ===========================

    ============
    Description:
    ============

    You are given a 2D boolean matrix grid.

    A collection of 3 elements of grid is a right triangle if one of its
    elements is in the same row with another element and in the same column
    with the third element. The 3 elements may not be next to each other.

    Return an integer that is the number of right triangles that can be made
    with 3 elements of grid such that all of them have a value of 1.

    ======================================================================
    FUNCTION: long long numberOfRightTriangles(vector<vector<int>>& grid);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,0],[0,1,1],[0,1,0]]
    Output: 2
    Explanation: There are two right triangles with elements of the value 1.
                 Notice that the blue ones do not form a right triangle because
                 the 3 elements are in the same column.

    --- Example 2 ---
    Input: grid = [[1,0,0,0],[0,1,0,1],[1,0,0,0]]
    Output: 0
    Explanation: There are no right triangles with elements of the value 1.
                 Notice that the blue ones do not form a right triangle.


    --- Example 3 ---
    Input: grid = [[1,0,1],[1,0,0],[1,0,0]]
    Output: 2
    Explanation:
    There are two right triangles with elements of the value 1.


    *** Constraints ***
    1 <= grid.length <= 1000
    1 <= grid[i].length <= 1000
    0 <= grid[i][j] <= 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

    Just go through the code and you'll get it.

*/

/* Time  Beats: 6.00% */
/* Space Beats: 5.33% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> right(ROWS, vector<int>(COLS, 0));
        vector<vector<int>> down (ROWS, vector<int>(COLS, 0));
        vector<vector<int>> up   (ROWS, vector<int>(COLS, 0));
        vector<vector<int>> left (ROWS, vector<int>(COLS, 0));

        // Initialize Right
        for (int row = ROWS-1; row >= 0; row--)
            right[row][COLS-1] = grid[row][COLS-1];

        // Initialize Down
        for (int col = COLS-1; col >= 0; col--)
            down[ROWS-1][col] = grid[ROWS-1][col];

        // Initiale Left
        for (int row = 0; row < ROWS; row++)
            left[row][0] = grid[row][0];

        // Initiale Up
        for (int col = 0; col < COLS; col++)
            up[0][col] = grid[0][col];


        // Right
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-2; col >= 0; col--)
            {
                right[row][col] = grid[row][col] + right[row][col+1];
            }
        }

        // Down
        for (int col = COLS-1; col >= 0; col--)
        {
            for (int row = ROWS-2; row >= 0; row--)
            {
                down[row][col] = grid[row][col] + down[row+1][col];
            }
        }

        // Left
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 1; col < COLS; col++)
            {
                left[row][col] = left[row][col-1] + grid[row][col];
            }
        }

        // Up
        for (int col = 0; col < COLS; col++)
        {
            for (int row = 1; row < ROWS; row++)
            {
                up[row][col] = up[row-1][col] + grid[row][col];
            }
        }


        long long result = 0;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    if (col < COLS-1)
                    {
                        if (row < ROWS-1)
                            result += right[row][col+1] * down[row+1][col];

                        if (row > 0)
                            result += right[row][col+1] * up[row-1][col];
                    }

                    if (col > 0)
                    {
                        if (row < ROWS-1)
                            result += left[row][col-1] * down[row+1][col];

                        if (row > 0)
                            result += left[row][col-1] * up[row-1][col];
                    }
                }
            }
        }

        return result;
    }
};
