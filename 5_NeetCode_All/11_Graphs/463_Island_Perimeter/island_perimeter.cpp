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

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.38% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int perimeter = 0;

        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0, -1}, {0,1}};

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    perimeter += 4;

                    perimeter -= (row-1 >= 0    && grid[row-1][col  ] == 1 ? 1 : 0);
                    perimeter -= (row+1 <  ROWS && grid[row+1][col  ] == 1 ? 1 : 0);
                    perimeter -= (col-1 >= 0    && grid[row  ][col-1] == 1 ? 1 : 0);
                    perimeter -= (col+1 <  COLS && grid[row  ][col+1] == 1 ? 1 : 0);
                }
            }
        }

        return perimeter;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A little bit more efficient. This way we only checking "Down" and "Right"
    instead of all 4 directions, each time.

    It's not a big optimization, but it's:

        O(ROWS * COLS * 4) --> O(ROWS * COLS * 2)

    In terms of Big O notation it's virtually the same, but the "wall time
    clock" is better with this one.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.04% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution_2 {
public:
    int islandPerimeter(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int perimeter = 0;

        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0, -1}, {0,1}};

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    perimeter += 4;

                    if (row+1 < ROWS && grid[row+1][col  ] == 1)
                        perimeter -= 2; // One for each land cell

                    if (col+1 < COLS && grid[row  ][col+1] == 1)
                        perimeter -= 2;
                }
            }
        }

        return perimeter;
    }
};
