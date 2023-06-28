#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	==================================
	166) Fraction To Recurring Decimal
	==================================

	============
	Description:
	============

	Given two integers representing the numerator and denominator of a
	fraction, return the fraction in string format.

	If the fractional part is repeating, enclose the repeating part in
	parentheses.

	If multiple answers are possible, return any of them.

	It is guaranteed that the length of the answer string is less than 104 for
	all the given inputs.

	===================================================================
	FUNCTION: string fractionToDecimal(int numerator, int denominator);
	===================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: numerator = 1, denominator = 2
	Output: "0.5"

	--- Example 2 ---
	Input: numerator = 2, denominator = 1
	Output: "2"

	--- Example 3 ---
	Input: numerator = 4, denominator = 333
	Output: "0.(012)"

	*** Constraints ***
	-2^31 <= numerator, denominator <= 2^31 - 1
	denominator != 0

*/

/*
	------------
	--- IDEA ---
	------------

	So we can divide this question in three parts:

	1. Division with its own multiple for eg. 8 / 4 = 2
	2. Division without repeating numbers after decimal for eg. 41 / 2 = 20.5
	3. Division with repeating numbers after decimal for eg. 14 / 3 = 4.(6) or 
	                                                         47 / 18 = 2.6(1)

	Note : Here the repeating part is in parenthesis.

	For 1st Part we can normally divide the numbers and add it to the result
	string and return if the remainder is 0.

		//Code: 
		int q = num / den;
		int r = num % den;
		result += q;
		if(r == 0) return result;
	


	For 2nd part we need to add a “.” if remainder is not zero and then make
	the remainder 10 times everytime and append the quotient to the result
	string.

		//Code:
		while(r != 0)
			r *= 10;
			q = r / den;
			r = r % den;
			result += q;
	
	For the 3rd part we need to use and unordered_map so that we can store the
	position from where the repeating of number starts in front of the
	remainder. If the remainder is already in the map then we insert the “(”
	opening parenthesis at the position of that rem and lastly append a “)”
	closing parenthesis and break out of the loop and return the result.
	
		//Code :
		unordered_map<int, int> mp;
		while(r != 0)
			if(mp(r) is in map)
				int pos = mp[r];
				ans.insert(pos, "(");
				ans += ')';
				break;
			else
				mp[r] = ans.length();
				r *= 10;
				q = r / den;
				r = r % den;
				ans += q;


	Now it will give runtime error for cases like -1 / -2147483648 so we need
	to change the int to long.

		long num = labs(numerator), den = labs(denominator);
		long q = num / den;
		long r = num % den;
	
	and

		unordered_map<long, int> mp;
	
	We need to handle the case where there are negative numbers. So if
	numerator is negative and denominator is positive or numerator is positive
	and denominator is negative we need to add a “-“ negative symbol in the
	result.

		if (numerator > 0 ^ denominator > 0) 
			ans += '-';
	
	Final Code: (Down below)
*/

/* Time  Beats:  100% */
/* Space Beats: 57.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string fractionToDecimal(int numerator, int denominator)
	{
        if(!numerator)
			return "0";

        std::string result = "";

        if (numerator > 0 ^ denominator > 0)
			result += '-';

        long num = std::labs(numerator);
		long den = std::labs(denominator);

        long quotient = num / den;
        long remainder= num % den;
        result += to_string(quotient);
        
        if(remainder == 0)
			return result;
        
        result += '.';
        unordered_map<long, int> map;

        while(remainder != 0)
		{
            if(map.find(remainder) != map.end())
			{
                int pos = map[remainder];
                result.insert(pos, "(");
                result += ')';

                break;
            }
            else
			{
                map[remainder] = result.length();

				remainder *= 10;
                quotient  = remainder / den;
				remainder = remainder % den;

                result += to_string(quotient);
            }
        }

        return result;
    }
};
