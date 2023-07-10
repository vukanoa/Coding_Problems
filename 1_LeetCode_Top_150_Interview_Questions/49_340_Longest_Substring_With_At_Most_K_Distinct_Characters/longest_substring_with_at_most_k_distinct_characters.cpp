#include <iostream>

/*
	###############
	### PREMIUM ###
	###############
*/

/*
	==============
	=== MEDIUM ===
	==============

	=========================================================
	340) Longest Substring With At Most K Distinct Characters
	=========================================================

	============
	Description:
	============

	Given a string s and an integer k, return the length of the longest
	substring of s that contains at most k distinct characters.

	=======================================================================
	FUNCTION: int lengthOfLongestSubstringKDistinct(std::string& s, int k);
	=======================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "eceba", k = 2
	Output: 3
	Explanation: The Substring is "ece" with length 3

	--- Example 2 ---
	Input: s = "aa", k = 1
	Output: 2
	Explanation: The substring is "aa" with lenght 2

	*** Constraints ***
	1 <= s.length <= 5 * 10^9
	0 <= k <= 50

*/

/*
	------------
	--- IDEA ---
	------------

	Basic Sliding with with HashMap.
	
*/


/* Time  Complexity: O(n) */
/*
	Space Complexity: O(1)
	O(1) because if there are only lowercase English letters, it's always 26.
*/
class Solution {
public:
	int lengthOfLongestSubstringKDistinct(std::string& s, int k)
	{
		if (s.length() == 0 || k == 0)
			return 0;

		int left  = 0;
		int right = 0;

		int distinct = 0;

		int result = -1;

		// Assumed that 's' contains only lowercase English letters
		std::vector<int> map(26, 0);

		while (right < s.length())
		{
			if (distinct == k)
			{
				if (map[s[right] - 'a'] == 0)
				{
					result = std::max(result, right - left);

					while (distinct > k-1)
					{
						map[s[left] - 'a']--;

						if (map[s[left] - 'a'] == 0)
							distinct--;

						left++;
					}
				}
			}

			// Add new
			if (map[s[right] - 'a'] == 0)
				distinct++;

			map[s[right] - 'a']++;
		}
	
		return result;
	}
};




/*
	------------
	--- IDEA ---
	------------

	The same idea, written differently.
	
*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
	int lengthOfLongestSubstringKDistinct(std::string& s, int k)
	{
		if (s.length() == 0 || k == 0)
			return 0;

		int left  = 0;
		int right = 0;

		int result = 0;
		int map_size = 0;

		// Assumed that 's' contains only lowercase English letters
		std::vector<int> map(26, 0);

		while (right < s.length())
		{
			map[s[right] - 'a']++;

			if (map[s[right] - 'a'] == 1)
				map_size++;

			while (map_size > k)
			{
				map[s[left - 'a']]--;

				if (map[s[left - 'a']] == 0)
					map_size--;

				left++;
			}

			result = std::max(result, right - left + 1);
		}
	
		return result;
	}
};
