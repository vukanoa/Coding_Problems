/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    74) Search a 2D Matrix
    ===========================

    ============
    Description:
    ============

    Write an efficient algorithm that searches for a value "target" in an
    "m x n" integer matrix "matrix". This matrix has the following properties.

    - Integers in each row are sorted from left to right.

    - The first integer of each row is greater than the last integer of the
      previous row.

    =====================================================================
    FUNCTION: bool searchMatrix(vector<vector<int>>& matrix, int target);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  matrix = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], target = 3
    Output: true

    --- Example 2 ---
    Input:  matrix = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], target = 13
    Output: false

    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -10^4 <= matrix[i][j], target <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since integers are sorted from left to right and since the first integer of
    each row is greater than the last integer of the previous row, we don't
    have to search through an entire matrix.

    We iterater through each row and we're checking if our target is within the
    range of current row.

    How do we do that?

    Well, since it is sorted from left to right, just check if target is
    greater than or equal to matrix[row][0] and if target is less than or equal
    to matrix[row][COLS - 1].

    If we find a row that fulfills these statements then iterate through that
    entire row.
    If you find it, return true, if not return false.

    Also, at the very beginning we can check if the target is less than our
    matrix[0][0] element or if it is greater than our matrix[ROWS-1][COLS-1]
    element.

    In either case, return false since the target is certainly not inside of
    matrix.

*/

/* Time  Beats:   100% */ // I have no idea how is this one faster
/* Space Beats: 96.94% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution_Brute_Force {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        if (target < matrix[0][0] || target > matrix[ROWS - 1][COLS - 1])
            return false;

        for (int row = 0; row < ROWS; row++)
        {
            if (matrix[row][0] <= target && target <= matrix[row][COLS - 1])
            {
                for (int col = 0; col < COLS; col++)
                {
                    if (matrix[row][col] == target)
                        return true;
                }

                return false;
            }
        }

        return false;
    }
};
