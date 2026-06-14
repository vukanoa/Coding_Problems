/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    54) Spiral Matrix
    ===========================

    ============
    Description:
    ============

    Given an m x n matrix, return all elements of the matrix in spiral order.

    ===============================================================
    FUNCTION: vector<int> spiralOrder(vector<vector<int>>& matrix);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    Output: [1, 2, 3, 6, 9, 8, 7, 4, 5]

    --- Example 2 ---
    Input:  matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]
    Output: [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]

    *** Constraints ***
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Idea is self-explanatory

    It's important to be aware that it is HARD to get the implementation right.

*/

/* Time  Beats:   100% */
/* Space Beats: 28.09% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        vector<int> result;
        result.reserve(ROWS * COLS); // To prevent reallocations

        int left_col  = 0;
        int right_col = COLS;

        int top_row = 0;
        int bot_row = ROWS;

        while (left_col < right_col && top_row < bot_row)
        {
            // Top   row:    Left to Right
            for (int j = left_col; j < right_col; j++)
                result.push_back(matrix[top_row][j]);
            top_row++;

            // Right col:    Top to Bottom
            for (int i = top_row; i < bot_row; i++)
                result.push_back(matrix[i][right_col-1]);
            right_col--;

            /* Consider one-row matrix or one-column matrix */
            // if (left >= right || top >= bottom)
            if ( ! (left_col < right_col && top_row < bot_row))
                break;

            // Bottom row:    Right to Left
            for (int j = right_col-1; j >= left_col; j--)
                result.push_back(matrix[bot_row-1][j]);
            bot_row--;

            // Left   col:    Bottom to Top
            for (int i = bot_row-1; i >= top_row; i--)
                result.push_back(matrix[i][left_col]);
            left_col++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Elegant way of solving it. If you haven't seen this before, it's almost
    impossible to devise this on the spot.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  14.27% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution_Elegant {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        vector<int> result;
        result.reserve(ROWS * COLS); // To prevent reallocations

        /* Clockwise */
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<int> steps = {COLS, ROWS - 1};

        int row = 0;
        int col = -1;

        int dir = 0;
        while (steps[dir % 2])
        {
            for (int i = 0; i < steps[dir % 2]; i++)
            {
                row += directions[dir].first;
                col += directions[dir].second;

                result.push_back(matrix[row][col]);
            }

            steps[dir % 2]--;
            dir = (dir + 1) % 4;
        }

        return result;
    }
};
