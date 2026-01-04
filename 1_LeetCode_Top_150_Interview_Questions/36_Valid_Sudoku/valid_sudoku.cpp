/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    37) Valid Sudoku
    ===========================

    ============
    Description:
    ============

    Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
    validated according to the following rules:

        1. Each row must contain the digits 1-9 without repetition.

        2. Each column must contain the digits 1-9 without repetition.

        3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits
           1-9 without repetition.

    Note:
        A Sudoku board (partially filled) could be valid but is not necessarily
        solvable. Only the filled cells need to be validated according to the
        mentioned rules.


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

#include <vector>
#include <bitset>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most simple idea.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.70% */

/* Time  Complexity: O(1) */ // Because Sudoku is ALWAYS 9x9
/* Space Complexity: O(1) */ // Because Sudoku is ALWAYS 9x9
class Solution_Basic {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        const int ROWS = 9;
        const int COLS = 9;

        bool row[9][10]    = {false};
        bool col[9][10]    = {false};
        bool box[3][3][10] = {false};

        for (int curr_row = 0; curr_row < ROWS; curr_row++)
        {
            for (int curr_col = 0; curr_col < COLS; curr_col++)
            {
                if (board[curr_row][curr_col] == '.')
                    continue;

                // Convert from ASCII
                int digit = board[curr_row][curr_col] - '0';

                /* Check Row */
                if (row[curr_row][digit] == true)
                    return false;
                row[curr_row][digit] = true;

                /* Check Column */
                if (col[curr_col][digit] == true)
                    return false;
                col[curr_col][digit] = true;

                /* Check Box */
                if (box[curr_row / 3][curr_col / 3][digit] == true)
                    return false;
                box[curr_row / 3][curr_col / 3][digit] = true;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    By using bitset, we can reduce needed Space even further. However, since
    Sudoku is always 9x9, this is neglibile. But it's worth seeing it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.40% */

/* Time  Complexity: O(1) */ // Because Sudoku is ALWAYS 9x9
/* Space Complexity: O(1) */ // Because Sudoku is ALWAYS 9x9
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        bitset<9> col[9];
        bitset<9> row[9];
        bitset<9> block[9];

        for (int curr_row = 0; curr_row < 9; curr_row++)
        {
            for (int curr_col = 0; curr_col < 9; curr_col++)
            {
                char chr = board[curr_row][curr_col];

                if (chr == '.')
                    continue;

                int digit = chr - '0';

                /* Check Row */
                if (row[curr_row][digit] == true)
                    return false;
                row[curr_row][digit] = 1;

                /* Check Column */
                if (col[curr_col][digit] == true)
                    return false;
                col[curr_col][digit] = 1;

                /* Check Box */
                int block_idx = (curr_row / 3) * 3 + curr_col / 3;
                if (block[block_idx][digit] == true)
                    return false;

                block[block_idx][digit] = 1;
            }
        }

        return true;
    }
};
