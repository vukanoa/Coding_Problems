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

/* Time  Beats:   100% */
/* Space Beats: 51.65% */

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




/*
	------------
	--- IDEA ---
	------------

	The only "problematic" scenarios in this problem are 2 cases:
	k[k[k[]]]
		and
	k[k[]k[]k[]]

	It could be done using recursion, as we have already did in the above
	solution, however, we could do it using a stack, as well.

	Consider this example:
	54[ab6[cd]]

	Let's go character by character:

	1)
	54[ab6[cd]]
	#

	Stack:
	{5 |   |   |   |   |   |   |   |   }
	{5 | 4 |   |   |   |   |   |   |   }
	{5 | 4 | [ |   |   |   |   |   |   }
	{5 | 4 | [ | a |   |   |   |   |   }
	{5 | 4 | [ | a | b |   |   |   |   }
	{5 | 4 | [ | a | b | 6 |   |   |   }
	{5 | 4 | [ | a | b | 6 | [ |   |   }
	{5 | 4 | [ | a | b | 6 | [ | c | d }
	// First ']' closed bracket detected

	Now we're going to pop from our stack into our string "substr" like this:
		substr = stack.back() + substr;
	Since we want the right order.

	We pop until we get to an opening bracket '['. (We are sure there is at
	least one since we're told that the string input will always be valid. So
	If we had stumbled upon a closing bracket ']' then we're sure that an
	opening bracket '[' is already in our stack).

	After the while loop we pop once more, to get rid of the opening bracket
	'[' itself.

	Now we have the substring "cd". What do we want to do with it?
	Now that we have popped an opening bracket '[' as well, we have to pop
	digits until we get to a non digit character or until we get to the
	beginning of the string and then convert that number in our string 'k' and
	then multiply our substring "cd" exactly k numbers.

	The stack should look like this:

	{5 | 4 | [ | a | b                 }

	k = "6" // We have to convert a string to integer

	By multiplying it is meant that we push that substring into the stack
	exactly k times.

	So our stack now looks like this:

	{5 | 4 | [ | a | b | c | d | c | d | c | d | c | d | c | d | c | d }
	                    ----------------------------------------------
	                                 cd cd cd cd cd cd

	And then we do the outer problem by continuing to iterate through our
	while loop.

	The outer problem is now: 54[abcdcdcdcdcdcd]

	At the end we will have "abcdcdcdcdcdcd" repeated 54 times and put in our
	string "stack".

	We just return that.

	There was a minor issue with this problem. It is said that the string will
	always be valid, however 54-th Input was just "3".

	So I've added:
		if (isdigit(stack.back()))
			return "";

	To overcome that.
*/

/* Time  Beats:   100% */
/* Space Beats: 90.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Stack{
public:
	std::string decodeString(std::string s)
	{
		std::string stack;

		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ']')
				stack += s[i];
			else
			{
				std::string substr;

				while (stack.back() != '[')
				{
					substr = stack.back() + substr;
					stack.pop_back();
				}

				stack.pop_back(); // Pop the '['

				std::string k;
				while (!stack.empty() && isdigit(stack.back()))
				{
					k = stack.back() + k;
					stack.pop_back();
				}

				int num = std::stoi(k);

				while (num-- > 0)
					stack += substr;
			}
		}

		if (isdigit(stack.back()))
			return "";

		return stack;
	}
};


int
main()
{
	Solution sol;
	Solution_Stack sol_stack;

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
	// std::string result = sol.decodeString(s);
	std::string result = sol_stack.decodeString(s);


	/* Write Output */
	std::cout << "\n\tOutput: " << result << "\n\n";


	return 0;
}
