/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    48) Rotate Image
    ===========================

    ============
    Description:
    ============

    You are given an "n x n" 2D matrix representing an image, rotate the image
    by 90 degrees(clockwise).

    You have to rotate the image in-place, which means you have to modify the
    input 2D matrix directly. DO NOT allocate another 2D matrix and so the
    rotation.

    =============================================================
    FUNCTION: void rotate(vector<vector<int>>& matrix);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    Output: [[7, 4, 1], [8, 5, 2], [9, 6, 3]]

    --- Example 2 ---
    Input:  matrix = [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]
    Output: [[15, 13, 2, 5], [14, 3, 4, 1], [12, 6, 8, 9], [16, 7, 10, 11]]

    *** Constraints ***
    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000
*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The main thing is that we rotate in "cycles".
    In 1st Example:
    1 2 3
    4 5 6
    7 8 9

    First we process(swap) (0, 0) element and its all 3 remaining ones:
        1 -> 3 -> 9 -> 7 -> 1
    (We use matrix[x][y], matrix[0][0] in this case, as a "tmp" variable)

    Then we process (0, 1), then (0, 2)(In a bigger matrix) and so on.

    Important thing is that whenever we are done with a current row(i), we MUST
    start with incremented "i", that is [i, i]. So:
        (0, 0) for row 0, then
        (1, 1) for row 1, then
        (2, 2) for row 2, then
        ...
        (n/2 - 1, n/2 - 1)

    But since we're rotating, our "i" won't go all the way up until "n - 1".
    We will only begin the "cycle"(of swapping 4 elements) up until "i < n/2"

    Consider this:
    1  2  3  4  5
    6  7  8  9  10
    11 12 13 14 15
    16 17 18 19 20
    21 22 23 24 25

    We're ONLY doing the "cycles" on elements:
        Row 0:
            1 (0, 0)
            2 (0, 1)
            3 (0, 2)
            4 (0, 3)
            5 (0, 4)

        Row 1:
            7 (1, 1)
            8 (1, 2)

        Row 2:
            13 (2, 2) // This will "cycle" with itself

    All of the other elements will be processed as a part of the "cycle" of one
    of these elements.

    *** GENERAL RULE FOR SWAPPING ***
    [x][y] -> [y][n - 1 - x] -> [n - 1 - x][n - 1 - y] -> [n - 1 - y][x] -> [x][y]

*/

/*
    ------------
    --- IDEA ---
    ------------

    Keep pointers: Left, Right, Top, Bottom

    After that it becomes easy, just do simulate example and you'll get it.
*/

/* Time  Beats: 100% */
/* Space Beats: 21.11% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_L_R_T_B {
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size();

        int left  = 0;
        int right = n-1;

        while (left < right)
        {
            int top    = left;
            int bottom = right;

            int tmp;
            for (int i = 0; i < right-left; i++)
            {
                tmp = matrix[top][left + i];

                swap(tmp, matrix[top + i   ][right    ]);
                swap(tmp, matrix[bottom    ][right - i]);
                swap(tmp, matrix[bottom - i][left     ]);
                swap(tmp, matrix[top       ][left + i ]);
            }

            left++;
            right--;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Transpose Matrix and then Reverse Columns.

    Check Linear Algebra.

*/

/* Time  Beats:  100% */
/* Space Beats: 58.65% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_Transpose_Reverse {
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int rows = matrix.size();

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < row; col++)
                swap(matrix[row][col], matrix[col][row]);
        }

        for (int row = 0; row < rows; row++)
            reverse(matrix[row].begin(), matrix[row].end());
    }
};
