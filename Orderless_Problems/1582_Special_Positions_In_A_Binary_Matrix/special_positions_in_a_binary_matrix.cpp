/*
    ============
    === EASY ===
    ============

    ==========================================
    1582) Special Positions in a Binary Matrix
    ==========================================

    ============
    Description:
    ============

    Given an m x n binary matrix mat, return the number of special positions in
    mat.

    A position (i, j) is called special if mat[i][j] == 1 and all other
    elements in row i and column j are 0 (rows and columns are 0-indexed).

    ===================================================
    FUNCTION: int numSpecial(vector<vector<int>>& mat);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
    Output: 1
    Explanation: (1, 2) is a special position because mat[1][2] == 1 and all
                 other elements in row 1 and column 2 are 0.

    --- Example 2 ---
    Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
    Output: 3
    Explanation: (0, 0), (1, 1) and (2, 2) are special positions.


    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 100
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

/* Time  Beats: 100.00% */
/* Space Beats:  41.51% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();
        int result = 0;

        vector<int> value_row(ROWS, 0);
        vector<int> value_col(COLS, 0);

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mat[row][col] == 1)
                {
                    value_row[row]++;
                    value_col[col]++;
                }
            }
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mat[row][col] == 1 && value_row[row] == 1 && value_col[col] == 1)
                    result++;
            }
        }

        return result;
    }
};
