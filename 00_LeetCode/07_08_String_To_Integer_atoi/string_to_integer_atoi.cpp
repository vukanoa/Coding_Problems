#include <iostream>
#include <vector>
#include <climits>

static const int ASCII_ZERO = 48;
static const int ASCII_NINE = 57;

/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	8) String to Integer (atoi)
	===========================
	
	============
	Description:
	============
	
	Implement the myAtoi(string s) function, which converts a string to a
	32-bit signed integer(similar to C/C++'s atoi function).
	
	The algorithm for myAtoi(string s) is as follows:
	
	Read in and ignore any leading whitespace.
	
	Check if the next character(if not already at the end of the string) is
	'-' or '+'. Read this character in if it is either. This determines if the
	final resust is negative or positive respectively. Assume the resust is
	positive if neither is present.
	
	Read in next the characters until the next non-digit character or the end
	of the input is reached. The rest of the string is ignored.
	
	Convert these digits into an integer(i.r. "123" -> 123, "0032" -> 32). If
	no digits were read, then the integer is 0. Change the sign as necessary
	(from step 2).
	
	If integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], 
	then clamp the integer so that it remains in the range. Specifically,
	integer less than -2^31 should be clamped to -2^31, and integers greater
	than 2^31 - 1 should be clamped to 2^31 - 1.
	
	Return the integer as the final result.
	
	=====
	Node:
	=====
	
	- Only the space character ' ' is considered a whitespace character.
	- Do NOT ignore any characters other than the leading whitespace or the
	  rest of the string after the digits.
	
	===============================
	FUNCTION: int myAtoi(string s);
	===============================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  s = "42"
	Output: 42
	
	--- Example 2 ---
	Input:  s = "    -42"
	Output: -42
	
	--- Example 3 ---
	Input:  s = "4193 with words"
	Output: 4193
	
	*** Constraints ***
	0 <= s.length <= 200
	s consists of English Letters(lower-case and upper-case), digits(0-9), ' ',
	'+', '-', and '.'.
*/

using namespace std;

class Solution{
public:
	int myAtoi(const string& s)
	{
		std::vector<int> number;

		int integer = 0;
		bool negative = false;

		int i = 0;
		while (s[i] == ' ')
			i++;

		if (s[i] == '-')
		{
			negative = true;
			i++;
		}
		else if (s[i] == '+')
			i++;

		// While it's a digit
		while (i < s.length() && s[i] >= 48 && s[i] <= 57)
			number.push_back(s[i++] - '0');

		for (int i = 0; i < number.size(); i++)
		{
			if ((integer >= INT_MAX / 10 && number[i] >= 7) || (integer >= ((INT_MAX / 10) + number[i])))
				return INT_MAX;
			else if ((integer <= INT_MIN / 10 && number[i] >= 8) || (integer <= ((INT_MIN / 10) - number[i])))
				return INT_MIN;

			if (negative)
			    integer = integer * 10 - number[i];
			else
			    integer = integer * 10 + number[i];
		}

		return integer;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// string s = "42";
	// int num = sol.myAtoi(s);

	/* Example 2 */
	// string s = "   42";
	// int num = sol.myAtoi(s);

	/* Example 3 */
	// string s = "   -42";
	// int num = sol.myAtoi(s);

	/* Example 4 */
	// string s = "   -42with words";
	// int num = sol.myAtoi(s);

	/* Example 5 */
	// string s = "4193 with words";
	// int num = sol.myAtoi(s);

	/* Example 6 */
	// string s = "0032";
	// int num = sol.myAtoi(s);

	/* Example 7 */
	// string s = "2147483647";
	// int num = sol.myAtoi(s);

	/* Example 8 */
	// string s = "-2147483648";
	// int num = sol.myAtoi(s);

	/* Example 9 */
	string s = "2147483646";
	int num = sol.myAtoi(s);

	std::cout << "\n\tString \"" << s << "\" converted is " << num << "\n\n";
	
	return 0;
}

/*
		I could've saved some memory, but the efficiency would decrease

		// std::vector<int> digits;
		// While it's a digit
		// while (i < s.length() && s[i] >= 48 && s[i] <= 57)
		// 	number.push_back(s[i++] - '0');

		for (int i = 0; i < number.size(); i++)
		{
			int digit = s[i++] - '0';
            if ((integer >= INT_MAX / 10 && digit >= 7) || (integer >= ((INT_MAX / 10) + digit)))
				return INT_MAX;
			else if ((integer <= INT_MIN / 10 && digit >= 8) || (integer <= ((INT_MIN / 10) - digit)))
				return INT_MIN;

			if (negative)
			    integer = integer * 10 - digit;
			else
			    integer = integer * 10 + digit;
		}
*/

