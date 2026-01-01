#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    52) N Queens II
    ===========================

    ============
    Description:
    ============

    The n-queens puzzle is the problem of placing n queens on an n x n
    chessboard such that no two queens attack each other.

    Given an integer n, return the number of distinct solutions to the n-queens
    puzzle.

    ==================================
    FUNCTION: int totalNQueens(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+      +-----+-----+-----+-----+
    |     |  Q  |     |     |      |     |     |  Q  |     |
    +-----+-----+-----+-----+      +-----+-----+-----+-----+
    |     |     |     |  Q  |      |  Q  |     |     |     |
    +-----+-----+-----+-----+      +-----+-----+-----+-----+
    |  Q  |     |     |     |      |     |     |     |  Q  |
    +-----+-----+-----+-----+      +-----+-----+-----+-----+
    |     |     |  Q  |     |      |     |  Q  |     |     |
    +-----+-----+-----+-----+      +-----+-----+-----+-----+
    Input: n = 4
    Output: 2
    Explanation: There are two distinct solutions to the 4-queens puzzle as
                 shown.


    --- Example 2 ---
    Input: n = 1
    Output: 1



    *** Constraints ***
    1 <= n <= 9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.47% */
class Solution {
public:
    int totalNQueens(int n)
    {
        std::vector<bool> col(n);
        std::vector<bool> diag(2*n-1);
        std::vector<bool> anti_diag(2*n-1);

        return backtracking(0, col, diag, anti_diag);
    }

    int backtracking(int row,
                     std::vector<bool>& col,
                     std::vector<bool>& diag,
                     std::vector<bool>& anti_diag)
    {
        int count = 0;
        int n = size(col);

        if(row == n)
            return 1;

        for(int column = 0; column < n; column++)
        {
            if(!col[column] && !diag[row + column] && !anti_diag[row - column + n - 1])
            {
                col[column] = diag[row + column] = anti_diag[row - column + n - 1] = true;
                count += backtracking(row + 1, col, diag, anti_diag);
                col[column] = diag[row + column] = anti_diag[row - column + n - 1] = false;
            }
        }

        return count;
    }
};
