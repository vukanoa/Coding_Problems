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

	Sieve of Eratosthenes.

	Suppose we are given N = 10

	1  Non-Prime
	2  Prime
	3  Prime
	4  Non-Prime
	5  Prime
	6  Non-Prime
	7  Prime
	8  Non-Prime
	9  Non-Prime
	10 Non-Prime


	Now Suppose we are given N = 30
	1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P

	'-' - True  for all the Composite numbers
	'P' - False for all the Prime numbers

	At the very beginning we only mark 1 to True since 1 is certainly a
	Composite number.

	We start from index 2. Since 2 is a Prime number we are going to mark every
	multiple of 2 as a Composite number(set to "-", meaning "Composite").

	1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	-   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P   P

	After doing a "2", we'll be in this situation:

	1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	-   P   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -   P   -

	Now we're doing a 3. We will mark all the multiples of 3 as Composite:

	1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	-   P   P   -   P   -   P   -   -   -   P   -   P   -   -   -   P   -   P   -   -   -   P   -   P   -   -   -   P   -


	...

	We essentially do that for all N numbers, thus making it O(n).
	We'll end up with this:

	1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	-   P   P   -   P   -   P   -   -   -   P   -   P   -   -   -   P   -   P   -   -   -   P   -   -   -   P   -   P   -

	Now just traverse this vector and count P's.
	i.e. count how many Primes("false" values) are there.
		false == Prime
		true  == Composite number

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
