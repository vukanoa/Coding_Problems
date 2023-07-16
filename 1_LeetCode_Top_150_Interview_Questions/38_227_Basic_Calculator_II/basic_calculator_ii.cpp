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

	Self-Explanatory code using Stacks(actually vector, but as a stack).

*/

/* Time  Beats: 88.05% */
/* Space Beats: 23.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Stack{
public:
	int calculate(string s)
	{
		char op  = '+'; 
		int curr = 0; 
		std::vector<int> stack; 
		
		for (int i = 0; i < s.size(); ++i)
		{
			if(std::isdigit(s[i]))
				curr = curr*10 + (s[i] - '0'); 

			if(i == s.size() - 1 || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			{
				if (op == '+')
					stack.push_back(curr); 
				else if (op == '-')
					stack.push_back(curr * (-1)); 
				else if (op == '*')
				{
					int num = stack.back();
					stack.pop_back();
					stack.push_back(num * curr);
				}
				else if (op == '/')
				{
					int num = stack.back();
					stack.pop_back();
					stack.push_back(num / curr); 
				}

				curr = 0;
				op = s[i];      
			}
		}

		return accumulate(stack.begin(), stack.end(), 0); 
	}
};
