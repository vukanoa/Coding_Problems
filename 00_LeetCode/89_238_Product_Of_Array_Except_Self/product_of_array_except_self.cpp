#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	=================================
	238) Product of Array Except Self
	=================================

	============
	Description:
	============

	Given an integer array "nums", return an array "answer" such that answer[i]
	is equal to the product of all the elements of "nums" except nums[i].

	The product of any prefix or suffix of "nums" is guaranteed to fit in a
	32-bit integer.

	You must write an algorithm that runs in O(n) time and without using the
	division operation.

	Follow up: Can you solve the problem in O(1) extra space complexity?
	(The output array does NOT count as extra space for space complexity
	analysis)

	===========================================================
	FUNCTION: vector<int> productExceptSelf(vector<int>& nums);
	===========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 2, 3, 4]
	Output: [24, 12, 8, 6]

	--- Example 2 ---
	Input:  nums = [-1, 1, 0, -3, 3]
	Output: [0, 0, 9, 0, 0]

	*** Constraints ***
	2 <= nums.length <= 10^5
	-30 <= nums[i] <= 30
	The product of any prefix or suffix of "nums" is guaranteed to fit in a
	32-bit integer.

*/


/*
	------------
	--- IDEA ---
	------------

	First we got from left to right and multiply:
		answer[i - 1] with nums[i - 1]

	Why?
	That will create an array answer where only the very last element have
	fulfilled the description. Only that element in an array "answer" is truly
	a product of all the other elements without itself.
	So:
		n-1st element is fulfilled
		n-2nd element needs to be multiplied by the n-1st element
		n-3rd element needs to be multiplied by both n-1st and n-2nd element
		...
		0th   element needs to be multiplied by elements from n-1st to 1st, inclusive

	So essentially we only need 2 passes.
	One from left to right.
	One from right to left.

	If we were to start from the right to left first, then we would have:
		0th element is fulfilled
		1st element needs to be multiplied by 1st
		2nd element needs to be multiplied by 1st and 0th
		...
		n-1st eleemnt needs to be multiplied by every element from 0 to n-2, inclusive

	However, since we've already done the "left to right", once we finish the
	"right to left" as well, we will have required values.

	Let's look at an example:
	[2, 3, 4, 5]

	Regarding the third number '4' the product of array except '4' is 2 * 3 * 5
	which consists of two parts:
		left:  2 * 3
		right: 5

	The product is left * right. We can get lefts and rights:
        Numbers:     2     3     4     5
        Lefts:       1     2    2*3  2*3*4
        Rights:    3*4*5  4*5    5     1

	We can calculate lefts and rights in 2 loops.
	We store lefts in "answer". If we allocate a new array for rights the
	space complexity is O(n). To make it O(1), we just need to store it in a
	variable which is "remaining_product" and multiply with the "answer" array.

*/



/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	std::vector<int> productExceptSelf(std::vector<int>& nums)
	{
		int n = nums.size();
		std::vector<int> answer(n, 1);

		for (int i = 1; i < n; i++)
			answer[i] = answer[i - 1] * nums[i - 1];

		int remaining_product = 1;
		for (int i = n - 1; i >= 0; i--)
		{
			answer[i] *= remaining_product;
			remaining_product *= nums[i];
		}

		return answer;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums {1, 2, 3, 4};

	/* Example 2 */
	// std::vector<int> nums {-1, 1, 0, -3, 3};

	/* Example 3 */
	// std::vector<int> nums {5, 4, -1, 2, 3};

	std::cout << "\n\t====================================";
	std::cout << "\n\t=== PRODUCT OF ARRAY EXCEPT SELF ===";
	std::cout << "\n\t====================================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tnums: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	std::vector<int> answer = sol.productExceptSelf(nums);

	/* Write Output */

	first = true;
	std::cout << "\n\tanswer: [";
	for (auto x: answer)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";



	return 0;
}
