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

	Let's look at an example:
	
	    k = 2
	    s = "ababbcaabc"
	
	We will first count the occurrence of each character between the whole
	string.

	Occurrences:

	| a | b | c |
	+---+---+---+
	| 4 | 5 | 1 |

	Once we have a count with us, we'll start from the 0th character and we
	check:
		
		if occurrence of ith(0 in this case) is greater than K(2 in our case):
			i++;

		We will be repeating this until we find a character which occur less
		than K times or if we reach the end of the string.

	In our Example, we'd stop at:
	    k = 2
	    s = " a b a b b c a a b c"
	          0 1 2 3 4 5 6 7 8 9
	                    i

	At this particular index, we break the string into two:
	                    | 
	    s = " a b a b b | c a a b c"
	          0 1 2 3 4 | 5 6 7 8 9
	                    | i
	                    |

	The answer lies in one of the substrings. It's either left or right.
	This is now done recursively.

	We'll apply the same logic again with updated "start" and "end" value.

	Now just look at the code and it'll be become obvious.

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

		std::vector<int> count(26, 0); // Hash Map
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
