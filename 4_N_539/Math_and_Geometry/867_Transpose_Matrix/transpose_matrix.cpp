#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    867) Transpose Matrix
    ===========================

    ============
    Description:
    ============

    Given a 2D integer array matrix, return the transpose of matrix.

    The transpose of a matrix is the matrix flipped over its main diagonal,
    switching the matrix's row and column indices.

    =====================================================================
    FUNCTION: vector<vector<int>> transpose(vector<vector<int>>& matrix); 
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [[1,4,7],[2,5,8],[3,6,9]]

    --- Example 2 ---
    Input: matrix = [[1,2,3],[4,5,6]]
    Output: [[1,4],[2,5],[3,6]]


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 1000
    1 <= m * n <= 105
    -10^9 <= matrix[i][j] <= 10^9

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.96% */
/* Space Beats: 54.41% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        vector<vector<int>> result(COLS, vector<int>(ROWS, 0));

        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                result[col][row] = matrix[row][col];
            }
        }

        return result;
    }
};
