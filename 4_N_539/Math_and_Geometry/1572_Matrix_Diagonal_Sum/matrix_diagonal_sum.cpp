#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    1572) Matrix Diagonal Sum
    ===========================

    ============
    Description:
    ============

    Given a square matrix mat, return the sum of the matrix diagonals.

    Only include the sum of all the elements on the primary diagonal and all
    the elements on the secondary diagonal that are not part of the primary
    diagonal.

    ====================================================
    FUNCTION: int diagonalSum(vector<vector<int>>& mat);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,2,3],
                  [4,5,6],
                  [7,8,9]]
    Output: 25
    Explanation: Diagonals sum: 1 + 5 + 9 + 3 + 7 = 25
    Notice that element mat[1][1] = 5 is counted only once.


    --- Example 2 ---
    Input: mat = [[1,1,1,1],
                  [1,1,1,1],
                  [1,1,1,1],
                  [1,1,1,1]]
    Output: 8


    --- Example 3 ---
    Input: mat = [[5]]
    Output: 5


    *** Constraints ***
    n == mat.length == mat[i].length
    1 <= n <= 100
    1 <= mat[i][j] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 37.88% */
/* Space Beats: 58.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int diagonalSum(std::vector<std::vector<int>>& mat)
    {
        int n = mat.size();
        unsigned long long sum = 0;

        // Primary Diagonal
        for (int i = 0; i < n; i++)
            sum += mat[i][i];

        // Secondary Diagonal
        for (int i = n-1; i >= 0; i--)
        {
            int row = n-1 - i;
            int col = i;

            if (row == col)
                continue;

            sum += mat[row][col];
        }

        return sum;
    }
};




/* Time  Beats: 37.88% */
/* Space Beats: 58.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Short {
public:
    int diagonalSum(std::vector<std::vector<int>>& mat)
    {
        int n = mat.size();
        int result = 0;

        for(int i = 0; i < n; i++)
            result += mat[i][i] + mat[i][n-i-1];

        return (n % 2 == 1) ? result - mat[n/2][n/2] : result;
    }
};
