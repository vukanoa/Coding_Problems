#include <iostream>
#include <vector>
#include <set>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	139) Word Break
	===========================

	============
	Description:
	============

	Given a string 's' and a dictionary of strings "wordDict", return true
	if 's' can be segmented a space-separated sequence of one or more
	dictrionary words.

	=====
	Node: The same word in the dictionary may be reused multiple times in the
	===== segmentation.

	=============================================================
	FUNCTION: bool wordBreak(string s, vector<string>& wordDict);
	=============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s = "leetcode", wordDict = ["leet", "code"]
	Output: true

	--- Example 2 ---
	Input:  s = "applepenapple", wordDict = ["apple", "pen"]
	Output: pen

	--- Example 3 ---
	Input:  s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
	Output: false

	*** Constraints ***
	1 <= s.length <= 300
	1 <= wordDict.length <= 1000
	1 <= wordDict[i].length <= 20
	s and wordDict[i] consist of only lowercase English letters.
	All the strings of wordDict are unique.

*/


/*
	------------
	--- IDEA ---
	------------

	--- Brute force(Using recursion) ---

	It starts with an index = 0;
	Then tries to find the substring of a string s that is present in the
	wordDict. As soon as it finds, it calls recursion again but now with:
		i + 1 as a starting index
	Essentially - Do the same thing but for a subproblem.

	Algorithm goes something like this:
		1. "l"
			doesn't exist in wordDict.
		2. "le"
			doesn't exist in wordDict.
		3. "lee"
			doesn't exist in wordDict.
		4. "leet"
			does indeed exist in wordDict => Enter recursion with (4, s, wordDict);
			1. "c"
				doesn't exist in wordDict.
			2. "co"
				doesn't exist in wordDict.
			3. "cod"
				doesn't exist in wordDict.
			4. "code"
				does indeed exist in wordDict => Enter recursion with (8, s, wordDict);
				8 == s.length() => Return true

	At first glance, this will seem more efficient than the Memoization
	solution explained below, but consider this example:

	std::string s = "aaaaaaaaaaaaaaaaaaaab";
	std::vector<std::string> wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa"};

	If you try to simulate this program, you'll find that it will have an
	enormous amount of inefficient, unnecessary attempts in finding if this
	substring is able to be assembled from the words in wordDict.

	This Algorithm causes TLE(Time Limit Exceeded). Now consider this:


	--- Memoization ---

	We can notice that we're doing a lot of unnecessary attepmts, thus we can
	try and remember some of the previous results so that we don't have to
	spend our precious time down the recursion we knew were going to fail.

	So what is the idea?

	Since we're only asked to return if it is possible or not that means
	we only need to say either "true" or "false".

	Therefore, we're going to make a vector of booleans called dp
	(Dynamic Programming).

	So how are we going to utilize this vector? We're going to change the way
	we're traversing the string s. We're going to try and go backwards.
	And any time we get that a certain word is able to be found in the wordDict
	we're going to say:
		If we found that the prefix of this word is possible to be assembled
		then the rest(meaning this word we've just found) is also possible
		to assemble thus the whole word is possible to be assembled => return
		"true"

	We're going to do that essentially for every letter in string s, thus that
	makes it O(n^2), but every time we do that, we're using a function
	"s.substr(index, i - index + 1) which is always going to be O(n), thus,
	the Time Complexity of the whole algorithm is:
		O(n^2 * n) => O(n^3)

	On the fist example, Algorithm works like this:

	String s = "leetcode"
	wordDict["leet", "code"];


	1.
		'e' // Index: 7
	i = 7   "e"

	2.
		'd' // Index: 6
	i = 6   "d"
	i = 7   "de"

	3.
		'o' // Index: 5
	i = 5   "o"
	i = 6   "od"
	i = 7   "ode"

	4.
		'c' //Index: 4       index + 1 ----
	i = 4   "c"                           |
	i = 5   "co"                          |
	i = 6   "cod"                         v
	i = 7   "code" && dp[8] == true => dp[4] = true
						 ^
						 |
		i + 1 ------------


	5. 't' // Index: 3
	i = 3   "t"
	i = 4   "tc"
	i = 5   "tco"
	i = 6   "tcod"
	i = 7   "tcode"

	6. 'e' // Index: 2
	i = 2   "e"
	i = 3   "et"
	i = 4   "etc"
	i = 5   "etco"
	i = 6   "etcod"
	i = 7   "etcode"

	7. 'e' // Index: 1
	i = 1   "e"
	i = 2   "ee"
	i = 3   "eet"
	i = 4   "eetc"
	i = 5   "eetco"
	i = 6   "eetcod"
	i = 7   "eetcode"

	8. 'l' // Index: 0       index + 1 ----
	i = 0   "l"                           |
	i = 1   "le"                          |
	i = 2   "lee"                         v
	i = 3   "leet" && dp[4] == true => dp[0] = true
						 ^
						 |
		i + 1 ------------

	9. Exit the for loop

	10. return dp[0]; // Which in this case is "true".


	dp of index 'i' tells us that the subproblem, string s starting from the
	index 'i', is able to be solved. That's why we're going backwards and that
	is why, at the very end, we're returning "dp[0]".



	TODO:
		1. BFS
		2. DFS + Trie

*/



