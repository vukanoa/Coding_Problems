#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	12) Integer to Roman
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

	For example, 2 is written as II in Roman numeral, just two one's added
	together. 12 is written as XII, which is simply X + II. The number 27
	is written as XXVII, which is XX + V + II.

	Roman numerals are usually written largest to smallest from left to right.
	However, the numeral for four is not IIII. Instead, the number four is
	written as IV. Because the one is before the five we subtract it making
	four. The same principle applies to the number nine, which is written as
	IX. There are six instances where subtraction is used:
		1. 'I' can be placed before V(5) and X(10) to make 4 and 9.
		2. 'X' can be placed before L(50) and C(100) to make 40 and 90.
		3. 'C' can be placed before D(500) and M(1000) to make 400 and 900.

	Given an integer, convert it to a roman numeral.

	====================================
	FUNCTION: string intToRoman(int num)
	====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  num = 3
	Output: "III"

	--- Example 2 ---
	Input:  num = 58
	Output: "LVIII"

	--- Example 3 ---
	Input:  num = 1994
	Output: "MCMXCIV"

	*** Constraints ***
	1 <= num <= 3999
*/



/*
	------------
	--- IDEA ---
	------------

	--- Solution 1 ---

	We have 13 different values in "values" array.

	While number is greater than 0 we are trying to find the very first value
	from this array that is less then the current value of num(since we are
	subtracting the "covered" part in each iteration).

	For example 58.
	We stop when x = 6(x is starting from 12). Why?

	Because x = 6 is 50 which is the largest roman letter we have in our
	number.
	Then we subtract 58 from this largest roman letter, which is 50 in this
	case, and we get 8.

	Now we repeat the process until we have "covered" the whole number, meaning
	num == 0



	--- Solution 2 ---

	It's self-explanatory. We are able to do this only because we are told that
	the number isn't greater than 3999.

	We wouldn't be able to do this if a number was able to be arbitrarily
	large.

*/



/*
	Time  Complexity: O(n)
	Since 3999 is max value possible, the number of digits is negligible. It
	could also be considered O(1)

*/
/* Space Complexity: O(1) */
class Solution{
public:
	std::string intToRoman(int num)
	{
		int values[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
		std::string romans[13] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

		int x = 13 - 1;
		std::string roman_num = "";

		while (num > 0)
		{
			while (num < values[x])
				x--;

			roman_num += romans[x];
			num -= values[x];
		}

		return roman_num;
	}
};


/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
	std::string intToRoman(int num)
	{
		std::string ones      [] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
		std::string tens      [] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
		std::string hundreds  [] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
		std::string thousands [] = {"", "M", "MM", "MMM"};

		return thousands[num/1000] + hundreds[(num % 10) / 100] + tens[(num % 100) / 10] + ones[num % 10];
	}
};


int
main()
{
	Solution sol;
	// Solution sol2;

	// int num = 1994;
	// int num = 8;
	// int num = 9;
	// int num = 37;
	// int num = 1998;
	int num = 2004;

	std::cout << "\n\t========================";
	std::cout << "\n\t=== INTEGER TO ROMAN ===";
	std::cout << "\n\t========================\n";

	std::string roman = sol.intToRoman(num);
	// std::string roman = sol2.intToRoman(num);

	std::cout << "\n\tInteger: " << num;
	std::cout << "\n\tRoman:   " << roman << "\n\n";

	return 0;
}
