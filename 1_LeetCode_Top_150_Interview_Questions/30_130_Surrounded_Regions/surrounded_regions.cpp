#include <iostream>

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




/*
    ------------
    --- IDEA ---
    ------------


    This is one of those problems where you have to think in reverse.

    Instead of asking yourself:"How do I capture all regions where O's are
    surrounded by X?"

    Ask this instead:"How do I mark all the O's that are 4-directionally
    connected to one of four edges of this entire matrix?"

    Edges are:

        1. Top(1's)        // First Row
        2. Right side(2's) // First Column
        3. Bottom(3's)     // Last  Row
        4. Left side(4's)  // Last  Column


                        +---+---+---+---+---+---+---+
                        | 41| 1 | 1 | 1 | 1 | 1 |12 |
                        +---+---+---+---+---+---+---+
                        | 4 | O | O | X | X | X | 2 |
                        +---+---+---+---+---+---+---+
                        | 4 | X | O | X | X | X | 2 |
                        +---+---+---+---+---+---+---+
                        | 4 | O | X | X | X | X | 2 |
                        +---+---+---+---+---+---+---+
                        | 43| 3 | 3 | 3 | 3 | 3 |32 |
                        +---+---+---+---+---+---+---+


    We will use boundary DFS to solve this problem.

    Consider these two cases for clarity :

    O's won't be flipped          O's will be flipped
       X O X X X                     X X X X X
       X O O O X                     X O O O X
       X O X X X                     X O X X X
       X X X X X                     X X X X X

    As we've said - We want to ask ourselves:"How do I mark all the O's that
    are 4-directionally connected to one of four edges of this entire matrix?"

    Why do we want to mark them in the first place?

    Because once we mark those O's that are connected to any edge by a
    4-directional O's, then we can flip all of the remaining O's(the ones that
    are NOT connected to any edge, i.e. the ones that are indeed surrounded
    entirely by X).

    Once we capture those surrounded O's, then all we have to do is flip our
    marked O's(let's say we've marked them with a '#') back to O and voila.


    Steps to Solve :
    1. Move over the boundary of board, and find O's

    2. Every time we find an O, perform DFS from it's position

    3. In DFS convert all 'O' to '#'
       (why? so that we can differentiate which 'O' can be flipped and which
        cannot be)

    4. After all DFSs have been performed, board contains three elements:
       '#', 'O' and 'X'

    5. 'O' are left over elements which are not connected to any boundary O,
       therefore - Flip them to 'X'(i.e. capture all of those O's).

    6. '#' are elements(O's) which cannot be flipped to 'X', so flip them
       back to 'O'
*/

/* Time  Beats: 89.51% */
/* Space Beats: 93.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */ // Due to recursion
class Solution {
public:
    void solve(vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        /* Rows */
        for (int j = 0; j < COLS; j++)
        {
            /* First Row */
            if (board[0][j] == 'O')
                dfs(board, 0, j);

            /* Last Row */
            if (board[ROWS-1][j] == 'O')
                dfs(board, ROWS-1, j);
        }

        /* Columns */
        for (int i = 0; i < ROWS; i++)
        {
            /* First Column */
            if (board[i][0] == 'O')
                dfs(board, i, 0);

            /* Last Column */
            if (board[i][COLS-1] == 'O')
                dfs(board, i, COLS-1);
        }

        /* Capture all regions that are 4-directionally surrounded by 'X' */
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }

        /* Flip #'s back to O's */
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (board[i][j] == '#')
                    board[i][j] = 'O';
            }
        }
    }


private:

    /* Flip O's, that are connected to edges, to #'s */
    void dfs(std::vector<std::vector<char>>& board, int i, int j)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (i < 0 || j < 0 || i == ROWS || j == COLS || board[i][j] != 'O')
            return;

        board[i][j] = '#'; // Flip to '#' or any char other than 'X' or 'O'

        dfs(board, i-1, j  );
        dfs(board, i+1, j  );
        dfs(board, i  , j-1);
        dfs(board, i  , j+1);
    }
};
