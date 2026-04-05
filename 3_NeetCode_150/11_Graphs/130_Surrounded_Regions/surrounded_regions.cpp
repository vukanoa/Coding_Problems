/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    130) Surrounded Regions
    ===========================

    ============
    Description:
    ============

    Given an m x n matrix board containing 'X' and 'O', capture all regions
    that are 4-directionally surrounded by 'X'.

    A region is captured by flipping all 'O's into 'X's in that surrounded
    region.

    ==================================================
    FUNCTION: void solve(vector<vector<char>>& board);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +---+---+---+---+             +---+---+---+---+
    | X | X | X | X |             | X | X | X | X |
    +---+---+---+---+             +---+---+---+---+
    | X | O | O | X |             | X | X | X | X |
    +---+---+---+---+    ====>    +---+---+---+---+
    | X | X | O | X |             | X | X | X | X |
    +---+---+---+---+             +---+---+---+---+
    | X | O | X | X |             | X | O | X | X |
    +---+---+---+---+             +---+---+---+---+

    Input: board = [["X","X","X","X"],
                    ["X","O","O","X"],
                    ["X","X","O","X"],
                    ["X","O","X","X"]]

    Output: [["X","X","X","X"],
             ["X","X","X","X"],
             ["X","X","X","X"],
             ["X","O","X","X"]]

    Explanation: Notice that an 'O' should not be flipped if:
    - It is on the border, or
    - It is adjacent to an 'O' that should not be flipped.
    The bottom 'O' is on the border, so it is not flipped.
    The other three 'O' form a surrounded region, so they are flipped.


    --- Example 2 ---
    Input: board = [["X"]]
    Output: [["X"]]


    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is 'X' or 'O'.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is one of those problems where you have to think in reverse, i.e. you
    have to INVERT the problem.

    Instead of asking yourself:
        "How do I capture all regions where Os are surrounded by X?"

    Ask this instead:
        "How do I mark all the Os that are 4-directionally connected to one of
         four edges of this entire matrix?"


    We will use boundary DFS to solve this problem.
    Consider these two cases for clarity:

            Os won't be flipped           Os will be flipped
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | O | X | X | X |        | X | O | X | X | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | O | O | O | X |        | X | O | O | O | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | O | X | X | X |        | X | O | X | X | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | X | X | X | X |        | X | X | X | X | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   

    As we've said - We want to ask ourselves:
    "How do I mark all the Os that are 4-directionally connected to one of
     four edges of this entire matrix?"

    Why do we want to mark them in the first place?

    Because once we mark those Os that are connected to any edge by a
    4-directional Os, then and only then can we flip all of the remaining
    Os(the ones that are NOT connected to any edge, i.e. the ones that are
    indeed surrounded entirely by X) without messing up the rest of the grid.

    Once we capture those surrounded O's, then all we have to do is flip our
    previously marked Os(let's say we've marked them with a '#') back to O and
    voila.


    Steps to Solve:
    1. Move over the boundary of board, and find Os

    2. Every time we find an O, perform DFS from it's position

    3. In DFS convert all 'O's to '#'
       (why? so that we can differentiate which 'O' can be flipped and which
        CANNOT be)

    4. After all DFSs have been performed, board contains three elements:
       '#', 'O' and 'X'

    5. 'O' are left over elements which are not connected to any boundary O,
       therefore - Flip them to 'X'(i.e. capture all of those O's).

    6. '#' are elements(O's) which cannot be flipped to 'X', so flip them
       back to 'O'

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.87% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS {
public:
    void solve(vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        // First and last ROW
        for (int col = 0; col < COLS; col++)
        {
            dfs(0,      col, board);
            dfs(ROWS-1, col, board);
        }

        // First and last COLUMN
        for (int row = 0; row < ROWS; row++)
        {
            dfs(row, 0     , board);
            dfs(row, COLS-1, board);
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] == '#')
                    board[row][col] = 'O';
                else
                    board[row][col] = 'X';
            }
        }
    }

private:
    void dfs(int row, int col, vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (board[row][col] != 'O')
            return;

        board[row][col] = '#';

        /* Signing Cross */
        dfs(row-1, col  , board); // Up
        dfs(row+1, col  , board); // Down
        dfs(row  , col-1, board); // Left
        dfs(row  , col+1, board); // Right
    }
};
