#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===============================
    1380) Lucky Numbers in a Matrix
    ===============================

    ============
    Description:
    ============

    Given an m x n matrix of distinct numbers, return all lucky numbers in the
    matrix in any order.

    A lucky number is an element of the matrix such that it is the minimum
    element in its row and maximum in its column.

    =================================================================
    FUNCTION: vector<int> luckyNumbers (vector<vector<int>>& matrix);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    |  3  |  7  |  8  |
    +-----+-----+-----+
    |  9  | 11  | 13  |
    +-----+-----+-----+
    | 15  | 16  | 17  |
    +-----+-----+-----+
    Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
    Output: [15]
    Explanation: 15 is the only lucky number since it is the minimum in its row
                 and the maximum in its column.

    --- Example 2 ---
    +-----+-----+-----+-----+
    |  1  | 10  |  4  |  2  |
    +-----+-----+-----+-----+
    |  9  |  3  |  8  |  7  |
    +-----+-----+-----+-----+
    | 15  | 16  | 17  | 12  |
    +-----+-----+-----+-----+
    Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
    Output: [12]
    Explanation: 12 is the only lucky number since it is the minimum in its row
                 and the maximum in its column.

    --- Example 3 ---
    +-----+-----+
    |  7  |  8  |
    +-----+-----+
    |  1  |  2  |
    +-----+-----+
    Input: matrix = [[7,8],[1,2]]
    Output: [7]
    Explanation: 7 is the only lucky number since it is the minimum in its row
                 and the maximum in its column.


    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= n, m <= 50
    1 <= matrix[i][j] <= 10^5.
    All elements in the matrix are distinct.

*/

using namespace std;

/* Time  Beats: 90.82% */
/* Space Beats: 12.50% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M + N) */
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        vector<int> result;

        vector<int> min_in_rows(ROWS, INT_MAX);
        vector<int> max_in_cols(COLS, INT_MIN);

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                min_in_rows[i] = min(min_in_rows[i], matrix[i][j]);
                max_in_cols[j] = max(max_in_cols[j], matrix[i][j]);
            }
        }

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (min_in_rows[i] == matrix[i][j] && max_in_cols[j] == matrix[i][j])
                    result.push_back(matrix[i][j]);
            }
        }

        return result;
    }
};
