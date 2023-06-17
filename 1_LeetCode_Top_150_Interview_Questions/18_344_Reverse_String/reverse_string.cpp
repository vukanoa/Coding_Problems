#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	344) Reverse String
	===========================

	============
	Description:
	============

	Write a function that reverses a string. The input string is given as an
	array of characters s.

	You must do this by modifying the input array in-place with O(1) extra
	memory.

	==============================================
	FUNCTION: void reverseString(vector<char>& s);
	==============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = ["h","e","l","l","o"]
	Output: ["o","l","l","e","h"]

	--- Example 2 ---
	Input: s = ["H","a","n","n","a","h"]
	Output: ["h","a","n","n","a","H"]


	*** Constraints ***
	1 <= s.length <= 105
	s[i] is a printable ascii character.

*/

/*
	------------
	--- IDEA ---
	------------

	Self Explanatory.
	
*/

/* Time  Beats: 87.20% */
/* Space Beats: 94.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	void reverseString(std::vector<char>& s)
	{
		int left  = 0;
		int right = s.size() - 1;

		while (left < right)
			std::swap(s[left++], s[right--]);
	}
};
