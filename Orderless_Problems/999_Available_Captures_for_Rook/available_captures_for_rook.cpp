/*
    ============
    === EASY ===
    ============

    ================================
    999) Available Captures for Rook
    ================================

    ============
    Description:
    ============

    You are given an 8 x 8 matrix representing a chessboard. There is exactly
    one white rook represented by 'R', some number of white bishops 'B', and
    some number of black pawns 'p'. Empty squares are represented by '.'.

    A rook can move any number of squares horizontally or vertically (up, down,
    left, right) until it reaches another piece or the edge of the board. A
    rook is attacking a pawn if it can move to the pawn's square in one move.

    Note: A rook cannot move through other pieces, such as bishops or pawns.
    This means a rook cannot attack a pawn if there is another piece blocking
    the path.

    Return the number of pawns the white rook is attacking.

    ===========================================================
    FUNCTION: int numRookCaptures(vector<vector<char>>& board);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

    Input: board = [[".",".",".",".",".",".",".","."],
                    [".",".",".","p",".",".",".","."],
                    [".",".",".","R",".",".",".","p"],
                    [".",".",".",".",".",".",".","."],
                    [".",".",".",".",".",".",".","."],
                    [".",".",".","p",".",".",".","."],
                    [".",".",".",".",".",".",".","."],
                    [".",".",".",".",".",".",".","."]]
    Output: 3
    Explanation:
    In this example, the rook is attacking all the pawns.

    --- Example 2 ---

    Input: board = [[".",".",".",".",".",".","."],
                    [".","p","p","p","p","p",".","."],
                    [".","p","p","B","p","p",".","."],
                    [".","p","B","R","B","p",".","."],
                    [".","p","p","B","p","p",".","."],
                    [".","p","p","p","p","p",".","."],
                    [".",".",".",".",".",".",".","."],
                    [".",".",".",".",".",".",".","."]]
    Output: 0
    Explanation:
    The bishops are blocking the rook from attacking any of the pawns.

    --- Example 3 ---
    Input: board = [[".",".",".",".",".",".",".","."],
                    [".",".",".","p",".",".",".","."],
                    [".",".",".","p",".",".",".","."],
                    ["p","p",".","R",".","p","B","."],
                    [".",".",".",".",".",".",".","."],
                    [".",".",".","B",".",".",".","."],
                    [".",".",".","p",".",".",".","."],
                    [".",".",".",".",".",".",".","."]]
    Output: 3
    Explanation:
    The rook is attacking the pawns at positions b5, d6, and f5.


    *** Constraints ***
    board.length == 8
    board[i].length == 8
    board[i][j] is either 'R', '.', 'B', or 'p'
    There is exactly one cell with board[i][j] == 'R'

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.73% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        int result = 0;

        int rook_row = -1;
        int rook_col = -1;

        // Find the position of the Rook
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] == 'R')
                {
                    rook_row = row;
                    rook_col = col;

                    // Break out of both loops
                    row = ROWS-1; // Or just 'ROWS' it doesn't matter here
                    break;
                }
            }
        }

        // Upward
        for (int row = rook_row-1; row >= 0; row--)
        {
            if (board[row][rook_col] == 'B')
                break;
            else if (board[row][rook_col] == 'p')
            {
                result++;
                break;
            }
        }

        // Downward
        for (int row = rook_row+1; row < ROWS; row++)
        {
            if (board[row][rook_col] == 'B')
                break;
            else if (board[row][rook_col] == 'p')
            {
                result++;
                break;
            }
        }

        // To the left
        for (int col = rook_col-1; col >= 0; col--)
        {
            if (board[rook_row][col] == 'B')
                break;
            else if (board[rook_row][col] == 'p')
            {
                result++;
                break;
            }
        }

        // To the right
        for (int col = rook_col+1; col < COLS; col++)
        {
            if (board[rook_row][col] == 'B')
                break;
            else if (board[rook_row][col] == 'p')
            {
                result++;
                break;
            }
        }

        return result;
    }
};
