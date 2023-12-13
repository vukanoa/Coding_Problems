#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    909) Snakes and Ladders
    ===========================

    ============
    Description:
    ============

    You are given an n x n integer matrix board where the cells are labeled
    from 1 to n2 in a Boustrophedon style starting from the bottom left of the
    board (i.e. board[n - 1][0]) and alternating direction each row.

    You start on square 1 of the board. In each move, starting from square
    curr, do the following:

        Choose a destination square next with a label in the range [curr + 1,
        min(curr + 6, n2)].  This choice simulates the result of a standard
        6-sided die roll: i.e., there are always at most 6 destinations,
        regardless of the size of the board.  If next has a snake or ladder,
        you must move to the destination of that snake or ladder. Otherwise,
        you move to next.  The game ends when you reach the square n2.

    A board square on row r and column c has a snake or ladder if board[r][c]
    != -1. The destination of that snake or ladder is board[r][c]. Squares 1
    and n2 do not have a snake or ladder.

    Note that you only take a snake or ladder at most once per move. If the
    destination to a snake or ladder is the start of another snake or ladder,
    you do not follow the subsequent snake or ladder.

        For example, suppose the board is [[-1,4],[-1,3]], and on the first
        move, your destination square is 2. You follow the ladder to square 3,
        but do not follow the subsequent ladder to 4.

    Return the least number of moves required to reach the square n2. If it is
    not possible to reach the square, return -1.

    ===========================================================
    FUNCTION: int snakesAndLadders(vector<vector<int>>& board);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +---------+---------+---------+---------+---------+---------+
    |         |         |         |         |         |         |
    |   36    |   35    |   34    |   33    |   32    |   31    |
    |         |      |  |         |         |         |         |
    +---------+------|--+---------+---------+---------+---------+
    |         |      |  |         |         |         |         |
    |   25    |   26 |  |   27    |   27    |   29    |   30    |
    |         |      |  |         |         |         |         |
    +---------+------|--+---------+---------+---------+---------+
    |         |      |  |         |         |         |         |
    |   24    |   23 |  |   22    |   21    |   20    |   19    |
    |         |      |  |         |         |         |         |
    +---------+------|--+---------+---------+---------+---------+
    |    #####|#############################|###      |         |
    |   13    |   14    |   15    |   16    |   17    |   18    |
    |         |         |  /      |         |         |         |
    +---------+---------+-/-------+---------+---------+---------+
    |         |         |/        |         |         |         |
    |   12    |   11    /   10    |    9    |    8    |    7    |
    |         |        /|         |         |         |         |
    +---------+-------/-+---------+---------+---------+---------+
    |         |      /  |         |         |         |         |
    |    1    |    2    |    3    |    4    |    5    |    6    |
    |         |         |         |         |         |         |
    +---------+---------+---------+---------+---------+---------+

    Legend: '|' or '/' are considered "ladders"

            '#' is considered a "snake"

    Input: board =
    [[-1, -1, -1, -1, -1, -1],
     [-1, -1, -1, -1, -1, -1],
     [-1, -1, -1, -1, -1, -1],
     [-1, 35, -1, -1, 13, -1],
     [-1, -1, -1, -1, -1, -1],
     [-1, 15, -1, -1, -1, -1]]

    Output: 4
    Explanation:
    In the beginning, you start at square 1 (at row 5, column 0).
    You decide to move to square 2 and must take the ladder to square 15.
    You then decide to move to square 17 and must take the snake to square 13.
    You then decide to move to square 14 and must take the ladder to square 35.
    You then decide to move to square 36, ending the game.
    This is the lowest possible number of moves to reach the last square, so
    return 4.


    --- Example 2 ---
    Input: board = [[-1,-1], [-1,3]]
    Output: 1


    *** Constraints ***
    n == board.length == board[i].length
    2 <= n <= 20
    board[i][j] is either -1 or in the range [1, n^2].
    The squares labeled 1 and n2 do not have any ladders or snakes.

*/

/* Time  Beats: 63.15% */
/* Space Beats: 31.61% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board)
    {
        int n = board.size();

        // So that it's easier to index
        std::reverse(board.begin(), board.end());

        std::queue<std::pair<int, int>> queue;
        queue.push({1, 0}); // {square, moves}

        std::unordered_set<int> visited;

        while (!queue.empty())
        {
            int square = queue.front().first;
            int moves  = queue.front().second;
            queue.pop();

            for (int i = 1; i < 7; i++) // Roll a Dice
            {
                int next_square = square + i;

                auto field = real_position(next_square, n);
                int r = field.first;
                int c = field.second;

                if (board[r][c] != -1)
                    next_square = board[r][c];

                if (next_square == n * n) // We've reached the endpoint
                    return moves + 1;

                if (visited.find(next_square) == visited.end()) // Not Visited
                {
                    visited.insert(next_square);
                    queue.push({next_square, moves + 1});
                }
            }
        }

        return -1;
    }

    std::pair<int, int> real_position(int& next_square, int& n)
    {
        int row = (next_square-1) / n;
        int col = (next_square-1) % n;

        if (row & 1) // Odd row
            col = n - 1 - col;

        return {row, col};
    }
};
