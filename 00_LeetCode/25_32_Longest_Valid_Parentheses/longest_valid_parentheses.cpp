#include <iostream>
#include <stack>


/*
	============
	=== HARD ===
	============
	
	=============================
	32) Longest Valid Parentheses
	=============================
	
	============
	Description:
	============

	Given a string containing just the characters '(' and ')', return the
	length of the longest valid (well-formed) parentheses substring.
	
	=====================================================
	FUNCTION: int longestValidParentheses(std::string s);
	=====================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  s = "(()"
	Output: 2
	
	--- Example 2 ---
	Input:  s = ")()())"
	Output: 4
	
	--- Example 3 ---
	Input:  s = ""
	Output: 0
	
	--- Example 4 ---
	Input:  s = "()(()"
	Output: 2
	
	--- Example 5 ---
	Input:  s = ")()())()()("
	Output: 4

	*** Constraints ***
	0 <= s.length <= 3 * 10^4
	s[i] is '(', or ')'.

*/

/*
	------------
	--- IDEA ---
	------------

	Dynamic Programming:
	We use array dp where i-th element represents longest valid substring
	ending at i-th index.

	dp is initialized with 0's at the beginning.

	Valid substring MUST end with ')', therefore substrings ending with '('
	will always contain '0' at their corresponding dp indices.

	Thus, we update the dp array only when ')' is encountered.

	To fill dp array we will check every two consecutive characters of the
	string and if:
		1. s[i] == ')' and s[i - 1] == '(', i.e. string looks like "...()" then
			dp[i] = dp[i - 2] + 2;

			We do so because the ending "()" portion is a valid substring
			anyhow and leads to an increment of 2 in the length of the just
			previous valid substring's length.

		2. s[i] == ')' and s[i - 1] == ')', i.e. string looks like "...))" then
			if s[i - dp[i - 1] - 1] == '(' then
				dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2;

			The reason behind this is that if the 2nd last ')', the left one, 
			was a part of a valid substring, for the last ')' to be a part of a
			larger substring, there must be a corresposnding start '(' which
			lies before the valid substring of which the 2nd lat ')' is a part.
			Thus, if the character before this substring, happens to be '(', we
			update the dp[i] as an addition of 2 in the length of this
			substring which is dp[i - 1].

			To this, we also add the length of the valid substring just before
			the term "(,sub_s,)", i.e. dp[i - dp[i - 1] - 2]

*/



/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_dp{
public:
	int
	longestValidParentheses(std::string s)
	{
		int longest = 0;

		int dp[s.length()];
		for (int i = 0; i < s.length(); i++)
			dp[i] = 0;

		for (int i = 1; i < s.length(); i++)
		{
			if (s[i] == ')')
			{
				if (s[i - 1] == '(')
					dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
				else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')
					dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;

				longest = std::max(longest, dp[i]);
			}
		}

		return longest;
	}
};



/*
	------------
	--- IDEA ---
	------------

	Using Stack

	Instead of finding every possible strin and checking its validiy, we can
	make use of a stack while scanning the given string to:
		1. Check if the string scanned so far is valid.
		2. Find the length of the longest valid string.
	
	In order to do so, we start by pushing -1 onto the stack. For every '('
	encountered, we push its index onto the stack.

	For every ')' encountered, we pop the topmost element. Then, the length of
	the currently encountered valid string of parentheses will be the
	difference between the current element's index and the top element of the
	stack.

	If, while popping the element, the stack becomes empty, we will push the
	current element's index onto the stack. In this way, we can continue to
	calculate the length of the valid substrings and return the lengths of the
	longest valid string at the end.

	( ) ) ( ( ( ) )
	0 1 2 3 4 5 6 7

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_stack{
public:
	int
	longestValidParentheses(std::string s)
	{
		int longest = 0;
		std::stack<int> stack;
		stack.push(-1);

		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '(')
				stack.push(i);
			else
			{
				stack.pop();

				if (stack.empty())
					stack.push(i);
				else
					longest = std::max(longest, i - stack.top());
			}
		}
		
		return longest;
	}
};


int
main()
{
	// Solution_dp sol;
	Solution_stack sol;

	/* Example 1 */
	std::string s = "(()";

	/* Example 2 */
	// std::string s = ")()())";

	/* Example 3 */
	// std::string s = "";

	/* Example 4 */
	// std::string s = "()(()";

	/* Example 5 */
	// std::string s = ")()())()()(";

	std::cout << "\n\t=================================";
	std::cout << "\n\t=== LONGEST VALID PARENTHESES ===";
	std::cout << "\n\t=================================\n\n";



	int output = sol.longestValidParentheses(s);
	std::cout << "\n\tString: \"" << s << "\"\n";
	std::cout << "\n\tLongest Valid parentheses: " << output << "\n\n";

	return 0;
}
