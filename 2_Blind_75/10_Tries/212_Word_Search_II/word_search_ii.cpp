/*
    ============
    === HARD ===
    ============

    ===========================
    212) Word Search II
    ===========================

    ============
    Description:
    ============

    Given an m x n board of characters and a list of strings words, return all
    words on the board.

    Each word must be constructed from letters of sequentially adjacent cells,
    where adjacent cells are horizontally or vertically neighboring. The same
    letter cell may not be used more than once in a word.

    =======================================================================================
    FUNCTION: vector<string> findWords(vector<vector<char>>& board, vector<string>& words); 
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+-----+
    |  o  |  a  |  a  |  n  |
    +-----+-----+-----+-----+
    |  e  |  t  |  a  |  e  |
    +-----+-----+-----+-----+
    |  i  |  h  |  k  |  r  |
    +-----+-----+-----+-----+
    |  i  |  f  |  l  |  v  |
    +-----+-----+-----+-----+

    Input: board = [["o","a","a","n"],
                    ["e","t","a","e"],
                    ["i","h","k","r"],
                    ["i","f","l","v"]],

           words = ["oath","pea","eat","rain"]


    Output: ["eat","oath"]





    --- Example 2 ---
    +-----+-----+
    |  a  |  b  |
    +-----+-----+
    |  c  |  d  |
    +-----+-----+

    Input: board = [["a","b"],
                    ["c","d"]],
           
           words = ["abcb"]


    Output: []




    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m, n <= 12
    board[i][j] is a lowercase English letter.
    1 <= words.length <= 3 * 10^4
    1 <= words[i].length <= 10
    words[i] consists of lowercase English letters.
    All the strings of words are unique.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    While doing a DFS traversal on the board, we can, simultaneously go through
    the Trie data structure that we've constructed from the words vector.

    Then we ask a question:"Does the current PREFIX exists in our wordlist?"


    Let's have an example wordlist:

        words = ["app", "ape", "ace", "blue"]

    For this wordlist, our Prefix Tree(aka "Trie") would look like this:

                          Prefix Tree(aka "Trie")
                               /    |
                              a     b
                            / |     |
                           p  c     l
                         / |  |     |
                        p  e  e     u
                                    |
                                    e
        Board
    +-----+-----+
    |  a  |  c  |
    +-----+-----+
    |  p  |  e  |
    +-----+-----+

    Now we start with letter 'a' at board[0][0] as the starting letter and we
    are checking if there are any letter that are starting with letter 'a'.
    How are we checking that?

    In the Trie, we have a field named "children", which consists of 26 letters
    which are nullptr at the beginning. Once a word with a certain letter that
    previously was nullptr start with it, insert its characters level by level
    in the appropriate level.

    This way, we can check if there are any words in our wordlist that begin
    with any letter and not only that, but we can achieve such functionality in
    O(1) Time Complexity.

    We only have to check if root->children[letter_we_are_searching_for] is
    nullptr.

    If it is then that means there is no word that starts with that letter.
    Otherwise, there is.

    So, in this case, we start with letter 'a' in board[0][0] and we do a DFS
    on it. Each time we're checking if a certain PREFIX exists in the trie.
    It's essentially as if we're doing a subproblem each time. That's why we
    always pass the "Trie level" of the letter we're on.

    What do I mean by this?

    Original Trie:

                          Prefix Tree(aka "Trie") // Root Level(0th level)
                               /    |
                              a     b
                            / |     |
                           p  c     l
                         / |  |     |
                        p  e  e     u
                                    |
                                    e
    
    Once we start with letter 'a':

                          Prefix Tree(aka "Trie") // 1st level
                            / | 
                           p  c 
                         / |  | 
                        p  e  e 
                                
    Since we're ON the letter 'a', we can only see the "subtrees" from it.
    Therefore, we only see letters 'p' and 'c'.
    Meaning that in our wordlist, only letters 'p' and 'c' come afer letter 'a'
    which is true since our wordlist looks like this:

        ["app", "ape", "ace", "blue"]

    Once we're on the letter 'a', we can only have either letter 'p' or 'c'.

    We do that for every letter on the board as a starting letter.

    That way the Time Complexity is highly optimized.

    From:
        O(W * ROWS * COLS * 4^L)
    to
        O(ROWS * COLS * 4 * 3^(L - 1) + S)

    L is the maximum length of ANY word.
    S is the sum of lengths of ALL the lengths of all the words.

*/

/* Time  Beats: 74.13% */
/* Space Beats: 70.06% */

/* Time  Complexity: O(ROWS * COLS * 4 * 3^(L - 1) + S) */
/* Space Complexity: O(S)                               */
class Solution {
private:
    struct TrieNode {
        TrieNode* letter[26] = {nullptr};
        string    full_word;

        TrieNode()
            : full_word("")
        {}
    };

    TrieNode* root = nullptr;

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        vector<string> results;

        /* Insert all words in Trie */
        for (const string& word : words)
            insert(word);

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                backtracking(row, col, root, results, board);
            }
        }

        return results;
    }

private:
    void insert(const string& word)
    {
        if ( ! root)
            root = new TrieNode();

        TrieNode* node = root;
        for (const char& chr : word)
        {
            if ( ! node->letter[chr - 'a'])
                node->letter[chr - 'a'] = new TrieNode();

            node = node->letter[chr - 'a'];
        }
        node->full_word = word;
    }

    void backtracking(int row, int col, TrieNode* node, vector<string>& results, vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        char chr = board[row][col];
        if (chr == '#')
            return;

        if ( ! node->letter[chr - 'a'])
            return;

        node = node->letter[chr - 'a'];

        if ( ! node->full_word.empty())
        {
            results.push_back(node->full_word);
            node->full_word = ""; // To avoid pushing same word multiple times
        }

        board[row][col] = '#';

        backtracking(row - 1, col    , node, results, board);
        backtracking(row + 1, col    , node, results, board);
        backtracking(row    , col - 1, node, results, board);
        backtracking(row    , col + 1, node, results, board);

        board[row][col] = chr;
    }
};
