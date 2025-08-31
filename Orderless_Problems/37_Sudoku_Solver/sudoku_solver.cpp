/*
    ============
    === HARD ===
    ============

    ===========================
    37) Sudoku Solver
    ===========================

    ============
    Description:
    ============

    Write a program to solve a Sudoku puzzle by filling the empty cells.

    A sudoku solution must satisfy all of the following rules:

        1. Each of the digits 1-9 must occur exactly once in each row.
        2. Each of the digits 1-9 must occur exactly once in each column.
        3. Each of the digits 1-9 must occur exactly once in each of the 9 3x3
           sub-boxes of the grid.

    The '.' character indicates empty cells.

    ========================================================
    FUNCTION: void solveSudoku(vector<vector<char>>& board);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    [["5","3",".",".","7",".",".",".","."],
     ["6",".",".","1","9","5",".",".","."],
     [".","9","8",".",".",".",".","6","."],
     ["8",".",".",".","6",".",".",".","3"],
     ["4",".",".","8",".","3",".",".","1"],
     ["7",".",".",".","2",".",".",".","6"],
     [".","6",".",".",".",".","2","8","."],
     [".",".",".","4","1","9",".",".","5"],
     [".",".",".",".","8",".",".","7","9"]]
    Output:
    [["5","3","4","6","7","8","9","1","2"],
     ["6","7","2","1","9","5","3","4","8"],
     ["1","9","8","3","4","2","5","6","7"],
     ["8","5","9","7","6","1","4","2","3"],
     ["4","2","6","8","5","3","7","9","1"],
     ["7","1","3","9","2","4","8","5","6"],
     ["9","6","1","5","3","7","2","8","4"],
     ["2","8","7","4","1","9","6","3","5"],
     ["3","4","5","2","8","6","1","7","9"]]
    Explanation: The input board is shown above and the only valid solution is
    shown below:


    *** Constraints ***
    board.length == 9
    board[i].length == 9
    board[i][j] is a digit or '.'.
    It is guaranteed that the input board has only one solution.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.62% */
/* Space Beats: 27.06% */

/* Time  Complexity: O(N^2 * N!) */
/* Space Complexity: O(N^2)      */
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board)
    {
        vector<vector<bool>> col(9, vector<bool>(10, false));
        vector<vector<bool>> row(9, vector<bool>(10, false));
        vector<vector<bool>> mat(9, vector<bool>(10, false));
        vector<vector<char>> curr;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int x = board[i][j] - '0';

                    row[i][x] = true;
                    col[j][x] = true;
                    mat[3*(i/3) + (j/3)][x] = true;
                }
            }
        }

        backtracking(0, 0, board, curr, col, row, mat);
        board = curr;
    }

private:
    void backtracking(int i,
                      int j,
                      vector<vector<char>>& board,
                      vector<vector<char>>& curr,
                      vector<vector<bool>>& col,
                      vector<vector<bool>>& row,
                      vector<vector<bool>>& mat)
    {
        // Find the next empty cell
        while (i < 9 && board[i][j] != '.')
        {
            if (j < 8)
            {
                j++;
            }
            else
            {
                j = 0;
                i++;
            }
        }

        // If we have reached the end of the board, we have found a solution
        if (i == 9)
        {
            curr = board;
            return;
        }

        // Try different numbers from 1 to 9
        for (int k = 1; k <= 9; k++)
        {
            // If a solution has already been found, exit the loop
            if (curr.size() > 0)
                break;

            // Check if the current number k is valid for the current cell
            if ( ! col[j][k] &&  ! row[i][k] &&  ! mat[3*(i/3) + (j/3)][k])
            {
                // Mark the current number k as used
                col[j][k] = true;
                row[i][k] = true;
                mat[3*(i/3) + (j/3)][k] = true;

                // Place the current number k in the current cell
                board[i][j] = (char)('0' + k);

                // Recursively solve the Sudoku puzzle
                backtracking(i, j, board, curr, col, row, mat);

                // Undo the current number k and mark it as unused
                col[j][k] = false;
                row[i][k] = false;
                mat[3*(i/3) + (j/3)][k] = false;
                board[i][j] = '.';
            }
        }
    }
};
