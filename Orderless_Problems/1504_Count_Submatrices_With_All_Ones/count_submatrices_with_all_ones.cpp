/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1504) Count Sumatrices With All Ones
    ====================================

    ============
    Description:
    ============

    Given an m x n binary matrix mat, return the number of submatrices that
    have all ones.

    ==================================================
    FUNCTION: int numSubmat(vector<vector<int>>& mat);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
    Output: 13
    Explanation: 
    There are 6 rectangles of side 1x1.
    There are 2 rectangles of side 1x2.
    There are 3 rectangles of side 2x1.
    There is 1 rectangle of side 2x2. 
    There is 1 rectangle of side 3x1.
    Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.

    --- Example 2 ---
    Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
    Output: 24
    Explanation: 
    There are 8 rectangles of side 1x1.
    There are 5 rectangles of side 1x2.
    There are 2 rectangles of side 1x3. 
    There are 4 rectangles of side 2x1.
    There are 2 rectangles of side 2x2. 
    There are 2 rectangles of side 3x1. 
    There is 1 rectangle of side 3x2. 
    Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.


    *** Constraints ***
    1 <= m, n <= 150
    mat[i][j] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.17% */
/* Space Beats: 26.21% */

/* Time  Complexity: O(ROWS^2 * COLS) */
/* Space Complexity: O(ROWS   * COLS) */
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        int result = 0;
        vector<vector<int>> dp(ROWS, vector<int>(COLS, 0));

        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                if (col == 0)
                    dp[row][col] = mat[row][col];
                else
                    dp[row][col] = (mat[row][col] == 0) ? 0 : dp[row][col - 1] + 1;

                int curr = dp[row][col];
                for (int k = row; k >= 0; k--)
                {
                    curr = min(curr, dp[k][col]);

                    if (curr == 0)
                        break;

                    result += curr;
                }
            }
        }

        return result;
    }
};
