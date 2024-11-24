#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1975) Maximum Matrix Sum
    ===========================

    ============
    Description:
    ============

    You are given an n x n integer matrix. You can do the following operation
    any number of times:

        + Choose any two adjacent elements of matrix and multiply each of them
          by -1.

    Two elements are considered adjacent if and only if they share a border.

    Your goal is to maximize the summation of the matrix's elements. Return the
    maximum sum of the matrix's elements using the operation mentioned above.

    ==============================================================
    FUNCTION: long long maxMatrixSum(vector<vector<int>>& matrix);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[1,-1],[-1,1]]
    Output: 4
    Explanation: We can follow the following steps to reach sum equals 4:
    - Multiply the 2 elements in the first row by -1.
    - Multiply the 2 elements in the first column by -1.

    --- Example 2 ---
    Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
    Output: 16
    Explanation: We can follow the following step to reach sum equals 16:
    - Multiply the 2 last elements in the second row by -1.


    *** Constraints ***
    n == matrix.length == matrix[i].length
    2 <= n <= 250
    -10^5 <= matrix[i][j] <= 10^5

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.29% */
/* Space Beats: 31.40% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        long long sum = 0;
        long long min_element = INT_MAX;

        int negative_count = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                sum += abs(matrix[row][col]);

                if (matrix[row][col] < 0)
                    negative_count++;

                min_element = min(min_element, static_cast<long long>(abs(matrix[row][col])));
            }
        }

        if (negative_count & 1) // Odd number of negative elements in matrix
            sum -= 2 * abs(min_element);

        return sum;
    }
};
