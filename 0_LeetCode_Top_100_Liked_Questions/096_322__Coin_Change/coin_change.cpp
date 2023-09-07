#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	322) Coin Change
	===========================

	============
	Description:
	============

	You are given an integer array "coins" representing coins of different
	denominations and an integer "amount" representing a total amount of money.

	Return the fewest number of coins that you need to make up that amount. If
	that amount of money cannot be made up by any combination of the coins,
	return -1.

	You may assume that you have an infinite number of each kind of coin.

	=========================================================
	FUNCTION: int coinChange(vector<int>& coins, int amount);
	=========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  coins = [1, 2, 5], amount = 11
	Output: 3
	Explanation: 11 = 5 + 5 + 1

	--- Example 2 ---
	Input:  coins = [2], amount = 3
	Output: -1

	--- Example 3 ---
	Input:  coins = [1], amount = 0
	Output: 0

	*** Constraints ***
	1 <= coins.length <= 12
	1 <= coins[i] <= 2^31 - 1
	0 <= amount <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	Inuitively, at a first glance at this problem you'd probably think:
	"Is it this easy? Is it just a greedy?"

	But upon a further examination, you'll quickly find an example that
	dispproves such hypothesis.

	Consider this:
	Array: [1, 3, 4]
	Amount: 6

	If you were to use a greedy algorithm, you'd quickly find that you'd need
	3 coins which we clearly see that it's not optimal.

	So you cannot "just pick the largest one and go with it and then drop it
	after you cannot fit it once again and go for a smaller one", since the
	largest one maybe shouldn't even be in the solution.

	The next thing that comes up to mind is: Can this be a DFS-Backtracking?

	Well, yes it can be. It will work, but probably will give you a TLE(Time
	Limit Exceeded) on LeetCode.

	However, if you were to draw yourself a whole tree in DFS-Backtracking
	process you would've seen that there are certain things that unnecessarily
	compute more than once.

	So a natural question arises - Can I memorize this?
	As soon as you ask this question, the answer almost always is - Yes.

	We could use a "Top-Down memoization"(Not memoRization) approach and that
	would be a DP(Dynamic Programming approach).

	However, a more natural way of using DP is writing it "Bottom-Up".

	So is it possible to write a "Bottom-Up" approach for this problem? Yes.

	We have to solve the subproblems of our given problem, one by one, and then
	at the very end - Solve our given problem.

	So how do we do this?
	Let's consider the previous example that crushed our "Is it greedy?"
	question.

	Array: [1, 3, 4]
	Amount: 6

	We have to solve subproblems, but what are those subproblems?
	Since our goal is to reach 6, let's try to find an answer to:
		1, 2, 3, 4 and 5
	before we try to go for our given amount 6.

	First, let's make an array dp. What length should it be?
	Well, since dp[0] is always 0 since we need 0 coins to get to amount of 0,
	we must have this base case solved which will make our dp of size: amount+1

	What are the values we should initialize this array with?
	It's important that we assign 0 to dp[0] and all the other should be either
	amount + 1(since any combination we try will be less than that) or INT_MAX

	Let's go with INT_MAX. So initially our DP looks like this:

	[0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX]
	 0     1        2        3        4        5        6

	So let's try to solve this problem as if the amount given is 1.

	We should iterate through all the coins and if our amount(1 in this case)
	minus the coin we're currently on is less than 0, then that means there is
	no solution for this amount.(We are iterating through coins from the
	smallest to the largest) [Example below]

	Note that the coins don't have to be in sorted order, thus we should always
	sort it as a first thing.
	(We can sort them because that won't worsen our overall Time Complexity)

	So, we're doing this:
	Array: [1, 3, 4]
	Amount: 1

	if (amount - coins[0] < 0)
		break; // This will return -1 to denote that there is no way getting it

	else if (dp[amount - coins[0]] != INT_MAX)
		dp[amount] = std::min(dp[amount], dp[amount - coins[0]] + 1); // +1 to add this coin

	The idea is to find the minimum number of coins needed to solve all these
	subproblems and then each time we search for amount X, subtract value of
	the current coin from the amount and then try to see what is the minimum
	number of coins for that newly calulated amount.

	Example:
	Array: [1, 3, 4]
	Amount: 6

	dp[0] = 0;
	dp[1] = 1
	dp[2] = 2
	dp[3] = 1
	dp[4] = 1
	dp[5] = 2

	So how do we find what is the minimum number of coins needed that sum up to
	6?

	Let's iterate through all the coins:
		1) We take coin with value 1(coin at index 0)
			Amount(which is 6) minus value of current coin => 6 - 1 = 5
			Now we try and see what is the value of dp[5] since that is the
			minimum number of coins needed to sum up to 5 and then we add 1
			more(this current coin we're trying)
			Previously dp[6] was INT_MAX, now it's 3.
			Let's continue

		2) We take coin with value 3(coin at index 1)
			6 - 3 = 3
			dp[3] = 1
			dp[3] + 1 => 1 + 1 = 2

			dp[6] = std::min(dp[6], dp[3] + 1)
			dp[6] = std::min(  3  ,   1   + 1)

			Now our dp[6] is 2.

		3) We take coin with value 4(coin at index 2)
			6 - 4 = 2
			dp[2] = 2
			dp[2] + 1 => 2 + 1 = 3

			dp[6] = std::min(dp[6], dp[2] + 1);
			dp[6] = std::min(  2  ,   2   + 1);

			Since dp[6] was 2 because of the previous step, we're doing this:
			dp[6] = std::min(2, 2 + 1);
			dp[6] = std::min(2, 3);

			Thus we won't change the dp[6] to 3, since 2 is smaller.

	And at the end we ask if dp[6] is NOT INT_MAX.
	If it is NOT    INT_MAX, then we return the value we got.

	if it is INDEED INT_MAX, then we return -1 since that means we did not
	found a way to sum up to the amount value.

