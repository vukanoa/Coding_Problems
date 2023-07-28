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


/* Time  Complexity: TLE. Used to pass all tests prior to June 2022. */

/* Time  Complexity: O(words.length * m * n * 4^words.length) */
/* Space Complexity: O(words.length + m * n) */
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

	Looking at the previous TLE Solution we can see that we are, sort of, doing
	repetitive work. It seems as though we can optimize it.

	In the above Solution, we're going through each word and for each word,
	we're going to try each of the letter in the board(unless, of course, we
	happen to find the whole word starting from a position before the last one
	in the board, in that case, we won't check the remaining letter on the
	board for that specific word, since we have already found it).

	However, thinking about it, we can see that it would be more optimal, if we
	could, somehow, iterate through the board only once, and for each letter
	we're on we can ask if that is the starting letter and then if it is, we
	consider it as we do a dfs on that letter. And then every subsequent letter
	we "take" while doing this dfs we can ask if that prefix exists in our
	wordlist.

	Since we have asked a question:"Does that PREFIX exists in our wordlist?"
	that highly suggests that, to solve this problem optimally, we must use a
	Trie as a data structure.

	Let's have an example wordlist:["app", "ape", "ace", "blue"]

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
		O(words.length * m * n * 4^words.length)
	to
		O(m * n * 4^words.length)

*/

/* Time  Beats: 95.83% */
/* Space Beats: 69.66% */

/* Time  Complexity: O(m * n * 4^words.length) */
/* Space Complexity: O(words.length + m * n) */
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

		for (int i = 0; i < words.size(); i++)
		{
			std::string word = words[i];
			TrieNode *curr = root;

			for (int j = 0; j < word.length(); j++) 
			{
				int letter_index = word[j] - 'a';

				if (curr->children[letter_index] == nullptr)
					curr->children[letter_index] = new TrieNode();

				curr = curr->children[letter_index];
			}

			curr->word = word;
		}

		return root;
	}

	void dfs(std::vector<std::vector<char>>& board, int i, int j, TrieNode *trie, std::vector<std::string>& result)
	{
		char c = board[i][j];

		if (c == '#' || !trie->children[c - 'a'])
			return;

		trie = trie->children[c - 'a'];

		if (trie->word.size() > 0)
		{
			result.push_back(trie->word);
			trie->word = "";
		}

		int m = board.size();
		int n = board[0].size();

		board[i][j] = '#';

		if (i > 0)     dfs(board, i - 1, j    , trie, result); // Up
		if (j > 0)     dfs(board, i    , j - 1, trie, result); // Left
		if (i < m - 1) dfs(board, i + 1, j    , trie, result); // Down
		if (j < n - 1) dfs(board, i    , j + 1, trie, result); // Right

		board[i][j] = c;
	}
};
