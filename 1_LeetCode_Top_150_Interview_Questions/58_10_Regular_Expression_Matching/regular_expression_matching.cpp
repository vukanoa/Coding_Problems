#include <iostream>
#include <vector>

/*
	============
	=== HARD ===
	============

	===============================
	10) Regular Expression Matching
	===============================

	============
	Description:
	============

	Given an input string s and a pattern p, implement regular expression
	matching with support for '.' and '*' where:

		'.' Matches any single character.
		'*' Matches zero or more of the preceding element.

	The matching should cover the entire input string (not partial).

	===========================================
	FUNCTION: bool isMatch(string s, string p);
	===========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "aa", p = "a"
	Output: false
	Explanation: "a" does not match the entire string "aa".

	--- Example 2 ---
	Input: s = "aa", p = "a*"
	Output: true
	Explanation: '*' means zero or more of the preceding element, 'a'.
	Therefore, by repeating 'a' once, it becomes "aa".

	--- Example 3 ---
	Input: s = "ab", p = ".*"
	Output: true
	Explanation: ".*" means "zero or more (*) of any character (.)".


	*** Constraints ***
    1 <= s.length <= 20
    1 <= p.length <= 20
    s contains only lowercase English letters.
    p contains only lowercase English letters, '.', and '*'.
    It is guaranteed for each appearance of the character '*', there will be a
	previous valid character to match.

*/


/*
	------------
	--- IDEA ---
	------------

	TODO

*/

/* Time  Beats: 83.20% */
/* Space Beats: 68.18% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(n * m) */
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();

		std::vector<std::vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;

		for (int i = 0; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (p[j - 1] == '*')
				{
					dp[i][j] = dp[i][j - 2] || (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else
				{
					dp[i][j] = i && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}
		}

		return dp[m][n];
	}
};




/* You may further reduce the memory usage down to two vectors O(n) */

/* Time  Beats: 83.20% */
/* Space Beats: 90.41% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(n) */
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();
		vector<bool> pre(n + 1, false), cur(n + 1, false);
		cur[0] = true;

		for (int i = 0; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (p[j - 1] == '*')
				{
					cur[j] = cur[j - 2] || (i && pre[j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else
				{
					cur[j] = i && pre[j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}
			}

			fill(pre.begin(), pre.end(), false);
			swap(pre, cur);
		}

			return pre[n];
	}
};





/* Reduce it to one vector */

/* Time  Beats: 100% */
/* Space Beats: 90.41% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(1) */
class Solution {
public:
	bool isMatch(string s, string p)
	{
		int m = s.size(), n = p.size();
		vector<bool> cur(n + 1, false);

		for (int i = 0; i <= m; i++)
		{
			bool pre = cur[0];
			cur[0] = !i;

			for (int j = 1; j <= n; j++)
			{
				bool temp = cur[j];
				if (p[j - 1] == '*')
				{
					cur[j] = cur[j - 2] || (i && cur[j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
				}
				else 
				{
					cur[j] = i && pre && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
				}

				pre = temp;
			}
		}

		return cur[n];
	}
};
