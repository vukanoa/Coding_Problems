#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	=========================================
	153) Find Minimum in Rotated Sorted Array
	=========================================

	============
	Description:
	============

	Suppose an array of length "n" sorted in ascending order is rotated between
	1 and n times. For ecample, the array "nums" = [0, 1, 2, 4, 5, 6, 7] might
	become:
		[4, 5, 6, 7, 0, 1, 2] if it was rotated 4 times
		[0, 1, 2, 4, 5, 6, 7] if it was rotated 7 times

	Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
	results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

	Given the sorted rotated array "nums" of unique elements, return the
	minimum element of this array.

	You must write an algorithm that runs in O(log n) time.

	=========================================
	FUNCTION: int findMin(vector<int>& nums);
	=========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [3, 4, 5, 1, 2]
	Output: 1

	--- Example 2 ---
	Input:  nums = [4, 5, 6, 7, 0, 1, 2]
	Output: 0

	--- Example 3 ---
	Input:  [11, 13, 15, 17]
	Output: 11

	*** Constraints ***
	n = nums.length
	1 <= n <= 5000
	-5000 <= nums[i] <= 5000
	All the integers of "nums" are unique.
	"nums" is sorted and rotated between 1 and n times.

*/


/*
	------------
	--- IDEA ---
	------------

	At the very beginning we assign the nums[0] as the minimum value.

	Then we forward an entire arrya in a helper function called: binary_search
	This is a bit of a tweaked version of a binary search, but it is highly
	reminiscent.

	Consider this example:
		[4, 5, 6, 7, 0, 1, 2]
		 0  1  2  3  4  5  6

	First we check the edge case - If that is the only element.
	Second, we check if the current nums[start] is less than nums[end] if that
	is the case then it's over, just check if the nums[start] is less than
	the current minimum and return min from the findMind function.

	Third, if nums[end] > nums[start] then that means the array/subarray we are
	currently checking is rotated. That further means that we have to divide
	this one and repeat the process either on its left or its right part of the
	current array/subarray.

	So how do we decide where to go?
	Again, consider this example:
		[4, 5, 6, 7, 0, 1, 2]
		 0  1  2  3  4  5  6

	We will then calculate 4 positions:
		1. left_start
		2. left_end
		3. right_start
		4. right_end

	if we find out that nums[left_start] is less than nums[left_end] then that
	means that that subarray is completely sorted which further means that our
	desired minimum value is certainly not there. Therefore, we should proceed
	our search in the other, right, half of this array/subarray.

	And vice-versa.

	And the end of the recursion we have our minimum value stored in our
	variable "min", so we return that from our function "findMin".

*/



/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
	void binary_search(std::vector<int>& nums, int start, int end, int& min)
	{
		if (start == end)
		{
			if (nums[start] < min)
				min = nums[start];
		}
		else if(nums[start] < nums[end])
		{
			if (nums[start] < min)
				min = nums[start];
		}
		else
		{
			int left_start  = start;
			int left_end    = (start + end) / 2;
			int right_start = left_end + 1;
			int right_end   = end;

			if (nums[left_start] > nums[left_end]) // Process left subarray
				binary_search(nums, left_start, left_end, min);
			else // Process right subarray
				binary_search(nums, right_start, right_end, min);
		}
	}

	int findMin(std::vector<int>& nums)
	{
		int min = nums[0];

		int start = 0;
		int end = nums.size() - 1;

		binary_search(nums, start, end, min);

		return min;
	}
};



int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {3, 4, 5, 1, 2};

	/* Example 2 */
	// std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

	/* Example 3 */
	// std::vector<int> nums = {11, 13, 15, 17};

	/* Example 4 */
	// std::vector<int> nums = {2, 1};

	/* Example 5 */
	// std::vector<int> nums = {2, 3, 4, 1};

	/* Example 6 */
	// std::vector<int> nums = {5};

	std::cout << "\n\t============================================";
	std::cout << "\n\t=== FIND MINIMUM IN ROTATED SORTED ARRAY ===";
	std::cout << "\n\t============================================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tArray: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	int min = sol.findMin(nums);

	/* Write Output */
	std::cout << "\n\tMinimum is: " << min << "\n\n";

	return 0;
}
