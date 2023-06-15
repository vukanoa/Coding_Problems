#include <iostream>
#include <unordered_set>

/*
	============
	=== EASY ===
	============

	===========================
	217) Contains Duplicate
	===========================

	============
	Description:
	============

	Given an integer array nums, return true if any value appears at least
	twice in the array, and return false if every element is distinct.

	====================================================
	FUNCTION: bool containsDuplicate(vector<int>& nums); 
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [1, 2, 3, 1]
	Output: true

	--- Example 2 ---
	Input: nums = [1, 2, 3, 4]
	Output: false

	--- Example 3 ---
	Input: nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2]
	Output: true

	*** Constraints ***
	1 <= nums.length <= 105
	-109 <= nums[i] <= 109

*/


/*
	------------
	--- IDEA ---
	------------

	Iterate through the array and check if that number was already visited.
	How are we going to do that?

	By putting the number in a Hash Set if it doesn't exist already.

	If it does exist, then we're done - return true.
	
*/

/* Time  Beats: 79.53% */
/* Space Beats: 45.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool containsDuplicate(vector<int>& nums)
	{
		std::unordered_set<int> uset;

		for (int& num : nums)
		{
			if (uset.find(num) != uset.end())
				return true;

			uset.insert(num);
		}

		return false;
    }
};
