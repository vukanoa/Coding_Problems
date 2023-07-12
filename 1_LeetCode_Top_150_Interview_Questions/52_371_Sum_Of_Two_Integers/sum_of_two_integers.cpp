#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	371) Sum Of Two Integers
	===========================

	============
	Description:
	============

	Given two integers a and b, return the sum of the two integers without
	using the operators + and -.	

	===================================
	FUNCTION: int getSum(int a, int b);
	===================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: a = 1, b = 2
	Output: 3

	--- Example 2 ---
	Input: a = 2, b = 3
	Output: 5

	*** Constraints ***
	-1000 <= a, b <= 1000
*/


/*
	------------
	--- IDEA ---
	------------

	1)
		a + b
	
	2)
		2^a * 2^b => log2(2^a * 2^b) => log2(2^(a + b)) => (a + b) * log2(2) => (a + b) * 1 => (a + b)

*/

/* Time  Beats:   100% */
/* Space Beats: 12.66% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution{
public:
	int getSum(int a, int b)
	{
		return std::log(std::pow(2, a) * std::pow(2, b)) / std::log(2);
	}
};
