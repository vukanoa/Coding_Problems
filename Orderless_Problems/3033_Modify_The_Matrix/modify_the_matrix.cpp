/*
    ============
    === EASY ===
    ============

    ===========================
    3033) Modify the Matrix
    ===========================

    ============
    Description:
    ============

    Given a 0-indexed m x n integer matrix matrix, create a new 0-indexed
    matrix called answer. Make answer equal to matrix, then replace each
    element with the value -1 with the maximum element in its respective column

    Return the matrix answer.

    ==========================================================================
    FUNCTION: vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[1,2,-1],[4,-1,6],[7,8,9]]
    Output: [[1,2,9],[4,8,6],[7,8,9]]
    Explanation: The diagram above shows the elements that are changed (in blue).
    - We replace the value in the cell [1][1] with the maximum value in the column 1, that is 8.
    - We replace the value in the cell [0][2] with the maximum value in the column 2, that is 9.

    --- Example 2 ---
    Input: matrix = [[3,-1],[5,2]]
    Output: [[3,2],[5,2]]
    Explanation: The diagram above shows the elements that are changed (in blue).


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    2 <= m, n <= 50
    -1 <= matrix[i][j] <= 100
    The input is generated such that each column contains at least one
    non-negative integer.

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.60% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(COLS)        */
class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        vector<int> col_max(COLS, INT_MIN);
        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                col_max[col] = max(col_max[col], matrix[row][col]);
            }
        }

        vector<vector<int>> answer = matrix;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (answer[row][col] == -1)
                    answer[row][col] = col_max[col];
            }
        }

        return answer;
    }
};
