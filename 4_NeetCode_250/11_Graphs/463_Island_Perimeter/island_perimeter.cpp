/*
    ============
    === EASY ===
    ============

    ===========================
    463) Island Perimeter
    ===========================

    ============
    Description:
    ============

    You are given row x col grid representing a map where grid[i][j] = 1
    represents land and grid[i][j] = 0 represents water.

    Grid cells are connected horizontally/vertically (not diagonally). The grid
    is completely surrounded by water, and there is exactly one island (i.e.,
    one or more connected land cells).

    The island doesn't have "lakes", meaning the water inside isn't connected
    to the water around the island. One cell is a square with side length 1.
    The grid is rectangular, width and height don't exceed 100. Determine the
    perimeter of the island.

    =====================================================
    FUNCTION: islandPerimeter(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+
    |     |  X  |     |     |
    +-----+-----+-----+-----+
    |  X  |  X  |  X  |     |
    +-----+-----+-----+-----+
    |     |  X  |     |     |
    +-----+-----+-----+-----+
    |  X  |  X  |     |     |
    +-----+-----+-----+-----+

    Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
    Output: 16
    Explanation: The perimeter is the 16 yellow stripes in the image above.

    --- Example 2 ---
    Input: grid = [[1]]
    Output: 4

    --- Example 3 ---
    Input: grid = [[1,0]]
    Output: 4


    *** Constraints ***
    row == grid.length
    col == grid[i].length
    1 <= row, col <= 100
    grid[i][j] is 0 or 1.
    There is exactly one island in grid.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is much more Space efficient for it does not use recursion.
    However I think this was not the point of this problem, but it is faster
    on LeetCode, so here it is.

    The point of this problem is to practice "Number of Islands" kind of
    problem.

*/

/* Time  Beats: 93.74% */
/* Space Beats: 79.44% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid)
    {
        int perimeter = 0;
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                if(grid[i][j] == 1)
                {
                    // Unconnected cell
                    perimeter += 4;

                    // Check if it's connected Upwards
                    if(i > 0        && grid[i-1][j] == 1)
                        perimeter -= 1;

                    // Check if it's connected Downwards
                    if(i < ROWS - 1 && grid[i+1][j] == 1)
                        perimeter -= 1;

                    // Check if it's connected to the Left
                    if(j > 0        && grid[i][j - 1] == 1)
                        perimeter -= 1;

                    // Check if it's connected to the Right
                    if(j < COLS - 1 && grid[i][j + 1] == 1)
                        perimeter -= 1;
                }
            }
        }

        return perimeter;
    }
};
