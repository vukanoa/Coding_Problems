#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	204) Count Primes
	===========================

	============
	Description:
	============

	Given an integer n, return the number of prime numbers that are strictly
	less than n.

	=================================
	FUNCTION: int countPrimes(int n);
	=================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 10
	Output: 4
	Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

	--- Example 2 ---
	Input: n = 0
	Output: 0

	--- Example 3 ---
	Input: n = 1
	Output: 0

	*** Constraints ***
	0 <= n <= 5 * 10^6

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 36.41% */
/* Space Beats: 94.12% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution{
public:
	int countPrimes(int n)
	{
		if (n == 0 || n == 1 || n == 2)
			return 0;

		std::vector<bool> vec(n+1, false);

		// 1 is not a Prime number
		vec[1] = true;

		for (int i = 2; i <= n; i++)
		{
			if (vec[i] == false)
			{
				int increment = 2;

				while(i * increment <= n)
				{
					vec[i * increment] = true;
					increment++;
				}
			}
		}

		/* Count "False"(Primes) */
		int count = 0;

		for (int i = 1; i < n; i++)
		{
			if (vec[i] == false)
				count++;
		}

		return count;
	}
};
