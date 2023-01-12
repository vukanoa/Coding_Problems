#include <iostream>
#include <vector>


/*
	============
	=== EASY ===
	============

	====================================
	121) Best Time to Buy and Sell Stock
	====================================

	============
	Description:
	============

	You are given an array "prices" where "prices[i]" is the price of a given
	stock on the "i"-th day.

	You want to maximize your profit by choosing a single day to buy one stock
	and choosing a different day in the future to sell that stock.

	Return the maximum profit you can achieve from this transactin. If you
	cannot achieve any profit, return 0.

	============================================
	FUNCTION: int maxProfit(vecto<int>& prices);
	============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  prices = [7, 1, 5, 3, 6, 4]
	Output: 5

	--- Example 2 ---
	Input:  prices = [7, 6, 4, 3, 1]
	Output: 0

	*** Constraints ***
	1 <= prices.length <= 10^5
	0 <= prices[i] <= 10^4

*/


/*
	------------
	--- IDEA ---
	------------

	Two pointers.

	Imagine a coordinate system.
	Values on the Y axis are the prices.
	Values on the X axis are the days.

	We put "left"  to point to 0th day.
	We put "right" to point to 1st day.

	If we find that prices[right] is lower than prices[left](which is the
	current day) then we make "left" point to "right" and we increment "right"
	by one.
	We don't want to buy it today it tomorrow's price is going to be lower.

	However, if prices[right] is greater than prices[left], meaning we would
	make some profit, then calculate if that profit is the maximum and also
	increment "right" by one, but only "right", "left" remains fixed.

	Once we get "right" pointer to the end of the array "prices" we are done.
	Just return "max".

	We are sure that is the maximum since if we were to find out that some
	other value was lower than our fixed "left" pointer, we would've moved it
	and calculate profit from that point.

	We pass through the array only once, thus the Complexity is O(n).
*/



/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int maxProfit(std::vector<int>& prices)
	{
		int left  = 0;
		int right = 1;

		int max = 0;

		while (right < prices.size())
		{
			if (prices[left] > prices[right])
				left = right;
			else
			{
				if (prices[right] - prices[left] > max)
					max = prices[right] - prices[left];
			}

			right++;
		}

		return max;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> prices = {7, 1, 5, 3, 6, 4};

	/* Example 2 */
	// std::vector<int> prices = {7, 6, 4, 3, 1};

	std::cout << "\n\t=======================================";
	std::cout << "\n\t=== BEST TIME TO BUY AND SELL STOCK ===";
	std::cout << "\n\t=======================================\n\n";

	/* Solution */
	int max = sol.maxProfit(prices);


	bool first = true;
	std::cout << "\n\tPrices: [";
	for (auto x: prices)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	std::cout << "\n\tMax profit is: " << max << "\n\n";

	return 0;
}
