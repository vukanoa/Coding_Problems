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
	that amount of money cannot be made up by any comination of the coins,
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


/* Time  Complexity: O(amount * coins.size()) */
/* Space Complexity: O(amount) */
class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount)
	{
        int dp[++amount];
        dp[0] = 0;

        std::sort(begin(coins), end(coins));

        for (int a = 1; a < amount; a++)
        {
            dp[a] = INT_MAX;
            for (int c: coins)
            {
                if (a - c < 0)
                    break;
                else if (dp[a - c] != INT_MAX)
                    dp[a] = std::min(dp[a], 1 + dp[a - c]);
            }
        }
        return dp[--amount] == INT_MAX ? -1 : dp[amount];
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
	std::vector<int> nums = {1, 3, 4};
	int amount = 6;

	std::cout << "\n\t===================";
	std::cout << "\n\t=== COIN CHANGE ===";
	std::cout << "\n\t===================\n\n";


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

	std::cout << "\n\n\tMin coins used: " << number << "\n\n";

	return 0;
}
