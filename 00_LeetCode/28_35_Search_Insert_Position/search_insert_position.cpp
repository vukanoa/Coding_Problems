#include <iostream>
#include <vector>


/*
	============
	=== EASY ===
	============
	
	===========================
	35) Search Insert Position
	===========================
	
	============
	Description:
	============

	Given a sorted array of distinct integers and a target value, return the
	index if the target is found. If not, return the index where it would be if
	it were inserted in order.
	
	=====
	Node: You must write an algorithm with O(log n) runtime complexity.
	=====
	
	==========================================================
	FUNCTION: int searchInsert(vector<int>& nums, int target);
	==========================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  nums = [1, 3, 5, 6], target = 5
	Output: 2
	
	--- Example 2 ---
	Input:  nums = [1, 3, 5, 6], target = 2
	Output: 1
	
	--- Example 3 ---
	Input: nums = [1, 3, 5, 6], target = 7
	Output: 4
	
	*** Constraints ***
	1 <= nums.length <= 10^4
	-10^4 <= nums[i] <= 10^4
	nums contains distinct values sorted in ascending order.
	-10^4 <= target <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	Since we're told we must have a runtime complexity of O(log n), that means
	we have to use a Binary Search.

	Let's cover the base cases first.
		1. Target value is less than or equal to the very first element in the
		array. That means we should return 0, since if we were to insert it
		in this sorted array, it would've been inserted index 0.

		2. Target value is greater than the very last element in the arrat.
		That means we should return n. If we were to insert and it is
		greater than the last element, then we would've insert it at index n.
	
	We do a simple Binary search and in each iteration we're only checking
	the position of nums[mid] relative to our target value.

	If nums[mid] == target, that's it. We've found it. Return mid.
	If target < nums[mid], just update high to point to mit and repeat.
	If nums[mid] < target, update low to point to mid if it wasn't mid, and if
	low and mid are the same, then make low = mid + 1.

	Why do we do this?
	Let's say that we've always done low = mid + 1;

	std::vector<int> nums = {1, 3, 5, 6};
	int target = 4;

	1st iteration:
	low  = 0 [1]
	mid  = 1 [3]
	high = 3 [6]

	2nd iteration
	low  = 2 [5]
	mid  = 2 [5]
	high = 3 [6]

	and we would return "prev_high" which after the 2nd iteration would be:
		prev_high = 3
	
	which isn't right.
	We have gone over the right bound, i.e. over the very next element of our
	target value.

	So if our low != mid, always make low = mid, ONLY if low == mid
	make low = mid + 1 so our iteration doens't get stuck.
	
	Also - What is this "prev_high" value? Why do we use that?
	Since we've jumped over Base Cases, meaning our target value isn't less or
	equal to out first element nor it is greater than our greater or last
	element in the array, then that certainly means that whether or not our
	target value is present in our array, the index is > 0 && < n.

	That's why we memorize "prev_high" which is previous value of high, since
	when our while loop statement gets to be false, that is - low >= high
	we're sure we should only return the index of prev_high.
	
*/



class Solution{
public:
	int searchInsert(std::vector<int>& nums, int target)
	{
		int n = nums.size();
		int low  = 0;
		int high = n - 1;

		if (target <= nums[low])
			return 0;
		else if (nums[high] < target)
			return n;
		
		int prev_high;
		
		while (low < high)
		{
			int mid = (low + high) / 2;

			prev_high = high;

			if (nums[mid] == target)
				return mid;
			else if (nums[mid] < target)
				low == mid ? low = mid + 1 : low = mid;
			else if (target < nums[mid])
				high = mid;
		}

		return prev_high;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {1, 3, 5, 6};
	int target = 5;

	/* Example 2 */
	// std::vector<int> nums = {1, 3, 5, 6};
	// int target = 2;

	/* Example 3 */
	// std::vector<int> nums = {1, 3, 5, 6};
	// int target = 7;

	/* Example 4 */
	// std::vector<int> nums = {1, 3, 5, 6};
	// int target = 4;

	/* Example 5 */
	// std::vector<int> nums = {1, 3, 5, 6};
	// int target = 0;

	/* Example 6 */
	// std::vector<int> nums = {1, 3, 5, 6};
	// int target = 10;

	/* Example 7 */
	// std::vector<int> nums = {1};
	// int target = 1;

	/* Example 8 */
	// std::vector<int> nums = {1};
	// int target = -7;

	bool first = true;
	std::cout << "\n\tInput: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";
	std::cout << "\n\tTarget: " << target << "\n";

	// Solution
	int output = sol.searchInsert(nums, target);

	std::cout << "\n\tOutput: " << output << "\n\n";

	return 0;
}
