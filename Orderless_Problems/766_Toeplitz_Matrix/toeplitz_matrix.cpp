#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    766) Toeplitz Matrix
    ===========================

    ============
    Description:
    ============

    Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise,
    return false.

    A matrix is Toeplitz if every diagonal from top-left to bottom-right has
    the same elements.

    ---------------
    -- Follow Up --
    ---------------

    + What if the matrix is stored on disk, and the memory is limited such that
      you can only load at most one row of the matrix into the memory at once?

    + What if the matrix is so large that you can only load up a partial row
      into the memory at once?

    =============================================================
    FUNCTION: bool isToeplitzMatrix(vector<vector<int>>& matrix);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+
    |  1  |  2  |  3  |  4  |
    +-----+-----+-----+-----+
    |  5  |  1  |  2  |  3  |
    +-----+-----+-----+-----+
    |  9  |  5  |  1  |  2  |
    +-----+-----+-----+-----+
    Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
    Output: true
    Explanation:
    In the above grid, the diagonals are:
    "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
    In each diagonal all elements are the same, so the answer is True.


    --- Example 2 ---
    +-----+-----+
    |  1  |  2  |
    +-----+-----+
    |  2  |  2  |
    +-----+-----+
    Input: matrix = [[1,2],[2,2]]
    Output: false
    Explanation:
    The diagonal "[1, 2]" has different elements.


    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 20
    0 <= matrix[i][j] <= 99

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.44% */
/* Space Beats: 35.77% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1) */
class Solution_Brute_Force {
public:
    bool isToeplitzMatrix(std::vector<std::vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        //rowwise iteration
        for (int i = 0; i < COLS; i++)
        {
           // first element of each row is taken for reference
            int top_elem = matrix[0][i];
            int y = i+1;
            int x = 1;

            // Check if coordinates are within the matrix
            while (x < ROWS  &&  y < COLS)
            {
                // Compare with reference element accross the diagonal even if
                // one mismatches return false
                if (matrix[x][y] != top_elem)
                    return false;

                x++;
                y++;
            }
        }

        /* Colwise iteration */

        // Here we started with 1 as principal diagonal was already checked.
        // Starting with 0 also doesnot hamper the results.
        for (int i = 1; i < ROWS; i++)
        {
            // first element of each column is taken for reference
            int top_elem = matrix[i][0];

            int y = 1;
            int x = i+1;

           // Check if coordinates are within the matrix
            while (x < ROWS  &&  y < COLS)
            {
                // Compare with reference element accross the diagonal even if
                // one mismatches return false

                if (matrix[x][y] != top_elem)
                    return false;

                x++;
                y++;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.42% */
/* Space Beats: 72.57% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1) */
class Solution_Short {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix)
    {
      const int ROWS = matrix.size();
      const int COLS = matrix[0].size();

        for (int i = 0; i < ROWS-1; i++)
        {
            for (int j = 0; j < COLS-1; j++)
            {
                if (matrix[i+1][j+1] != matrix[i][j])
                    return false;
            }
        }

        return true;
    }
};
