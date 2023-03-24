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


/*
	------------
	--- IDEA ---
	------------

	First check if the string 's' is of length 1. If it is then it's certainly
	false.

	Make a stack.

	Example:
		([{]})
	is FALSE. Closing parenthesis/bracket/brace MUST match lastly opened
	parenthesis/bracket/brace.

	([)] is FALSE
	([]) is TRUE
	()[] is TRUE

	Iterate through each character in our string 's'.
	If it is an open parenthesis/bracket/brace then push it onto the stack.
	If it is NOT an open(meaning it's closed) parenthesis/bracket/brace then:
		1. Check if the stack is Empty
			This check if the very first character in our string 's' is a
			closing parenthesis/bracket/brace. If it is - return false

		2. If current character is a closing parenthesis:
			Check if a corresponding open parenthesis is on the top of the
			stack with a function: stack.top().
			If at the top is anything other than '(' - return false.

		3. If current character is a closing bracket:
			Check if a corresponding open bracket is on the top of the stack
			with a function: stack.top().
			If at the top is anything other than '[' - return false.

		4. If current character is a closing brace:
			Check if a corresponding open brace is on the top of the stack with
			a function: stack.top().
			If at the top is anything other than '{' - return false.
		
		5. If it was a corresponding opened parenthesis/bracket/brace on the
		   top, then just pop from the stack.

		stack.top() just returns what is at the top of the stack without
		popping it.

		After we've processed the whole string 's', just check if the stack
		is empty.
		If it is INDEED Empty, then return TRUE,  meaning a string s is VALID
		If it is NOT    Empty, then return FALSE, meaning a string s is INVALID

*/


/* Time  Beats: 100% */
/* Space Beats: 56.7% */
/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(n)
	O(n) when the string 's' is: ([{{{{{{{
	All openened (any) combination of parentheses/brackets/braces.
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


	/* Write Input */
	std::cout << "\n\tString: \"" << s << "\" ";


	/* Solution */
	bool valid = sol.isValid(s);


	/* Write Output */
	if (valid)
		std::cout << "is INDEED valid!\n\n";
	else
		std::cout << "is NOT valid!\n\n";

	return 0;
}
