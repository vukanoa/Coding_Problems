#include <iostream>

/*
	============
	=== HARD ===
	============

	===========================
	44) Wildcard Matching
	===========================

	============
	Description:
	============

	Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

		'?' Matches any single character.
		'*' Matches any sequence of characters (including the empty sequence).

	The matching should cover the entire input string (not partial).

	=====================================================
	FUNCTION: bool isMatch(std::string s, std::string p);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "aa", p = "a"
	Output: false
	Explanation: "a" does not match the entire string "aa".

	--- Example 2 ---
	Input: s = "aa", p = "*"
	Output: true
	Explanation: '*' matches any sequence.

	--- Example 3 ---
	Input: s = "cb", p = "?a"
	Output: false
	Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

	*** Constraints ***
    0 <= s.length, p.length <= 2000
    s contains only lowercase English letters.
    p contains only lowercase English letters, '?' or '*'.

*/

/*
	------------
	--- IDEA ---
	------------

	*** Greedy solution with idea of DFS ***

	starj stores the position of last * in p
	last_match stores the position of the previous matched char in s after a *

	Example:
		s: a c d s c d
		p: * c d

	After the first match of the *:
		starj = 0
		last_match = 1

	When we come to i = 3 and j = 3, we know that the previous match of * is
	actually wrong(the first branch of DFS we take is wrong) then it
	resets j = starj + 1  since we already know i = last_match will give us the
	wrong answer.

	So this time:
		i = last_match+1

	And we try to find a longer match of *

	Then after another match we have starj = 0 and last_match = 4, which is the
	right solution, since we don't know where the right match for * ends, we
	need to take a guess (one branch in DFS), and store the information(starj
	and last_match) so we can always backup to the last correct place and take
	another guess.

*/

/* Time  Beats: 100% */
/* Space Beats: 99.12% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution{
public:
	bool isMatch(string s, string p)
	{
		int i = 0;
		int j = 0;
		int m = s.length();
		int n = p.length();

		int last_match = -1;
		int starj      = -1;

		while (i < m)
		{
			if (j < n && (s[i] == p[j] || p[j] == '?'))
			{
				i++;
				j++;
			}
			else if (j < n && p[j] == '*')
			{
				starj = j;
				j++;
				last_match = i;
			}
			else if (starj != -1)
			{
				j = starj + 1;
				last_match++;
				i = last_match;
			}
			else
				return false;
		}

		while (p[j] == '*' && j < n)
			j++;

		return j == n;
	}
};
