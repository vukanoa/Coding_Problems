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

using namespace std;

/* Time  Complexity: O(S), where S is the sum of all characters of all strings in the vector */
/* Space Complexity: O(1) */
class Solution{
public:
	string longestCommonPrefix(vector<string>& strs)
	{
		if (strs.empty())
			return "";
		else if (strs.size() == 1)
			return strs[0];
		else if (strs[0].empty() || strs[1].empty())
			return "";
		else if (strs[0][0] != strs[1][0])
			return "";

		string prefix = strs[0];
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


int
main()
{
	Solution sol;

	/* Example 1 */
	vector<string> strs = {"flower", "flow", "flight"};

	/* Example 2 */
	// vector<string> strs = {"dog", "racecar", "car"};

	/* Example 3 */
	// vector<string> strs = {"",""};

	/* Example 4 */
	// vector<string> strs = {"c", "c"};

	/* Example 5 */
	// vector<string> strs = {"apple"};

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

	string prefix = sol.longestCommonPrefix(strs);
	std::cout << "\n\tLongest Common Prefix is: \"" << prefix << "\"\n\n";

	return 0;
}
