/*
    ============
    === EASY ===
    ============

    ======================================
    3643) Flip Square Submatrix Vertically
    ======================================

    ============
    Description:
    ============

    You are given an m x n integer matrix grid, and three integers x, y, and k.

    The integers x and y represent the row and column indices of the top-left
    corner of a square submatrix and the integer k represents the size
    (side length) of the square submatrix.

    Your task is to flip the submatrix by reversing the order of its rows
    vertically.

    Return the updated matrix.

    ===============================================================================================
    FUNCTION: vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], x = 1, y = 0, k = 3
    Output: [[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]
    Explanation:
    The diagram above shows the grid before and after the transformation.

    --- Example 2 ---
    Input: grid = [[3,4,2,3],[2,3,4,2]], x = 0, y = 2, k = 2
    Output: [[3,4,4,2],[2,3,2,3]]
    Explanation:
    The diagram above shows the grid before and after the transformation.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    1 <= grid[i][j] <= 100
    0 <= x < m
    0 <= y < n
    1 <= k <= min(m - x, n - y)

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 18.09% */
/* Space Beats: 38.39% */

/* Time  Complexity: O(k^2) */
/* Space Complexity: O(1)  */
class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        for (int row = 0; row < (k >> 1); row++)
        {
            for (int col = 0; col < k; col++)
            {
                swap(grid[row + x][col + y], grid[x + k - 1 - row][col + y]);
            }
        }

        return grid;
    }
};
