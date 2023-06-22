#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	50) Pow(x, n)
	===========================

	============
	Description:
	============

	Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

	========================================
	FUNCTION: double myPow(double x, int n);
	========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: x = 2.00000, n = 10
	Output: 1024.00000

	--- Example 2 ---
	Input: x = 2.10000, n = 3
	Output: 9.26100

	--- Example 3 ---
	Input: x = 2.00000, n = -2
	Output: 0.25000
	Explanation: 2-2 = 1/22 = 1/4 = 0.25

	*** Constraints ***
	-100.0 < x < 100.0
	-231 <= n <= 231-1
	n is an integer.
	Either x is not zero or n > 0.
	-104 <= xn <= 104

*/

/*
	------------
	--- IDEA ---
	------------

	This code gives TLE, but I wanted to have it here to remind myself that you
	CANNOT do it like this, even if this is "intuitive".
	
*/

class Solution_TLE{
public:
	double myPow(double x, int n)
	{
		if (x == 1.0000)
			return 1;

		double result = 1.00000;

		if (n > 0)
		{
			for (int i = 0; i < n; i++)
				result *= x;
		}
		else // n < 0
		{
			bool was_int_min = false;

			if (n == INT_MIN)
			{
				was_int_min = true;
				n = n + 1; // Subtracting; But since n is negative, add 1
			}

			for (int i = 0; i < -n; i++)
				result *= x;

			if (was_int_min)
				result *= x;
			
			result = 1.00000 / result;
		}

		return result;
	}
};




/*
	------------
	--- IDEA ---
	------------

	So what is, for example:
		2^10?
	
	It's: 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
	      ~~~~~~~~~~~~~~~~~v~~~~~~~~~~~~~~~~~~~
	                      10

	So is it this easy? We can just iterate n times and multiply?
	No. That would give a TLE. That Solution is O(n) which doesn't passes all
	the tests.

	So how are we going to solve it in less than O(n).

	Consider this same example:
	2^10 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
	       ~~~~~~~~~~~~~~~~~v~~~~~~~~~~~~~~~~~~~
	                       10
	We can notice that:
		2^10 = 2^5 * 2^5
	
	Can you see the repeated work?
	Can't we just take calculated 2^5 and multiply it by itself? That's half
	the work.

	But, why stop there?
	We can go further. We can break down: 2^5 now.
	
	How are we going to break it down if the exponent is an odd number?

	Let's write it down:
		2^5 = 2^2 * 2^2 * 2;

		That's 2^2 twice, multiplied by a constant value of 2.

	Let's break it down even further:
		
		2^2 = 2^1 * 2^1
	
	And now, we can just go backwards and multiply with given results.

	This indicates that we're going to use a recursion, that further indicates
	that we need some form of base case at which we'll stop.

	So what will be the Base Case:

	if x == 0, it's always going to be 0.
	if n == 0, it's always going to be 1.
	
*/

/* Time  Beats:  100% */
/* Space Beats: 69.48% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(log2(n)) */
class Solution_Neat {
public:
	double myPow(double x, int n)
	{
		double result = helper(x, std::abs(n));

		if (n >= 0)
			return result;

		return 1 / result;
	}

private:
	double helper(double x, int n)
	{
		if (x == 0)
			return 0;

		if (n == 0)
			return 1;

		double result = helper(x, n / 2); 
		result = result * result;

		if (n % 2 == 0)
			return result;

		return x * result;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same IDEA, just using a bit more algebra on a noted line.
	
*/

/* Time  Beats:  100% */
/* Space Beats: 95.78% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(log2(n)) */
class Solution_Neat_2 {
public:
	double myPow(double x, int n)
	{
		double result = helper(x, std::abs(n));

		if (n >= 0)
			return result;

		return 1 / result;
	}

private:
	double helper(double x, int n)
	{
		if (x == 0)
			return 0;

		if (n == 0)
			return 1;

		/* A bit of algebra */
		double result = helper(x * x, n / 2); // x * x, instead of res *= res;
		// Deleted: results *= results;

		if (n % 2 == 0)
			return result;

		return x * result;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Similar approach, written in a different way.
	
*/

/* Time  Beats: 42.32% */
/* Space Beats: 69.48% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(log2(n)) */
class Solution {
public:
	double myPow(double x, int n)
	{
		if(n == 0)
				return 1;

		if(n < 0)
		{
			n = std::abs(n);
			x = 1 / x;
		}

		if(n % 2 == 0)
			return myPow(x * x, n / 2);
		else
			return x * myPow(x, n - 1);
	}
};
