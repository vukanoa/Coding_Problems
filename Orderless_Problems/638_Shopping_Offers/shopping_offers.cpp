/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    638) Shopping Offers
    ===========================

    ============
    Description:
    ============

    In LeetCode Store, there are n items to sell. Each item has a price.
    However, there are some special offers, and a special offer consists of one
    or more different kinds of items with a sale price.

    You are given an integer array price where price[i] is the price of the ith
    item, and an integer array needs where needs[i] is the number of pieces of
    the ith item you want to buy.

    You are also given an array special where special[i] is of size n + 1 where
    special[i][j] is the number of pieces of the jth item in the ith offer and
    special[i][n] (i.e., the last integer in the array) is the price of the ith
    offer.

    Return the lowest price you have to pay for exactly certain items as given,
    where you could make optimal use of the special offers. You are not allowed
    to buy more items than you want, even if that would lower the overall
    price. You could use any of the special offers as many times as you want.

    ===================================================================================================
    FUNCTION: int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs);
    ===================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
    Output: 14
    Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively.
    In special offer 1, you can pay $5 for 3A and 0B
    In special offer 2, you can pay $10 for 1A and 2B.
    You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.

    --- Example 2 ---
    Input: price = [2,3,4], special = [[1,1,0,4],[2,2,1,9]], needs = [1,2,1]
    Output: 11
    Explanation: The price of A is $2, and $3 for B, $4 for C.
    You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C.
    You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C.
    You cannot add more items, though only $9 for 2A ,2B and 1C.


    *** Constraints ***
    n == price.length == needs.length
    1 <= n <= 6
    0 <= price[i], needs[i] <= 10
    1 <= special.length <= 100
    special[i].length == n + 1
    0 <= special[i][j] <= 50
    The input is generated that at least one of special[i][j] is non-zero for 0 <= j <= n - 1.

*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This one gives a TLE, but it's good to be able to see this aproach as well.

*/

/* Time  Complexity: O(2^N) */
/* Space Complexity: O(N)   */
class Solution_TLE {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
    {
        return shopping(price, special, needs);
    }

private:
    int shopping(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
    {
        int minimum_cost = dot_product(needs, price);

        for (const auto& offer : special)
        {
            vector<int> remaining_needs = needs;
            int j = 0;

            for (j = 0; j < needs.size(); j++)
            {
                int remaining = remaining_needs[j] - offer[j];

                if (remaining < 0)
                    break;

                remaining_needs[j] = remaining;
            }

            if (j == needs.size())
                minimum_cost = min(minimum_cost, offer[j] + shopping(price, special, remaining_needs));
        }

        return minimum_cost;
    }

    int dot_product(const vector<int>& a, const vector<int>& b)
    {
        int sum = 0;

        for (int i = 0; i < a.size(); i++)
            sum += a[i] * b[i];

        return sum;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 60.32% */
/* Space Beats: 64.40% */

/* Time  Complexity: O(m * (max_need)^n) */
/* Space Complexity: O((max_need)^n)     */
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t hash = 0;
        for (int num : v) {
            hash ^= hash * 31 + std::hash<int>{}(num);
        }
        return hash;
    }
};

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs)
    {
        unordered_map<vector<int>, int, VectorHash> memo;
        return shopping(price, special, needs, memo);
    }

private:
    int shopping(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, unordered_map<vector<int>, int, VectorHash>& memo)
    {
        if (memo.count(needs))
            return memo[needs];

        int minimum_cost = dot_product(needs, price);

        for (const auto& offer : special)
        {
            vector<int> remaining_needs = needs;
            int j = 0;

            for (j = 0; j < needs.size(); j++)
            {
                int remaining = remaining_needs[j] - offer[j];
                if (remaining < 0)
                    break;

                remaining_needs[j] = remaining;
            }

            if (j == needs.size())
                minimum_cost = min(minimum_cost, offer[j] + shopping(price, special, remaining_needs, memo));
        }

        memo[needs] = minimum_cost;
        return minimum_cost;
    }

    int dot_product(const vector<int>& a, const vector<int>& b)
    {
        int sum = 0;
        for (int i = 0; i < a.size(); i++)
            sum += a[i] * b[i];

        return sum;
    }
};
