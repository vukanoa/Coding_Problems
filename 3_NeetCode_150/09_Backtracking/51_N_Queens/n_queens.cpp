/*
    ============
    === HARD ===
    ============

    ===========================
    51) N-Queens
    ===========================

    ============
    Description:
    ============

    The n-queens puzzle is the problem of placing 'n' queens on an n x n
    chessboard such that no two queens attack each other.

    Given an integer n, return all distinct solutions to the n-queens puzzle.
    You may return the answer in any order.

    Each solution contains a distinct board configuration of the n-queens
    placement, where 'Q' and '.' both indicate a queen and an empty space,
    respectively.

    =====================================================
    FUNCTION: vector<vector<string>> solveNQueens(int n);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  n = 4
    Output: [[".Q..","...Q","Q...","..Q."], ["..Q.","Q...","...Q",".Q.."]]

    --- Example 2 ---
    Input:  n = 1
    Output: [["Q"]]

    *** Constraints ***
    1 <= n <= 9

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We're trying to "fit" a Queen column by column, that's why we only need
    to check if the current Queen attacks any:
        1. Left  upper diagonal
        2. Right upper diagonal

    We're also using "taken_col" which helps us check if the given column is
    taken.

    If the column is NOT taken and the cell is VALID, i.e. it's NOT attacked
    by any other Queen in the rows above, then and only then we can take the
    current cell on the current row.

*/

/* Time  Beats:  100.00% */
/* Space Beats:   67.67% */

/* Time  Complexity: O(N!) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> results;
        unordered_set<int> taken_col;

        vector<string> layout;
        backtracking(0, layout, taken_col, n, results);

        return results;
    }

private:
    void backtracking(int row, vector<string>& layout, unordered_set<int>& taken_col, int n, vector<vector<string>>& results)
    {
        if (row == n)
        {
            results.push_back(layout);
            return;
        }

        for (int col = 0; col < n; col++)
        {
            if (taken_col.count(col) || ! valid(row, col, layout, n))
                continue;

            string row_layout(n, '.');
            row_layout[col] = 'Q';

            layout.push_back(row_layout);
            taken_col.insert(col);

            backtracking(row + 1, layout, taken_col, n, results);

            taken_col.erase(col);
            layout.pop_back();
        }
    }

    bool valid(int row, int col, vector<string> layout, int n)
    {
        int i = row-1;
        int j = col-1;
        while (i >= 0 && j >= 0)
        {
            if (layout[i][j] == 'Q')
                return false;

            i--;
            j--;
        }

        i = row-1;
        j = col+1;
        while (i >= 0 && j < n)
        {
            if (layout[i][j] == 'Q')
                return false;

            i--;
            j++;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    There are (2 * (N-1) + 1) diagonals of each "type", where types are:

        + "Forward  slash" diagonals    formula: 1 << (row + col)
        + "Backward slash" diagonals    formula: 1 << (row - col + N)


        Forward slashes:

                      /   /   /   /
                     /   /   /   /
                +---+---+---+---+
                |  /|  /|  /|  /|
                | / | / | / | / | /
                |/  |/  |/  |/  |/
                +---+---+---+---+
               /|  /|  /|  /|  /| 
              / | / | / | / | / | /
 row + col = 0  |/  |/  |/  |/  |/
                +---+---+---+---+
               /|  /|  /|  /|  /| 
              / | / | / | / | / | /
             1  |/  |/  |/  |/  |/ 
                +---+---+---+---+
               /|  /|  /|  /|  /| 
              / | / | / | / | / | 
             2  |/  |/  |/  |/  | 
                +---+---+---+---+
               /   /   /   /
              /   /   /   /
             3   4   5   6



        Backward slashes:

              \   \   \   \
               \   \   \   \
                +---+---+---+---+
                |\  |\  |\  |\  |
              \ | \ | \ | \ | \ |
               \|  \|  \|  \|  \|
                +---+---+---+---+
                |\  |\  |\  |\  | \
              \ | \ | \ | \ | \ |  \
               \|  \|  \|  \|  \|   1 = row - col + N
                +---+---+---+---+
                |\  |\  |\  |\  | \
              \ | \ | \ | \ | \ |  \
               \|  \|  \|  \|  \|   2
                +---+---+---+---+
                |\  |\  |\  |\  | \
                | \ | \ | \ | \ |  \
                |  \|  \|  \|  \|   3
                +---+---+---+---+
                     \   \   \   \
                      \   \   \   \
                       7   6   5   4

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.97% */

/* Time  Complexity: O(N!) */
/* Space Complexity: O(N)  */ // Because of the Call Stack, w/o "results"
class Solution_Bitmask {
private:
        int column = 0;
        int forward_slash_diagonal  = 0; // There are (2 * (N-1) + 1) diagonals
        int backward_slash_diagonal = 0; // There are (2 * (N-1) + 1) diagonals

public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> results;

        vector<string> board(n, string(n, '.'));
        backtracking(0, board, results, n);

        return results;
    }

private:
    void backtracking(int row, vector<string>& board, vector<vector<string>>& results, int& n)
    {
        if (row == n)
        {
            results.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++)
        {
            if (
                (column                  & (1 << (col)))           ||
                (backward_slash_diagonal & (1 << (row + col)))     ||
                (forward_slash_diagonal  & (1 << (row - col + n)))
               )
            {
                continue;
            }

            board[row][col] = 'Q';
            column                  ^= 1 << (col);
            backward_slash_diagonal ^= 1 << (row + col);
            forward_slash_diagonal  ^= 1 << (row - col + n);

            backtracking(row + 1, board, results, n);

            forward_slash_diagonal  ^= 1 << (row - col + n);
            backward_slash_diagonal ^= 1 << (row + col);
            column                  ^= 1 << (col);
            board[row][col] = '.';
        }
    }
};
