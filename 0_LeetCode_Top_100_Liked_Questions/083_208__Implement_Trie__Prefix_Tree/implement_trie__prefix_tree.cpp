#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	==================================
	208) Implement Trie (Prefix Tree);
	==================================

	============
	Description:
	============

	A trie (pronounced as "try") or prefix tree is a tree data structure used
	to efficiently store and retrieve keys in a dataset of strings. There are
	various applications od this data structure, such as autocomplete and
	spellchecker.

	Implements the Trie class:
		- "Trie()" Initializes the trie object.

		- "void insert(String word)" Inserts the string "word" into the trie.

		- "boolean search(String word)" Returns true if the string "word" is in
		  the trie (i. e., was inserted before), and false otherwise.

		- "boolean startsWith(String prefix)" Returns true if there is a
		  previously inserted string "word" that has the prefix "prefix", and
		  false otherwise.

	===============================
	CLASS:
	class Trie{
		Trie()
		{

		}

		void insert(std::string word)
		{

		}

		bool search(std::string word)
		{

		}

		bool startsWith(std::string prefix)
		{

		}
	};
	===============================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:
	["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
	[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
	Output: [null, null, true, false, true, null, true]

	Explanation
	Trie *trie = new Trie();
	trie.insert("apple");
	trie.search("apple");    // return true
	trie.search("app");      // return false
	trie.startsWith("app");  // return true
	trie.insert("app");
	trie.search("app");      // return true

	*** Constraints ***
	1 <= word.length, prefix.length <= 200
	word and prefix consist only of lowercase English letters
	At most 3 * 10^4 in total will be made to insert, search, and startsWith.

*/


/*
	------------
	--- IDEA ---
	------------

	Applications

	Trie (we pronounce "try") or prefix tree is a tree data structure, which is
	used for retrieval of a key in a dataset of strings. There are various
	applications of this very efficient data structure such as:
		1. Autocomplete
		2. Spell Checker
		3. IP routing (Longest prefix matching)
		4. T9 predictive text
		5. Solving word games

	There are several other data structures, like balanced trees and hash
	tables, which give us the possibility to search for a word in a dataset of
	strings. Then why do we need trie? Although hash table has O(1) time
	complexity for looking for a key, it is not efficient in the following
	operations:
		- Finding all keys with a common prefix.
		- Enumerating a dataset of strings in lexicographical order.

	Another reason why trie outperforms hash table, is that as has table
	increases in size, there are lots of hash collisions and the search time
	complexity could deteriorate to O(n), where n is the number of keys
	inserted. Trie could use less space compared to hash Table when storing
	many keys with the same prefix. In this case using trie has only O(m) time
	complexity, where "m" is the key length. Searching for a key in a balanced
	tree costs O(m * logn) time complexity.


	Trie node structure:
	Trie is a rooted tree. Its nodes have the following fields:
		- Maximum of "R" links to its children, where each link corresponds to
		  one of "R" character values from dataset alphabet. In this article
		  we assume that "R" is 26, the number of loewrcase latin letters.

		- Boolean field which specifies whether the node corresponds to the end
		  of the key, or is just a key prefix.

	Root:
		isEnd: false
		a b c d e f g h i j k l m n o p q r s t u v w x y z
		                      #
						|
						| link
						v
		isEnd: false
		a b c d e f g h i j k l m n o p q r s t u v w x y z
		        #
						|
						|
						v
		isEnd: false
		a b c d e f g h i j k l m n o p q r s t u v w x y z
		        #
						|
						|
						v
		isEnd: false
		a b c d e f g h i j k l m n o p q r s t u v w x y z
		                                      #
						|
						|
						v
		isEnd: true
		a b c d e f g h i j k l m n o p q r s t u v w x y z

	============
	=== CODE ===
	============

	class TrieNode {
	private:
		const int R = 26;
		bool is_end;

	public:
		TrieNode()
		{
			// R links to node children
			std::vector<struct TrieNode*> links;
		}

		bool contains_key(char ch)
		{
			return links[ch - 'a'] != nullptr;
		}

		struct TrieNode* get_node(char ch)
		{
			return links[ch - 'a'];
		}

		void put_node(char ch, TrieNode* node)
		{
			links[ch - 'a'] = node;
		}

		void set_end()
		{
			is_end = true;
		}

		bool is_end()
		{
			return is_end();
		}
	}

	Two of the most common operations in a trie are insertion of a key and
	search for a key.

	## Insertion of a key to a trie.

	We insert a key by searching into the trie. We start from the root and
	search a link, which corresponds to the first key character. There are two
	cases:
		- A links exists. Then we move down the tree following the link to the
		  next child level. The algorithm continues with searching for the next
		  key character.

		- A link does not eist. Then we create a new node and link it with the
		  parent's link matching the curent key character. We repeat this step
		  until we encounter the last character of the key, then we mark the
		  current node as an end node and the algorithm finishes.

	Inserting "le" into the Trie:

	root
     1
      \'l'
       2
        \'e'
         3 (end of key "le")


	Inserting "leet" into the Trie:

	root
     1
      \'l'
       2
        \'e'
         3 (end of key "le")
          \'e'
           4
            \'t'
             5 (end of key "leet")



	Inserting "code" into the Trie:
                        root
                          1
                      'c'/ \'l'
                        6   2
                    'o'/     \'e'
					  7       3 (end of key "le")
				  'd'/         \'e'
				    8           4
				'e'/             \'t'
                  9 (end "code")  5 (end "leet")

	This was built from dataset {"le", "leet", "code"}

	============
	=== CODE ===
	============

	class Trie{
	private:
		struct TrieNode* root;

	public:
		Trie()
		{
			root = new TrieNode();
		}

		// Inserts a word into the trie
		void insert(std::string word)
		{
			struct TrieNode* node = root;

			for (int i = 0; i < word.length(); i++)
			{
				char curr_char = word[i];
				if (!node.contains_key(current_char))
					node->put(current_char, new TrieNode());

				node = node->get_node(current_char);
			}

			node->set_end();
		}
	};

	** Complexity Analysis **
	- Time Complexity: O(m), where m is the key length.
	In each iteration of the algorithm, we either examine or create a node in
	the trie till we reach the end of the key. This takes only "m" operations.

	- Space Complexity: O(m)
	In the worst case newly inserted key doesn't share a prefix with the keys
	already inserted in the trie. We have to add "m" new nodes, which takes us
	O(m) space.


	## Search for a key in a trie.

	Each key is represented in the trie as a path from the root to the internal
	node or leaf.
	We start from the root with the first key character. We examine the current
	node for a link to the key character. There are two cases:
		1. A link exist. We move to the next node in hte path following this
		   link, and proceed searching for the next key character.

		2. A link does not exist. IF there are no available key characters and
		   current node is marked as "isEnd" we return true. Otherwise there
		   are possible two cases in each of them we return false:
		       - There are key characters left, but it is impossible to follow
			     the key path in the trie, and the key is missing.

		       - No key characters left, but current node is not marked as
			     "isEnd". Therefore the search key is only a prefix of another
				 key in the trie.


		Search for key "leet" in the Trie

                        root
                          1
                      'c'/ \'l'        <---------------- 'l'
                        6   2
                    'o'/     \'e'      <---------------- 'e'
                      7       3 (end of key "le")
                  'd'/         \'e'    <---------------- 'e'
                    8           4
                'e'/             \'t'  <---------------- 't'
                  9(end "code")   5(end "leet") <----- KEY FOUND

           Searching for a key in a Trie from dataset {le, leet, code}

	============
	=== CODE ===
	============

	class Trie{
	private:
		struct TrieNode* search_prefix(std::string word)
		{
			structNode* node = root;

			for (int i = 0; i < word.length(); i++)
			{
				char curr_letter = word[i];
				if (node->contains_key(curr_letter))
					node = node->get_node(curr_letter);
				else
					return nullptr;
			}

			return node;
		}

	public:
		// Returns if the word is in the trie
		boolean search(std::string word)
		{
			struct TrieNode* node = search_prefix(word);

			return node != nullptr && node->is_end();
		}
	};

	** Complexity Analysis **
		- Time complexity: O(m) In each step of the algorithm we search for
		  the next key character. In the worst case the algorithm performs "m"
		  operations.

		- Space complexity: O(1)



	## Search for a key prefix in a trie

	The approach is very similar to the one we used for searching a key in a
	trie. We traverse the trie from the root, till there are no characters left
	in key prefix or it is impossible to continue the path in the trie with the
	current key character. The only difference with the mentioned above "search
	for a key" algorithm is that when we come to an end of the kye prefix, we
	always return true. We don't need to consider the "is_end" mark of the
	current trie node, because we are searching for a prefix of a key, not for
	a whole key.

			Searching for "co" in the Trie

                         root
                          1
    c ----------->    'c'/ \'l'
                        6   2
    o ----------->  'o'/     \'e'
	PREFIX FOUND      7       3 (end of key "le")
                  'd'/         \'e'
                    8           4
                'e'/             \'t'
                  9 (end "code")  5 (end "leet")

	Searching for a prefix in a Trie from dataset {le, leet, code};

	============
	=== CODE ===
	============

	class Trie{
	public:
		bool start_with(std::string prefix)
		{
			struct TrieNode* node = search_prefix(prefix);

			return node != nullptr;
		}
	};


	** Complexity Analysis **
		- Time complexity: O(m)
		- Space complexity: O(1)


	Practice Problems
	Here are some wonderful problems for you to practice which uses the Trie
	data structure.

	1. Add and Search Word - Data structure design
		- Pretty much a direct application of Trie.

	2. Word Search II
		- Similar to Boggle.

*/

/* Time  Beats: 95.61% */
/* Space Beats: 27.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Trie {
public:

	struct TrieNode{
		TrieNode* child[26];
		bool is_leaf_node;
	};

	TrieNode* root = NULL;

	TrieNode* get_trie_node()
	{
		TrieNode* node = new TrieNode();
		for (int i = 0; i < 26; i++)
			node->child[i] = nullptr;

		node->is_leaf_node = false;

		return node;
	}


	void insert(std::string word)
	{
		// Already inserted then return
		if (search(word))
			return;

		// If inserting for first time then create root node first
		if (!root)
			root = get_trie_node();

		TrieNode* node = root;

		// Iterate over all characters of the word
		for (int i = 0; i <word.length(); i++)
		{
			int idx = word[i] - 'a';
			if (!node->child[idx])
				node->child[idx] = get_trie_node();

			node = node->child[idx];
		}

		node->is_leaf_node = true;
	}


	bool search(std::string word)
	{
		TrieNode* node = root;
		if (!root)
		{
			// std::cout << "root is null" << "\n";
			return false;
		}

		for(int i = 0; i < word.length() && node; i++)
		{
			int idx = word[i] - 'a';
			node = node->child[idx];
		}

		if (node)
			return node->is_leaf_node;

		return false;
	}


	bool startsWith(std::string prefix)
	{
		TrieNode* node = root;

		if (!root)
			return false;

		for (int i = 0; (i < prefix.length()) && node; i++)
		{
			int idx = prefix[i] - 'a';
			node = node->child[idx];
		}

		return (node != nullptr);
	}
};




/* Time  Beats: 68.26% */
/* Space Beats: 23.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Trie_Cleaner_Impl {
public:

	Trie()
	{
		root = new Node();
	}

	void insert(std::string word)
	{
		if (search(word))
			return;

		Node* tmp = root;

		for (int i = 0; i < word.length(); i++)
		{
			if (tmp->letters[word[i] - 'a'] == nullptr)
				tmp->letters[word[i] - 'a'] = new Node();

			tmp = tmp->letters[word[i] - 'a'];
		}

		tmp->end = true;
	}


	bool search(std::string word)
	{
		Node* tmp = root;

		for (int i = 0; i < word.length(); i++)
		{
			if (tmp->letters[word[i] - 'a'] == nullptr)
				return false;

			tmp = tmp->letters[word[i] - 'a'];
		}

		return tmp->end;
	}


	bool startsWith(std::string prefix)
	{
		Node* tmp = root;

		for (int i = 0; i < prefix.length(); i++)
		{
			if (tmp->letters[prefix[i] - 'a'] == nullptr)
				return false;

			tmp = tmp->letters[prefix[i] - 'a'];
		}

		return true;
	}

private:
	struct Node{
		std::vector<Node*> letters;
		bool end = false;

		Node() : letters(26, nullptr) {}
	};

	struct Node* root = nullptr;
};


int
main()
{
	std::cout << "\n\t==================================";
	std::cout << "\n\t=== IMPLEMENT TRIE PREFIX NODE ===";
	std::cout << "\n\t==================================\n";

	/* Example 1 */
	/*

	["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
	[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
	Output: [null, null, true, false, true, null, true]

	Explanation
	Trie *trie = new Trie();
	trie.insert("apple");
	trie.search("apple");    // return true
	trie.search("app");      // return false
	trie.startsWith("app");  // return true
	trie.insert("app");
	trie.search("app");      // return true

	*/
	Trie *trie = new Trie();
	std::cout << "\n\tInsert \"apple\"\n";
	trie->insert ("apple");

	if (trie->search("apple"))
		std::cout << "\n\tWord \"apple\" does INDEED exist!\n";
	else
		std::cout << "\n\tWord \"apple\" does NOT exist!\n";

	if (trie->search("app"))
		std::cout << "\n\tWord \"app\" does INDEED exist!\n";
	else
		std::cout << "\n\tWord \"app\" does NOT exist!\n";

	if (trie->startsWith("app"))
		std::cout << "\n\tPrefix \"app\" does INDEED exist!\n";
	else
		std::cout << "\n\tPrefix \"app\" does NOT exist!\n";

	std::cout << "\n\tInsert \"app\"\n";
	trie->insert("app");

	if (trie->search("app"))
		std::cout << "\n\tWord \"app\" does INDEED exist!\n";
	else
		std::cout << "\n\tWord \"app\" does NOT exist!\n";

	std::cout << "\n\n";

	return 0;
}
