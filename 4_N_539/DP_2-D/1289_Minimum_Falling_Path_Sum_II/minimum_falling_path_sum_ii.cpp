#include <iostream>

/*
    ============
    === HARD ===
    ============

    =================================
    1289) Minimum Falling Path Sum II
    =================================

    ============
    Description:
    ============

    Given an n x n integer matrix grid, return the minimum sum of a falling
    path with non-zero shifts.

    A falling path with non-zero shifts is a choice of exactly one element from
    each row of grid such that no two elements chosen in adjacent rows are in
    the same column.

    ===========================================================
    FUNCTION: int minFallingPathSum(vector<vector<int>>& grid);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
    Output: 13
    Explanation:
    The possible falling paths are:
    [1,5,9], [1,5,7], [1,6,7], [1,6,8],
    [2,4,8], [2,4,9], [2,6,7], [2,6,8],
    [3,4,8], [3,4,9], [3,5,7], [3,5,9]
    The falling path with the smallest sum is [1,5,7], so the answer is 13.


    --- Example 2 ---
    Input: grid = [[7]]
    Output: 7


    *** Constraints ***
    n == grid.length == grid[i].length
    1 <= n <= 200
    -99 <= grid[i][j] <= 99

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.15% */
/* Space Beats: 81.25% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid)
    {
        int n = grid.size();

        for (int i = 1; i < n; i++)
        {
            int min1 = INT_MAX;
            int min2 = INT_MAX;
            int idx1 = -1;

            for (int j = 0; j < n; j++)
            {
                if (grid[i - 1][j] < min1)
                {
                    min2 = min1;
                    min1 = grid[i - 1][j];
                    idx1 = j;
                }
                else if (grid[i - 1][j] < min2 && idx1 != j)
                    min2 = grid[i - 1][j];
            }

            for (int j = 0; j < n; j++)
                grid[i][j] += (j == idx1 ? min2 : min1);
        }

        return *min_element(grid[n - 1].begin(), grid[n - 1].end());
    }
};
