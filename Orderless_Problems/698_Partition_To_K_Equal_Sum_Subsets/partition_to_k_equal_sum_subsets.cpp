#include <iostream>
 #include <numeric>

/*
	==============
	=== MEDIUM ===
	==============

	=====================================
	698) Partition to K Equal Sum Subsets
	=====================================

	============
	Description:
	============

	Given an integer array nums and an integer k, return true if it is possible
	to divide this array into k non-empty subsets whose sums are all equal.

	==================================================================
	FUNCTION: bool canPartitionSubsets(std::vector<int>& nums, int k);
	==================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [4,3,2,3,5,2,1], k = 4
	Output: true
	Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3),
	(2,3) with equal sums.

	--- Example 2 ---
	Input: nums = [1,2,3,4], k = 3
	Output: false

	*** Constraints ***
	1 <= k <= nums.length <= 16
	1 <= nums[i] <= 104
	The frequency of each element is in the range [1, 4].

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 5.63% */
/* Space Beats: 77.37% */

/* Time  Complexity: O(K * 2^n) */
/* Space Complexity: O(n) */
class Solution{
public:
	bool canPartitionKSubsets(std::vector<int>& nums, int k)
	{
		int sum = std::accumulate(nums.begin(), nums.end(), 0);

		if (sum % k)
			return false;

		// Sort(it won't worsen the Time Complexity)
		std::sort(nums.begin(), nums.end(), std::greater<int>());

		std::vector<bool> used(nums.size(), false);

		return backtracking(nums, 0, k, 0, used, sum / k);
	}

private:
	bool backtracking(std::vector<int>& nums, int start, int k, int subset_sum, std::vector<bool>& used, int target)
	{
		if (k == 0)
			return true;

		if (subset_sum == target)
			return backtracking(nums, 0, k - 1, 0, used, target);

		for (int j = start; j < nums.size(); j++)
		{
			if (used[j] || subset_sum + nums[j] > target)
				continue;

			used[j] = true;

			if (backtracking(nums, j + 1, k, subset_sum + nums[j], used, target))
				return true;

			used[j] = false;
		}

		return false;
	}
};




/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 90.78% */
/* Space Beats: 30.17% */

/* Time  Complexity: O(K * 2^n) */
/* Space Complexity: O(n) */
class Solution{
public:
	bool canPartitionKSubsets(vector<int>& nums, int k)
	{
		int sum = std::accumulate(nums.begin(), nums.end(), 0);

		if (sum % k)
			return false;

		// Sort array in decreasing order
		std::sort(nums.begin(), nums.end(), greater<int>());

		std::vector<bool> used(nums.size(), false);

		return backtracking(nums, 0, k, 0, used, sum / k);
	}

private:
	bool backtracking(vector<int> nums, int start, int k, int subset_sum, std::vector<bool>& used, int target)
	{
		if(k == 0)
			return true;

		if(subset_sum > target)
			return false;

		if(subset_sum == target)
			return backtracking(nums, 0, k-1, 0, used, target);

		for(int i=start;i<nums.size();i++)
		{
			if(used[i])
				continue;

			used[i] = true;

			if(backtracking(nums, i + 1, k, subset_sum + nums[i], used, target))
				return true;

			used[i] = false;

			// Optimization 
			if(subset_sum == 0)
				break;
		}

		return false;
	}
};
