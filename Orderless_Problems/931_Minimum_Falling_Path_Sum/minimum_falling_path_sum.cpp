#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    931) Minimum Falling Path Sum
    =============================

    ============
    Description:
    ============

    Given an n x n array of integers matrix, return the minimum sum of any
    falling path through matrix.

    A falling path starts at any element in the first row and chooses the
    element in the next row that is either directly below or diagonally
    left/right. Specifically, the next element from position (row, col) will be
    (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

    =============================================================
    FUNCTION: int minFallingPathSum(vector<vector<int>>& matrix);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    |  2  |  1  |  3  |
    +-----+-----+-----+
    |  6  |  5  |  4  |
    +-----+-----+-----+
    |  7  |  8  |  9  |
    +-----+-----+-----+

    Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
    Output: 13
    Explanation: There are two falling paths with a minimum sum as shown.


    --- Example 2 ---
    +-----+-----+
    | -19 |  57 |
    +-----+-----+
    | -40 |  -5 |
    +-----+-----+

    Input: matrix = [[-19,57],[-40,-5]]
    Output: -59
    Explanation: The falling path with a minimum sum is shown.


    *** Constraints ***
    n == matrix.length == matrix[i].length
    1 <= n <= 100
    -100 <= matrix[i][j] <= 100

*/

/* Time  Beats: 88.47% */
/* Space Beats: 76.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    int minFallingPathSum(vector<vector<int>>& matrix)
    {
        int n = matrix.size();

        for (auto i = 1; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
                matrix[i][j] += std::min(
                                         { // Initializer list
                                          matrix[i-1][j],
                                          matrix[i-1][max(0, j-1)],
                                          matrix[i-1][min(n-1, j+1)]
                                         }
                                        );
        }

        return *min_element(begin(matrix[n - 1]), end(matrix[n - 1]));
    }
};
