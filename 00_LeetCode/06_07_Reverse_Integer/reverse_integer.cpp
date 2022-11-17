#include <iostream>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================
    7) Reverse Integer
    ==================
    
    ============
    Description:
    ============
    
    Given a signed 32-bit integer x, return x with its digits reversed.
    If reversing x causes the value to go outside the signed 32-bit integer
    range [-2^31, 2^31 - 1], then return 0;
    
    =====
    Note: Assume the environment does not allow you to store 64-bit integers (signed or unsigned)
    =====
    
    =============================================================================================
    
    --- Example 1 ---
    Input: x = 123
    Output: 321
    
    --- Example 2 ---
    Input: x = -123
    Ouput: -321
    
    --- Example 3 ---
    Input: x = 120
    Output: 21
    
    *** Constraints ***
    -2^31 <= x <= 2^31 - 1
*/

/*
	INT_MAX =  2147483647
	INT_MIN = -2147483648
*/

class Solution {
public:
	int reverse(int x)
	{
		int rev = 0;
		int number;

		// If it was 1B then -8 can exist, but 8 cannot
		if (x == INT_MIN)
			return 0;

		// If it is a negative number
		if (x < 0)
			number = x * (-1);
		else
			number = x;

		while (number)
		{
			// Exceeded 32-bit range
			if (rev > (INT_MAX / 10) || rev > ((INT_MAX / 10) + number % 10))
				return 0;

			rev = rev * 10 + number % 10;
			number = number / 10;
		}

		// If it was a negative number
		if (x < 0)
			return rev * (-1);

		return rev;
	}
};


int
main()
{
	Solution sol;
	// int number =  123;
	// int number = -123;
	// int number =  120;
	// int number = -120;
	int number = -2147483412;
	// int number =  2147483647; // INT_MAX
	// int number = -2147483648; // INT_MIN

	int rev = sol.reverse(number);
	
	std::cout << "\n\tOriginal number: " << number << "\n\n";
	std::cout << "\n\tReversed number: " << rev << "\n\n";

	return 0;
}
