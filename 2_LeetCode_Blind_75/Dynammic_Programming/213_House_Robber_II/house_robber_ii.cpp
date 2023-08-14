#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	213) House Robber II
	===========================

	============
	Description:
	============

	You are a professional robber planning to rob houses along a street. Each
	house has a certain amount of money stashed. All houses at this place are
	arranged in a circle. That means the first house is the neighbor of the
	last one. Meanwhile, adjacent houses have a security system connected, and
	it will automatically contact the police if two adjacent houses were broken
	into on the same night.

	Given an integer array nums representing the amount of money of each house,
	return the maximum amount of money you can rob tonight without alerting the
	police.

	=====================================
	FUNCTION: int rob(vector<int>& nums);
	=====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [2,3,2]
	Output: 3
	Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money
	             = 2), because they are adjacent houses.


	--- Example 2 ---
	Input: nums = [1,2,3,1]
	Output: 4
	Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
	Total amount you can rob = 1 + 3 = 4.


	--- Example 3 ---
	Input: nums = [1,2,3]
	Output: 3


	*** Constraints ***
	1 <= nums.length <= 100
	0 <= nums[i] <= 1000

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 100% */
/* Space Beats: 57.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
	int rob(vector<int>& nums)
	{
		int n = nums.size(); 

		if (n < 2)
			return n ? nums[0] : 0;

		return max(robber(nums, 0, n - 2), robber(nums, 1, n - 1));
	}

private:
	int robber(vector<int>& nums, int start, int end)
	{
	    int pre  = 0;
		int curr = 0;

	    for (int i = start; i <= end; i++)
		{
	        int tmp = max(pre + nums[i], curr);

	        pre  = curr;
	        curr = tmp;
	    }

	    return curr;
	}
};
