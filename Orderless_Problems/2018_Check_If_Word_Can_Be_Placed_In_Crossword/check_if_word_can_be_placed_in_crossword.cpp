/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    2018) Check if Word can be place in Crossword
    =============================================

    ============
    Description:
    ============

    You are given an m x n matrix board, representing the current state of a
    crossword puzzle. The crossword contains lowercase English letters (from
    solved words), ' ' to represent any empty cells, and '#' to represent any
    blocked cells.

    A word can be placed horizontally (left to right or right to left) or
    vertically (top to bottom or bottom to top) in the board if:

        + It does not occupy a cell containing the character '#'.

        + The cell each letter is placed in must either be ' ' (empty) or match
          the letter already on the board.

        + There must not be any empty cells ' ' or other lowercase letters
          directly left or right of the word if the word was placed
          horizontally.

        + There must not be any empty cells ' ' or other lowercase letters
          directly above or below the word if the word was placed vertically.

    Given a string word, return true if word can be placed in board, or false
    otherwise.

    ==============================================================================
    FUNCTION: bool placeWordInCrossword(vector<vector<char>>& board, string word);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]], word = "abc"
    Output: true
    Explanation: The word "abc" can be placed as shown above (top to bottom).

    --- Example 2 ---
    Input: board = [[" ", "#", "a"], [" ", "#", "c"], [" ", "#", "a"]], word = "ac"
    Output: false
    Explanation: It is impossible to place the word because there will always
                 be a space/letter above or below it.

    --- Example 3 ---
    Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", " ", "c"]], word = "ca"
    Output: true
    Explanation: The word "ca" can be placed as shown above (right to left). 


    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m * n <= 2 * 10^5
    board[i][j] will be ' ', '#', or a lowercase English letter.
    1 <= word.length <= max(m, n)
    word will contain only lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.12% */
/* Space Beats: 32.72% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word)
    {
        int ROWS = board.size();
        int COLS = board[0].size();

        vector<vector<char>> transposed_board(COLS, vector<char>(ROWS));
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++ col)
            {
                transposed_board[col][row] = board[row][col];
            }
        }

        return match(board, word) || match(transposed_board, word);
    }

private:
    // Returns TRUE if curr_row[first_col...last_col] equals the word or REVERSED word
    bool same(vector<char> &curr_row, int first_col, int last_col, const string &s)
    {
        const int N = s.size();

        if (last_col - first_col + 1 != N)
            return false;

        int i = 0;

        while (i < N && (curr_row[first_col + i] == ' ' || curr_row[first_col + i] == s[i]))
            ++i; // match from left to RIGHT

        if (i == N)
            return true;

        i = 0;
        while (i < N && (curr_row[last_col - i] == ' ' || curr_row[last_col - i] == s[i]))
            ++i; // match from RIGHT to left

        return i == N;
    }

    // Returns TRUE if matrix matches the word HORIZONTALLY
    bool match(vector<vector<char>> &board, const string& word)
    {
        int COLS = board[0].size();

        for (auto& curr_row : board)
        {
            for (int col = 0; col < COLS; )
            {
                while (col < COLS && curr_row[col] == '#')
                    ++col;

                int start = col;

                while (col < COLS && curr_row[col] != '#')
                    ++col;

                if (same(curr_row, start, col - 1, word))
                    return true; // match `row[start..(i-1)]` with `s`.
            }
        }

        return false;
    }
};
