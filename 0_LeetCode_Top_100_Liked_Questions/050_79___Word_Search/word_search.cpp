#include <iostream>
#include <vector>
#include <functional> // For Lambda function

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

    It's the same idea as in Solution_Efficient(2nd one down below), but
    unoptimized. It uses another m * n matrix named "flags".

    However, it's a bit easier for reading in my opinion, so I'll leave it.

*/


/* Time  Beats: 51.81% */
/* Space Beats: 85.30% */

/*
    Time  Complexity: O(M * N * 4^L)

    The Time Complexity of the "backtracking" function is O(4^L), where L is
    the length of the input "word". This is because for each call to
    "backtracking", there are up to four recursive calls (up, right, down,
    left), and this recursion depth can go up to L.  Therefore, the Time
    Complexity of the "exist" function is O(M * N * 4^L).

    M - Number of Rows    in the Board.
    N - Number of Columns in the Board.
*/
/*
    Space Complexity: max( O(L), O(M * N) )

    Since the maximum depth of recursion is L, and each recursion depth
    requires O(1) extra space. Additionally, the "flags" vector has a Space
    Complexity of O(M * N).

    M - Number of Rows    in the Board.
    N - Number of Columns in the Board.
*/
class Solution_Messy{
private:
    bool backtracking(std::vector<std::vector<char>>& board, std::string word,
                      std::vector<std::vector<bool>>& flags, std::string current,
                      int i, int j, int w)
    {
        int m = board.size();
        int n = board[0].size();

        if (current == word)
            return true;

        for (int x = 0; x < 4; x++)
        {
            switch(x)
            {
                case 0:
                    if (i-1 >= 0 && board[i-1][j] == word[w] && flags[i-1][j] == true)
                    {
                        flags[i][j] = false;
                        if (backtracking(board, word, flags, current + word[w], i-1, j, w+1))
                            return true;

                        flags[i][j] = true;
                    }
                    break;

                case 1:
                    if (j + 1 < n && board[i][j+1] == word[w] && flags[i][j+1] == true)
                    {
                        flags[i][j] = false;
                        if (backtracking(board, word, flags, current + word[w], i, j+1, w+1))
                            return true;

                        flags[i][j] = true;
                    }
                    break;

                case 2:
                    if (i + 1 < m && board[i+1][j] == word[w] && flags[i+1][j] == true)
                    {
                        flags[i][j] = false;
                        if (backtracking(board, word, flags, current + word[w], i+1, j, w+1))
                            return true;

                        flags[i][j] = true;
                    }
                    break;

                case 3:
                    if (j - 1 >= 0 && board[i][j - 1] == word[w] && flags[i][j-1] == true)
                    {
                        flags[i][j] = false;
                        if (backtracking(board, word, flags, current + word[w], i, j-1, w+1))
                            return true;

                        flags[i][j] = true;
                    }
                    break;
            }
        }

        return false;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        int m = board.size();
        int n = board[0].size();

        std::vector<std::vector<bool>> flags(m, std::vector<bool>(n, true));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    std::string str = "";
                    str.push_back(board[i][j]);

                    if (backtracking(board, word, flags, str, i, j, 1))
                        return true;

                    str.pop_back();
                }
            }
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same Solution as the below one, but written in an inefficient way. It's
    good to see the difference, so here it is.

*/

/* Time  Beats: 5.02% */
/* Space Beats: 5.04% */

/*
    Time  Complexity: O(M * N * 4^L)

    The Time Complexity of the "backtracking" function is O(4^L), where L is
    the length of the input "word". This is because for each call to
    "backtracking", there are up to four recursive calls (up, right, down,
    left), and this recursion depth can go up to L.  Therefore, the Time
    Complexity of the "exist" function is O(M * N * 4^L).

    M - Number of Rows    in the Board.
    N - Number of Columns in the Board.
*/
/*
    Space Complexity: max( O(L), O(M * N) )

    Since the maximum depth of recursion is L, and each recursion depth
    requires O(1) extra space. Additionally, the "flags" vector has a Space
    Complexity of O(M * N).

    M - Number of Rows    in the Board.
    N - Number of Columns in the Board.
*/
class Solution_Inefficient {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        int m = board.size();
        int n = board[0].size();

        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (board[row][col] == word[0]) // If first letter matches
                {
                    char letter = word[0];
                    board[row][col] = '#';

                    std::string curr_str = "";
                    if (backtracking(board, word, row, col, curr_str + word[0], 1))
                        return true;

                    board[row][col] = letter;
                }
            }
        }

        return false;
    }

private:
    bool backtracking(std::vector<std::vector<char>>& board, std::string& word, int row, int col, std::string curr_str, int i)
    {
        if (curr_str == word)
            return true;

        int m = board.size();
        int n = board[0].size();

        // Clockwise
        // Up, Right, Down, Left
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        for (const auto& dir : directions)
        {
            if (row + dir.first  < 0 || row + dir.first  >= m || col + dir.second < 0 || col + dir.second >= n)
                continue;

            if (board[row + dir.first][col + dir.second] == word[i])
            {
                char letter = word[i];
                board[row + dir.first][col + dir.second] = '#';

                if (backtracking(board, word, row + dir.first, col + dir.second, curr_str + word[i], i + 1))
                    return true;

                board[row + dir.first][col + dir.second] = letter;
            }
        }

        return false;
    }
};



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
class Solution_Efficient {
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




/*
    ------------
    --- IDEA ---
    ------------

    It's the same as the one above, however this one uses a Lambda Function.
    I wanted to show that as well.

*/

/* Time  Beats: 49.50% */
/* Space Beats: 23.98% */

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
class Solution_Efficient_Lambda {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        int m = board.size();
        int n = board[0].size();

        std::function<bool(int, int, int)> dfs;

        dfs = [&](int i, int j, int w)
        {
            if (w == word.length())
                return true;

            if (i < 0 || j < 0 || i == m || j == n || board[i][j] != word[w])
                return false;

            char letter = board[i][j]; // So that we don't use the same element twice
            board[i][j] = '#';

            if (dfs(i-1, j  , w+1)) return true;
            if (dfs(i+1, j  , w+1)) return true;
            if (dfs(i  , j-1, w+1)) return true;
            if (dfs(i  , j+1, w+1)) return true;

            board[i][j] = letter; // Return used element so that we can use it again since we haven't found it yet

            return false;
        };

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dfs(i, j, 0))
                    return true;
            }
        }

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
    Solution_Messy sol_mess;
    Solution_Efficient sol_eff;

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
    bool found = sol_eff.exist(board, word);


    /* Write Output */
    if (found)
        std::cout << "\n\n\tOuput: True\n\n";
    else
        std::cout << "\n\n\tOuput: False\n\n";


    return 0;
}
