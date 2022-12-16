#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	49) Group Anagrams
	===========================

	============
	Description:
	============

	Given an array of strings 'strs', group the anagrams together. You can
	return the answer in any order.

	An Anagram is a wrod or phrase formed by rearranging the letters of a
	different word or phrase, typically using all the original letters exactly
	once.

	=====================================================================
	FUNCTION: vector<vector<string>> groupAnagrams(vector<string>& strs);
	=====================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
	Output: [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]

	--- Example 2 ---
	Input:  strs = [""]
	Output: [[""]]

	--- Example 3 ---
	Input:  strs = ["a"]
	Output: [["a"]]

	*** Constraints ***
	1 <= strs.length <= 10^4
	0 <= strs[i].length <= 100
	strs[i] consists of lowercase English letters

*/


/*
	------------
	--- IDEA ---
	------------

	Two strings are anagrams if and only if their sorted strings are equal.

	We have a Hash Map with lexicographically sorted string as a "key" and
	original strings(in a vector) as "values"
*/


/* Time  Complexity: O(n * k * logk)
   Where 'n' is the length of "strs", and 'k' is the maximum length of a string
   in "strs". The outer loop has complexity O(n) as we iterate through each
   string. Then, we sort each string in O(k * logk) time.
*/
/* Space Complexity: O(n * k) */
class Solution{
public:
	std::vector<std::vector<std::string>>
	groupAnagrams(std::vector<std::string>& strs)
	{
		std::vector<std::vector<std::string>> results;
		std::unordered_map<std::string, std::vector<std::string>> umap;

		for (const auto& str: strs)
		{
			std::string key = str;
			std::sort(key.begin(), key.end());

			umap[key].push_back(str);
		}

		for (const auto& m : umap)
			results.push_back(m.second);

		return results;
	}
};


/*
	------------
	--- IDEA ---
	------------

	Two strings are anagrams if and only if their character counts(respective
	number of occurrences of each character) are the same.

	We have an array "counter" which counts number of occurrences of each
	letter in a current string.

	Once we've done that, we transform that array into a string and we use it
	as a key for our Hash Map.
	As for "values" we keep a vector of original strings.

	At the end we iterate through Hash Map's keys and add each "value"(entire
	vector) to our vector of vector "results" and we return that.

*/


/* Time  Complexity: O(n * k)
   Where 'n' is the length of "strs", and 'k' is the maximum length of a string
   in "strs". Counting each string is linear in the size of the string, and we
   count every string.
*/
/* Space Complexity: O(n * k) */
class Solution_improved{
public:
	std::vector<std::vector<std::string>>
	groupAnagrams(std::vector<std::string>& strs)
	{
		std::vector<std::vector<std::string>> results;
		std::unordered_map<std::string, std::vector<std::string>> umap;

		int counter[26];

		for (std::string& str : strs)
		{
			memset(counter, 0, sizeof(counter));

			for (char c : str)
				counter[c - 'a']++;

			std::string key;
			for (int i = 0; i < 26; i++)
				key += counter[i];

			umap[key].push_back(str);
		}

		for (const auto& m : umap)
			results.push_back(m.second);

		return results;
	}
};


int
main()
{
	// Solution sol;
	Solution_improved sol_improved;

	/* Example 1 */
	std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

	/* Example 2 */
	// std::vector<std::string> strs = {""};

	/* Example 3 */
	// std::vector<std::string> strs = {"a"};

	/* Example 4 */
	// std::vector<std::string> strs = {"", "b"};

	/* Example 5 */
	// std::vector<std::string> strs = {"", ""};

	/* Example 6 */
	// std::vector<std::string> strs = {"hhhhu","tttti","tttit","hhhuh","hhuhh","tittt"};

	/* Example 7 */
	// std::vector<std::string> strs = {"ddddddddddg","dgggggggggg"};

	std::cout << "\n\t======================";
	std::cout << "\n\t=== GROUP ANAGRAMS ===";
	std::cout << "\n\t======================\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tCandidates: [";
	for (auto x: strs)
	{
		if (!first)
			std::cout << ", ";

		std::cout << "\"" << x << "\"";
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	// std::vector<std::vector<std::string>> results = sol.groupAnagrams(strs);
	std::vector<std::vector<std::string>> results = sol_improved.groupAnagrams(strs);

	/* Write Output */
	first = true;
	std::cout << "\n\tResults: [";
	for (auto x: results)
	{
		if (!first)
			std::cout << ", ";

		bool first_first = true;
		std::cout << "[";
		for (const auto& xx : x)
		{
			if (!first_first)
				std::cout << ", ";

			std::cout << "\"" << xx << "\"";
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n\n";

	return 0;
}