*/

/* Time  Beats: 97.90% */
/* Space Beats:   100% */

/*
	Time  Complexity: O(amount * coins.size())

	Sorting is: O(coins.size() * log(coins.size()))
	but:
		O(coins.size() * log(coins.size())) < O(amount * coins.size())
	
	That's why O(amount * coins.size()) is the overall Complexity.

*/
/* Space Complexity: O(amount) */
class Solution {
public:
	int coinChange(std::vector<int>& coins, int amount)
	{
		int dp[amount + 1];
		dp[0] = 0;

		// O(coins.size() * log(coins.size()))
		std::sort(begin(coins), end(coins));

		// O(amount * coins.size())
		for (int a = 1; a <= amount; a++)
		{
			dp[a] = amount + 1;
			for (const int& coin : coins)
			{
				if (a - coin >= 0)
					dp[a] = std::min(dp[a], 1 + dp[a - coin]);
				else
					break;
			}
		}

		return dp[amount] > amount ? -1 : dp[amount];
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 2, 5};
	// int amount = 11;

	/* Example 2 */
	// std::vector<int> nums = {2};
	// int amount = 3;

	/* Example 3 */
	// std::vector<int> nums = {1};
	// int amount = 0;

	/* Example 4 */
	// std::vector<int> nums = {1, 3, 4};
	// int amount = 6;

	/* Example 5 */
	// std::vector<int> nums = {1, 3, 5};
	// int amount = 7;

	/* Example 6 */
	// std::vector<int> nums = {1, 2, 5, 10};
	// int amount = 18;

	/* Example 7 */
	// std::vector<int> nums = {1, 3, 4};
	// int amount = 6;

	/* Example 8 */
	std::vector<int> nums = {1, 3, 4, 5};
	int amount = 7;


	std::cout << "\n\t===================";
	std::cout << "\n\t=== COIN CHANGE ===";
	std::cout << "\n\t===================\n";


	/* Write Input */
	std::cout << "\n\tAmount: " << amount << "\n";

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
	int number = sol.coinChange(nums, amount);

	
	/* Write Output */
	std::cout << "\n\n\tMin coins used: " << number << "\n\n";


	return 0;
}
