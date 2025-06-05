/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    3070) Count Submatrices with Top-Left Element and Sum Less Than K
    =================================================================

    ============
    Description:
    ============

    You are given a 0-indexed integer matrix grid and an integer k.

    Return the number of
    that contain the top-left element of the grid, and have a sum less than or
    equal to k.

    =================================================================
    FUNCTION: int countSubmatrices(vector<vector<int>>& grid, int k);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[7,6,3],[6,6,1]], k = 18
    Output: 4
    Explanation: There are only 4 submatrices, shown in the image above, that
                 contain the top-left element of grid, and have a sum less than
                 or equal to 18.

    --- Example 2 ---
    Input: grid = [[7,2,9],[1,5,0],[2,6,6]], k = 20
    Output: 6
    Explanation: There are only 6 submatrices, shown in the image above, that
                 contain the top-left element of grid, and have a sum less than
                 or equal to 20.


    *** Constraints ***
    m == grid.length 
    n == grid[i].length
    1 <= n, m <= 1000 
    0 <= grid[i][j] <= 1000
    1 <= k <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Using the well-known "Magic Box" for calculating the sum of submatrices.

    It's matrix-equivalent of "prefix_sum technique".

    Usually it's called: 2D Prefix Sum (also called Summed-Area Table)

*/

/* Time  Beats: 20.39% */
/* Space Beats:  8.74% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        vector<vector<int>> magic_box(ROWS+1, vector<int>(COLS+1, 0));

        // Fill cumulative_sum
        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                magic_box[row][col] = magic_box[row+1][col] + magic_box[row][col+1] - magic_box[row+1][col+1];
                magic_box[row][col] += grid[row][col];
            }
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                long long sum = magic_box[0][0] - magic_box[0][col+1] - magic_box[row+1][0] + magic_box[row+1][col+1];

                if (sum <= k)
                    result++;
            }
        }

        return result;
    }
};
