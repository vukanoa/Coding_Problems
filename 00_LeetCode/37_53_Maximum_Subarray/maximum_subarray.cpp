#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include "big_example.cpp"


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	53) Maximum Subarray
	===========================

	============
	Description:
	============

	Given an integer array "nums", find the subarray which has the largest sum
	and return its sum.

	=============================================
	FUNCTION: int maxSubArray(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
	Output: 6
	Explanation: [4, -1, 2, 1] has the largest sum = 6

	--- Example 2 ---
	Input:  nums = [1]
	Output: 1

	--- Example 3 ---
	Input: nums = [5, 4, -1, 7, 8]
	Output: 23

	*** Constraints ***
	1 <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	Keep adding each integer to the sequence until the "sum" drops below 0.
	If "sum" is negative, then should reset the sequence.

*/


/* Time  Beats: 70.21% */
/* Space Beats: 5.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_unoptimized{
public:
	int maxSubArray(std::vector<int>& nums)
	{
		std::vector<int> dp(nums.size(), 0);
		dp[0] = nums[0];
		int max = dp[0];

		for (int i = 1; i < nums.size(); i++)
		{
			dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);

			if (dp[i] > max)
				max = dp[i];
		}

		return max;
	}
};


/* We only need the dp[i - 1] each time, so using a vector is redundant */

/* Time  Beats: 91.19% */
/* Space Beats: 63.38% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_efficient{
public:
	int maxSubArray(std::vector<int>& nums)
	{
		int dp = nums[0];
		int max = dp;

		for (int i = 1; i < nums.size(); i++)
		{
			dp = std::max(dp + nums[i], nums[i]);

			if (dp > max)
				max = dp;
		}

		return max;
	}
};


extern std::vector<int> big_example();


int
main()
{
	Solution_unoptimized sol_unopt;
	Solution_efficient   sol_eff;

	/* Example 1 */
	std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

	/* Example 2 */
	// std::vector<int> nums = {1};

	/* Example 3 */
	// std::vector<int> nums = {5, 4, -1, 7, 8};

	/* Example 4 */
	// std::vector<int> nums = big_example();

	std::cout << "\n\t========================";
	std::cout << "\n\t=== MAXIMUM SUBARRAY ===";
	std::cout << "\n\t========================\n";

	
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
	// int max = sol_unopt.maxSubArray(nums);
	int max = sol_eff.maxSubArray(nums);


	/* Write Output */
	std::cout << "\n\tMax SubArray: " << max << "\n\n";


	return 0;
}
