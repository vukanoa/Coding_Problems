#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    419) Battleships In A Board
    ===========================

    ============
    Description:
    ============

    Given an m x n matrix board where each cell is a battleship 'X' or empty
    '.', return the number of the battleships on board.

    Battleships can only be placed horizontally or vertically on board. In
    other words, they can only be made of the shape 1 x k (1 row, k columns) or
    k x 1 (k rows, 1 column), where k can be of any size. At least one
    horizontal or vertical cell separates between two battleships (i.e., there
    are no adjacent battleships).


    ---------------
    -- Follow Up --
    ---------------

    Could you do it in one-pass, using only O(1) extra memory and without
    modifying the values board?


    ============================================================
    FUNCTION: int countBattleships(vector<vector<char>>& board);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+
    |  X  |     |     |  X  |
    +-----+-----+-----+-----+
    |     |     |     |  X  |
    +-----+-----+-----+-----+
    |     |     |     |  X  |
    +-----+-----+-----+-----+
    |     |     |     |     |
    +-----+-----+-----+-----+

    Input: board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
    Output: 2


    --- Example 2 ---
    Input: board = [["."]]
    Output: 0


    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is either '.' or 'X'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since in the "Follow-Up", we are asked if we can solve it in one-pass and
    using O(1) extra space and without modifying the board, we are left with
    only one option.

    Check this Example:

        +-----+-----+-----+-----+
        |  X  |     |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |  X  |
        +-----+-----+-----+-----+
        |  X  |  X  |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |     |
        +-----+-----+-----+-----+

    If a DFS comes to mind, cross that option off because we are NOT allowed to
    modify the board and therefore we wouldn't be able to pull it off.

    The way this Solution works is as following:

    Since we want to count only the first X of any battleship, we need to
    devise a way of ignoring subsequent X's.

    Also, since battleships can be of different sizes and can be constructed
    only horizontally and vertically but NOT diagonally, we need a way of
    checking horizontal and vertical lines, in O(1) while traversing, if some
    X is owned by a battleship we've already counted.

    To illustrate with an example - At the above ASCII drawn table, take a look
    at the rightmost vertical battleship.

    Let's isolate that battleship as if it's the only one on the board:

        +-----+-----+-----+-----+
        |     |     |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |     |
        +-----+-----+-----+-----+

    If we are iterating row-by-row and column-by-column, meaning a standard
    matrix traversal:

        +-----+-----+-----+-----+
        |  1  |  2  |  3  |  4  |
        +-----+-----+-----+-----+
        |  5  |  6  |  7  |  8  |
        +-----+-----+-----+-----+
        |  9  |  10 |  11 |  12 |
        +-----+-----+-----+-----+
        |  13 |  14 |  15 |  16 |
        +-----+-----+-----+-----+

    Then ask yourselves - How can we make sure to ignore all the X's of a
    battleships we've already taken into account?

    The answer is - Check if left of the current X we're on and if above the
    current X we're on there is an X as well. If there is an X on any of the
    two positions we've checked, then this current X is a subsequent X and we
    shall ignore it. We shouldn't be taking it into account since we're certain
    we've counted this battleship already.

    The answer is - Check:

        1. If left  of the current X we're on there is an X as well
        2. If above    the current X we're on there is an X as well

    If there is an X on any of the two positions(left or above the current
    position), then that means this current X is a subsequent X and we shall
    ignore it. We shouldn't be taking it into account since we're certain we've
    counted this battleship already.

    Since at each iteration we're checking left and above the current position,
    it can happen that there is not left or above.

    If we are at column 0, then there is no left of the current position.
    If we are at    row 0, then there is no above   the current position.

    Therefore before checking each of the positions we have to check
        1. if column > 0
        2. if    row > 0

    Furthermore, that leaves is with this if statement:

        if ((row > 0 && board[row-1][col  ] == 'X') ||
            (col > 0 && board[row  ][col-1] == 'X'))
            continue;

    If either of these two options is true, then we're ignoring the current X.
    Also, if the current position is NOT an X, then we should, obviously ignore
    it as well.

    With this approach we've covered all the possible shapes of battleships on
    the board.

    Take a look at this one:

           0     1     2     3
        +-----+-----+-----+-----+
     0  |     |     |     |     |
        +-----+-----+-----+-----+
     1  |  X  |     |     |     |
        +-----+-----+-----+-----+
     2  |  X  |  X  |     |     |
        +-----+-----+-----+-----+
     3  |     |     |     |     |
        +-----+-----+-----+-----+

    
    Once we get to be at board[1][0], we will see that it's an X and that
    neither left of it or above it there isn't any X.

    Since that is the case we are going to increment variable "battleships".

    However, once we get to board[2][0] and board[2][1], one of the two cases
    are going to be true, meaning for board[2][0] we can see that ABOVE it,
    there is an X, therefore we will ignore this one. At board[2][1] we can see
    that LEFT of it there is an X, therefore we shall ignore this one as well.

    At the end, variable "battleships" is going to be equal to 1, which is
    exactly what we wanted.

    Now, knowing all of the above information, iterate in your mind through
    example like this and check if this method outputs the desired output.

        +-----+-----+-----+-----+
        |  X  |     |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |  X  |
        +-----+-----+-----+-----+
        |  X  |  X  |     |  X  |
        +-----+-----+-----+-----+
        |     |     |     |     |
        +-----+-----+-----+-----+

    It will, variable "battleships" is going to be 3.

*/

/* Time  Beats: 94.24% */
/* Space Beats: 99.68% */

/* Time  Complexity: O(n) */ // One-pass
/* Space Complexity: O(1) */
class Solution_Follow_Up_Implementation_1 {
public:
    int countBattleships(std::vector<std::vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        int battleships = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if ((row > 0 && board[row-1][col  ] == 'X') ||
                    (col > 0 && board[row  ][col-1] == 'X'))
                    continue;

                // We need this "if" only because board[0][0] can be '.'
                // Otherwise, we would always increment battleships once we
                // pass the previous "if statement" up above
                if (board[row][col] == 'X')
                    battleships++;
            }
        }

        return battleships;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent as above, however this one is implemented a bit
    differently. Some people may find this implementation easier to read and
    grasp.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.52% */

/* Time  Complexity: O(n) */ // One-pass
/* Space Complexity: O(1) */
class Solution_Follow_Up_Implementation_2 {
public:
    int countBattleships(std::vector<std::vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        int battleships = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] == '.'                  ||
                    (row > 0 && board[row-1][col  ] == 'X') ||
                    (col > 0 && board[row  ][col-1] == 'X'))
                    continue;

                battleships++;
            }
        }

        return battleships;
    }
};
