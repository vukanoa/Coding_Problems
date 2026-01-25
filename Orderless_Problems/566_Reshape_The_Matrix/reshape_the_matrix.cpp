/*
    ============
    === EASY ===
    ============

    ===========================
    566) Reshape the Matrix
    ===========================

    ============
    Description:
    ============

    In MATLAB, there is a handy function called reshape which can reshape an m
    x n matrix into a new one with a different size r x c keeping its original
    data.

    You are given an m x n matrix mat and two integers r and c representing the
    number of rows and the number of columns of the wanted reshaped matrix.

    The reshaped matrix should be filled with all the elements of the original
    matrix in the same row-traversing order as they were.

    If the reshape operation with given parameters is possible and legal,
    output the new reshaped matrix; Otherwise, output the original matrix.

    ====================================================================================
    FUNCTION: vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,2],[3,4]], r = 1, c = 4
    Output: [[1,2,3,4]]

    --- Example 2 ---
    Input: mat = [[1,2],[3,4]], r = 2, c = 4
    Output: [[1,2],[3,4]]


    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 100
    -1000 <= mat[i][j] <= 1000
    1 <= r, c <= 300

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Flat Mapping:

        mat[i / COLS][i % COLS]

*/

/* Time  Beats: 100.00% */
/* Space Beats:  56.60% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */ // Even though "result" is not EXTRA
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        if (ROWS * COLS != r * c)
            return mat;

        vector<vector<int>> result(r, vector<int>(c));

        for (int i = 0; i < ROWS * COLS; i++)
            result[i / c][i % c] = mat[i / COLS][i % COLS];

        return result;
    }
};
