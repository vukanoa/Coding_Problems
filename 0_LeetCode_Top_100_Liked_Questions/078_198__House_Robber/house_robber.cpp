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
	connected and *it will automatically contact the police if two adjacent
	houses were broken into on the same night.*

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
	============
	=== NOTE ===
	============

	There are 4 Solutions down there. In reality it's 2 approaches of which
	each has both Space O(n) and improvement, i.e. Space O(n).

	Every Solution runs in O(n) Time and Beats 100%.

	In the very first Solution down, in Explanation(IDEA) there is an
	explanation on how to approach DP problem, but I don't like it how it ended
	up looking and "sounding", therefore I suggest you reading only the
	explanation of the 3rd Solution down below.

	I believe that is the most clear on how to solve this problem.
	
	Update: I added one more Solution, the 5th one. I believe it is the most
	        concise. However, maybe the 3rd one still remains easier to
	        comprehend.

*/


/*
	------------
	--- IDEA ---
	------------

	From good to great. How to approach most of DP problems.

	There is some frustration when people publish their perfect fine-grained
	algorithms without sharing any information about how they were derived.
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

	If an option "a" is selected it means the robber can't rob previous "i-1" 
	house, but can safely proceed to the one before previous, i.e. "i-2" and 
	gets all cumulative loot that follows.

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

		return std::max(recursion(nums, i-2) + nums[i], recursion(nums, i-1));
	}

	This algorithm will process the same "i" multiple times and it needs
	improvement. Time Complexity: O(2^n)



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
	are set to nums[0] and std::max(nums[0], nums[1]), respecitvely.

	Now we iteratively start from the 2nd index and calculate max of:
		1. dp[i - 2] + nums[i]
		2. dp[i - 1]

	and assign that to dp[i].

	At the end, the biggest amount of money we can get away with is in:
		dp[nums.size() -1]
	Meaning in the last position of vector "dp".

*/

