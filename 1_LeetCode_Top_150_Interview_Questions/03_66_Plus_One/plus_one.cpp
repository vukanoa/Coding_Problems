#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	66) Plus One
	===========================

	============
	Description:
	============

	You are given a **large integer** represented as an integer array "digits",
	where eeach digit[i] is the i-th digit of the integer.o

	You are given a large integer represented as an integer array digits, where
	each digits[i] is the ith digit of the integer. The digits are ordered from
	most significant to least significant in left-to-right order. The large
	integer does not contain any leading 0's.

	Increment the large integer by one and return the resulting array of
	digits.

	===================================================
	FUNCTION: vector<int> plusOne(vector<int>& digits);
	===================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: digits = [1,2,3]
	Output: [1,2,4]
	Explanation: The array represents the integer 123.
	Incrementing by one gives 123 + 1 = 124.
	Thus, the result should be [1,2,4].

	--- Example 2 ---
	Input: digits = [4,3,2,1]
	Output: [4,3,2,2]
	Explanation: The array represents the integer 4321.
	Incrementing by one gives 4321 + 1 = 4322.
	Thus, the result should be [4,3,2,2].


	--- Example 3 ---
	Input: digits = [9]
	Output: [1,0]
	Explanation: The array represents the integer 9.
	Incrementing by one gives 9 + 1 = 10.
	Thus, the result should be [1,0].


	*** Constraints ***
    1 <= digits.length <= 100
    0 <= digits[i] <= 9
    digits does not contain any leading 0's.
	

*/


/*
	------------
	--- IDEA ---
	------------

	Try to increment the least significant digit in the vector and if it's less
	than 10 after incrementing(basically if it's NOT 9) then just increment
	that digits in the vector and return the entire vector as a result.

	On the other hand, if the digit we tried to increment was 9 indeed, then
	put 0 in its place and try to increment the digit before(left of it).

	Do this until:
		either you find that you weren't incrementing number 9 or
			In that case just return the whole "digits" vector.
		
		or
		i becomes less than 0(meaning that even the very first digit, i.e. the
		most significant one) was 9 before incrementing.
			In that case we have to make a new vector, push 1 in it(because
			that is the carry after we have incremented the most significant
			digits) and then push all the other elements from digits to that
			new vector.

			At the end, just return that new vector.
	
*/

/* Time  Beats: 100% */
/* Space Beats: 78.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	std::vector<int> plusOne(std::vector<int>& digits)
	{
		for (int i = digits.size() - 1; i >= 0; i--)
		{
			if (digits[i] + 1 < 10)
			{
				digits[i]++;

				return  digits;
			}
			else
				digits[i] = 0;

		}

		// If we need to increment the most significant digit.
		std::vector<int> result;
		result.push_back(1);

		for (auto& d : digits)
			result.push_back(d);

		return result;
	}
};


int
main()
{
	Solution sol;


	/* Example 1 */
	// std::vector<int> digits = {1, 2, 3};

	/* Example 2 */
	// std::vector<int> digits = {4, 3, 2, 1};

	/* Example 3 */
	// std::vector<int> digits = {9};

	/* Example 4 */
	std::vector<int> digits = {9, 9, 9, 9};

	/* Example 5 */
	// std::vector<int> digits = {9, 9, 4, 9, 9, 9, 9};


	std::cout << "\n\t================";
	std::cout << "\n\t=== PLUS ONE ===";
	std::cout << "\n\t================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tDigits: [";
	for (auto x: digits)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	std::vector<int> result = sol.plusOne(digits);


	/* Write Input */
	first = true;
	std::cout << "\n\t\t*** After incrementing ***\n";
	std::cout << "\n\tResult: [";
	for (auto x: result)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
