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

    TODO

*/

/* Time  Beats:  66.71% */
/* Space Beats:  83.40% */

/* Time  Complexity: O(81) */
/* Space Complexity: O(81) */
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        bitset<9> col[9];
        bitset<9> row[9];
        bitset<9> block[9];

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char chr = board[i][j];

                if (chr == '.')
                    continue;

                int x = (chr - '0') % 9; 

                if (row[i][x])
                    return false;
                row[i][x] = 1;

                if (col[j][x])
                    return false;
                col[j][x] = 1;
                
                int block_idx = (i / 3) * 3 + j / 3;
                if (block[block_idx][x])
                    return false;

                block[block_idx][x] = 1;
            }
        }

        return true;
    }
};