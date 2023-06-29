#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	==============================
	172) Factorial Trailing Zeroes
	==============================

	============
	Description:
	============

	Given an integer n, return the number of trailing zeroes in n!.

	Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.


	Follow up: Could you write a solution that works in logarithmic time
	           complexity?

	====================================
	FUNCTION: int trailingZeroes(int n);
	====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: n = 3
	Output: 0
	Explanation: 3! = 6, no trailing zero.

	--- Example 2 ---
	Input: n = 5
	Output: 1
	Explanation: 5! = 120, one trailing zero.

	--- Example 3 ---
	Input: n = 0
	Output: 0

	*** Constraints ***
	0 <= n <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	First a Question - In what situation will you get a trailing zero?

	The most obvious answer is: Whenever we multiply a non-zero value by 10.

	1 * 10 = 10
	2 * 10 = 20
	etc.

	If we multiply a number by 10, 7 times, we will get 7 trailing zeroes.
	
	Although we can see that number 10 can be "built" by using 2 and 5:
		2 * 5 = 10
	
	So what does that tell us?

	Another way to get a trailing zero is to multiply a number by 2 and 5.

	So the number of 2*5's will tell us how many trailing zeroes we will have.

	1 * 2 * 5 * 2 * 5 = 100
	    ~~~~~   ~~~~~
	     one     two 

	
	Now let's look at factorial of 5:
		
		5! = 1 * 2 * 3 * 4 * 5 = 120
		                 |	
		                 v	
		                 _____	
		5! = 1 * 2 * 3 * 2 * 2 * 5 = 120
		                     ~~~~~
		                      one 

	How many times did we multiply a 2 by 5? Once. Therefore one trailing zero.

	However, instead of keeping track of number of 2*5's, we only have to count
	the 5's. Why? How?

	In any factorial number, it's guaranteed that we'll always have more 2's
	than 5's.

	So however many 5's we got, it's guaranteed that the number of 2's will be
	at least greater by one than the number of 5's, usually the difference is
	much larger. It's important to emphasize that there are ALWAYS more 2's.

	Therefore, we'll only count up the 5's.

	Let's look at another example: 

	10! = 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 = 3628800
	                  |                       |
	                  ---                     -------
	                    |                           |
	                    v                           v
	                  _____                       _____
	10! = 1 * 2 * 3 * 2 * 2 * 5 * 6 * 7 * 8 * 9 * 2 * 5 = 3628800
	                      ~~~~~                   ~~~~~
	                       one                     two
	

	If we had a factorial of 25:
	25 = 1*2*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19*20*21*22*23*24*25

	We have to find the multiples of 5 to get the number of trailing zeroes.

	Here we have 5 numbers that are multiples of 5:
	    5   *    10   *   15    *   20    *   25 // 25 contains TWO 5's
	    |        |        |          |        |      
	    v        v        v          v        v      
	(2 * 5) * (2 * 5) * (2 * 5) * (2 * 5) * (5 * 5)

	However, we can notice that we don't have to calculate the factorial and
	then traverse the elements that form a product to count up the 5's.

	We can work on the number n itself.

	Keep diving by 5 until it's no longer greater than 0. Each time increment
	the counter.

	That's the whole idea.
*/

/* Time  Beats:  100% */
/* Space Beats: 93.31% */

/* Time  Complexity: O(log(n)) */
/* Space Complexity: O(1) */
class Solution{
public:
	int trailingZeroes(int n)
	{
		int count = 0;

		while (n > 0)
		{
			n /= 5;
			count += n;
		}

		return count;
	}
};
