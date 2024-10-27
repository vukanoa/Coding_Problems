#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1277) Count Square Submatrices with All Ones
    ============================================

    ============
    Description:
    ============

    Given a m * n matrix of ones and zeros, return how many square submatrices
    have all ones.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix =
    [
      [0,1,1,1],
      [1,1,1,1],
      [0,1,1,1]
    ]
    Output: 15
    Explanation:
    There are 10 squares of side 1.
    There are 4 squares of side 2.
    There is  1 square of side 3.
    Total number of squares = 10 + 4 + 1 = 15.

    --- Example 2 ---
    Input: matrix =
    [
      [1,0,1],
      [1,1,0],
      [1,1,0]
    ]
    Output: 7
    Explanation:
    There are 6 squares of side 1.
    There is 1 square of side 2.
    Total number of squares = 6 + 1 = 7.


    *** Constraints ***
    1 <= arr.length <= 300
    1 <= arr[0].length <= 300
    0 <= arr[i][j] <= 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.85% */
/* Space Beats: 56.40% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(n * m) */
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix)
    {
        // Get dimensions of the matrix
        int ROWS = matrix.size();    // number of rows
        int COLS = matrix[0].size(); // number of columns

        // Create a DP table with same dimensions as matrix
        vector<vector<int>> dp(ROWS, vector<int>(COLS, 0));

        // Variable to store total count of squares
        int result = 0;

        // Initialize first column of DP table
        // Each cell in first column can only form a 1x1 square if matrix[i][0] = 1
        for (int i = 0; i < ROWS; i++)
        {
            dp[i][0] = matrix[i][0];
            result += dp[i][0];  // Add the count of squares from the first column
        }

        // Initialize first row of DP table
        // Each cell in first row can only form a 1x1 square if matrix[0][j] = 1
        for (int j = 1; j < COLS; j++)
        {
            dp[0][j] = matrix[0][j];
            result += dp[0][j];  // Add the count of squares from the first row
        }

        // Fill the DP table for remaining cells
        for(int i = 1; i < ROWS; i++)
        {
            for(int j = 1; j < COLS; j++)
            {
                // Only process if current cell in matrix is 1
                if(matrix[i][j] == 1)
                {
                    // For each cell, check the minimum value among:
                    // 1. Left cell (dp[i][j-1])
                    // 2. Top cell (dp[i-1][j])
                    // 3. Top-left diagonal cell (dp[i-1][j-1])
                    // Add 1 to this minimum value
                    dp[i][j] = 1 + min( {dp[i][j-1], dp[i-1][j], dp[i-1][j-1]} );
                }
                // Add current cell's value to total count
                result += dp[i][j];
            }
        }

        // Return total count of squares
        return result;
    }
};
