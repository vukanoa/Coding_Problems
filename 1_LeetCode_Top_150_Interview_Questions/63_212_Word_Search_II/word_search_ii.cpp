#include <iostream>
#include <vector>

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

/* Time  Complexity: TLE */

/* Time  Complexity: O(wods.length * m * n) */
/* Space Complexity: O(words[i].length) */
class Solution_TLE_Solution {
public:
	std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words)
	{
		std::vector<std::string> results;
		int m = board.size();
		int n = board[0].size();

		for (int i = 0; i < words.size(); i++)
		{
			for (int row = 0; row < m; row++)
			{
				for (int col = 0; col < n; col++)
				{
					if (words[i][0] == board[row][col])
					{
						char starting_letter = words[i][0];
						board[row][col] = '#';

						std::string current;
						current += starting_letter;

						bool found;
						found = dfs(board, words, current, results, words[i], row, col, 1);

						board[row][col] = starting_letter;

		 				if (found)
						{
							// Breaks out of 2 for loops
							row = col = 32000;
							break;
						}
					}
				}
			}
		}

		return results;
	}

private:
	bool dfs(std::vector<std::vector<char>>& board,
	         std::vector<std::string>& words,
			 std::string current,
			 std::vector<std::string>& results,
			 std::string& search_word,
			 int row,
			 int col,
			 int word_pos)
	{
		if (word_pos >= search_word.size())
		{
			results.push_back(current);
			return true;
		}

		// Up, Right, Down, Up
		std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

		for (const auto& dir : directions) // Constant time
		{
			// Out of bounds
			if (row + dir.first < 0 || row + dir.first >= board.size() || col + dir.second < 0 || col + dir.second >= board[0].size())
				continue;
			
			if (board[row + dir.first][col + dir.second] == search_word[word_pos])
			{
				char previously_on_board = board[row + dir.first][col + dir.second];
				board[row + dir.first][col + dir.second] = '#';
				current += previously_on_board;

				bool found = dfs(board, words, current, results, search_word, row + dir.first, col + dir.second, word_pos + 1);

				// If found, we still have to give back the "previously_on_board" character;
				board[row + dir.first][col + dir.second] = previously_on_board;

				if (found)
					return true;
				else
					current.pop_back();
			}
		}

		return false;
	}
};




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 95.83% */
/* Space Beats: 69.66% */

class Solution {
	struct TrieNode {
	TrieNode *children[26];
	string word;

	TrieNode() : word("")
	{
		for (int i = 0; i < 26; i++)
			children[i] = nullptr;
	}
};

public:
	std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words)
	{
		TrieNode *root = buildTrie(words);
		std::vector<std::string> result;

		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[0].size(); j++)
			{
				dfs(board, i, j, root, result);
			}
		}

			return result;
	}

	/* Inserts a word into the Trie */
	TrieNode *buildTrie(std::vector<std::string>& words)
	{
		TrieNode *root = new TrieNode();

		for (int j = 0; j < words.size(); j++)
		{
			std::string word = words[j];
			TrieNode *curr = root;

			for (int i = 0; i < word.length(); i++) 
			{
				char c = word[i] - 'a';

				if (curr->children[c] == nullptr)
					curr->children[c] = new TrieNode();

				curr = curr->children[c];
			}

			curr->word = word;
		}

		return root;
	}

	void dfs(std::vector<std::vector<char>>& board, int i, int j, TrieNode *p, std::vector<std::string>& result)
	{
		char c = board[i][j];

		if (c == '#' || !p->children[c - 'a'])
			return;

		p = p->children[c - 'a'];

		if (p->word.size() > 0)
		{
			result.push_back(p->word);
			p->word = "";
		}

		int m = board.size();
		int n = board[0].size();

		board[i][j] = '#';
		if (i > 0)     dfs(board, i - 1, j    , p, result);
		if (j > 0)     dfs(board, i    , j - 1, p, result);
		if (i < m - 1) dfs(board, i + 1, j    , p, result);
		if (j < n - 1) dfs(board, i    , j + 1, p, result);

		board[i][j] = c;
	}
};
