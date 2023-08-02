#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	338) Counting Bits
	===========================

	============
	Description:
	============

	Given an integer n, return an array ans of length n + 1 such that for each
	i (0 <= i <= n), ans[i] is the number of 1's in the binary representation
	of i.

	~~~ Follow Up ~~~
	It is very easy to come up with a solution with a runtime of O(n log n).

	Can you do it in linear time O(n) and possibly in a single pass?
	Can you do it without using any built-in function (i.e., like
	__builtin_popcount in C++)?


	=======================================
	FUNCTION: vector<int> countBits(int n);
	=======================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 2
	Output: [0,1,1]
	Explanation:
	0 --> 0
	1 --> 1
	2 --> 10


	--- Example 2 ---
	Input: n = 5
	Output: [0,1,1,2,1,2]
	Explanation:
	0 --> 0
	1 --> 1
	2 --> 10
	3 --> 11
	4 --> 100
	5 --> 101


	*** Constraints ***
	0 <= n <= 105
*/


/*
	------------
	--- IDEA ---
	------------

	Self-Explanatory.
	
*/

/* Time  Beats: 41.06% */
/* Space Beats: 30.68% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	vector<int> countBits(int n)
	{
		std::vector<int> ans;

		for (int i = 0; i <= n; i++)
		{
			int num = i;
			int count = 0;

			for (int j = 0; j < 32; j++) // O(32) => constant => O(1)
			{
				if (num & 1)
				count++;

				num >>= 1;
			}

			ans.push_back(count);
		}

		return ans;
	}
};




/* Time  Beats: 95.87% */
/* Space Beats: 63.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	std::vector<int> countBits(int n)
	{
		
		vector<int> ans(n+1);
		ans[0] = 0;

		for(int i = 1; i <= n; ++i)
			ans[i] = ans[i/2] + i%2;

		return ans;
	}
};




/* Time  Beats: 95.87% */
/* Space Beats: 51.59% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	std::vector<int> countBits(int num)
	{
		std::vector<int> ans(num+1, 0);

		for (int i = 1; i <= num; ++i)
			ans[i] = ans[i & (i-1)] + 1;

		return ans;
	}
};
