#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	55) Jump Game
	===========================

	============
	Description:
	============

	You are given an integer array "nums". You are initially positioned at the
	array's first index, and each element in the array represents your maximum
	jump length at that position.

	Return "true" if you can reach the last index, or "false" otherwise.

	==========================================
	FUNCTION: bool canJump(vector<int>& nums);
	==========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [2, 3, 1, 1, 4]
	Output: true

	--- Example 2 ---
	Input:  nums = [3, 2, 1, 0, 4]
	Output: false

	--- Example 3 ---
	Input:  nums = [2, 3, 1, 1, 2, 4, 1, 2, 1, 3]
	Output: true

	*** Constraints ***
	1 <= nums.length <= 10^4
	0 <= nums[i] <= 10^5

*/


/*
	------------
	--- IDEA ---
	------------

	We check each element only once.

	Consider this Example:
	[2, 3, 1, 1, 2, 4, 1, 2, 1, 3]
	 0  1  2  3  4  5  6  7  8  9

	We begin by putting both "start" and "end" variables at 0.

	In the very first iteration we only check if there's a max_reach that is
	longer than 0. If there's not => return false.

	Since we're updating our start to begin each iteration at "end + 1" if
	we exceed our "max_reach", that is "start" becomes a higher index than we
	calculated is possible to reach, we return false.

	So how do we check each element only once?

	The idea is simple.
	1st Iteration    - Find max_reach and move to nums[1];
	Other Iterations - Check if any element from "start" to our "max_reach"
	                   reaches or exceeds the very last element.
					   If it does => return true.
					   If it does NOT => start from "old max_reach" + 1
					   "old max_reach" is "end".

*/


/* Time  Beats: 99.94% */
/* Space Beats: 51.60% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
	bool canJump(std::vector<int>& nums)
	{
		if (nums.size() == 1)
			return true;

		int n = nums.size();

		int start = 0;
		int end = 0;
		int max_reach = 0;

		while (end < n - 1)
		{
			for (int i = start; i <= end; i++)
			{
				if (i + nums[i] >= n - 1)
					return true;

				max_reach = std::max(max_reach, i + nums[i]);
			}

			start = end + 1;
			end = max_reach;

			if (start > max_reach)
				break;
		}

		return false;

	}
};





/*
	------------
	--- IDEA ---
	------------

	Another way to implemented the same idea. This one seems easier to read and
	grasp.

*/

/* Time  Beats: 76.88% */
/* Space Beats: 79.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
	bool canJump(std::vector<int>& nums)
	{
		int n = nums.size();

		int i = 0;
		int start = 0;
		int end = nums[0];

		while (i <= start+end)
		{
			if (i+nums[i] == n-1 || i == n-1)
				return true;
				
			if (i+nums[i] > start+end)
			{
				start = i;
				end = nums[i];
			}

			i++;
		}

		return false;
	}
};


int
main()
{
	Solution   sol;
	Solution_2 sol_2;


	/* Example 1 */
	std::vector<int> nums = {2, 3, 1, 1, 4};

	/* Example 2 */
	// std::vector<int> nums = {3, 2, 1, 0, 4};

	/* Example 3 */
	// std::vector<int> nums = {2, 3, 1, 1, 2, 4, 1, 2, 1, 3};

	/* Example 4 */
	// std::vector<int> nums = {3, 0, 8, 2, 0, 0, 1};

	/* Example 5 */
	// std::vector<int> nums = {3, 0, 3, 2, 0, 0, 5};

	std::cout << "\n\t=================";
	std::cout << "\n\t=== JUMP GAME ===";
	std::cout << "\n\t=================\n";


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
	bool possible = sol.canJump(nums);
	// bool possible = sol_2.canJump(nums);


	/* Write Output */
	if (possible)
		std::cout << "\n\tOutput: POSSIBLE to reach the very last element!";
	else
		std::cout << "\n\tOutput: IMPOSSIBLE to reach the very last element!";

	std::cout << "\n\n";

	return 0;
}
