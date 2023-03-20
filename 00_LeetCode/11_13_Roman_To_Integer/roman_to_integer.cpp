#include <iostream>
#include <unordered_map>

/*
	============
	=== EASY ===
	============

	===========================
	13) Roman to Integer
	===========================

	============
	Description:
	============

	Roman numerals are represented by seven different symbols:
	I, V, X, L, C, D and M.

	Symbol    Value
	I         1
	V         5
	X         10
	L         50
	C         100
	D         500
	M         1000

	===================================
	FUNCTION: int romanToInt(string s);
	===================================

	For example, 2 is written as II in Roman numeral, just two ones added
	together. 12 is written as XII, which is simply X + II. The number 27 is
	written as XXVII, which is XX + V + II.

	Roman numerals are usually written largest to smallest from left to right.
	However, the numeral for four is not IIII. Instead, the number four is
	written as IV. Because the one is before the five we subtract it making
	four. The same principle applies to the number nine, which is written as
	IX. There are six instances where subtraction is used:
		1. 'I' can be placed before 'V' (5) and 'X'(10) to make 4 and 9.
		2. 'X' can be placed before 'L' (50) and 'C'(100) to make 40 and 90.
		3. 'C' can be placed before 'D' (500) and 'M'(1000) ot make 400 and 900.

	Given a roman numeral, convert it to an integer.

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  s = "III"
	Output: 3

	--- Example 2 ---
	Input:  s = "LVIII"
	Output 58

	--- Example 3 ---
	Input:  s = "MCMXCIV"
	Output: 1994

	*** Constraints ***
	1 <= s.length <= 15
	s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
	It is guaranteed that s is a valid roman numeral in the range [1, 3999]

*/


/*
	------------
	--- IDEA ---
	------------

	We have an unordered Hash Map [char, int] corresponding to Roman characters
	and its values.

	We iterate through a given Roman number from left to right.
	Consider Example:
		MCIV
		^

	If we find that the current one is greater than its right Roman character
	then we just add its value to our variable "number" which we return as a
	final result.

	However, if the current one is less than its right Roman character(less in
	values) then we subtract current Roman character's value from our variable
	"number".

	Why?
	If we are at position 2(at character 'I' for the above example) then
	if its right Roman character is greater in value than the current one('I')
	then that means that this character represent "decreasing part" of the very
	next Roman character. Thus we subtract this one and add the next one.

*/



/* Time  Beats: 74.40% */
/* Space Beats: 32.17% */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int romanToInt(std::string s)
	{
		std::unordered_map<char,int> umap;
		int number = 0;

		umap.insert({'I', 1});
		umap.insert({'V', 5});
		umap.insert({'X', 10});
		umap.insert({'L', 50});
		umap.insert({'C', 100});
		umap.insert({'D', 500});
		umap.insert({'M', 1000});

		for (int i = 0; i < s.length(); i++)
		{
			if (umap[s[i]] >= umap[s[i + 1]])
				number += umap[s[i]];
			else
				number -= umap[s[i]];
		}

		return number;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::string s = "III";

	/* Example 2 */
	// std::string s = "LVIII";

	/* Example 3 */
	// std::string s = "MCMXCIV";

	/* Example 4 */
	std::string s = "MDLXXIX";

	/* Example 5 */
	// std::string s = "XIV";

	std::cout << "\n\t========================";
	std::cout << "\n\t=== ROMAN TO INTEGER ===";
	std::cout << "\n\t========================\n";

	/* Write Input */
	std::cout << "\n\tRoman: " << s << "\n";

	/* Solution */
	int number = sol.romanToInt(s);

	/* Write Output */
	std::cout << "\n\tInteger: " << number << "\n\n";

	return 0;
}
