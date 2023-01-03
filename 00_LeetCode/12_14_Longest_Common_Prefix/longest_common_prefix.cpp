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
	Explanation: THere is no common prefix among the input stringsn.

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


int
main()
{
	Solution sol;

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

	std::string prefix = sol.longestCommonPrefix(strs);
	std::cout << "\n\tLongest Common Prefix is: \"" << prefix << "\"\n\n";

	return 0;
}
