#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	704) Binary Search
	===========================

	============
	Description:
	============

	Given an array of integers "nums" which is sorted in ascending order, and
	an integer "target", write a function to search "target" in "nums". If
	"target" exists, then return its index. Otherwise, return -1.

	=====
	Node: You must write an algorithm with O(log n) runtime Complexity.
	=====

	====================================================
	FUNCTION: int search(vector<int>& nums, int target);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  [-1, 0, 3, 5, 9, 12], target = 9
	Output: 4
	Explanation: 9 exists in nums and its index is 4

	--- Example 2 ---
	Input:  [-1, 0, 3, 5, 9, 12], target = 2
	Output: -1
	Explanation: 2 does not exist in nums so return -1

	*** Constraints ***
	1 <= nums.length <= 10^4
	-10^4 <= nums[i], target < 10^4
	All the integers in "nums" are unique.
	"nums" is sorted in ascending order.

*/

/*
	------------
	--- IDEA ---
	------------

	The most basic Binary Search.
	
*/

/* Time  Beats: 86.59% */
/* Space Beats: 50.71% */

/* Time  Complexity: O(log n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int search(std::vector<int>& nums, int target)
	{
		int l = 0;
		int r = nums.size() - 1;

		while (l <= r)
		{
			int mid = (l + r) / 2;

			if (nums[mid] == target) 
				return mid;
			else if (target < nums[mid])
				r = mid - 1;
			else if (target > nums[mid])
				l = mid + 1;
		}
		
		return -1;
	}
};


int
main()
{
	Solution sol;


	/* Example 1 */
	std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
	int target = 9;

	/* Example 2 */
	// std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
	// int target = 2;


	std::cout << "\n\t=====================";
	std::cout << "\n\t=== BINARY SEARCH ===";
	std::cout << "\n\t=====================\n";


	/* Write Input */
	std::cout << "\n\tTarget: " << target;
	bool first = true;
	std::cout << "\n\tNums: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";



	/* Solution */
	int result = sol.search(nums, target);


	/* Write Output */
	if (result != -1)
		std::cout << "\n\tOutput: " << target << " exist at index " << result;
	else
		std::cout << "\n\tOutput: " << target << " does NOT exist!";
	std::cout << "\n\n";


	return 0;
}
