#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===================================
	334) Increasing Triplet Subsequence
	===================================

	============
	Description:
	============

	Given an integer array nums, return true if there exists a triple of
	indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k].

	If no such indices exists, return false.


	Follow up: Could you implement a solution that runs in O(n) time
	           complexity and O(1) space complexity?

	====================================================
	FUNCTION: bool increasingTriplet(vector<int>& nums);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [1,2,3,4,5]
	Output: true
	Explanation: Any triplet where i < j < k is valid.


	--- Example 2 ---
	Input: nums = [5,4,3,2,1]
	Output: false
	Explanation: No triplet exists.


	--- Example 3 ---
	Input: nums = [2,1,5,0,4,6]
	Output: true
	Explanation: The triplet (3, 4, 5) is valid because:
	             nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

	*** Constraints ***
    1 <= nums.length <= 5 * 10^5
    -2^31 <= nums[i] <= 2^31 - 1

*/


/*
	------------
	--- IDEA ---
	------------

	As soon as you look at the code, it becomes painfully obvious.
	
*/

/* Time  Beats: 91.12% */
/* Space Beats: 96.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	bool increasingTriplet(vector<int>& nums)
	{
		int num_1 = INT_MAX;
		int num_2 = INT_MAX;

		for (int x : nums)
		{
			if (x <= num_1)
				num_1 = x;       // num_1 is min seen so far (it's a candidate for 1st element)
			else if (x <= num_2) // here when x > num_1, i.e. x might be either num_2 or num_3
				num_2 = x;       // x is better than the current num_2, store it
			else                 // here when we have/had num_1 < num_2 already and x > num_2
				return true;     // the increasing subsequence of 3 elements exists
		}

		return false;
	}
};
