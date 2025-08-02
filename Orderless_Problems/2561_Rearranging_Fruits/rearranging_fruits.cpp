/*
    ============
    === HARD ===
    ============

    ===========================
    2561) Rearranging Fruits
    ===========================

    ============
    Description:
    ============

    You have two fruit baskets containing n fruits each. You are given two
    0-indexed integer arrays basket1 and basket2 representing the cost of fruit
    in each basket. You want to make both baskets equal. To do so, you can use
    the following operation as many times as you want:

       +  Chose two indices i and j, and swap the ith fruit of basket1 with the
          jth fruit of basket2. The cost of the swap is
          min(basket1[i],basket2[j]).

    Two baskets are considered equal if sorting them according to the fruit
    cost makes them exactly the same baskets.

    Return the minimum cost to make both the baskets equal or -1 if impossible.

    ========================================================================
    FUNCTION: long long minCost(vector<int>& basket1, vector<int>& basket2);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
    Output: 1
    Explanation: Swap index 1 of basket1 with index 0 of basket2, which has
                 cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2].
                 Rearranging both the arrays makes them equal.


    --- Example 2 ---
    Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
    Output: -1
    Explanation: It can be shown that it is impossible to make both the baskets
                 equal.


    *** Constraints ***
    basket1.length == basket2.length
    1 <= basket1.length <= 10^5
    1 <= basket1[i],basket2[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 23.45% */
/* Space Beats: 24.14% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2)
    {
        map<int, int> total_counts;
        for (const int& fruit : basket1)
            total_counts[fruit]++;

        for (const int& fruit : basket2)
            total_counts[fruit]++;

        long long min_val = LLONG_MAX;
        for (auto const& [fruit, count] : total_counts)
        {
            if (count % 2 != 0)
                return -1;

            min_val = min(min_val, 1LL * fruit);
        }
        
        vector<long long> fruits_to_swap;
        unordered_map<int, int> umap;
        for (const int& fruit : basket1)
            umap[fruit]++;
        
        for (const auto& [fruit, total_count] : total_counts)
        {
            int diff = umap[fruit] - (total_count / 2);

            for (int i = 0; i < abs(diff); i++)
                fruits_to_swap.push_back(fruit);
        }
        
        /* Sort */
        sort(fruits_to_swap.begin(), fruits_to_swap.end());
        
        long long total_cost = 0;
        int swaps_to_make = fruits_to_swap.size() / 2;

        for (int i = 0; i < swaps_to_make; i++)
            total_cost += min(fruits_to_swap[i], 2 * min_val);
        
        return total_cost;
    }
};
