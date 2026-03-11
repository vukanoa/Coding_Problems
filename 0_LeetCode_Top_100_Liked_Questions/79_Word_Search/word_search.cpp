/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    79) Word Search
    ===========================

    ============
    Description:
    ============

    Given an "m x n" grid of characters "board" and a string "word", return
    "true" if "word" exists in the grid.

    The word can be constructed from letters of sequentially adjacent cells,
    where adjacent cells are horizontally or vertically neighboring. The same
    letter cell may not be used more than once.

    ===============================================================
    FUNCTION: bool exist(vector<vector<char>>& board, string word);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"], ["A", "D", "E", "E"]], word = "ABCCED"
    Output: true

    --- Example 2 ---
    Input:  board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], word = "SEE"
    Output: true

    --- Example 3 ---
    Input:  board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]], word = "ABCB"
    Output: false


    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    "board" and "word" consists of only lowercase and uppercase English letters

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    As the name of the helper function says: We are doing a DFS using
    Backtracking.

    In the description it says that the same letter cell may not be used twice.
    To make sure we don't use it twice, once we find that current cell is the
    one that we need at a given point of searching through the word, we replace
    that letter cell with a '#' character(It can be ANY character that is NOT
    lowercase or uppercase English character)

    Why are we doing that?
    So that whenever we compare '#' character to a word[index] it
    won't match so we won't be using it twice.

    However if going down that path we find out that this path will not result
    in a complete word, we replace back '#' character with the original
    character we previously replaced, the one that was there at the beginning.

    It's VERY important that we're using logical OR when trying 4 different
    paths(Signing Cross way).
    
    Why?
    Because if ANY of those returns "true", we'll skip the remaining calls.

    However, it we just prunned the search by returning "true" immediately,
    then we wouldn't be returning the original character.

    And usually speaking, it's not permissible to change the Input, especially
    when it's passed as a reference.

    Therefore, we really must be careful with this and we need to make sure
    that the original characters are properly restored.

*/

/* Time  Beats: 69.49% */
/* Space Beats: 99.29% */

/* Time  Complexity: O(ROWS * COLS * 4^WORD_SIZE) */
/* Space Complexity: O(ROWS * COLS * 4^WORD_SIZE) */
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        const int WORD_SIZE = word.size();

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] == word[0])
                {
                    if (dfs(row, col, board, word, 0))
                        return true;
                }
            }
        }

        return false;
    }

private:
    bool dfs(int row, int col, vector<vector<char>>& board, string& word, int idx)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        const int WORD_SIZE = word.size();
        if (idx >= WORD_SIZE)
            return true;

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return false;

        if (board[row][col] != word[idx])
            return false;

        char original_chr = board[row][col];
        board[row][col] = '#';

        bool is_found = dfs(row-1, col  , board, word, idx + 1) ||
                        dfs(row+1, col  , board, word, idx + 1) ||
                        dfs(row  , col-1, board, word, idx + 1) ||
                        dfs(row  , col+1, board, word, idx + 1);

        board[row][col] = original_chr;

        return is_found;
    }
};
