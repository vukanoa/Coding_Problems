#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    36) Valid Sudoku
    ===========================

    ============
    Description:
    ============

    Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to
    be validated according to the following rules:

    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9
    without repetition.


    =====
    Node: A Sudoku board (partially filled) could be valid but is not
          necessarily solvable. Only the filled cells need to be validated
          according to the mentioned rules.
    =====

    ==========================================================
    FUNCTION: bool isValidSudoku(vector<vector<char>>& board);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: board =
    [["5","3",".",".","7",".",".",".","."]
    ,["6",".",".","1","9","5",".",".","."]
    ,[".","9","8",".",".",".",".","6","."]
    ,["8",".",".",".","6",".",".",".","3"]
    ,["4",".",".","8",".","3",".",".","1"]
    ,["7",".",".",".","2",".",".",".","6"]
    ,[".","6",".",".",".",".","2","8","."]
    ,[".",".",".","4","1","9",".",".","5"]
    ,[".",".",".",".","8",".",".","7","9"]]
    Output: true

    --- Example 2 ---


    Input: board =
    [["8","3",".",".","7",".",".",".","."]
    ,["6",".",".","1","9","5",".",".","."]
    ,[".","9","8",".",".",".",".","6","."]
    ,["8",".",".",".","6",".",".",".","3"]
    ,["4",".",".","8",".","3",".",".","1"]
    ,["7",".",".",".","2",".",".",".","6"]
    ,[".","6",".",".",".",".","2","8","."]
    ,[".",".",".","4","1","9",".",".","5"]
    ,[".",".",".",".","8",".",".","7","9"]]
    Output: false
    Explanation: Same as Example 1, except with the 5 in the top left corner
    being modified to 8. Since there are two 8's in the top left 3x3 sub-box,
    it is invalid.


    *** Constraints ***
    board.length == 9
    board[i].length == 9
    board[i][j] is a digit 1-9 or '.'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Make 5 sets(I use vectors since it's faster):
        1. "row", for current row.
        2. "left",  for the left  box in one of 3 box rows.
        3. "mid",   for the mid   box in one of 3 box rows.
        4. "right", for the right box in one of 3 box rows.

        5. "col", for current column.

    Why have I "separated" visually this list?
    I did that since you **cannot** check row and column at the same time. You
    must iterate twice. Once row by row and once column by column.

    I check the Boxes validity in "row by row" iteration.

    That's the whole idea.
*/


/* Time  Beats: 93.98% */
/* Space Beats: 62.99% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        int m = board.size();
        int n = board[0].size();
        const int ZERO_ASCII = 0;

        std::vector<bool> row(10, false); // 10 For easier access

        std::vector<bool> left (10, false);
        std::vector<bool> mid  (10, false);
        std::vector<bool> right(10, false);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j == 0)
                    row.assign(10, false);

                if (j == 0 && (i == 3 || i == 6))
                {
                    left.assign (10, false);
                    mid.assign  (10, false);
                    right.assign(10, false);
                }

                if (board[i][j] == '.')
                    continue;

                int num = board[i][j] - ZERO_ASCII;

                // Check row
                if (row[num])
                    return false;
                else
                    row[num] = true;

                // Check Boxes
                if (j < 3) // Left Box
                {
                    if (left[num])
                        return false;
                    else
                        left[num] = true;
                }
                else if (j >= 3 && j < 6) // Mid Box
                {
                    if (mid[num])
                        return false;
                    else
                        mid[num] = true;
                }
                else if (j >= 6) // Right Box
                {
                    if (right[num])
                        return false;
                    else
                        right[num] = true;
                }
            }
        }


        std::vector<bool> col(10, false);

        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < m; i++)
            {
                if (i == 0)
                    col.assign(10, false);

                if (board[i][j] == '.')
                    continue;

                int num = board[i][j] - ZERO_ASCII;

                if (col[num])
                    return false;
                else
                    col[num] = true;
            }
        }

        return true;
    }
};
