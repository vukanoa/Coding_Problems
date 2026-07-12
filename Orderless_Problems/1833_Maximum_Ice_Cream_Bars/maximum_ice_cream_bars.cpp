/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    1833) Maximum Ice Cream Bars
    ============================

    ============
    Description:
    ============

    It is a sweltering summer day, and a boy wants to buy some ice cream bars.

    At the store, there are n ice cream bars. You are given an array costs of
    length n, where costs[i] is the price of the ith ice cream bar in coins.
    The boy initially has coins coins to spend, and he wants to buy as many ice
    cream bars as possible. 

    =====
    Note: The boy can buy the ice cream bars in any order.

          Return the maximum number of ice cream bars the boy can buy with coins
          coins.

          You must solve the problem by counting sort. 
    =====

    =========================================================
    FUNCTION: int maxIceCream(vector<int>& costs, int coins);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: costs = [1,3,2,4,1], coins = 7
    Output: 4
    Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total
                 price of 1 + 3 + 2 + 1 = 7.

    --- Example 2 ---
    Input: costs = [10,6,8,7,7,8], coins = 5
    Output: 0
    Explanation: The boy cannot afford any of the ice cream bars.

    --- Example 3 ---
    Input: costs = [1,6,3,1,2,5], coins = 20
    Output: 6
    Explanation: The boy can buy all the ice cream bars for a total price of 1
                 + 6 + 3 + 1 + 2 + 5 = 18.


    *** Constraints ***
    costs.length == n
    1 <= n <= 10^5
    1 <= costs[i] <= 10^5
    1 <= coins <= 10^8

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  29.62% */

/* Time  Complexity: O(N + M) */ // Where 'N' is the size of array "costs"
/* Space Complexity: O(M)     */ // Where 'M' is the price range
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins)
    {
        const int N = costs.size();
        static constexpr int SIZE = 1e5 + 1; // +1 because we skip cost 0
        int result = 0;

        int freq[SIZE] = {0}; // Allocated on the Stack

        for (const int& price : costs)
            freq[price]++;

        for (int price = 1; price < SIZE; price++)
        {
            if (1LL * price * freq[price] > coins)
            {
                result += coins / price;
                break;
            }

            result += freq[price];
            coins  -= 1LL * price * freq[price];
        }

        return result;
    }
};
