/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    3195) Find the Minimum Area to Cover All Ones I
    ===============================================

    ============
    Description:
    ============

    You are given a 2D binary array grid. Find a rectangle with horizontal and
    vertical sides with the smallest area, such that all the 1's in grid lie
    inside this rectangle.

    Return the minimum possible area of the rectangle.

    =====================================================
    FUNCTION: int minimumArea(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,1,0],[1,0,1]]
    Output: 6

    --- Example 2 ---
    Input: grid = [[1,0],[0,0]]
    Output: 1


    *** Constraints ***
    1 <= grid.length, grid[i].length <= 1000
    grid[i][j] is either 0 or 1.
    The input is generated such that there is at least one 1 in grid.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 44.41% */
/* Space Beats: 86.58% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int leftmost  = COLS;
        int rightmost = -1;

        int highest = ROWS;
        int lowest  = -1;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    leftmost  = min(leftmost,  col);
                    rightmost = max(rightmost, col);
                }
            }
        }

        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                if (grid[row][col] == 1)
                {
                    highest = min(highest, row);
                    lowest  = max(lowest,  row);
                }
            }
        }

        int A = rightmost - leftmost + 1;
        int B = lowest - highest + 1;

        return A * B;
    }
};
