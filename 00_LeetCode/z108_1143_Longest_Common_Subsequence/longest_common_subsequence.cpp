#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	1143) Longest Common Subsequence
	================================

	============
	Description:
	============

	Given two strings text1 and text2, return the length of their longest
	common subsequence. If there is no common subsequence, return 0.

	A subsequence of a string is a new string generated from the original
	string with some characters(can be none) deleted without changing the
	relative order of the remaining characters.

		- For example, "ace" is a subsequence of "abcde".

	A common subsequence of two strings is a subsequence that is common to both
	strings.

	===================================================================
	FUNCTION: int longestCommonSubsequence(string text1, string text2);
	===================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  text = "abcde", text2 = "ace"
	Output: 3
	Explanation: The longest common subsequence is "ace" and its length is 3.

	--- Example 2 ---
	Input:  text1 = "abc", text2 = "abc"
	Output: 3
	Explanation: The longest common subsequence is "abc" and its length is 3.

	--- Example 3 ---
	Input:  text1 = "abc", text2 = "def"
	Output:
	Explanation: There is no such common subsequence, so the result is 0.

	*** Constraints ***
	1 <= text1.length, text2.length <= 1000
	text1 and text2 consist of only lowercase English characters.

*/

/*

bbcde
ace

"oxcpqrsvwf"
"shmtulqrypy"

*/


/*
	------------
	--- IDEA ---
	------------



*/


/* Time  Beats: 21.0% */
/* Space Beats: 10.9% */
/* Time  Complexity: O(n * m) */
/* Space Complexity: O(n * m) */
class Solution{
public:
	int longestCommonSubsequence(std::string& text1, std::string& text2)
	{
		std::vector<std::vector<int>> dp(text1.length() + 1, std::vector<int>(text2.length() + 1, 0));

		for (int i = text1.length() - 1; i >= 0; i--)
		{
			for (int j = text2.length() - 1; j >= 0; j--)
			{
				if (text1[i] == text2[j])
					dp[i][j] = 1 + dp[i + 1][j + 1];
				else
					dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);
			}
		}

		return dp[0][0];
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string text1 = "abcde";
	// std::string text2 = "ace";

	/* Example 2 */
	// std::string text1 = "abc";
	// std::string text2 = "abc";

	/* Example 3 */
	// std::string text1 = "abc";
	// std::string text2 = "def";

	/* Example 4 */
	std::string text1 = "oxcpqrsvwf";
	std::string text2 = "shmtulqrypy";

	std::cout << "\n\t==================================";
	std::cout << "\n\t=== LONGEST COMMOM SUBSEQUENCE ===";
	std::cout << "\n\t==================================\n";

	/* Write Input */
	std::cout << "\n\tText 1: \"" << text1 << "\"";
	std::cout << "\n\tText 2: \"" << text2 << "\"\n";

	/* Solution */
	int output = sol.longestCommonSubsequence(text1, text2);

	/* Write Output */
	std::cout << "\n\tOutput: " << output << "\n\n";

	return 0;
}
