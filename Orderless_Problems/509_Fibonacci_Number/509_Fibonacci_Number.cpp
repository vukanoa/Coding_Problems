#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	509) Fibonacci Number
	===========================

	============
	Description:
	============

	The Fibonacci numbers, commonly denoted F(n) form a sequence, called the
	Fibonacci sequence, such that each number is the sum of the two preceding
	ones, starting from 0 and 1. That is,

	F(0) = 0, F(1) = 1
	F(n) = F(n - 1) + F(n - 2), for n > 1.

	Given n, calculate F(n).

	=========================
	FUNCTION: int fib(int n);
	=========================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 2
	Output: 1
	Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.


	--- Example 2 ---
	Input: n = 3
	Output: 2
	Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.


	--- Example 3 ---
	Input: n = 4
	Output: 3
	Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.


	*** Constraints ***
	0 <= n <= 30

*/

/*
	------------
	--- IDEA ---
	------------

	Basic 1-D Dynamic Programming using Bottom-Up Approach.

*/

/* Time  Beats: 100% */
/* Space Beats: 25.09% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int fib(int n)
    {
        if (n == 0)
            return 0;
        
        int dp_2 = 0;
        int dp_1 = 1;

        for (int i = 2; i < n; i++)
        {
            int sum = dp_1 + dp_2;

            dp_2 = dp_1;
            dp_1 = sum;
        }

        return dp_1 + dp_2;
    }
};




/*
	------------
	--- IDEA ---
	------------

	Golder Ration Method

	When we take any two successive (one after the other) Fibonacci Numbers,
	their ratio is very close to the Golden Ratio "φ"(phi) which is approximately
	1.618034...

	The golden ratio (symbol is the Greek letter "phi", φ) is a special number
	approximately equal to 1.618

	We find the golden ratio when we divide a line into two parts so that: the
	whole length divided by the long part is also equal to the long part
	divided by the short part xn = ((φ^n) − ((1−φ)^n)) / √5

*/

/* Time  Beats: 100% */
/* Space Beats: 25.09% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
	int fib(int n) {
		double ratio = (sqrt(5) + 1) / 2;

		double up_to_powers = 1;
		while (n > 0) 
		{
			if(n & 1) // n is odd
				up_to_powers *= ratio;

			ratio = ratio * ratio;
			n = n >> 1; // n = n / 2;
		}

		return round(up_to_powers / sqrt(5));
	}
};
