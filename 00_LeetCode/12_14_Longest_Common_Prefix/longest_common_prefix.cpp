#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	14) Longest Common Prefix
	===========================

	============
	Description:
	============

	Write a function to find the longest common prefix string amongst
	an array of strings.

	If there is no common prefix, return an empty string "".

	===========================================================
	FUNCTION: string longestCommonPrefix(vector<string>& strs);
	===========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  strs = ["flower", "flow", "flight"]
	Output: "fl"

	--- Example 2 ---
	Input:  strs = ["dog", "racecar", "car"]
	Output: ""
	Explanation: There is no common prefix among the input stringsn.

	*** Constraints ***
	1 <= strs.length() <= 200
	0 <= strs[i].length() <= 200
	strs[i] consists of only lowercase English letters.
*/


/*
	------------
	--- IDEA ---
	------------

	The longest common prefix is common to all the strings. So, we can fix one
	string and check the common prefix of this string with other strings. The
	minimum such length is found and the answer is the substring of the fixed
	string starting from 0 to the length of the above such minimum.

*/


/* Time  Beats: 100%   */
/* Space Beats: 83.19% */
/* Time  Complexity: O(S), where S is the sum of all characters of all strings in the vector */
/* Space Complexity: O(1) */
class Solution{
public:
	std::string longestCommonPrefix(std::vector<std::string>& strs)
	{
		int prefix_size = strs[0].length();
		int n = strs.size();

		for (int i = 1; i < n; i++)
		{
			if (prefix_size == 0)
				return "";

			int x = 0;
			while (x < strs[i].length() && strs[0][x] == strs[i][x])
				x++;

			prefix_size = std::min(prefix_size, x);
		}

		return strs[0].substr(0, prefix_size);
	}
};



/* Time  Beats: 100%    */
/* Space Beats: 27.88%% */
/* Time  Complexity: O(S) */
/* Space Complexity: O(1) */
class Solution_2{
public:
	std::string longestCommonPrefix(std::vector<std::string>& strs)
	{
		if (strs.empty())
			return "";
		else if (strs.size() == 1)
			return strs[0];
		else if (strs[0].empty() || strs[1].empty())
			return "";
		else if (strs[0][0] != strs[1][0])
			return "";

		std::string prefix = strs[0];
		for (int i = 1; i < strs.size(); i++)
		{
			if (strs[i] == "" || prefix == "")
				return "";

			while (prefix != strs[i].substr(0, prefix.size()))
				prefix.pop_back();
		}

		return prefix;
	}
};



/*
	------------
	--- IDEA ---
	------------

	We iterate through all the words for letter at index 0, then
	thorugh all the words for letter at index 1, etc.

	As soon as we find en empty character, meaning all the letters in that word
	were alerady checked, that means that is the longest commong prefix and
	we just return substring of any word from (0, prefix.size);

	If at any point in iteration through the words we find out that two
	adjacent letters are not the same, we immediately return substring of any
	word from (0, prefix.size)

	It's important to note that we're iterating thorugh to word from:
		0 to n - 2
	and NOT
		0 to n - 1

	That is because we always check current letter x with it's right neighbor.
	Last character doesn't have a neighbor.

*/


/* Time  Beats: 100%   */
/* Space Beats: 83.19% */
/*
	Time  Complexity: O(p)
	Where p is the longestCommonPrefixSize * strs.size()
	Meaning:
	all the letters that are a part of longest common prefix * numbe of words

	In theory it's faster than O(S) solution since we don't have to iterate
	through every letter of every word, but they are both beating 100%, so
	I guess it's not that important.

*/
/* Space Complexity: O(1) */
class Solution_3{
public:
	std::string longestCommonPrefix(std::vector<std::string>& strs)
	{
		if (strs.empty())
			return "";
		else if (strs[0].empty())
			return "";
		else if (strs.size() == 1)
			return strs[0];

		int prefix_size = 0;
		int n = strs.size();

		int x = 0;
		for (;;) // For every prefix letter
		{
			// i < n MINUS 1, not n
			for (int i = 0; i < n-1; i++) // In every word
			{
				if (x >= strs[i].length())
					return strs[0].substr(0, prefix_size);

				if (strs[i][x] != strs[i + 1][x])
					return strs[0].substr(0, prefix_size);
			}

			prefix_size++; // Could use just 'x', but it's more verbose
			x++;
		}

		return strs[0].substr(0, prefix_size);
	}
};


int
main()
{
	Solution sol;
	Solution_2 sol_2;
	Solution_3 sol_3;

	/* Example 1 */
	std::vector<std::string> strs = {"flower", "flow", "flight"};

	/* Example 2 */
	// std::vector<std::string> strs = {"dog", "racecar", "car"};

	/* Example 3 */
	// std::vector<std::string> strs = {"",""};

	/* Example 4 */
	// std::vector<std::string> strs = {"c", "c"};

	/* Example 5 */
	// std::vector<std::string> strs = {"apple"};

	std::cout << "\n\t=============================";
	std::cout << "\n\t=== LONGEST COMMON PREFIX ===";
	std::cout << "\n\t=============================\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tStrings: [";
	for (auto s: strs)
	{
		if (!first)
			std::cout << ", ";

		std::cout << "\"" << s << "\"";
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	std::string prefix = sol.longestCommonPrefix(strs);
	// std::string prefix = sol_2.longestCommonPrefix(strs);
	// std::string prefix = sol_3.longestCommonPrefix(strs);

	/* Write Output */
	std::cout << "\n\tLongest Common Prefix is: \"" << prefix << "\"\n\n";

	return 0;
}
