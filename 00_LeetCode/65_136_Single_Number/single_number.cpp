#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	136) Single Number
	===========================

	============
	Description:
	============

	Given a non-empty array of integers "nums", every element appears twice
	except for one. Find that single one.


	You must implement a solution with a linear runtime and use only constant
	extra space.

	==============================================
	FUNCTION: int singleNumber(vector<int>& nums);
	==============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [2, 2, 1]
	Output: 1

	--- Example 2 ---
	Input:  nums = [4, 1, 2, 1, 2]
	Output: 4

	--- Example 3 ---
	Input:  nums = [1]
	Output: 1

	*** Constraints ***
	1 <= nums.length <= 3 * 10^4
	-3 * 10 ^ 4 <= nums[i] <= 3 * 10^4
	Each element in the array apperas twice except for one element which
	  appears only once.

*/


/*
	------------
	--- IDEA ---
	------------

	Just XOR all the elements.

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int singleNumber(std::vector<int>& nums)
	{
		int result = 0;
		for (int i = 0; i < nums.size(); i++)
			result ^= nums[i];

		return result;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {2, 2, 1};

	/* Example 2 */
	// std::vector<int> nums = {4, 1, 2, 1, 2};

	/* Example 3 */
	// std::vector<int> nums = {1};

	/* Example 4 */
	// std::vector<int> nums = {3, 1, 4, -1, 3, 4, 1};

	/* Example 5 */
	// std::vector<int> nums = {-1, -1, -2};


	std::cout << "\n\t=====================";
	std::cout << "\n\t=== SINGLE NUMBER ===";
	std::cout << "\n\t=====================\n";


	/* Write Input */
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
	int result = sol.singleNumber(nums);

	/* Write Output */
	std::cout << "\n\tOutput: " << result << "\n\n";

	return 0;
}
