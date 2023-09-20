#include <iostream>

/*
	============
	=== EASY ===
	============

	============================
	1137) N-th Tribonacci Number
	============================

	============
	Description:
	============

	The Tribonacci sequence Tn is defined as follows: 

	T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

	Given n, return the value of Tn.

	================================
	FUNCTION: int tribonacci(int n);
	================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 4
	Output: 4
	Explanation:
	T_3 = 0 + 1 + 1 = 2
	T_4 = 1 + 1 + 2 = 4


	--- Example 2 ---
	Input: n = 25
	Output: 1389537


	*** Constraints ***
    0 <= n <= 37
	The answer is guaranteed to fit within a 32-bit integer, i.e. 
	answer <= 2^31 - 1.

*/

/*
	------------
	--- IDEA ---
	------------

	Basic Fibonacci Bottom-Up Dynamic Problem Solution.

*/

/* Time  Beats:  100% */
/* Space Beats: 5.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int tribonacci(int n)
	{
		if (n == 0)
			return 0;
		else if (n == 1 || n == 2)
			return 1;

		int dp3 = 0;
		int dp2 = 1;
		int dp1 = 1;

		for (int i = 4; i <= n; i++)
		{
			int dp = dp3 + dp2 + dp1;

			dp3 = dp2;
			dp2 = dp1;
			dp1 = dp;
		}

		return dp3 + dp2 + dp1;
	}
};
