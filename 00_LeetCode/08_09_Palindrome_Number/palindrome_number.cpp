#include <iostream>
#include <climits>


/*
	============
	=== EASY ===
	============

	====================
	9) Palindrome Number
	====================

	============
	Description:
	============

	Given an integer x, return "true" if x is a palindrome, and "false"
	otherwise.

	===================================
	FUNCTION: bool isPalindrome(int x);
	===================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: x = 121
	Output: true

	--- Example 2 ---
	Input: x = -121
	Output: false

	--- Example 3 ---
	Input: x = 10
	Output: false

	*** Constraints ***
	-2^(31) <= x <= 2^(31) - 1

	=========================================================================
	FOLLOW UP: Could you solve it without converting the integer to a string?
	=========================================================================
*/


/*
	------------
	--- IDEA ---
	------------

	Negative numbers are never palindromes because of a sign '-'.
	Also if a number is not 0, meaning it's greater than 0(since we know, at
	this point that our number x isn't negative or else we would've been out
	of this functions already).

	If it's greater than 0, then check if the last digit of that number is 0.
	If it is 0 then that means that there is no corresponding Palindrome since
	we are sure our initial value "x" does NOT contain leading zeroes.

	If initial number x is == 0, then that is already a Palindrome so just
	return true.

	In while loop we do the same thing as in Problem: 06_07_Reverse_Integer
	if x_rev > INT_MAX / 10 then whichever number we are adding will always
	Overflow, therefore:
		return false.

	If we successfully finish the while loop then just check if now constructed
	value x_rev is equal to initial value.

	If it is INDEED then that's a Palidrome, return true;
	If it is NOT    then return false;

*/


class Solution {
public:
	bool isPalindrome(const int& x)
	{
		if (x < 0 || (x != 0 && x % 10 == 0))
			return false;
		else if (x == 0)
			return true;

		int tmp = x;
		int x_rev = 0;

		while (tmp)
		{
			if (x_rev > INT_MAX / 10 || x_rev > (INT_MAX / 10 + tmp % 10))
				return false;

			x_rev = x_rev * 10 + tmp % 10;
			tmp = tmp / 10;
		}

		return x == x_rev;
	}
};

int
main()
{
	Solution sol;

	// int x = 121;
	// int x = -121;
	// int x = 10;
	// int x = 1234321;
	int x = 12344321;
	// int x = 123455221;
	// int x = INT_MAX;
	// int x = INT_MIN;
	// int x = 1234567899;

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== PALINDROME NUMBER ===";
	std::cout << "\n\t=========================\n";


	if (sol.isPalindrome(x))
		std::cout << "\n\tNumber: " << x << " is INDEED a Palindrome!\n\n";
	else
		std::cout << "\n\tNumber: " << x << " is NOT a Palindrome!\n\n";


	return 0;
}
