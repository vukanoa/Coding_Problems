#include <iostream>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===================================
	300) Longest Increasing Subsequence
	===================================

	============
	Description:
	============

	Given an integer array "nums", return the length of the longest strictly
	increasing subsequence.

	Follow Up: Can you come up with an algorithm that runs in O(n * logn) time
	complexity?

	=============================================
	FUNCTION: int lengthOfLIS(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [10, 9, 2, 5, 3, 7, 101, 18]
	Output: 4
	Explanation: The longest increasing subsequence is [2, 3, 7, 101],
	therefore the length is 4.

	--- Example 2 ---
	Input:  nums = [0, 1, 0, 3, 2, 3]
	Output: 4

	--- Example 3 ---
	Input:  [7, 7, 7, 7, 7, 7, 7]
	Output: 1

	*** Constraints ***
	1 <= nums.length <= 2500
	-10^4 <= nums[i] <= 10^4

*/



/*
	------------
	--- IDEA ---
	------------

	This is a classic Dynamic Programming problem.
	Let dp[i] is the longest increase subsequence of nums[0..i] which has
	nums[i] as the end element of the subsequence.

*/



/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution{
public:
	int lengthOfLIS(std::vector<int>& nums)
	{
		int n = nums.size();
		std::vector<int> dp(n, 1);

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (nums[i] > nums[j] && dp[i] < dp[j] + 1)
					dp[i] = dp[j] + 1;
			}
		}

		return *std::max_element(dp.begin(), dp.end());
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

	/* Example 2 */
	// std::vector<int> nums = {0, 1, 0, 3, 2, 3};

	/* Example 3 */
	// std::vector<int> nums = {7, 7, 7, 7, 7, 7, 7};

	std::cout << "\n\t======================================";
	std::cout << "\n\t=== LONGEST INCREASING SUBSEQUENCE ===";
	std::cout << "\n\t======================================\n\n";


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
	std::cout << "]\n\n";


	/* Solution */
	int longest = sol.lengthOfLIS(nums);

	std::cout << "\n\tLongest Increasing Subsequence: " << longest << "\n\n";

	return 0;
}
