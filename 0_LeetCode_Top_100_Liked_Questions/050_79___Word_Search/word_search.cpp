#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    As the name of the helper function says: We are doing a DFS using
    Backtracking.

    In the description it says that the same letter cell may not be used twice.
    To make sure we don't use it twice, once we find that current cell is the
    one that we need at a given point of searching through the word, we replace
    that letter cell with an empty character, or <Space> character.

    Why? So that whenever we compare <Space> character to a word[index] it
    won't match so we won't be using it twice.

    However if going down that path we find out that this path will not result
    in a complete word, we replace back <Space> character with the character
    we previously replaced, that is the one that was originally there.

*/


/* Time  Beats: 91.61% */
/* Space Beats: 86.30% */


/*
    Time  Complexity: O(M * N * 4^L)

    Where L is the length of the given word. This is because for each cell, the
    algorithm can potentially explore 4 adjacent cells(up, down, left, and
    right) and it explores up to L characters for each starting position.
*/
/*
    Space Complexity: O(L)

    Where L is the length of the given word. This is because the recursive
    stack will have at most L frames for each call to dfs.
*/
class Solution {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    if (dfs(board, word, i, j, 0))
                        return true;
                }
            }
        }

        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>>& board, std::string& word, int row, int col, int index)
    {
        if (index == word.size())
            return true;

        if (row < 0 || row == board.size() || col < 0 || col == board[0].size() || board[row][col] != word[index])
            return false;

        char c = board[row][col];
        board[row][col] = '#'; // So that we don't use the same element twice

        if (dfs(board, word, row-1, col  , index+1)) return true;
        if (dfs(board, word, row+1, col  , index+1)) return true;
        if (dfs(board, word, row  , col-1, index+1)) return true;
        if (dfs(board, word, row  , col+1, index+1)) return true;

        board[row][col] = c; // Return used element so that we can use it again since we haven't found it yet

        return false;
    }
};


void
print_matrix(std::vector<std::vector<char>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << "\n\t\t";

        for (int j = 0; j < matrix[0].size(); j++)
            printf("%2c ", matrix[i][j]);
    }
    std::cout << "\n";
}


int
main()
{
    Solution sol;

    /* Example 1 */
    std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}, {'A', 'D', 'E', 'E'}};
    std::string word = "ABCCED";

    /* Example 2 */
    // std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    // std::string word = "SEE";

    /* Example 3 */
    // std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    // std::string word = "ABCB";

    std::cout << "\n\t===================";
    std::cout << "\n\t=== WORD SEARCH ===";
    std::cout << "\n\t===================\n";


    /* Write Input */
    std::cout << "\n\tBoard:";
    print_matrix(board);
    std::cout << "\n\tWord: \"" << word << "\"\n";


    /* Solution */
    // bool found = sol_mess.exist(board, word);
    bool found = sol.exist(board, word);


    /* Write Output */
    if (found)
        std::cout << "\n\n\tOuput: True\n\n";
    else
        std::cout << "\n\n\tOuput: False\n\n";


    return 0;
}
