#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===============================================
	211) Design Add And Search Words Data Structure
	===============================================

	============
	Description:
	============

	Design a data structure that supports adding new words and finding if a
	string matches any previously added string.

	Implement the WordDictionary class:

		WordDictionary() Initializes the object.

		void addWord(word) Adds word to the data structure, it can be matched
		later.

		bool search(word) Returns true if there is any string in the data
		structure that matches word or false otherwise. word may contain dots
		'.' where dots can be matched with any letter.


	===============================
	CLASS: 
	class WordDictionary {
	public:
		WordDictionary()
		{}

		void addWord(string word)
		{}

		bool search(string word)
		{}

	private:
		struct Trie{
			std::vector<bool> letters(26, false);
			bool valid_word = false;
		};
	};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input
	["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
	[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]

	Output:
	[null,null,null,null,false,true,true,true]

	Explanation
	WordDictionary wordDictionary = new WordDictionary();
	wordDictionary.addWord("bad");
	wordDictionary.addWord("dad");
	wordDictionary.addWord("mad");
	wordDictionary.search("pad"); // return False
	wordDictionary.search("bad"); // return True
	wordDictionary.search(".ad"); // return True
	wordDictionary.search("b.."); // return True




	*** Constraints ***
	1 <= word.length <= 25
	word in addWord consists of lowercase English letters.
	word in search consist of '.' or lowercase English letters.
	There will be at most 2 dots in word for search queries.
	At most 104 calls will be made to addWord and search.

*/

/* Time  Beats: 95.27% */
/* Space Beats: 78.10% */
class WordDictionary {
private:
	struct TrieNode {
	    TrieNode* children[26];
	    bool end_of_a_word;
	
	    TrieNode()
		{
	        end_of_a_word = false;
	        memset(children, NULL, sizeof(children));
	    }
	};

public:
	/* Initialize */
	WordDictionary()
	{
		root = new TrieNode();
	}

	/* Add */
	void addWord(std::string word)
	{
		TrieNode* node = root;

		for (const char& c : word)
		{
			if (node->children[c - 'a'] == nullptr)
				node->children[c - 'a'] = new TrieNode();
			
			node = node->children[c - 'a'];
		}

		node->end_of_a_word = true;
	}

	/* Search */
	bool search(std::string word)
	{
		return backtracking(word, 0, root);
	}

	bool backtracking(std::string& word, int i, TrieNode* curr_node)
	{
		TrieNode* node = curr_node;

		while (i < word.length() && node)
		{
			if (word[i] == '.')
			{
				TrieNode* tmp = node;
				for (int j = 0; j < 26; j++)
				{
					node = tmp->children[j];
					if (backtracking(word, i+1, node))
						return true;
				}
			}
			else
				node = node->children[word[i] - 'a'];

			i++;
		}

		return node && node->end_of_a_word;
	}


private:
	struct TrieNode* root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
