/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    434) Diagonal Traverse
    ===========================

    ============
    Description:
    ============

    Given an m x n matrix mat, return an array of all the elements of the array
    in a diagonal order.

    ==================================================================
    FUNCTION: vector<int> findDiagonalOrder(vector<vector<int>>& mat);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
    Output: [1,2,4,7,5,3,6,8,9]

    --- Example 2 ---
    Input: mat = [[1,2],[3,4]]
    Output: [1,2,3,4]

    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 10^4
    1 <= m * n <= 10^4
    -10^5 <= mat[i][j] <= 10^5

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pointless to do.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.06% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix)
    {
        // Check for empty matrices
        if (matrix.empty() || matrix[0].empty())
            return {};

        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        vector<int> result(ROWS * COLS);

        int k = 0;
        vector<int> intermediate;

        for (int diagonal = 0; diagonal < ROWS + COLS - 1; diagonal++)
        {
            intermediate.clear();

            int row = (diagonal < COLS) ?     0    : diagonal - COLS + 1;
            int col = (diagonal < COLS) ? diagonal : COLS - 1;

            while (row < ROWS && col >= 0)
            {
                intermediate.push_back(matrix[row][col]);
                row++;
                col--;
            }

            // Reverse even numbered diagonals
            if (diagonal % 2 == 0)
                reverse(intermediate.begin(), intermediate.end());

            for (int val : intermediate)
                result[k++] = val;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Also pointless to do.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.64% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Using_Directions {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return {};

        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        int row = 0;
        int col = 0;

        int direction = 1;

        vector<int> result(ROWS * COLS);
        int idx = 0;

        while (row < ROWS && col < COLS)
        {
            result[idx++] = matrix[row][col];

            int new_row = row + (direction == 1 ? -1 :  1);
            int new_col = col + (direction == 1 ?  1 : -1);

            if (new_row < 0 || new_row == ROWS || new_col < 0 || new_col == COLS)
            {
                if (direction == 1)
                {
                    if (col == COLS - 1)
                        row++;
                    else
                        col++;
                }
                else
                {
                    if (row == ROWS - 1)
                        col++;
                    else
                        row++;
                }

                direction = 1 - direction;
            }
            else
            {
                row = new_row;
                col = new_col;
            }
        }

        return result;
    }
};
