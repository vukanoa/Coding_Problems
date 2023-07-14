#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================================================
	395) Longest Substring With At Least K Repeating Characters
	===========================================================

	============
	Description:
	============

	Given a string s and an integer k, return the length of the longest
	substring of s such that the frequency of each character in this substring
	is greater than or equal to k.

	=====================================================
	FUNCTION: int longestSubstring(std::string s, int k);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "aaabb", k = 3
	Output: 3
	Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.

	--- Example 2 ---
	Input: s = "ababbc", k = 2
	Output: 5
	Explanation: The longest substring is "ababb", as 'a' is repeated 2 times
	and 'b' is repeated 3 times.

	*** Constraints ***
    1 <= s.length <= 10^4
    s consists of only lowercase English letters.
    1 <= k <= 10^5

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats:   100% */
/* Space Beats: 85.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSubstring(std::string s, int k)
    {
		return helper(s, 0, s.length(), k);
    }

private:
	int helper(std::string& s, int start, int end, int k)
	{
		if (end - start < k)
			return 0;

		std::vector<int> count(26, 0);
		for (int i = start; i < end; i++)
			count[s[i] - 'a']++;

		for (int i = start; i < end; i++)
		{
			if (count[s[i] - 'a'] < k)
			{
				int j = i + 1;

				while (j < end && count[s[j] - 'a'] < k)
					j++;

				return std::max(helper(s, start, i, k), helper(s, j, end, k));
			}
		}

		return end - start;
	}
};
