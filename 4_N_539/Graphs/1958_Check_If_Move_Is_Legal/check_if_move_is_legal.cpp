#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    1958) Check if Move is Legal
    ============================

    ============
    Description:
    ============

    You are given a 0-indexed 8 x 8 grid board, where board[r][c] represents
    the cell (r, c) on a game board. On the board, free cells are represented
    by '.', white cells are represented by 'W', and black cells are represented
    by 'B'.

    Each move in this game consists of choosing a free cell and changing it to
    the color you are playing as (either white or black). However, a move is
    only legal if, after changing it, the cell becomes the endpoint of a good
    line (horizontal, vertical, or diagonal).

    A good line is a line of three or more cells (including the endpoints)
    where the endpoints of the line are one color, and the remaining cells in
    the middle are the opposite color (no cells in the line are free). You can
    find examples for good lines in the figure below:

                                   +-----+
                                   |  W  |
                                   +-----+
                                   |  B  |
    +-----+-----+-----+-----+      +-----+     +-----+-----+-----+-----+-----+
    |  B  |  W  |  W  |  B  |      |  W  |     |  W  |  W  |  B  |  B  |  B  |
    +-----+-----+-----+-----+      +-----+     +-----+-----+-----+-----+-----+



                               +-----+
                               |  W  |
                +-----+        +-----+-----+
                |  B  |              |  B  |
          +-----+-----+              +-----+-----+
          |  W  |                          |  B  |
    +-----+-----+                          +-----+-----+
    |  B  |                                      |  W  |
    +-----+                                      +-----+

    Given two integers rMove and cMove and a character color representing the
    color you are playing as (white or black), return true if changing cell
    (rMove, cMove) to color color is a legal move, or false if it is not legal.


    ========================================================================================
    FUNCTION: bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color);
    ========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  B  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  W  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  W  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  W  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  W  |  B  |  B  |  Xb |  W  |  W  |  W  |  B  | // Xb means starts with B
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  B  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  B  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  W  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    Input: board = [[".",".",".","B",".",".",".","."],
                    [".",".",".","W",".",".",".","."],
                    [".",".",".","W",".",".",".","."],
                    [".",".",".","W",".",".",".","."],
                    ["W","B","B",".","W","W","W","B"],
                    [".",".",".","B",".",".",".","."],
                    [".",".",".","B",".",".",".","."],
                    [".",".",".","W",".",".",".","."]],
    rMove = 4,
    cMove = 3,
    color = "B"

    Output: true
    Explanation: '.', 'W', and 'B' are represented by the colors blue, white,
                 and black respectively, and cell (rMove, cMove) is marked with
                 an 'X'.  The two good lines with the chosen cell as an
                 endpoint are annotated above with the red rectangles.




    --- Example 2 ---
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  .  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  B  |  .  |  .  |  W  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  W  |  .  |  .  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  W  |  B  |  .  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  .  |  Xw |  .  |  .  |  .  | // Xw means starts with W
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  .  |  B  |  W  |  .  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  .  |  .  |  .  |  W  |  .  |
    +-----+-----+-----+-----+-----+-----+-----+-----+
    |  .  |  .  |  .  |  .  |  .  |  .  |  .  |  B  |
    +-----+-----+-----+-----+-----+-----+-----+-----+

    Input: board = [[".",".",".",".",".",".",".","."],
                    [".","B",".",".","W",".",".","."],
                    [".",".","W",".",".",".",".","."],
                    [".",".",".","W","B",".",".","."],
                    [".",".",".",".",".",".",".","."],
                    [".",".",".",".","B","W",".","."],
                    [".",".",".",".",".",".","W","."],
                    [".",".",".",".",".",".",".","B"]],
    rMove = 4,
    cMove = 4,
    color = "W"

    Output: false
    Explanation: While there are good lines with the chosen cell as a middle
                 cell, there are no good lines with the chosen cell as an
                 endpoint.



    *** Constraints ***
    board.length == board[r].length == 8
    0 <= rMove, cMove < 8
    board[rMove][cMove] == '.'
    color is either 'B' or 'W'.

*/

/* Time  Beats: 93.27% */
/* Space Beats: 98.08% */

/* Time  Complexity: O(1) */ // Since it's always 8x8 and not NxN
/* Space Complexity: O(1) */ // Since it's always 8x8 and not NxN
class Solution {
public:
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color)
    {
        if (dfs(board, rMove-1, cMove  , color, 0, 0)) return true; // 0
        if (dfs(board, rMove-1, cMove+1, color, 0, 1)) return true; // 1
        if (dfs(board, rMove  , cMove+1, color, 0, 2)) return true; // 2
        if (dfs(board, rMove+1, cMove+1, color, 0, 3)) return true; // 3
        if (dfs(board, rMove+1, cMove  , color, 0, 4)) return true; // 4
        if (dfs(board, rMove+1, cMove-1, color, 0, 5)) return true; // 5
        if (dfs(board, rMove  , cMove-1, color, 0, 6)) return true; // 6
        if (dfs(board, rMove-1, cMove-1, color, 0, 7)) return true; // 7

        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, int i, int j, char& color, int step, int dir)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS)
          return false;

        if (board[i][j] == '.')
            return false;

        if (step == 0 && board[i][j] == color)
            return false;

        if (step > 0 && board[i][j] == color)
            return true;

        switch(dir)
        {
            case 0:
            if (dfs(board, i-1, j  , color, step+1, dir)) return true; // 0
            break;

            case 1:
            if (dfs(board, i-1, j+1, color, step+1, dir)) return true; // 1
            break;

            case 2:
            if (dfs(board, i  , j+1, color, step+1, dir)) return true; // 2
            break;

            case 3:
            if (dfs(board, i+1, j+1, color, step+1, dir)) return true; // 3
            break;

            case 4:
            if (dfs(board, i+1, j  , color, step+1, dir)) return true; // 4
            break;

            case 5:
            if (dfs(board, i+1, j-1, color, step+1, dir)) return true; // 5
            break;

            case 6:
            if (dfs(board, i  , j-1, color, step+1, dir)) return true; // 6
            break;

            case 7:
            if (dfs(board, i-1, j-1, color, step+1, dir)) return true; // 7
            break;
        }

        return false;
    }
};
