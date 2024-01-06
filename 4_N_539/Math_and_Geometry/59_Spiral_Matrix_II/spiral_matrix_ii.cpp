#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    59) Spiral Matrix II
    ===========================

    ============
    Description:
    ============

    Given a positive integer n, generate an n x n matrix filled with elements
    from 1 to n2 in spiral order.

    ====================================================
    FUNCTION: vector<vector<int>> generateMatrix(int n);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    |  1  |  2  |  3  |
    +-----+-----+-----+
    |  8  |  9  |  4  |
    +-----+-----+-----+
    |  7  |  6  |  5  |
    +-----+-----+-----+

    Input: n = 3
    Output: [[1,2,3],[8,9,4],[7,6,5]]



    --- Example 2 ---
    Input: n = 1
    Output: [[1]]



    *** Constraints ***
    1 <= n <= 20

*/

/*
    ------------
    --- IDEA ---
    ------------

    Just code it up. There is no any trick or technique you can use. We must
    generate it, therefore there's no other way around it.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 21.40%  */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

        int row_top    = 0;
        int row_bottom = matrix.size() - 1;
        int col_left   = 0;
        int col_right  = matrix.size() - 1;

        int num = 1;
        while (true)
        {
            // From Left to Right
            for (int i = col_left; i <= col_right; i++)
                matrix[row_top][i] = num++;
            row_top++;

            if (row_top > row_bottom || col_left > col_right)
                break;

            // From Top to Bottom
            for (int i = row_top; i <= row_bottom; i++)
                matrix[i][col_right] = num++;
            col_right--;

            if (row_top > row_bottom || col_left > col_right)
                break;

            // From Right to Left
            for (int i = col_right; i >= col_left; i--)
                matrix[row_bottom][i] = num++;
            row_bottom--;

            if (row_top > row_bottom || col_left > col_right)
                break;

            // From Bottom to Top
            for (int i = row_bottom; i >= row_top; i--)
                matrix[i][col_left] = num++;
            col_left++;

            if (row_top > row_bottom || col_left > col_right)
                break;
        }

        return matrix;
    }
};
