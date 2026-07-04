/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3938) Maximum Path Intersection Sum in a Grid
    =============================================

    ============
    Description:
    ============

    You are given an m x n integer matrix grid.

    Two players move across the grid:

        + Player 1 starts at the top-left cell (0, 0) and can move only right
          or down. Their destination is the bottom-right cell (m - 1, n - 1).

        +  Player 2 starts at the bottom-left cell (m - 1, 0) and can move only
           right or up. Their destination is the top-right cell (0, n - 1).

    Each player must choose a valid path from their respective starting cell to
    their destination.

    A cell is called shared if it belongs to both chosen paths.

    Return an integer denoting the maximum possible sum of values of all shared
    cells.

    ==================================================
    FUNCTION: int maxScore(vector<vector<int>>& grid);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2,0,-3],[1,-2,1,0],[-4,2,-1,3],[3,-3,3,-2],[-1,-5,0,1]]
    Output: 4
    Explanation:
    The diagram shows one optimal choice of paths.
        Player 1 follows the red/purple path from the top-left cell to the bottom-right cell:
            (0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2) → (2, 3) → (3, 3) → (4, 3)
        Player 2 follows the blue/purple path from the bottom-left cell to the top-right cell:
            (4, 0) → (4, 1) → (3, 1) → (2, 1) → (2, 2) → (2, 3) → (1, 3) → (0, 3)
        The shared cells are (2, 1), (2, 2), and (2, 3).
        The sum is 2 + (-1) + 3 = 4, which is the maximum possible sum.

    --- Example 2 ---
    Input: grid = [[4,-2,-3],[-1,-3,-1],[-4,2,-1]]
    Output: 3
    Explanation:
    One optimal pair of paths is shown in the diagram.
        Player 1 follows the red/purple path:
            (0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2)
        Player 2 follows the blue/purple path:
            (2, 0) → (1, 0) → (0, 0) → (0, 1) → (0, 2)
        The shared cells are (0, 0) and (1, 0).
        The sum is 4 + (-1) = 3, which is the maximum possible.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 5 * 10^5
    -100 <= grid[i][j] <= 100

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is actually pretty intuitive, you just have to closely examine the
    possible outcomes and you'll "notice a pattern".

    We need to find the maximum score from EITHER:

        + A HORIZONTAL segment in a ROW
        + A VERTICAL   segment in a COLUMN

    Any subarray of length >= 2 is ALWAYS VALID.

    A subarray of length 1 (i.e. single cell) is valid only if the cell is NOT
    on the border.

    That means that the single cell must have 'row' and 'col' be:
    For rows:

        row > 0 && row < ROWS-1   &&   col > 0 && col < COLS-1

    Same idea applies to columns as well.

    And we use "Prefix Sums" to increase the speed even further. We don't want
    to compute each subarray sum each time.

*/

/* Time  Beats:  5.01% */
/* Space Beats: 88.78% */

/* Time  Complexity: O(ROWS * COLS^2  +  COLS * ROWS^2) */
/* Space Complexity: O(max(ROWS, COLS))                 */
class Solution {
public:
    int maxScore(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int result = INT_MIN;

        for (int row = 0; row < ROWS; row++)
        {
            vector<int> prefix_sum(COLS, 0);

            prefix_sum[0] = grid[row][0];
            for (int col = 1; col < COLS; col++)
                prefix_sum[col] = prefix_sum[col - 1] + grid[row][col];

            for (int start_col = 0; start_col < COLS; start_col++)
            {
                for (int end_col = start_col; end_col < COLS; end_col++)
                {
                    int sum = prefix_sum[end_col] - (start_col > 0 ? prefix_sum[start_col - 1] : 0);
                    int subarray_len = end_col - start_col + 1;

                    if (subarray_len >= 2)
                    {
                        result = max(result, sum);
                    }
                    else if (subarray_len == 1)
                    {
                        if (row > 0 && row < ROWS - 1 && start_col > 0 && start_col < COLS - 1)
                            result = max(result, sum);
                    }
                }
            }
        }

        for (int col = 0; col < COLS; col++)
        {
            vector<int> prefix_sum(ROWS, 0);

            prefix_sum[0] = grid[0][col];
            for (int row = 1; row < ROWS; row++)
                prefix_sum[row] = prefix_sum[row - 1] + grid[row][col];

            for (int start_row = 0; start_row < ROWS; start_row++)
            {
                for (int end_row = start_row; end_row < ROWS; end_row++)
                {
                    int sum = prefix_sum[end_row] - (start_row > 0 ? prefix_sum[start_row - 1] : 0);
                    int subarray_len = end_row - start_row + 1;

                    if (subarray_len >= 2)
                    {
                        result = max(result, sum);
                    }
                    else if (subarray_len == 1)
                    {
                        if (start_row > 0 && start_row < ROWS - 1 && col > 0 && col < COLS - 1)
                            result = max(result, sum);
                    }
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can further improve the above Solution by actually using KADANE's
    Algorithm.

*/

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution_Kadane_Algo {
public:
    int maxScore(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int result = INT_MIN;

        for (int row = 0; row < ROWS; row++)
        {
            int curr_subarray_sum = grid[row][0];

            for (int col = 1; col < COLS; col++)
            {
                int length_two_or_more_sum = curr_subarray_sum + grid[row][col];

                result = max(result, length_two_or_more_sum);

                if (row > 0 && row < ROWS - 1 &&
                    col > 0 && col < COLS - 1)
                {
                    result = max(result, grid[row][col]);
                }

                curr_subarray_sum = max(grid[row][col], curr_subarray_sum + grid[row][col]);
            }
        }

        for (int col = 0; col < COLS; col++)
        {
            int curr_subarray_sum = grid[0][col];

            for (int row = 1; row < ROWS; row++)
            {
                int length_two_or_more_sum = curr_subarray_sum + grid[row][col];

                // Evry interior SINGLE CELL is already evaluated within the
                // length_ONE horizontal subarray, therefore we do NOT need to
                // have the same if-statement here. We only need to check the
                // vertical subarrays of length >= 2

                result = max(result, length_two_or_more_sum);

                curr_subarray_sum = max(grid[row][col], curr_subarray_sum + grid[row][col]);
            }
        }

        return result;
    }
};
