#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	198) House Robber
	===========================

	============
	Description:
	============

	You are a professional robber planning to rob houses along a street. Each
	house has a certain amount of money stashed, the only constraint stopping
	you from robbing each of them is that adjacent houses have security systems
	connected and it will automatically contact the police if two adjacent
	houses were broken into on the same night.

	Given an integer array "nums" representing the amount of money of each
	house, return the maximum amount of money you can rob tonight without
	alerting the police.

	=====================================
	FUNCTION: int rob(vector<int>& nums);
	=====================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 2, 3, 1]
	Output: 4

	--- Example 2 ---
	Input:  nums = [2, 7, 9, 3, 1]
	Output: 12

	*** Constraints ***
	1 <= nums.length <= 100
	0 <= nums[i] <= 400

*/


/*
	------------
	--- IDEA ---
	------------

	From good to great. How to approach most of DP problems.

	There is some frustration when people publish their perfect fine-grained
	algorithms without sharing any information about ohw they were derived.
	This is an attempt to change the situation. There is not much more
	explanation but it's rather an example of higher level improvements.
	Converting a solution to the next step shouldn't be as hard as attempting
	to come up with perfect algorithm at first attempt.

	This particular problem and most of others can be approached using the
	following sequence:
		1. Find recursive relation
		2. Recursive        (top-down)
		3. Recursive + memo (top-down)
		4. Iterative + memo (bottom-up)
		5. Iterative + N variables (bottom-up)


	Step 1. Figure out recursive relation.

	A robber has 2 options:
		a) rob current house "i"
		b) don't rob current house.

	If an option "a" is selected it means she can't rob previous "i-1" house
	but can safely proceed to the one before previous "i-2" and gets all
	cumulative loot that follows.

	If an option "b" is selected the robber gets all the possible loot from
	robbery of "i-1" and all the following buildings.

	So it boils down to calculating what is more profitable:
		- robbery of current house + loot from houses before the previous
		- loot from the previous house robbery and any loot captures before
		  that

	rob(i) = Math.max( rob(i - 2) + currentHouseValue, rob(i - 1) )


	Step 2. Recursive (top-down)
	Converting the recurrent relation from Step 1 shouldn't be very hard.
	============
	=== CODE ===
	============

	int rob(std::vector<int>& nums)
	{
		return recursion(nums, nums.size()) - 1);
	}

	int recursion(std::vector<int> nums, int i)
	{
		if (i < 0)
			return 0;

		return std::max(recursion(nums, i - 2) + nums[i], recursion(nums, i - 1));
	}

	This algorithm will process the same "i" multiple times and it needs
	improvement. Time Complexity: [to fill]



	Step 3. Recursive + memo (top-down)
	============
	=== CODE ===
	============


	int rob(std::vector<int>& nums)
	{
		std::vector<int> memo(nums.size() + 1), -1);

		return recursion(nums, nums.size() - 1, memo);
	}

	int recursion(std::vector<int> nums, int i, std::vector<int>& memo)
	{
		if (i < 0)
			return 0;

		if (memo[i] >= 0)
			return memo[i];

		int result = std::max(nums, i - 2, memo) + nums[i], recursion(nums, i - 1, memo);
		memo[i] = result;

		return result;
	}

	Much better. This should run in O(n) time. Space complexity is O(n) as
	well, because of the recursion stack, let's try to get rid of it.



	Step 4.
	============
	=== CODE ===
	============

	int rob(std::vector<int>& nums)
	{
		if (nums.size() == 0)
			return 0;

		std::vector<int> memo(nums.size() + 1, -1);

		memo[0] = 0;
		memo[1] = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			int val = nums[i];
			memo[i + 1] = std::max(memo[i], memo[i - 1] + val);
		}

		return memo[nums.size()];
	}


	Step 5. Iterative + 2 variables (bottom-up)
	We can notice that in the previous step we use only "memo[i]" and
	"memo[i - 1]", so going just 2 steps back. We can hold them in 2 variables
	instead. This optimization is met in Fibonacci sequence creation and some
	other problems.
	============
	=== CODE ===
	============

	// the order is: prev2, prev1, num
	int rob(std::vector<int>& nums)
	{
		if (nums.size() == 0)
			return 0;

		int prev_1 = 0;
		int prev_2 = 0;
		for (int num : nums)
		{
			int tmp = prev_1;
			prev_1 = std::max(prev_2 + num, prev_1);
			prev_2 = tmp;
		}

		return prev1;
	}



	--- My Solution ---
	This is an obvious DP problem.

	If "nums" is Empty => return 0.
	it "nums" is of size 1 => return nums[0].

	Since nums[0] and nums[1] cannot have "previous houses", dp[0] and dp[1]
	are set to nums[0] and std::max(nums[i], nums[1]), respecitvely.

	Now we iteratively start from the 2nd index and calculate max of:
		1. dp[i - 2] + nums[i]
		2. d[i - 1]

	and assign that to dp[i].

	At the end, the biggest amount of money we can get away with is in:
		dp[nums.size() -1]
	Meaning in the last position of vector "dp".

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(1)
   I can use prev_1 and prev_2 instead of the whole vector "dp", but this is
   way easier to read.

   I wrote a "prev_1, prev_2" solution above.
*/
class Solution{
public:
	int rob(std::vector<int>& nums)
	{
		if (nums.size() < 1)
			return 0;

		if (nums.size() == 1)
			return nums[0];

		std::vector<int> dp(nums.size(), 0);
		dp[0] = nums[0];
		dp[1] = std::max(nums[0], nums[1]);

		for (int i = 2; i < nums.size(); i++)
			dp[i] = std::max(dp[i - 2] + nums[i], dp[i - 1]);

		return dp[nums.size() - 1];
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 2, 3, 1};

	/* Example 2 */
	// std::vector<int> nums = {2, 7, 9, 3, 1};

	/* Example 3 */
	// std::vector<int> nums = {1, 2, 3, 1, 1, 100};

	/* Example 4 */
	std::vector<int> nums = {3, 6, 9, 2, 7, 5, 8, 4};

	std::cout << "\n\t=====================";
	std::cout << "\n\t=== HOUSE ROBBERY ===";
	std::cout << "\n\t=====================\n";

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
	int money = sol.rob(nums);

	/* Write Output */
	std::cout << "\n\tMaximum amount of money without alerting the police: " << money << "\n\n";

	return 0;
}
