/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    529) Minesweeper
    ===========================

    ============
    Description:
    ============


    Let's play the minesweeper game (Wikipedia, online game)!

    You are given an m x n char matrix board representing the game board where:

        + 'M' represents an unrevealed mine,

        + 'E' represents an unrevealed empty square,

        + 'B' represents a revealed blank square that has no adjacent mines
              (i.e., above, below, left, right, and all 4 diagonals),

        + digit ('1' to '8') represents how many mines are adjacent to this
                             revealed square, and

        + 'X' represents a revealed mine.

    You are also given an integer array click where click = [clickr, clickc]
    represents the next click position among all the unrevealed squares ('M' or
    'E').

    Return the board after revealing this position according to the following rules:

        + If a mine 'M' is revealed, then the game is over. You should change
          it to 'X'.

        + If an empty square 'E' with no adjacent mines is revealed, then
          change it to a revealed blank 'B' and all of its adjacent unrevealed
          squares should be revealed recursively.

        + If an empty square 'E' with at least one adjacent mine is revealed,
          then change it to a digit ('1' to '8') representing the number of
          adjacent mines. Return the board when no more squares will be
          revealed.

    ============================================================================================
    FUNCTION: vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click);
    ============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
    Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]

    --- Example 2 ---
    Input: board = [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]], click = [1,2]
    Output: [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]


    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m, n <= 50
    board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
    click.length == 2
    0 <= clickr < m
    0 <= clickc < n
    board[clickr][clickc] is either 'M' or 'E'.

*/

#include <queue>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic recursive DFS in all 8 directions.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    /* Clockwise */
    vector<pair<int, int>> directions =
    {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},           { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)
    {
        int row = click[0];
        int col = click[1];

        if (board[row][col] == 'M')
            board[row][col] = 'X';
        else
            dfs(board, row, col);

        return board;
    }

private:
    void dfs(vector<vector<char>>& board, int row, int col)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (board[row][col] != 'E')
            return;

        int adjacent_mines = count_mines(board, row, col);

        if (adjacent_mines > 0)
        {
            board[row][col] = char('0' + adjacent_mines);
            return;
        }

        board[row][col] = 'B';

        for (const auto& dir : directions)
            dfs(board, row + dir.first, col + dir.second);
    }

    int count_mines(vector<vector<char>>& board, int row, int col)
    {
        int mines = 0;
        const int ROWS = board.size();
        const int COLS = board[0].size();

        for (const auto& dir : directions)
        {
            int x = row + dir.first;
            int y = col + dir.second;

            if (x >= 0 && y >= 0 && x < ROWS && y < COLS && board[x][y] == 'M')
                mines++;
        }

        return mines;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    BFS way of doing the same.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS {
private:
    /* Clockwise */
    vector<pair<int, int>> directions =
    {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},           { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };


public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)
    {
        int row = click[0];
        int col = click[1];

        if (board[row][col] == 'M')
            board[row][col] = 'X';
        else
            BFS(board, row, col);

        return board;
    }

private:
    void BFS(vector<vector<char>>& board, int start_row, int start_col)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        queue<pair<int, int>> queue;

        if (board[start_row][start_col] != 'E')
            return;

        queue.push({start_row, start_col});
        board[start_row][start_col] = 'B';

        while ( ! queue.empty())
        {
            auto curr = queue.front();
            queue.pop();

            int row = curr.first;
            int col = curr.second;

            int adjacent_mines = count_mines(board, row, col);

            if (adjacent_mines > 0)
            {
                board[row][col] = char('0' + adjacent_mines);
                continue;
            }

            for (const auto& dir : directions)
            {
                int next_row = row + dir.first;
                int next_col = col + dir.second;

                if (next_row < 0 || next_col < 0 || next_row >= ROWS || next_col >= COLS)
                    continue;;

                if (board[next_row][next_col] != 'E')
                    continue;

                board[next_row][next_col] = 'B';
                queue.push( {next_row, next_col} );
            }
        }
    }

    int count_mines(vector<vector<char>>& board, int row, int col)
    {
        int mines = 0;
        const int ROWS = board.size();
        const int COLS = board[0].size();

        for (const auto& dir : directions)
        {
            int x = row + dir.first;
            int y = col + dir.second;

            if (x >= 0 && y >= 0 && x < ROWS && y < COLS && board[x][y] == 'M')
                mines++;
        }

        return mines;
    }
};
