#include<iostream>
#include <algorithm>
#include <string>

/*
	============
	=== EASY ===
	============

	===========================
	67) Add Binary
	===========================

	============
	Description:
	============

	Given two binary strings a and b, return their sum as a binary string.

	===============================================
	FUNCTION: string addBinary(string a, stirng b);
	===============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: a = "11", b = "1"
	Output: "100"


	--- Example 2 ---
	Input: a = "1010", b = "1011"
	Output: "10101"


	*** Constraints ***
	1 <= a.length, b.length <= 104
	a and b consist only of '0' or '1' characters.
	Each string does not contain leading zeros except for the zero itself.

*/

/* Time  Beats: 100% */
/* Space Beats: 41.40% */

/* Time  Complexity: O((m + n) * log(m + n)) */
/* Space Complexity: O(1) */
class Solution {
public:
	std::string addBinary(std::string a, std::string b)
	{
		int i = a.length() - 1;
		int j = b.length() - 1;
		int carry = 0;

		std::string result;

		while (i >= 0 || j >= 0 || carry)
		{
			int digit_a = i >= 0 ? a[i] - '0' : 0;
			int digit_b = j >= 0 ? b[j] - '0': 0;

			result += std::to_string(digit_a ^ digit_b ^ carry);
			carry = ((digit_a & digit_b) || ((digit_a || digit_b) & carry));
			i--;
			j--;
		}

		std::cout << result;

		// O((m * n) * log(m * n))
		std::reverse(result.begin(), result.end());

		return result;
	}
};
