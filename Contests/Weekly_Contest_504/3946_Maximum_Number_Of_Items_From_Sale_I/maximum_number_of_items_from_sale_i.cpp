/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3946) Maximum Number of Items From Sale I
    =========================================

    ============
    Description:
    ============

    You are given a 2D integer array items, where items[i] = [factori, pricei]
    represents the ith item. You are also given an integer budget.

    There are unlimited copies of each item available for purchase.You may buy
    any number of copies of any items such that the total cost of the purchased
    copies is at most budget.

    After buying items, you may receive free copies according to the following rules:

        + For each item i that you bought at least one copy of, you receive one
          free copy of every item j such that j != i and factori divides
          factorj.

        + Buying multiple copies of the same item i does not give additional
          free copies through item i.

        + The same item j can be received multiple times for free if it is
          received from purchases of different item types.

    Return the maximum total number of item copies you can obtain, including
    both purchased copies and free copies, while spending at most budget on
    purchased items.

    =======================================================================
    FUNCTION: int maximumSaleItems(vector<vector<int>>& items, int budget);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: items = [[6,2],[2,6],[3,4]], budget = 9
    Output: 4
    Explanation:
        You can buy 2 copies of item 0 and 1 copy of item 2 for a total cost of 2 * 2 + 4 = 8, which is not greater than budget = 9.
        Buying item 2 gives 1 free copy of item 0, because factor2 = 3 divides factor0 = 6.
        You leave with 3 purchased copies and 1 free copy, for a total of 4 item copies.

    --- Example 2 ---
    Input: items = [[2,4],[3,2],[4,1],[6,4],[12,4]], budget = 8
    Output: 10
    Explanation:
        You can buy 1 copy of item 0, 1 copy of item 1, and 2 copies of item 2 for a total cost of 4 + 2 + 2 * 1 = 8.
        Buying item 0 gives 1 free copy of items 2, 3, and 4.
        Buying item 1 gives 1 free copy of items 3 and 4.
        Buying item 2 gives 1 free copy of item 4.
        Thus, you receive 6 free copies. You leave with 4 purchased copies and 6 free copies, for a total of 10 item copies.


    *** Constraints ***
    1 <= items.length <= 1000
    items[i] = [factori, pricei]
    1 <= factori, pricei <= 1500
    1 <= budget <= 1500

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The absolute CRUX of this Solution is this part:

        if (curr_item >= N)
            return remaining_budget / cheapest_item_price; // This is the CRUX!

    We want to take some COMBINATION of items--but ONLY A SINGLE copy from each
    of those within the combination--and then the take as many copies as you
    can by buying the cheapest one.

    Why're we doing "ONLY A SINGLE copy from each of those within combination"?

    Because we want to MAXIMIZE the numbers of FREE COPIES we get.
    
    We take the combination that yields the MAXIMUM free copies and then just
    greedily buy the cheapest one since there are infinite copies of each item.


    Other than that it's a simple Take-Skip Memoization Problem.

*/

/* Time  Beats: 19.41% */
/* Space Beats: 63.04% */

/* Time  Complexity: O(N * MAX_BUDGET) */
/* Space Complexity: O(N * MAX_BUDGET) */
class Solution_Top_Down__Memoization {
private:
    int memo[1000][1501];

    int cheapest_item_price;
    vector<int> number_of_free_items;

public:
    int maximumSaleItems(vector<vector<int>>& items, int budget)
    {
        const int N = items.size();
        cheapest_item_price = INT_MAX;

        number_of_free_items.resize(N, 0);

        for (int curr_item = 0; curr_item < N; curr_item++)
        {
            cheapest_item_price = min(cheapest_item_price, items[curr_item][1]);

            for (int other_item = 0; other_item < N; other_item++)
            {
                if (items[other_item][0] % items[curr_item][0] == 0)
                    number_of_free_items[curr_item]++;
            }
        }

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(0, budget, items);
    }

private:
    int solve(int curr_item, int remaining_budget, vector<vector<int>>& items)
    {
        const int N = items.size();

        if (curr_item >= N)
            return remaining_budget / cheapest_item_price; // This is the CRUX!

        if (memo[curr_item][remaining_budget] != -1)
            return memo[curr_item][remaining_budget];


        int skip = solve(curr_item + 1, remaining_budget, items);
        int take = 0;

        if (remaining_budget >= items[curr_item][1])
        {
            take = number_of_free_items[curr_item] + solve(curr_item + 1, remaining_budget - items[curr_item][1], items);
        }

        return memo[curr_item][remaining_budget] = max(take, skip);
    }

};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.70% */
/* Space Beats: 23.72% */

/* Time  Complexity: O(N * MAX_BUDGET) */
/* Space Complexity: O(N * MAX_BUDGET) */
class Solution_Bottom_Up__Tabulation {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget)
    {
        const int N = items.size();

        vector<int> number_of_free_items(N, 0);
        int cheapest_item_price = INT_MAX;

        for (int curr_item = 0; curr_item < N; curr_item++)
        {
            cheapest_item_price = min(cheapest_item_price, items[curr_item][1]);

            for (int other_item = 0; other_item < N; other_item++)
            {
                if (items[other_item][0] % items[curr_item][0] == 0)
                    number_of_free_items[curr_item]++;
            }
        }

        vector<vector<int>> dp(N + 1, vector<int>(budget + 1, 0));

        for (int remaining_budget = 0; remaining_budget <= budget; remaining_budget++)
            dp[N][remaining_budget] = remaining_budget / cheapest_item_price;

        for (int curr_item = N-1; curr_item >= 0; curr_item--)
        {
            for (int remaining_budget = 0; remaining_budget <= budget; remaining_budget++)
            {
                int skip = dp[curr_item + 1][remaining_budget];
                int take = 0;

                if (remaining_budget >= items[curr_item][1])
                {
                    take = number_of_free_items[curr_item] + dp[curr_item + 1][remaining_budget - items[curr_item][1]];
                }

                dp[curr_item][remaining_budget] = max(take, skip);
            }
        }

        return dp[0][budget];
    }
};
