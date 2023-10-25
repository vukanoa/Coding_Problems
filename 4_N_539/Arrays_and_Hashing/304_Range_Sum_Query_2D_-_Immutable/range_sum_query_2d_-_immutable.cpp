#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.87% */
/* Space Beats: 20.80% */

/* Time  Complexity: O(1) for sumRegion and O(M * N) overall */
/* Space Complexity: O(M * N) */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix)
        : sum_matrix(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0))
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            int prefix = 0;
            for (int j = 0; j < matrix[0].size(); j++)
            {
                prefix += matrix[i][j];
                int above = sum_matrix[i][j+1];

                sum_matrix[i+1][j+1] = prefix + above;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return sum_matrix[row2+1][col2+1] - sum_matrix[row2+1][col1] - sum_matrix[row1][col2+1] + sum_matrix[row1][col1];
    }

private:
    std::vector<std::vector<int>> sum_matrix;
};
