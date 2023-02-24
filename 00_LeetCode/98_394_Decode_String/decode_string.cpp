#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	394) Decode String
	===========================

	============
	Description:
	============

	Given an encoded string, return its decoded string.

	The encoding rule is: k[encoded_string], where the "encoded_string" inside
	the square brackets is being repeated exactly 'k' times. Note that 'k' is
	guaranteed to be a positive integer.

	You may assume that the input string is always valid; there are no extra
	white spaces, square brackets are well-formed, etc. Furthermore, you may
	assume that the original data does not contain any digits and that digits
	are only for those repeat numbers, 'k'. For example, there will not be
	input like 3a or 2[4].

	The test cases are generated so tha the length of the output will never
	exceed 10^5.

	========================================
	FUNCTION: string decodeString(string s);
	========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s = "3[a]2[bc]"
	Output: "aaabcbc"

	--- Example 2 ---
	Input:  s = "3[a2[c]]"
	Output: "accaccacc"

	--- Example 3 ---
	Input:  s = "2[abc]3[cd]ef"
	Output: "abcabccdcdcdef

	*** Constraints ***
	1 <= s.length <= 30
	s consists of lowercase English letters, digits, and square brackets '[]'.
	s is guaranteed to be a valid input.
	All the integers in 's' are in the range [1, 300].

*/


/*
	------------
	--- IDEA ---
	------------

	It's pretty straight-forward.

	Algorithm:
	We call the helper function with a starting index.

	We do the while loop until we hit the end of the string or until we hit a
	character ']'(closing bracket).

	We need both since the Outer loop is going to stop once we hit end of the
	string 's' and inner labor is going to use the closing bracket ']'.

	First, let's explain the "else" part in the while loop, since that is where
	we're going first. We go down that path if a current character is a digit.

	And we must begin with a digit since we're told that the input is always a
	valid string.

	Since we can have multiple-digit numbers that we need to use as a
	multiplier of string inside '[]', we have to "parse" it one by one.

	n is 0 at the beginning.
	As long as current character is digits and we still haven't reached the end
	then
		n = n * 10 + s[i++] - '0';

	(We have to subtract '0' from s[i] since s[i] is a character of digit and
	not a digit itself).
	Ascii representation of digit 3 is 51, thus 51 - 48(which is 0 in ASCII)
	gives us the integer of value 3.

	We use that number to add to the previous n * 10.
	We multiply by 10 because that's how a number is constructed of individual
	digits from left to right.

	Then we skip the opening bracket '['.

	And then we recursively call this same function but with a current position
	of 'i'.
	This will only construct(maybe recursively again as in example 2) the
	string in the brackets '[]' that needs to be multiplied.

	Inner "multiplications" will already be present in the "result" string.

	At the end we just return "result".

	Easiest way to get a feel of how this works is to go line-by-line through
	this code for all of the 3 given examples and possibly some of your own
	ones.
*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	std::string decodeString(const std::string& s, int& i)
	{
		std::string result;

		while (i < s.length() && s[i] != ']')
		{
			if (!isdigit(s[i]))
				result += s[i++];
			else
			{
				int n = 0;

				while (i < s.length() && isdigit(s[i]))
					n = n * 10 + s[i++] - '0';

				i++; // '['
				std::string t = decodeString(s, i);
				i++; // ']'

				while (n-- > 0)
					result += t;
			}
		}

		return result;
	}

	std::string decodeString(std::string s)
	{
		int i = 0;

		return decodeString(s, i);
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string s = "3[a]2[bc]";

	/* Example 2 */
	// std::string s = "3[a2[c]]";

	/* Example 3 */
	// std::string s = "2[abc]3[cd]ef";

	/* Example 4 */
	std::string s = "12[x]3[cd4[g]]";

	std::cout << "\n\t=====================";
	std::cout << "\n\t=== DECODE STRING ===";
	std::cout << "\n\t=====================\n";

	/* Write Input */
	std::cout << "\n\ts = \"" << s << "\"\n";

	/* Solution */
	std::string result = sol.decodeString(s);

	/* Write Output */
	std::cout << "\n\tOutput: " << result << "\n\n";

	return 0;
}
