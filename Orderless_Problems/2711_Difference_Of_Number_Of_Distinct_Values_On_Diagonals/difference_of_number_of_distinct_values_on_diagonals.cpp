/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    2711) Difference of Number of Distinct Values on Diagonals
    ==========================================================

    ============
    Description:
    ============


    Given a 2D grid of size m x n, you should find the matrix answer of size
    m x n.

    The cell answer[r][c] is calculated by looking at the diagonal values of
    the cell grid[r][c]:

        + Let leftAbove[r][c] be the number of distinct values on the diagonal
          to the left and above the cell grid[r][c] not including the cell
          grid[r][c] itself.

        + Let rightBelow[r][c] be the number of distinct values on the diagonal
          to the right and below the cell grid[r][c], not including the cell
          grid[r][c] itself.

        Then answer[r][c] = |leftAbove[r][c] - rightBelow[r][c]|.

    A matrix diagonal is a diagonal line of cells starting from some cell in
    either the topmost row or leftmost column and going in the bottom-right
    direction until the end of the matrix is reached.

    Return the matrix answer.

    ====================================================================================
    FUNCTION: vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2,3],[3,1,5],[3,2,1]]
    Output: Output: [[1,1,0],[1,0,1],[0,1,1]]

    --- Example 2 ---
    Input: grid = [[1]]
    Output: Output: [[0]]


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n, grid[i][j] <= 50

*/

#include <cstdlib>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 12.62% */
/* Space Beats: 5.83% */

/* Time  Complexity: O(ROWS * COLS * min(ROWS, COLS)) */
/* Space Complexity: O(min(ROWS, COLS))               */
class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> answer(ROWS, vector<int>(COLS, 0));

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                // Left-Above
                unordered_set<int> uset_left_above;
                int r = row-1;
                int c = col-1;

                while (r >= 0 && c >= 0)
                {
                    uset_left_above.insert(grid[r][c]);
                    r--;
                    c--;
                }

                // Right-Below
                unordered_set<int> uset_right_below;
                r = row+1;
                c = col+1;
                while (r < ROWS && c < COLS)
                {
                    uset_right_below.insert(grid[r][c]);
                    r++;
                    c++;
                }

                int left_above_size  = uset_left_above.size();
                int right_below_size = uset_right_below.size();

                answer[row][col] = abs(left_above_size - right_below_size);
            }
        }

        return answer;
    }
};
