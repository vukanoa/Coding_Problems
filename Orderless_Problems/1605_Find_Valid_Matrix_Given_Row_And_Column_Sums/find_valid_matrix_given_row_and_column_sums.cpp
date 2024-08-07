#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1605) Find Valid Matrix Given Row and Column Sums
    =================================================

    ============
    Description:
    ============

    You are given two arrays rowSum and colSum of non-negative integers where
    rowSum[i] is the sum of the elements in the ith row and colSum[j] is the
    sum of the elements of the jth column of a 2D matrix. In other words, you
    do not know the elements of the matrix, but you do know the sums of each
    row and column.

    Find any matrix of non-negative integers of size rowSum.length x
    colSum.length that satisfies the rowSum and colSum requirements.

    Return a 2D array representing any matrix that fulfills the requirements.
    It's guaranteed that at least one matrix that fulfills the requirements
    exists.

    =====================================================================================
    FUNCTION vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum);
    =====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rowSum = [3,8], colSum = [4,7]
    Output: [[3,0],
             [1,7]]
    Explanation:
    0th row: 3 + 0 = 3 == rowSum[0]
    1st row: 1 + 7 = 8 == rowSum[1]
    0th column: 3 + 1 = 4 == colSum[0]
    1st column: 0 + 7 = 7 == colSum[1]
    The row and column sums match, and all matrix elements are non-negative.
    Another possible matrix is: [[1,2],
                                 [3,5]]


    --- Example 2 ---
    Input: rowSum = [5,7,10], colSum = [8,6,8]
    Output: [[0,5,0],
             [6,1,0],
             [2,0,8]]


    *** Constraints ***
    1 <= rowSum.length, colSum.length <= 500
    0 <= rowSum[i], colSum[i] <= 108
    sum(rowSum) == sum(colSum)

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 11.96% */
/* Space Beats: 16.25% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(1)     */
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum)
    {
        const int ROWS = rowSum.size();
        const int COLS = colSum.size();

        vector<vector<int>> matrix(ROWS, vector<int>(COLS, 0));

        for (long long r = 0; r < ROWS; r++)
            matrix[r][0] = rowSum[r];

        for (long long c = 0; c < COLS; c++)
        {
            long long curr_col_sum = 0;

            for (long long r = 0; r < ROWS; r++)
                curr_col_sum += matrix[r][c];

            long long r = 0;
            while (curr_col_sum > colSum[c])
            {
                long long diff = curr_col_sum - colSum[c];
                long long max_shift = min(diff, static_cast<long long>(matrix[r][c]));

                matrix[r][c]   -= max_shift;
                matrix[r][c+1] += max_shift; // Last column WON'T enter here

                curr_col_sum   -= max_shift;
                r++;
            }
        }

        return matrix;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one is more difficult to come up with)

*/

/* Time  Beats: 97.74% */
/* Space Beats: 11.51% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(1)     */
class Solution_2 {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum)
    {
        const int ROWS = rowSum.size();
        const int COLS = colSum.size();

        vector<vector<int>> matrix(ROWS, vector<int>(COLS, 0));

        int r = 0;
        int c = 0;
        while (r < ROWS && c < COLS)
        {
            matrix[r][c] = min(rowSum[r], colSum[c]);

            rowSum[r] -= matrix[r][c];
            colSum[c] -= matrix[r][c];

            if (rowSum[r] == 0)
                r++;
            else
                c++;
        }

        return matrix;
    }
};
