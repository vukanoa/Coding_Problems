#include <iostream>
#include <stack>


/*
	============
	=== EASY ===
	============
	
	===========================
	20) Valid Parentheses
	===========================
	
	============
	Description:
	============

	Given a string s containing just the characters '(', ')', '{', '}', '[' and
	']', determine if the input string is valid.

	An input string is valid if:
		Open brackets must be closed by the same type of brackets.
		Open brackets must be closed in the correct order.
		Every close bracket has a corresponding open bracket of the same type.

	======================================
	FUNCTION: bool isValid(std::string s);
	======================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  s = "()"
	Output: true
	
	--- Example 2 ---
	Input:  s = "()[]{}"
	Output: true
	
	--- Example 3 ---
	Input: s = "(]"
	Output: false
	
	*** Constraints ***
	1 <= s.legnth <= 10^4
	s consists of parentheses only '()[]{}'.

*/

class Solution{
public:
	bool isValid(std::string s)
	{

		if (s.length() == 1)
			return false;

		std::stack<char> stack;

		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '(' || s[i] == '[' || s[i] == '{')
				stack.push(s[i]);
			else
			{
				if (stack.empty())
					return false;

				if (s[i] == ')')
				{
					if ('(' != stack.top())
						return false;
				}
				else if (s[i] == ']')
				{
					if ('[' != stack.top())
						return false;
				}
				else if (s[i] == '}')
				{
					if ('{' != stack.top())
						return false;
				}

				stack.pop();
			}
		}

		return stack.empty();
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string s = "()";

	/* Example 2 */
	// std::string s = "()[]{}";

	/* Example 3 */
	// std::string s = "(]";

	/* Example 4 */
	// std::string s = ")[]";

	/* Example 5 */
	std::string s = "([]{{[]([])}})";

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== VALID PARENTHESES ===";
	std::cout << "\n\t=========================\n";

	std::cout << "\n\tString: \"" << s << "\" ";
	bool valid = sol.isValid(s);

	if (valid)
		std::cout << "is INDEED valid!\n\n";
	else
		std::cout << "is NOT valid!\n\n";

	return 0;
}
