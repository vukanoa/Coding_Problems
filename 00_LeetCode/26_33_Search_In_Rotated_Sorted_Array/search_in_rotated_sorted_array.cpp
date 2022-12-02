#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============
	
	==================================
	33) Search in Rotated Sorted Array
	==================================
	
	============
	Description:
	============

	There is an integer array "nums" sorted in ascending order(with distinct
	values).

	Prior to being passed to your function, "nums" is *possibly rotated* at an
	unknown pivot index k (1 <= k < nums.length) such that the resulting array
	is:
	[nums[k], nums[k + 1], ..., nums[n - 1], nums[0], nums[1], ..., nums[k - 1]]
	(0-indexed).

	For example, [0, 1, 2, 4, 5, 6, 7] might be rotated at pivot index 3 and
	become [4, 5, 6, 7, 0, 1, 2].

	Given the array "nums" after the possible rotation and an integer target,
	return the index of target if it is in "nums", or -1 if it is not in "nums".

	=====
	Node: You must write an algorithm with O(log n) runtime complexity.
	=====
	
	=========================================================
	FUNCTION: int search(std::vector<int>& nums, int target);
	=========================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  nums = [4, 5, 6, 7, 0, 1, 2], target = 0
	Output: 4
	
	--- Example 2 ---
	Input:  nums = [4, 5, 6, 7, 0, 1, 2], target = 3
	Output: -1
	
	--- Example 3 ---
	Input: nums = [1], target = 0
	Output: -1
	
	*** Constraints ***
	1 <= nums.length <= 5000
	-10^4 <= nums[i] <= 10^4
	All values of "nums" are unique
	"nums" is an ascending array that is possibly rotated
	-10^4 <= target <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	We have to use Binary Search, though there are a lot of cases we have to
	cover. Fortunately there is a XOR operator so the code looks a lot neater.

	Here is how the "if statement" inside the "while loop" would look like if
	there was no XOR operator.

	if ((target < nums[0]) && (nums[mid] > nums[0]) && (nums[mid] > target))
		low = mid + 1;
	else if ((target > nums[0]) && (nums[mid] < nums[0]) && (nums[mid] > target))
		low = mid + 1;
	else if ((target > nums[0]) && (nums[mid] > nums[0]) && (nums[mid] < target))
		low = mid + 1;
	else
		high = mid
	
*/


/* Time  Complexity: O(log n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int search(std::vector<int>& nums, int target)
	{
		int low = 0;
		int high = nums.size() - 1;

		while (low < high)
		{
			int mid = (low + high) / 2;

			if ((target < nums[0]) ^ (nums[mid] < nums[0]) ^ (nums[mid] < target))
				low = mid + 1;
			else
				high = mid;
		}

		return low == high && nums[low] == target ? low : -1;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
	// int target = 0;

	/* Example 2 */
	// std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
	// int target = 3;

	/* Example 3 */
	// std::vector<int> nums = {1};
	// int target = 0;

	/* Example 4 */
	// std::vector<int> nums =  {7, 8, 9, 10, 13, 0, 1, 2, 4, 5, 6};
	// int target = 3;

	/* Example 5 */
	// std::vector<int> nums =  {7, 8, 9, 10, 13, 0, 1, 2, 4, 5, 6};
	// int target = 12;

	/* Example 6 */
	// std::vector<int> nums =  {7, 8, 9, 10, 13, 0, 1, 2, 4, 5, 6};
	// int target = 10;

	/* Example 7 */
	// std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
	// int target = 2;

	/* Example 8 */
	// std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
	// int target = 4;

	/* Example 9 */
	std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
	int target = 5;



	int index = sol.search(nums, target);

	std::cout << "\n\tIndex od solution is: " << index << "\n\n";

	return 0;
}
