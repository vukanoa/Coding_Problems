#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===============================
	1679) Max Number of K-Sum Pairs
	===============================

	============
	Description:
	============

	You are given an integer array nums and an integer k.

	In one operation, you can pick two numbers from the array whose sum equals
	k and remove them from the array.

	Return the maximum number of operations you can perform on the array.

	======================================================
	FUNCTION: int maxOperations(vector<int>& nums, int k);
	======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [1,2,3,4], k = 5
	Output: 2
	Explanation: Starting with nums = [1,2,3,4]:
	- Remove numbers 1 and 4, then nums = [2,3]
	- Remove numbers 2 and 3, then nums = []
	There are no more pairs that sum up to 5, hence a total of 2 operations.


	--- Example 2 ---
	Input: nums = [3,1,3,4,3], k = 6
	Output: 1
	Explanation: Starting with nums = [3,1,3,4,3]:
	- Remove the first two 3's, then nums = [1,4,3]
	There are no more pairs that sum up to 6, hence a total of 1 operation.


	*** Constraints ***
	1 <= nums.length <= 105
	1 <= nums[i] <= 109
	1 <= k <= 109

*/


/* Time  Beats: 69.10% */
/* Space Beats: 6.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	int maxOperations(vector<int>& nums, int k)
	{
		std::unordered_map<int, int> umap;

		int count = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if (umap[k - nums[i]] > 0)
			{
				umap[k - nums[i]]--;
				count++;
			}
			else
				umap[nums[i]]++;
		}

		return count;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Even though this is O(n * logn) and the previous is O(n), this one seems to
	be faster.

	I have no idea why.

*/

/* Time  Beats: 92.65% */
/* Space Beats: 60.77% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
	int maxOperations(vector<int>& nums, int k)
	{
		std::sort(nums.begin(), nums.end());

		int left  = 0;
		int right = nums.size() - 1;

		int count = 0;

		while (left < right)
		{
			if (nums[left] + nums[right] == k)
			{
				left++;
				right--;
				count++;
			}
			else if (nums[left] + nums[right] > k)
				right--;
			else // nums[left] + nums[right] < k
				left++;
		}

		return count;
	}
};
