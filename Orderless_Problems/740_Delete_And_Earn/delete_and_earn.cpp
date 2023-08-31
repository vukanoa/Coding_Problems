#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	740) Delete and Earn
	===========================

	============
	Description:
	============

	You are given an integer array nums. You want to maximize the number of
	points you get by performing the following operation any number of times:

		Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you
		must delete every element equal to nums[i] - 1 and every element equal
		to nums[i] + 1.

	Return the maximum number of points you can earn by applying the above
	operation some number of times.

	===============================================
	FUNCTION: int deleteAndEarn(vector<int>& nums);
	===============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [3,4,2]
	Output: 6
	Explanation: You can perform the following operations:
	- Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
	- Delete 2 to earn 2 points. nums = [].
	You earn a total of 6 points.


	--- Example 2 ---
	Input: nums = [2,2,3,3,3,4]
	Output: 9
	Explanation: You can perform the following operations:
	- Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
	- Delete a 3 again to earn 3 points. nums = [3].
	- Delete a 3 once more to earn 3 points. nums = [].
	You earn a total of 9 points.


	*** Constraints ***
	1 <= nums.length <= 2 * 10^4
	1 <= nums[i] <= 10^4

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 86.75% */
/* Space Beats: 65.74% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution{
public:
	int deleteAndEarn(std::vector<int>& nums)
	{
		if (nums.size() == 1)
			return nums[0];

		// Sort
		std::sort(nums.begin(), nums.end());

		// Remove duplicates and count occurrences
		std::vector<int> nums_no_dup;
		nums_no_dup.push_back(nums[0]);

		std::unordered_map<int, int> umap;
		umap.insert({nums[0], 1});

		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] == nums[i - 1])
				umap[nums[i]]++;
			else
			{
				umap.insert({nums[i], 1});
				nums_no_dup.push_back(nums[i]);
			}
		}
		
		// Meat of the Solution
		int prev = 0;
		int curr = nums[0] * umap[nums[0]];

		for (int i = 1; i < nums_no_dup.size(); i++)
		{
			int val = nums_no_dup[i] * umap[nums_no_dup[i]];

			int tmp;
			if (nums_no_dup[i - 1] + 1 == nums_no_dup[i])
				tmp = std::max(prev + val, curr);
			else
				tmp = std::max(prev + val, curr + val);

			prev = curr;
			curr = tmp;
		}

		return std::max(prev, curr);
	}
};
