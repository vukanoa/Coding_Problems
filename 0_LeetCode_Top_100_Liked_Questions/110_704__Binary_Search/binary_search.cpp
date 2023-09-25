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

	The most basic Binary Search. However, it's important to note it here as
	well:

	    DO NOT write Binary Search like this: int mid = (l + r) / 2;
		Overflow can happen.
	
	Consider this:

	You have to find number: INT_MAX-3
	INT_MAX is: 2,147,483,647

	INT_MAX - 3 --> 2,147,483,647 - 3 = 2,147,483,644

	Imagine that the range we're searching this number in is: [0, INT_MAX];

	At some point in our process of Binary Search, our left bound will be
	somewhere close to INT_MAX-5 and our right bound will remain INT_MAX since
	we've always gone to the right after comparing mid with the target value.

	So now:
	left  = INT_MAX-5
	right = INT_MAX

	If we try to do this:
		int mid = (left + right) / 2
	
	The Overflow will happen. The computation is going to produce an invalid
	calculation because int is 32-bits(on 64-bit architecture) which means
	that the maximum positive value it can store is INT_MAX, therefore
	doing:
	    int mid + (left + right) / 2

	Where:
	left  = INT_MAX-5
	right = INT_MAX

	Will produce a mistake.

	So how can we resolve this?

	Simply use this formula instead:
	    int mid = left + (right - left) / 2;
	
	What this does is: It adds halfed current range on the left bound. That is
	guaranteed not to make a Overflow.

*/

/* Time  Beats: 91.14% */
/* Space Beats: 14.53% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution{
public:
	int search(std::vector<int>& nums, int target)
	{
		int l = 0;
		int r = nums.size() - 1;

		while (l <= r)
		{
			// DON'T write it like this: mid = (l + r) / 2; It can Overflow!!!
			int mid = l + (r - l) / 2;

			if (nums[mid] == target) 
				return mid;

			if (nums[mid] < target)
				l = mid + 1;
			else
				r = mid - 1;
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
