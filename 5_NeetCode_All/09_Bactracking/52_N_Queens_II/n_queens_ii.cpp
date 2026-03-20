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

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This Solution is LESS optimal then the 2nd one in this file, however it is
    beneficial to be able to see both of them and see the optimization.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.65% */

/* Time  Complexity: O(N * N!) */
/* Space Complexity: O(N^2)    */
class Solution_1 {
public:
    int totalNQueens(int n)
    {
        int result = 0;

        bool used_col[9] = {false};
        vector<vector<bool>> board(n, vector<bool>(n, false));

        backtracking(0, used_col, board, result);

        return result;
    }

private:
    void backtracking(int row, bool (& used_col)[9], vector<vector<bool>>& board, int& result)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (row < 0)
            return;

        if (row == ROWS)
        {
            result++;
            return;
        }

        for (int col = 0; col < COLS; col++)
        {
            if (used_col[col] || attacked(row, col, board))
                continue;

            used_col[col] = true;
            board[row][col] = true;

            backtracking(row+1, used_col, board, result);

            board[row][col] = false;
            used_col[col] = false;
        }
    }

    bool attacked(int row, int col, vector<vector<bool>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        int i = row-1;
        int j = col-1;
        while (i >= 0 && j >= 0)
        {
            if (board[i][j])
                return true;

            i--;
            j--;
        }

        i = row-1;
        j = col+1;
        while (i >= 0 && j < COLS)
        {
            if (board[i][j])
                return true;

            i--;
            j++;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.47% */
class Solution_2 {
public:
    int totalNQueens(int n)
    {
        vector<bool> used_col(n);
        vector<bool> diag(2*n-1);
        vector<bool> anti_diag(2*n-1);

        return backtracking(0, used_col, diag, anti_diag);
    }

    int backtracking(int row, vector<bool>& used_col, vector<bool>& used_diag, vector<bool>& used_anti_diag)
    {
        const int N = size(used_col);
        if (row == N)
            return 1;

        int count = 0;
        for (int col = 0; col < N; col++)
        {
            if (used_col[col] || used_diag[row + col] || used_anti_diag[row - col + N - 1])
                continue;

            used_col[col]                     = true;
            used_diag[row + col]              = true;
            used_anti_diag[row - col + N - 1] = true;

            count += backtracking(row + 1, used_col, used_diag, used_anti_diag);

            used_col[col]                     = false;
            used_diag[row + col]              = false;
            used_anti_diag[row - col + N - 1] = false;
        }

        return count;
    }
};