/* Time  Beats:   100% */
/* Space Beats: 58.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n)
   I can use prev_1 and prev_2 instead of the whole vector "dp", but this is
   way easier to read.

   I wrote a "prev_1, prev_2" solution above.
*/
class Solution_1 {
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




/*
	------------
	--- IDEA ---
	------------

	Space efficient of the above Solution.
	
*/

/* Time  Beats:  100% */
/* Space Beats: 97.9% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_1_Space_Efficient{
public:
	int rob(std::vector<int>& nums)
	{
		if (nums.size() < 1)
			return 0;

		if (nums.size() == 1)
			return nums[0];

		int dp_i_min_2 = nums[0];
		int dp_i_min_1 = std::max(nums[0], nums[1]);

		for (int i = 2; i < nums.size(); i++)
		{
			int dp_i = std::max(dp_i_min_2 + nums[i], dp_i_min_1);

			std::swap(dp_i_min_2, dp_i_min_1);
			std::swap(dp_i_min_1, dp_i);
		}

		return dp_i_min_1;
	}
};




/*
	------------
	--- IDEA ---
	------------

	I was doing this problem for the 2nd time and this is the Solution I came
	up with so I wanted to save it as well.

	It's a similar IDEA, , but it's not equivalent. It seems more obvious than 
	the previous ones.

	It's important to note that in the above Solution, we return:
		return dp[nums.size() - 1];
	
	However, in this one, we're not doing that. We are return the max rob of
	all the given houses. Let me explain.

	dp[0] is always nums[0].
	dp[1] is always nums[1], except when there is only one element in "nums".

	However, now it's not true that dp[1] is max(dp[0], dp[1]) because if I
	take 1-st(not 0-th, but at index 1) element, then that means that I must
	not include the value of dp[0] because that's an adjacent house.

	Therefore, dp[1] is equal to nums[1].
	
	At each step I check if i-3 is >= 0, but that is relevant only for element
	at index 2, at all the other elements, i-3 will be >=0.

	Then dp[i] becomes max(dp[i - 3], dp[i - 2]) + nums[i];

	Again it's important to note that if I include dp[x], then that means I did
	not rob dp[x-1].
	
	Example 1
	[2, 1, 1, 4]    The answer is 6

	Example 2
	[2, 1, 1, 4, 1] The answer is still 6, however, dp[n - 1] is not 6.

		dp[n - 1] is 5. If there were other houses as well, and I wanted to
		include the house at index 4(which is now at index n-1), then that
		means that I must not have robbed house at index 3. That's the
		condition for robbing house at index 4.

		But if you look at this whole array, the solution would be 5. The
		Solution doesn't give us the max rob if we rob the n-1st house in the
		array, but gives us the max rob value of all the houses that we're
		given.
	
	This Solution is different than the previous in so far that this Solution
	leaves the dp[n - 1] ready for concatenation of other houses, but returns
	the max rob value of the whole array anyway.

	On the other hand, previous Solution, returns the max rob value of the
	whole array, but is NOT ready for adding new houses. If we were to add
	more houses to this array(amount of money of those houses to be precise)
	we would have to run this program from the beginning as if it's a
	completely new Example, even though the previous example is a subproblem of
	this, new, one.

	Whereas this Solution would be able to just continue because saved results
	in dp truly work as Dynamic Programming algorithm should.

	Conclusion:
		If we were to add more houses to Solution_1's array, we would have to
		do the whole problem from the beginning, whereas Solution_Reusable can
		just continue from newly added houses.

*/

/* Time  Beats:   100% */
/* Space Beats: 58.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Reusable {
public:
	int rob(std::vector<int>& nums)
	{
		int n = nums.size();

		if (n == 1)
			return nums[0];

		std::vector<int> dp(n, 0);
		dp[0] = nums[0];
		dp[1] = nums[1];

		int max_rob = std::max(dp[0], dp[1]);

		for (int i = 2; i < n; i++)
		{
			if (i - 3 >= 0)
				dp[i] = std::max(dp[i - 3], dp[i - 2]) + nums[i];
			else // i - 2 >= 0 is certainly true(this "if" is only for i = 2)
				dp[i] = dp[i - 2] + nums[i]; // Here prev_3 is i-2nd element

			max_rob = std::max(max_rob, dp[i]);
		}

		return max_rob;
	}
};





/*
	------------
	--- IDEA ---
	------------

	Space Efficient of the above Solution.
	
*/

/* Time  Beats:  100% */
/* Space Beats: 97.9% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Reusable_Space_Efficient {
public:
	int rob(std::vector<int>& nums)
	{
		int n = nums.size();

		if (n == 1)
			return nums[0];

		int prev_3 = nums[0];
		int prev_2 = nums[1];
		int prev_1 = -1;
		int curr;

		int max_rob = std::max(prev_3, prev_2);

		for (int i = 2; i < n; i++)
		{
			if (i - 3 >= 0)
				curr = std::max(prev_3, prev_2) + nums[i];
			else // i - 2 >= 0 is certainly true
				curr = prev_3 + nums[i]; // Here prev_3 is i-2nd element

			max_rob = std::max(max_rob, curr);

			if (i - 3 >= 0)
			{
				prev_3 = prev_2;
				prev_2 = prev_1;
			}

			prev_1 = curr;
		}

		return max_rob;
	}
};




/*
	------------
	--- IDEA ---
	------------

	The most concise.

*/

/* Time  Beats:   100% */
/* Space Beats: 94.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
	int rob(std::vector<int>& nums)
	{
		int n = nums.size();

		if (n == 1)
		    return nums[0];

		int prev = 0;
		int curr = 0;

		for (int i = 0; i < n; i++)
		{
			int tmp = std::max(prev + nums[i], curr);

			prev = curr;
			curr = tmp;
		}

		return curr;
	}
};


int
main()
{
	Solution_1                        sol_1;
	Solution_1_Space_Efficient        sol_1_space;
	Solution_Reusable                 sol_reusable;
	Solution_Reusable_Space_Efficient sol_reusable_space;
	Solution_Concise                  sol_concise;


	/* Example 1 */
	// std::vector<int> nums = {1, 2, 3, 1};

	/* Example 2 */
	// std::vector<int> nums = {2, 7, 9, 3, 1};

	/* Example 3 */
	// std::vector<int> nums = {1, 2, 3, 1, 1, 100};

	/* Example 4 */
	std::vector<int> nums = {3, 6, 9, 2, 7, 5, 8, 4};

	/* Example 5 */
	// std::vector<int> nums = {2, 3, 2, 5, 7, 1};

	/* Example 6 */
	// std::vector<int> nums = {2, 1, 2, 5, 7, 1};


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
	// int money = sol_1.rob(nums);
	// int money = sol_1_space.rob(nums);
	// int money = sol_reusable.rob(nums);
	// int money = sol_reusable_space.rob(nums);
	int money = sol_concise.rob(nums);


	/* Write Output */
	std::cout << "\n\tMaximum amount of money without alerting the police: " << money << "\n\n";


	return 0;
}
