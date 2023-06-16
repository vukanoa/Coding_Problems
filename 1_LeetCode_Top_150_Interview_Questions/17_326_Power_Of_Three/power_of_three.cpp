#include <iostream>
#include <cmath>

/*
	============
	=== EASY ===
	============

	===========================
	326) Power Of Three
	===========================

	============
	Description:
	============

	Given an integer n, return true if it is a power of three. Otherwise,
	return false.

	An integer n is a power of three, if there exists an integer x such
	that n == 3x.


	Follow up: Could you solve it without loops/recursion?

	================================
	FUNCTION: isPowerOfThree(int n);
	================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 27
	Output: true
	Explanation: 27 = 33

	--- Example 2 ---
	Input: n = 0
	Output: false
	Explanation: There is no x where 3x = 0.

	--- Example 3 ---
	Input: n = -1
	Output: false
	Explanation: There is no x where 3x = (-1).

	*** Constraints ***
	-231 <= n <= 231 - 1

*/




/*
	------------
	--- IDEA ---
	------------

	While it's divisible by 3, keep dividing by 3 until it's no longer
	divisible by 3.

	Then just check if it's 1. If it is, then return true, else false.

	Note: I have NO IDEA why is this Approach more Space efficient than the
	other ones.
	
*/

/* Time  Beats: 96.56% */
/* Space Beats: 81.21% */
class Solution_Basic{
public:
	bool isPowerOfThree(int n)
	{
		if (n <= 0)
			return false;

		while (n % 3 == 0)
			n /= 3;

		return n == 1;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Let's assume that n is indeed a power of 3:
		n = 3^x    // Where 'x' is an INTEGER
	
	So if we take log base 3 on both sides:
		log3(n) = log3(3^x)

		log3(n) = x * log3(3)
		log3(n) = x * 1
		log3(n) = x

	Again, by the propery of Logarithm, we can change the base of log3(n):

		log10(n) / log10(3) = x
	
	Once we calculate this, if x turns out to be an INTEGER, then return true.
	It'll be an INTEGER if and only if n can be represented by the power of 3.

	Thus, if it's NOT an integer, then return false.

	However, since C++ works a bit differently than other languages, we cannot
	write it like this:

	bool isPowerOfThree(int n)
	{
		return std::log10(n) / std::log10(3) % 1 == 0;
	}

	Due to reasons of (double) values and % operator. Thus we have to implement
	it as shown below:

	(Or we can use a similar approach, as shown in the Solution below this
	one)
*/

/* Time  Beats: 96.56% */
/* Space Beats: 22.93% */

/* Time  Complexity: O(1) */
/*
	Space Complexity: O(1)
	I have no idea why this beats only around 22% Space. It's the same for
	all the other imeplementations of this Logarithmic Approach.
*/
class Solution_Logarithmic_1{
public:
	bool isPowerOfThree(int n)
	{
		return fmod(std::log10(n) / std::log10(3), 1.0) == 0;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same Idea, implemented differently.
	
*/

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Logarithmic_2{
public:
	bool isPowerOfThree(int n)
	{
		if (n <= 0)
			return false;

		double d = std::log10(n) / std::log10(3);

		return std::ceil(d) == std::floor(d);
	}
};




/*
	------------
	--- IDEA ---
	------------

	1162261467 is the largest integer power of 3. so if n is power of 3 it
	definitely divides 1162261467. Hope you understand it.
	
*/

/* Time  Beats: 11.30% */
/* Space Beats: 81.21% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Largest_Power_Of_3{
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};
