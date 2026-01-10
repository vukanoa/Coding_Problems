/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    304) Range Sum Query 2D - Immutable
    ===================================

    ============
    Description:
    ============

    Given a 2D matrix matrix, handle multiple queries of the following type:

        Calculate the sum of the elements of matrix inside the rectangle
        defined by its upper left corner (row1, col1) and lower right corner
        (row2, col2).

    Implement the NumMatrix class:

        NumMatrix(int[][] matrix) Initializes the object with the integer
        matrix matrix.  int sumRegion(int row1, int col1, int row2, int col2)
        Returns the sum of the elements of matrix inside the rectangle defined
        by its upper left corner (row1, col1) and lower right corner (row2,
        col2).

    You must design an algorithm where sumRegion works on O(1) time complexity.

    ===============================
    CLASS:
    class NumMatrix{
    public:
        NumMatrix(vector<vector<int>& matrix)
        {

        }

        int sumRegion(int row1, int col1, int row2, int col2)
        {

        }

    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
    [[[[3, 0, 1, 4, 2],
       [5, 6, 3, 2, 1],
       [1, 2, 0, 1, 5],
       [4, 1, 0, 1, 7],
       [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
    Output
    [null, 8, 11, 12]

    Explanation
    NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2],
                                         [5, 6, 3, 2, 1],
                                         [1, 2, 0, 1, 5],
                                         [4, 1, 0, 1, 7],
                                         [1, 0, 3, 0, 5]]);

    numMatrix.sumRegion(2, 1, 4, 3); // return 8  (sum of the red   rectangle)
    numMatrix.sumRegion(1, 1, 2, 2); // return 11 (sum of the green rectangle)
    numMatrix.sumRegion(1, 2, 2, 4); // return 12 (sum of the blue  rectangle)



    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    -10^4 <= matrix[i][j] <= 10^4
    0 <= row1 <= row2 < m
    0 <= col1 <= col2 < n
    At most 10^4 calls will be made to sumRegion.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.30% */
/* Space Beats: 87.58% */

/* Time  Complexity: O(ROWS * COLS) and O(1) */
/* Space Complexity: O(ROWS * COLS)          */
class NumMatrix {
public:
    // O(ROWS * COLS)
    NumMatrix(vector<vector<int>>& matrix)
        : my_matrix(matrix.begin(), matrix.end())
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                my_matrix[row][col] += (row+1 == ROWS                  ? 0 : my_matrix[row+1][col  ]) +
                                       (                 col+1 == COLS ? 0 : my_matrix[row  ][col+1]) -
                                       (row+1 == ROWS || col+1 == COLS ? 0 : my_matrix[row+1][col+1]);
            }
        }
    }

    // O(1)
    int sumRegion(int row1, int col1, int row2, int col2)
    {
        const int ROWS = my_matrix.size();
        const int COLS = my_matrix[0].size();

        return my_matrix[row1][col1] - (row2+1 == ROWS                   ? 0 : my_matrix[row2+1][col1  ])
                                     - (                  col2+1 == COLS ? 0 : my_matrix[row1  ][col2+1])
                                     + (row2+1 == ROWS || col2+1 == COLS ? 0 : my_matrix[row2+1][col2+1]);
    }

private:
    vector<vector<int>> my_matrix;
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.17% */
/* Space Beats: 87.58% */

/* Time  Complexity: O(ROWS * COLS) and O(1) */
/* Space Complexity: O(ROWS * COLS)          */
class NumMatrix_2 {
public:
    NumMatrix_2(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        sum_matrix.assign(ROWS+1, vector<int>(COLS+1, 0));

        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                sum_matrix[row][col] =       matrix[row  ][col  ]
                                       + sum_matrix[row+1][col  ]  // Down
                                       + sum_matrix[row  ][col+1]  // Right
                                       - sum_matrix[row+1][col+1]; // Diagonal
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return   sum_matrix[row1  ][col1  ]  // Add      Rectangle from  Left-Upper Corner
               - sum_matrix[row2+1][col1  ]  // Subtract Rectangle after col2
               - sum_matrix[row1  ][col2+1]  // Subtract Rectangle below row2
               + sum_matrix[row2+1][col2+1]; // Re-Add   Rectangle from  Diagonal of Lower-Right Corner
    }

private:
    vector<vector<int>> sum_matrix;
};
