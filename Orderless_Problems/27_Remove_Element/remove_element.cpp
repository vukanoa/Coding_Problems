#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	27) Remove Element
	===========================

	============
	Description:
	============

	Given an integer array nums and an integer val, remove all occurrences of
	val in nums in-place. The order of the elements may be changed. Then return
	the number of elements in nums which are not equal to val.

	Consider the number of elements in nums which are not equal to val be k, to
	get accepted, you need to do the following things:

	    Change the array nums such that the first k elements of nums contain
	    the elements which are not equal to val. The remaining elements of nums
	    are not important as well as the size of nums.

	    Return k.

	========================================================
	FUNCTION: int removeElement(vector<int>& nums, int val);
	========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [3,2,2,3], val = 3
	Output: 2, nums = [2,2,_,_]
	Explanation: Your function should return k = 2, with the first two elements
	             of nums being 2.  It does not matter what you leave beyond the
	             returned k (hence they are underscores).

	--- Example 2 ---
	Input: nums = [0,1,2,2,3,0,4,2], val = 2
	Output: 5, nums = [0,1,4,0,3,_,_,_]
	Explanation: Your function should return k = 5, with the first five
	             elements of nums containing 0, 0, 1, 3, and 4.  Note that the
	             five elements can be returned in any order.  It does not
	             matter what you leave beyond the returned k (hence they are
	             underscores).


	*** Constraints ***
	0 <= nums.length() <= 100
	0 <= nums[i] <= 50
	0 <= val <= 100

*/

/* Time  Beats:   100% */
/* Space Beats: 87.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
	int removeElement(vector<int>& nums, int val)
	{
		int left = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val)
				nums[left++] = nums[i];
		}

		return left;
	}
};
