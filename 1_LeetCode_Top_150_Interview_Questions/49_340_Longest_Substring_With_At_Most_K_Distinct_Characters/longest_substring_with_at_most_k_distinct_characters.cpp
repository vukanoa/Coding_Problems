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

	Basic Sliding Window with a HashMap.

	We'll keep track of "left" and "right" pointers since we're doing a Sliding
	Window technique.

	While right boundary is within the string 's', do the following:
		
		(
		  if number of distinct elements in our Hashmap is equal to k
			and
		  if the current element is NOT one of the distinct ones in the Hashmap
		)
		then:
			std::max(result up until this point, right - left);
	
			We should remove all the characters on the left until we
			have k-1 distinct ones in the Hashmap(because our current
			s[right] is not the distinct one and we need **at most** k)


		Either way, always ask if the current element, i.e. map[s[right]] == 0:
			If it is that means it's a new distinct element, therefore we
			should increment the number of distinct elements.

		At the end, always, increment the number of occurrences of that element
		in the Hash Map.
	
	After the while loop has ended, we got the longest substring with at most
	k elements in our "result" variable. Just return that.

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
			if (distinct == k && map[s[right] - 'a'] == 0)
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
