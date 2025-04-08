/*
    ============
    === EASY ===
    ============

    =======================================
    3127) Make a Square with the Same Color
    =======================================

    ============
    Description:
    ============


    You are given a 2D matrix grid of size 3 x 3 consisting only of characters
    'B' and 'W'. Character 'W' represents the white color, and character 'B'
    represents the black color.

    Your task is to change the color of at most one cell so that the matrix has
    a 2 x 2 square where all cells are of the same color.

    Return true if it is possible to create a 2 x 2 square of the same color,
    otherwise, return false.

    =========================================================
    FUNCTION: bool canMakeSquare(vector<vector<char>>& grid);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [["B","W","B"],["B","W","W"],["B","W","B"]]
    Output: true
    Explanation:
    It can be done by changing the color of the grid[0][2].

    --- Example 2 ---
    Input: grid = [["B","W","B"],["W","B","W"],["B","W","B"]]
    Output: false
    Explanation:
    It cannot be done by changing at most one cell.

    --- Example 3 ---
    Input: grid = [["B","W","B"],["B","W","W"],["B","W","W"]]
    Output: true
    Explanation:
    The grid already contains a 2 x 2 square of the same color.


    *** Constraints ***
    grid.length == 3
    grid[i].length == 3
    grid[i][j] is either 'W' or 'B'.

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
/* Space Beats:  71.73% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canMakeSquare(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        for (int row = 0; row < 2; row++)
        {
            for (int col = 0; col < 2; col++)
            {
                int black = 0;
                int white = 0;

                if (grid[row][col] == 'B')
                    black++;
                else
                    white++;

                if (grid[row][col+1] == 'B')
                    black++;
                else
                    white++;

                if (grid[row+1][col] == 'B')
                    black++;
                else
                    white++;

                if (grid[row+1][col+1] == 'B')
                    black++;
                else
                    white++;

                if (black >= 3 || white >= 3)
                    return true;
            }
        }

        return false;
    }
};
