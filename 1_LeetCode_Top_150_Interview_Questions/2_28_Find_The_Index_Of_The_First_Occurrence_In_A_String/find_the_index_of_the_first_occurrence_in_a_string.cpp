#include <iostream>

/*
	============
	=== EASY ===
	============

	======================================================
	28) Find The Index Of The First Occurrence In A String
	======================================================

	============
	Description:
	============

	Given two strings needle and haystack, return the index of the first
	occurrence of needle in haystack, or -1 if needle is not part of haystack.

	=====================================================
	FUNCTION: int strStr(string haystack, string needle);
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: haystack = "sadbutsad", needle = "sad"
	Output: 0
	Explanation: "sad" occurs at index 0 and 6.
	The first occurrence is at index 0, so we return 0.

	--- Example 2 ---
	Input: haystack = "leetcode", needle = "leeto"
	Output: -1
	Explanation: "leeto" did not occur in "leetcode", so we return -1.

	*** Constraints ***
    1 <= haystack.length, needle.length <= 104
	haystack and needle consist of only lowercase English characters.

*/

/*
	------------
	--- IDEA ---
	------------

	Basic, Brute Force Solution. Self-Explanatory.
	
*/


/* Time  Beats: 100% */
/* Space Beats: 61.50% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(1) */
class Solution {
public:
	int strStr(std::string haystack, std::string needle)
	{
		if (needle.length() > haystack.length())
			return -1;

		for (int i = 0; i < haystack.length() + 1 - needle.length(); i++)
		{
			bool found = true;

			for (int j = 0; j < needle.length(); j++)
			{
				if (haystack[i + j] != needle[j])
				{
					found = false;
					break;
				}
			}

			if (found)
				return i;
		}

			return -1;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Equivalent to the above one, just written with a bit of "STL magic".
	
*/


/* Time  Beats: 100% */
/* Space Beats: 23.32% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution_STL{
public:
	int strStr(std::string haystack, std::string needle)
	{
		if (needle.length() > haystack.length())
			return -1;

		for (int i = 0; i < haystack.length() + 1 - needle.length(); i++)
		{
			std::string s = haystack.substr(i, needle.length());

			if (s == needle)
				return i;
		}

		return -1;
	}
};


/* There is a Solution Time: O(m + n), Space: O(m). It's called KMP. TODO */


int
main()
{
	Solution     sol;
	Solution_STL sol_stl;


	/* Example 1 */
	// std::string haystack = "sadbutsad";
	// std::string needle   = "sad";

	/* Example 2 */
	// std::string haystack = "leetcode";
	// std::string needle   = "leeto";

	/* Example 3 */
	std::string haystack = "mississippi";
	std::string needle   = "pi";


	std::cout << "\n\t==========================================================";
	std::cout << "\n\t=== FIND_THE_INDEX_OF_THE_FIRST_OCCURRENCE_IN_A_STRING ===";
	std::cout << "\n\t==========================================================\n";


	/* Write Input */
	std::cout << "\n\tHaystack: \"" << haystack << "\"";
	std::cout << "\n\tNeedle  : \"" << needle   << "\"\n";


	/* Solution */
	// int result = sol.strStr(haystack, needle);
	int result = sol_stl.strStr(haystack, needle);


	/* Write Output */
	std::cout << "\n\tOutput: " << result << "\n\n";


	return 0;
}
