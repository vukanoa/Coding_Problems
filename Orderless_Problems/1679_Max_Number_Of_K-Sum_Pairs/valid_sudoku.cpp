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
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
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

                int digit_idx = (chr - '0') % 9; 

                if (row[i][digit_idx])
                    return false;
                row[i][digit_idx] = 1;

                if (col[j][digit_idx])
                    return false;
                col[j][digit_idx] = 1;
                
                int block_idx = (i / 3) * 3 + j / 3;
                if (block[block_idx][x])
                    return false;

                block[block_idx][x] = 1;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  16.01% */
/* Space Beats:   5.39% */

/* Time  Complexity: O(81) */
/* Space Complexity: O(81) */
class Solution_Unordered_Set {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        unordered_set<string> uset;

        int n = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char chr = board[i][j];
                if (chr != '.') {
                    n++;
                    string row = "row" + to_string(i) + chr;
                    string col = "col" + to_string(j) + chr;

                    int block_idx = (i / 3) * 3 + j / 3;
                    string block = "block" + to_string(block_idx) + chr;

                    uset.insert(row);
                    uset.insert(col);
                    uset.insert(block);
                }
            }
        }

        return uset.size() == 3*n;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.40% */

/* Time  Complexity: O(81) */
/* Space Complexity: O(81) */
class Solution_Bitmask {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        short col[9] = {0};
        short row[9] = {0};
        short block[9] = {0};

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char chr = board[i][j];
                if (chr == '.')
                    continue;

                int digit_idx  = (chr - '0') % 9;
                int digit_mask = 1 << digit_idx;
                
                int block_idx = (i/3)*3 + j/3; 

                if ((row[i] >> digit_idx) & 1 ||
                    (col[j] >> digit_idx) & 1 ||
                    (block[block_idx] >> digit_idx) & 1)
                {
                    return 0;
                }

                row[i] |= digit_mask;
                col[j] |= digit_mask;
                block[block_idx] |= digit_mask;
            }
        }

        return 1;
    }
};
