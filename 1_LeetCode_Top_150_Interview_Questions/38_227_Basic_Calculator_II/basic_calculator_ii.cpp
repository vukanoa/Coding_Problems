#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	227) Basic Calculator II
	===========================

	============
	Description:
	============

	Given a string s which represents an expression, evaluate this expression
	and return its value. 

	The integer division should truncate toward zero.

	You may assume that the given expression is always valid. All intermediate
	results will be in the range of [-2^31, 2^31 - 1].

	======
	Note: You are not allowed to use any built-in function which evaluates
	      strings as mathematical expressions, such as eval().
	======

	==================================
	FUNCTION: int calculate(string s);
	==================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: s = "3+2*2"
	Output: 7

	--- Example 2 ---
	Input: s = " 3/2 "
	Output: 1

	--- Example 3 ---
	Input: s = " 3+5 / 2 "
	Output: 5

	*** Constraints ***
	1 <= s.length <= 3 * 105
	s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
	s represents a valid expression.
	All the integers in the expression are non-negative integers in the range [0, 231 - 1].
	The answer is guaranteed to fit in a 32-bit integer.

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 43.92% */
/* Space Beats: 41.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int calculate(string s)
	{
		std::istringstream in('+' + s + '+');

		long long total = 0;
		long long term  = 0;
		long long n;

		char op;

		while (in >> op)
		{
			if (op == '+' or op == '-')
			{
				total += term;
				in >> term;
				term *= 44 - op;
			}
			else
			{
				in >> n;

				if (op == '*')
					term *= n;
				else
					term /= n;
			}
		}

		return total;
	}
};
