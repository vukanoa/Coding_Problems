#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	189) Rotate Array
	===========================

	============
	Description:
	============

	Given an integer array "nums", rotate the array to the right by "k" steps,
	where "k" is non-negative.

	Follow up:
		- Try to come up with as many solution as you can. There are at least
		  three different ways to solve this problem.

		- Could you do it in-place with O(1) extra space?

	================================================
	FUNCTION: void rotate(vector<int>& nums, int k);
	================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 2, 3, 4, 5, 6, 7], k = 3
	Output: [5, 6, 7, 1, 2, 3, 4]

	--- Example 2 ---
	Input:  [-1, -100, 3, 99], k = 2
	Output: [3, 99, -1, -100]

	*** Constraints ***
	1 <= nums.length <= 10^5
	-2^31 <= nums[i] <= 2^31 - 1
	0 <= k <= 10^5

*/


/*
	------------
	--- IDEA ---
	------------

	This Solution is based on the fact that when we rotate the array k times,
	k elements from the back end of the array come to the root and the rest
	of the elements from the front shift backwards.

	In this approach, we firstly reverse all the elements of the array. Then,
	reversing the first k elements followed by reversing the rest n - k
	elements gives us the required result.

	Let n = 7 and k = 3

	Original list                     : 1 2 3 4 5 6 7
	After reversing all numbers       : 7 6 5 4 3 2 1
	After reversing first k numbers   : 5 6 7 4 3 2 1
	After reversing last n - k numbers: 5 6 7 1 2 3 4 --> Result

*/

/* Time  Beats: 83.64% */
/* Space Beats: 99.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	void rotate(std::vector<int>& nums, int k)
	{
		int n = nums.size();

		k = k % n;
		reverse(nums, 0, n - 1);
		reverse(nums, 0, k - 1);
		reverse(nums, k, n - 1);
	}

private:
	void reverse(std::vector<int>& nums, int start, int end)
	{
		while (start < end)
			std::swap(nums[start++], nums[end--]);
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
	// int k = 3;

	/* Example 2 */
	// std::vector<int> nums = {-1, -100, 3, 99};
	// int k = 2;

	/* Example 3 */
	// std::vector<int> nums = {-1};
	// int k = 1;

	/* Example 4 */
	// std::vector<int> nums = {1, 2};
	// int k = 2;

	/* Example 5 */
	// std::vector<int> nums = {1, 2};
	// int k = 3;

	/* Example 6 */
	// std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	// int k = 5;

	/* Example 7 */
	std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int k = 2;


	std::cout << "\n\t====================";
	std::cout << "\n\t=== ROTATE ARRAY ===";
	std::cout << "\n\t====================\n";


	/* Write Input */
	std::cout << "\n\t=== BEFORE ===";
	bool first = true;
	std::cout << "\n\tArray: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	sol.rotate(nums, k);

	if (k == 1)
		std::cout << "\n\t\tRotated " << k << " place to the right!\n";
	else
		std::cout << "\n\t\tRotated " << k << " places to the right!\n";


	/* Write Output */
	std::cout << "\n\t=== AFTER ===";
	first = true;
	std::cout << "\n\tArray: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n\n";


	return 0;
}
