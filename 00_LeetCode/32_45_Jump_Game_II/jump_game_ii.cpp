#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	45) Jump Game II
	===========================

	============
	Description:
	============

	You are given an 0-indexed array of integers "nums" of length n. You are
	initially positioned at "nums[0]".

	Each element "nums[i]" represents the maximum length of a forward jump from
	index "i". In other words, if you are at "nums[i]", you can jump to any
	"nums[i + j] where:
		0 <= j <= nums[i]
			and
		i + j < n

	Return the minimum number of jumps to reach "nums[n - 1]". The test cases
	are generated such that you can reach "nums[n - 1]"

	===========================================
	FUNCTION: int jump(std::vector<int>& nums);
	===========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [2, 3, 1, 1, 4]
	Output: 2

	--- Example 2 ---
	Input: nums = [2, 3, 0, 1, 4]
	Output 2

	--- Example 3 ---
	Input: nums = [2, 2, 4, 1, 2, 1, 1]
	Output: 2

	--- Example 4 ---
	Input: nums = [2, 2, 3, 1, 2, 1, 1]
	Output: 3

	--- Example 5 ---
	Input: nums = [2, 3, 2, 1, 2, 1, 1]
	Output: 3

	--- Example 6 ---
	Input: nums = [2, 4, 2, 1, 4, 1, 2, 1, 1]
	Output: 3

	--- Example 7 ---
	Input: nums = [3, 4, 2, 5, 4, 1, 2, 1, 1]
	Output: 2

	*** Constraints ***
	1 <= nums.length <= 10^4
	0 <= nums[i] <= 1000

*/



/*
	------------
	--- IDEA ---
	------------

	This is BFS-structure problem.
	Consider the very first Example:
		nums = [2, 3, 1, 1, 4]

	We are initially at position 0. Then we can move at most nums[0] steps
	from it. So, after one move, we may reach nums[1] == 3 or nums[2] == 1.
	So these node are reachable in 1 jump.

	From these nodes, we can further move to nums[3] = 1 and nums[4] = 4. Now
	you can see that the target nums[4] = 4 is reachable in 2 jumps.

	We keep two pointers: "start" & "end" that record the current range of the
	starting nodes. Each time after we jump, update "start" to be "end + 1"
	and "end" to be the farthest index that can be reached in 1 jump from the
	current [start, end]



	Consider the Example 6:
	It isn't true that the farthest jump is always the most preferred.

	nums = [2, 4, 2, 1, 4, 1, 2, 1, 1]

	In this case the shortest path is: 0, 2, 4 (indexes) = 3 jumps
	And one would assume that we should've gone for 0, 1, 5, 6 = 4 jumps

	So, how do we get around this?
	When we are at nums[0] = 2, how to know if we should jump 4 or 2?
	Well, we should exceed our max_end that is the longest reach which can
	either be > end + 1 or end+1 itself.

	In either case, we move "start" to 'next level'(think of it as BFS).
	next_level would be "end + 1". Now since our max_end(longest reach) is
	either the same as the index we're currently on, or longer, now we will
	check if inside THAT range we can find a jump that gets us to us desired
	place.

	That's how, even if "taking 4" as an option isn't going to make the
	shortest path, this approach will. We aren't necessarily taking each jump,
	we are just "stretching" our max_end(longest reach) and checking if from
	within that range we can actually get to our desired goal which is the
	very last element.

*/



/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int jump(std::vector<int>& nums)
	{
		int n = nums.size();

		int count_jumps = 0;
		int start = 0;
		int end = 0;

		while (end < n - 1)
		{
			count_jumps++;
			int max_end = end + 1; // In case nums[i] == 0

			for (int i = start; i <= end; i++)
			{
				if (i + nums[i] >= n - 1)
					return count_jumps;

				max_end = std::max(max_end, i + nums[i]);
			}

			start = end + 1;
			end = max_end;
		}

		return count_jumps;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {2, 3, 1, 1, 4};

	/* Example 2 */
	// std::vector<int> nums = {2, 3, 0, 1, 4};

	/* Example 3 */
	// std::vector<int> nums = {2, 2, 4, 1, 2, 1, 1};

	/* Example 4 */
	// std::vector<int> nums = {2, 2, 3, 1, 2, 1, 1};

	/* Example 5 */
	// std::vector<int> nums = {2, 3, 2, 1, 2, 1, 1};

	/* Example 6 */
	std::vector<int> nums = {2, 4, 2, 1, 4, 1, 2, 1, 1};

	/* Example 7 */
	// std::vector<int> nums = {3, 4, 2, 5, 4, 1, 2, 1, 1};

	std::cout << "\n\t====================";
	std::cout << "\n\t=== JUMP GAME II ===";
	std::cout << "\n\t====================\n\n";

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
	int output = sol.jump(nums);

	std::cout << "\n\tOutput: " << output << "\n\n";

	return 0;
}