/*
	Time  Complexity: O(n^2 * n) => O(n^3)

*/
/* Space Complexity: O(n) */
class Solution{
public:
	bool wordBreak(std::string s, std::vector<std::string>& wordDict)
	{
		std::set<std::string> dict(wordDict.begin(), wordDict.end());
		std::vector<bool> dp(s.length() + 1, false);

		dp[s.length()] = true;

		for (int index = s.length() - 1; index >= 0; index--)
		{
			for (int i = index; i < s.length(); i++)
			{
				std::string current_str = s.substr(index, i - index + 1);
				if (dict.find(current_str) != dict.end() && dp[i + 1])
				{
					dp[index] = true;
					break;
				}
			}
		}

		return dp[0];
	}
};


/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
// TLE (Time Limit Exceeded)
class Solution_brute{
public:
	bool wordBreak(std::string s, std::vector<std::string>& wordDict)
	{
		std::set<std::string> dictionary_set(wordDict.begin(), wordDict.end());

		return recursion(0, s, dictionary_set);
	}

	bool recursion(int index, std::string& s, std::set<std::string>& dictionary_set)
	{
		if (index == s.length())
			return true;

		for (int i = index; i < s.length(); i++)
		{
			std::string current_str = s.substr(index, i - index + 1);

			if (dictionary_set.find(current_str) != dictionary_set.end())
			{
				if (recursion(i + 1, s, dictionary_set))
					return true;
			}
		}

		return false;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	std::string s = "leetcode";
	std::vector<std::string> wordDict = {"leet", "code"};

	/* Example 2 */
	// std::string s = "applepenapple";
	// std::vector<std::string> wordDict = {"apple", "pen"};

	/* Example 3 */
	// std::string s = "catsandog";
	// std::vector<std::string> wordDict = {"cats", "dog", "and", "sand", "cat"};

	/* Example 4 */
	// std::string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	// std::vector<std::string> wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};

	/* Example 5 */
	// std::string s = "a";
	// std::vector<std::string> wordDict = {"b"};

	std::cout << "\n\t==================";
	std::cout << "\n\t=== WORD BREAK ===";
	std::cout << "\n\t==================\n\n";

	std::cout << "\tString     = \"";
	for (const char& x : s)
		std::cout << x;
	std::cout << "\"\n";


	bool first = true;
	std::cout << "\n\tDictionary = [";
	for (auto x: wordDict)
	{
		if (!first)
			std::cout << ", ";

		std::cout << "\"";
		std::cout << x;
		std::cout << "\"";
		first = false;
	}
	std::cout << "]\n\n";


	/* Solution */
	bool possible = sol.wordBreak(s, wordDict);

	if (possible)
		std::cout << "\n\tIt is INDEED possible to create a word out of those in the dictionary!\n\n";
	else
		std::cout << "\n\tIt is NOT possible to create a word out of those in the dictionary!\n\n";


	return 0;
}
