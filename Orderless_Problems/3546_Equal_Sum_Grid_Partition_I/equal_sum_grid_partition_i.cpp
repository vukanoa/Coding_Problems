/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3546) Equal Sum Grid Partition I
    ================================

    ============
    Description:
    ============

    You are given an m x n matrix grid of positive integers. Your task is to
    determine if it is possible to make either one horizontal or one vertical
    cut on the grid such that:

        + Each of the two resulting sections formed by the cut is non-empty.

        + The sum of the elements in both sections is equal.

    Return true if such a partition exists; otherwise return false.

    ===========================================================
    FUNCTION: bool canPartitionGrid(vector<vector<int>>& grid);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    nput: grid = [[1,4],[2,3]]
    Output: true
    Explanation:
    A horizontal cut between row 0 and row 1 results in two non-empty sections,
    each with a sum of 5. Thus, the answer is true.

    --- Example 2 ---
    Input: grid = [[1,3],[2,4]]
    Output: false
    Explanation:
    No horizontal or vertical cut results in two non-empty sections with equal
    sums. Thus, the answer is false.


    *** Constraints ***
    1 <= m == grid.length <= 10^5
    1 <= n == grid[i].length <= 10^5
    2 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 10.11% */
/* Space Beats:  6.94% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<long long>> magic(ROWS, vector<long long>(COLS, 0));

        if (ROWS == 1)
        {
            long long to_the_right = 0;
            for (int col = COLS-1; col >= 0; col--)
            {
                magic[0][col]  = grid[0][col] + to_the_right;
                to_the_right  += grid[0][col];
            }
        }
        else if (COLS == 1)
        {
            long long under = 0;
            for (int row = ROWS-1; row >= 0; row--)
            {
                magic[row][0]  = grid[row][0] + under;
                under         += grid[row][0];
            }
        }
        else
        {
            for (int row = ROWS-1; row >= 0; row--)
            {
                long long to_the_right = 0;
                for (int col = COLS-1; col >= 0; col--)
                {
                    if (row + 1 < ROWS)
                        magic[row][col] += magic[row+1][col];

                    magic[row][col] += grid[row][col] + to_the_right;
                    to_the_right    += grid[row][col];
                }
            }
        }


        for (int row = 1; row < ROWS; row++)
        {
            if (magic[0][0] - magic[row][0] == magic[row][0])
                return true;
        }

        for (int col = 1; col < COLS; col++)
        {
            if (magic[0][0] - magic[0][col] == magic[0][col])
                return true;
        }

        return false;
    }
};
