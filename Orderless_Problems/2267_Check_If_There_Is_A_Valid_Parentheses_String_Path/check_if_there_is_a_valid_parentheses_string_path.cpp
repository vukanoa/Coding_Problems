/*
    ============
    === HARD ===
    ============

    =======================================================
    2267) Check if There is a Valid Parentheses String Path
    =======================================================

    ============
    Description:
    ============

    A parentheses string is a non-empty string consisting only of '(' and ')'.
    It is valid if any of the following conditions is true:

        + It is ().

        + It can be written as AB (A concatenated with B), where A and B are
          valid parentheses strings.

        + It can be written as (A), where A is a valid parentheses string.

    You are given an m x n matrix of parentheses grid. A valid parentheses
    string path in the grid is a path satisfying all of the following
    conditions:

        + The path starts from the upper left cell (0, 0).
        + The path ends at the bottom-right cell (m - 1, n - 1).
        + The path only ever moves down or right.
        + The resulting parentheses string formed by the path is valid.

    Return true if there exists a valid parentheses string path in the grid.
    Otherwise, return false.

    ========================================================
    FUNCTION: bool hasValidPath(vector<vector<char>>& grid);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]
    Output: true
    Explanation: The above diagram shows two possible paths that form valid parentheses strings.
    The first path shown results in the valid parentheses string "()(())".
    The second path shown results in the valid parentheses string "((()))".
    Note that there may be other valid parentheses string paths.

    --- Example 2 ---
    Input: grid = [[")",")"],["(","("]]
    Output: false
    Explanation: The two possible paths form the parentheses strings "))(" and
    ")((". Since neither of them are valid parentheses strings, we return
    false.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100
    grid[i][j] is either '(' or ')'.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    '(' in ASCII is 40, which is an EVEN number
    ')' in ASCII is 41, which is an ODD  number, i.e. (')' & 1) == 1

*/

/* Time  Beats: 91.63% */
/* Space Beats: 79.28% */

/* Time  Complexity: O(ROWS * COLS * (ROWS + COLS)) */
/* Space Complexity: O(ROWS * COLS * (ROWS + COLS)) */
class Solution_Top_Down__Memoization {
private:
    int memo[101][101][201];

public:
    bool hasValidPath(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // (grid[0][0] & 1 == 1)  <==>   grid[0][0] == ')' 
        if (((ROWS + COLS) & 1) == 0 || (grid[0][0] & 1) || (grid[ROWS-1][COLS-1] & 1) == 0)
            return false;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(0, 0, 0, grid);
    }

private:
    bool solve(int row, int col, int balance, vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        balance += 1 - ((grid[row][col] & 1) << 1);

        if (balance < 0 || balance > ROWS - row + COLS - col - 1)
            return false;

        if (row == ROWS-1 && col == COLS-1)
            return balance == 0;

        if (memo[row][col][balance] != -1)
            return memo[row][col][balance];

        bool result = (row < ROWS-1 && solve(row+1, col    , balance, grid)) ||
                      (col < COLS-1 && solve(row    , col+1, balance, grid));

        return memo[row][col][balance] = result;
    }
};
