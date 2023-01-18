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


/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^3) */
// TLE (Time Limit Exceeded)
class Solution{
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
