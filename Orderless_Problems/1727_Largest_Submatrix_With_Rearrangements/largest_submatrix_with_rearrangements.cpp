/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1727) Largest Submatrix With Rearrangements
    ===========================================

    ============
    Description:
    ============

    You are given a binary matrix matrix of size m x n, and you are allowed to
    rearrange the columns of the matrix in any order.

    Return the area of the largest submatrix within matrix where every element
    of the submatrix is 1 after reordering the columns optimally.

    ============================================================
    FUNCTION: int largestSubmatrix(vector<vector<int>>& matrix);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
    Output: 4
    Explanation: You can rearrange the columns as shown above.
    The largest submatrix of 1s, in bold, has an area of 4.


    --- Example 2 ---
    Input: matrix = [[1,0,1,0,1]]
    Output: 3
    Explanation: You can rearrange the columns as shown above.
    The largest submatrix of 1s, in bold, has an area of 3.


    --- Example 3 ---
    Input: matrix = [[1,1,0],[1,0,1]]
    Output: 2
    Explanation: Notice that you must rearrange entire columns, and there is no
                 way to make a submatrix of 1s larger than an area of 2.


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m * n <= 10^5
    matrix[i][j] is either 0 or 1.

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.13% */
/* Space Beats: 67.02% */

/* Time  Complexity: O(ROWS * COLS * logCOLS) */
/* Space Complexity: O(ROWS * COLS)           */
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& mat)
    {
        const int ROWS = mat.size();
        const int COLS = mat[0].size();
        int result = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mat[row][col] != 0 and row != 0)
                    mat[row][col] += mat[row-1][col];
            }

            vector<int>curr_row = mat[row];

            // Sort in DESCENDING order
            sort(curr_row.begin(), curr_row.end(), greater<int>());

            for (int col = 0; col < COLS; col++)
                result = max(result, curr_row[col] * (col+1));
        }

        return result;
    }
};
