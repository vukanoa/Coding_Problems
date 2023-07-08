#include <iostream>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	324) Wiggle Sort
	===========================

	============
	Description:
	============

	Given an integer array nums, reorder it such that:
	nums[0] < nums[1] > nums[2] < nums[3]....

	You may assume the input array always has a valid answer.


	Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra
	space?

	=============================================
	FUNCTION: void wiggleSort(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [1,5,1,1,6,4]
	Output: [1,6,1,5,1,4]
	Explanation: [1,4,1,5,1,6] is also accepted.


	--- Example 2 ---
	Input: nums = [1,3,2,2,3,1]
	Output: [2,3,1,3,1,2]


	*** Constraints ***
	1 <= nums.length <= 5 * 104
	0 <= nums[i] <= 5000
	It is guaranteed that there will be an answer for the given input nums.

*/


/*
	------------
	--- IDEA ---
	------------

	Once you sort and divide into left and right group, it's easy to see that
	we have to alternate between the groups and push those items from the back
	of certain group.

*/

/* Time  Beats:    89% */
/* Space Beats: 19.57% */

/* Time  Complexity: O(n * log) */
/* Space Complexity: O(n) */
class Solution{
public:
	void wiggleSort(std::vector<int>& nums)
	{
		std::sort(nums.begin(), nums.end());

		std::vector<int> left;
		std::vector<int> right;

		int n = nums.size();
		int border = n % 2 == 0 ? n/2 : n/2 + 1;

		for (int i = 0; i < border; i++)
			left.push_back(nums[i]);

		for (int i = border; i < n; i++)
			right.push_back(nums[i]);

		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
			{
				nums[i] = left.back();
				left.pop_back();
			}
			else
			{
				nums[i] = right.back();
				right.pop_back();
			}
		}
	}
};
