/*
    ============
    === EASY ===
    ============

    ==============================
    892) Surface Area of 3D Shapes
    ==============================

    ============
    Description:
    ============

    You are given an n x n grid where you have placed some 1 x 1 x 1 cubes.
    Each value v = grid[i][j] represents a tower of v cubes placed on top of
    cell (i, j).

    After placing these cubes, you have decided to glue any directly adjacent
    cubes to each other, forming several irregular 3D shapes.

    Return the total surface area of the resulting shapes.

    =====
    Note: The bottom face of each shape counts toward its surface area. 
    =====

    =====================================================
    FUNCTION: int surfaceArea(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2],[3,4]]
    Output: 34

    --- Example 2 ---
    Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
    Output: 32

    --- Example 3 ---
    Input: grid = [[2,2,2],[2,1,2],[2,2,2]]
    Output: 46

    *** Constraints ***
    n == grid.length == grid[i].length
    1 <= n <= 50
    0 <= grid[i][j] <= 50

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   4.76% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int surfaceArea(vector<vector<int>> grid)
    {
        const int N = grid.size();
        int result = 0;

        for (int row = 0; row < N; ++row)
        {
            for (int col = 0; col < N; ++col)
            {
                if (grid[row][col])
                    result += grid[row][col] * 4 + 2;

                if (row > 0)
                    result -= min(grid[row][col], grid[row - 1][col]) * 2;

                if (col > 0)
                    result -= min(grid[row][col], grid[row][col - 1]) * 2;
            }
        }

        return result;
    }
};
