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

	It's a basic Binary Search. There's only one thing that is important to be
	explained here.

	Why are we returning the "left" pointer after the while loop?

~~~~~~~~~~~~~~
~~ Smaller ~~~ (target smaller than the last we're checking in the while loop)
~~~~~~~~~~~~~~

	Consider this example:
	    nums = [2]
	indexes:    0

	target = 1;

	At the beginning of the while loop, both "left" and "right" are at index 0.
	"mid" is also going to be 0.

	           mid
	            R
	            L
	    nums = [2]
	indexes:    0


	Now since nums[mid] != target, we have to update either our "left" or our
	"right" pointer.

	target < nums[mid]
	  1   <   2
	
	Therefore we have to update our "right" pointer to mid - 1.

	Once we do that, our "right" becomes less than "left" which breaks our
	while loop.

	Now we're in this position:

                    R  L
            nums =    [2]
        indexes:   -1  0
                    ^
out of bounds ______|

	Look at the above "picture". Let's ask a question - Where should we place
	our target(1)?
	Well, at position 0, where our "left" pointer points.



	Now let's consider a target which is greater than the last item we're
	checking.


~~~~~~~~~~~~~~
~~ Greater ~~~ (target greater than the last we're checking in the while loop)
~~~~~~~~~~~~~~

	Consider this example: (Same example, different target)
	    nums = [2]
	indexes:    0

	target = 3;

	At the beginning both "left and "right" are at index 0, and "mid" as well.

	           mid
	            R
	            L
	    nums = [2]
	indexes:    0

	Now since:
		target > nums[mid]
			L = mid + 1;
	
	We update our "left" pointer and we're in this situation:
	
                    R  L
            nums = [2]
        indexes:    0  1
                       ^
out of bounds _________|

	Again, let's ask ourselves the same question - At which index should our
	target(3) be inserted?
	Well, at index 1. Which pointer points to index 1?
	The "left" one again!
~~~~~~~

	That's the whole "trick" of this problem.

*/


/* Time  Beats: 100% */
/* Space Beats: 35.98% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution{
public:
	int searchInsert(std::vector<int>& nums, int target)
	{
		int n = nums.size();

		int left  = 0;
		int right = n - 1;

		while (left <= right)
		{
			int mid = (left + right) / 2;

			if (target == nums[mid])
				return mid;

			if (target < nums[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}

		return left;
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


	std::cout << "\n\t==============================";
	std::cout << "\n\t=== SEARCH INSERT POSITION ===";
	std::cout << "\n\t==============================\n";


	/* Write Input */
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


	/* Solution */
	int output = sol.searchInsert(nums, target);


	/* Write Output */
	std::cout << "\n\tInsert at index: " << output << "\n\n";

	return 0;
}
