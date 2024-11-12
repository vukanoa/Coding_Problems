#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    2070) Most Beautiful Item for Each Query
    ========================================

    ============
    Description:
    ============

    You are given a 2D integer array items where items[i] = [pricei, beautyi]
    denotes the price and beauty of an item respectively.

    You are also given a 0-indexed integer array queries. For each queries[j],
    you want to determine the maximum beauty of an item whose price is less
    than or equal to queries[j]. If no such item exists, then the answer to
    this query is 0.

    Return an array answer of the same length as queries where answer[j] is the
    answer to the jth query.

    ======================================================================================
    FUNCTION: vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
    Output: [2,4,5,5,6,6]
    Explanation:
    - For queries[0]=1, [1,2] is the only item which has price <= 1. Hence, the
      answer for this query is 2.

    - For queries[1]=2, the items which can be considered are [1,2] and [2,4].
      The maximum beauty among them is 4.

    - For queries[2]=3 and queries[3]=4, the items which can be considered are
      [1,2], [3,2], [2,4], and [3,5].
      The maximum beauty among them is 5.

    - For queries[4]=5 and queries[5]=6, all items can be considered.
      Hence, the answer for them is the maximum beauty of all items, i.e., 6.


    --- Example 2 ---
    Input: items = [[1,2],[1,2],[1,3],[1,4]], queries = [1]
    Output: [4]
    Explanation:
    The price of every item is equal to 1, so we choose the item with the
    maximum beauty 4. Note that multiple items can have the same price and/or
    beauty.


    --- Example 3 ---
    Input: items = [[10,1000]], queries = [5]
    Output: [0]
    Explanation:
    No item has a price less than or equal to 5, so no item can be chosen.
    Hence, the answer to the query is 0.


    *** Constraints ***
    1 <= items.length, queries.length <= 10^5
    items[i].length == 2
    1 <= pricei, beautyi, queries[j] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since "lower_bound" returns the first item that is EQUAL or GREATER than
    the specified "target", that wouldn't work here even if we had our "items"
    sorted by the "prices"(first value).

    However if we had them sorted in reversed order by the first value and in
    ASCENDING order and by the second value in DESCENDING order, then we could
    indeed find the first item that is greater than or equals to the "target".

    However, that would be too "weird" to have a reversed sort in ASCENDING by
    the first value and then in DESCENDING by the second value, it's much
    easier to copy the entire 2D vector and negate the first value in each
    "pair" and THEN we perform a clasic sort by first value.

    (You'll see why we do NOT care about any particular order of the second
     value)

    But this is not enough.
    Consider this example:

        items = [[1,2],[3,2],[2,8],[5,6],[4,7],[3,5]]
        queries = [5]

    Let's say we've negated each first value:

        negative_items = [[-1,2],[-3,2],[-2,8],[-5,6],[-4,7],[-3,5]],
        queries = [5]

    Now if we sort it by first value in ASCENDING order(classical sort):

        negative_items = [[-5,6],[-4,7],[-3,2],[-3,5],[-2,8],[-1,2]],

    As you can see [-3,2] comes(or could come BEFORE or AFTER) before [-3,5].
    And since we're going to use a "lower_bound" function from "std", it seems
    as if we should've had this 2D vector sorted, also, by 2nd value in
    DESCENDING because if we had a target=3, then we could get [-3,2] but we
    can see that [-3,5] is greater.

    But that will NOT be a problem whatsoever since we're going to use a "dp"
    vector to store the biggest "beauty" value from this point(inclusive) until
    the end(meaning "same and lower prices").

    That way once we get to [-3,2] or [-3,5] we WON'T care since we're ONLY
    interested in the "price". We only care about the first value. That could
    be, if target is 3: 3, 2 or 1.

    But we don't care what beauty is next to that prices, we only care about
    "what is the biggest beauty value for this prices and less".

    In this case it would actually be 8, from [-2,8].

    It'll be much more clear after you look at this:
        negative_items = [[-5,6],[-4,7],[-3,2],[-3,5],[-2,8],[-1,2]],
                    dp = [   8  ,   8  ,   8  ,   8  ,   8  ,  2   ]

    After we've constructed this helper, the problem becomes trivial. All we
    have to do now is get "lower_bound" item and if it's not
    negative_items.end(), then take the index of that element and check the
    "biggest beautyf value" from the vector "dp" and place that at answer[i],
    since we're dealing with queries[i] at this moment.

    Vector "answer" is initialized with all 0s and of the same size as
    "queries", therefore if we aren't able to find any element using the
    "lower_bound" function, then just skip changing the 0 for that element. In
    that case 0 is the right answer.

*/

/* Time  Beats: 9.02% */
/* Space Beats: 9.46% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries)
    {
        const int n = items.size();

        vector<vector<int>> negative_items = items;

        for (vector<int>& pair : negative_items)
            pair[0] *= -1;

        /* Sort by first value : O(n * logn) */
        std::sort(negative_items.begin(), negative_items.end());

        vector<int> dp(negative_items.size(), 0);
        dp[n-1] = negative_items[n-1][1]; // last beauty value

        for (int i = n-2; i >= 0; i--)
            dp[i] = max(dp[i+1], negative_items[i][1]);


        vector<int> answer(queries.size(), 0);
        for (int i = 0; i < queries.size(); i++)
        {
            int query = -queries[i]; // Convert the query to negative for comparison

            auto it = std::lower_bound(negative_items.begin(), negative_items.end(), std::vector<int>{query, 0},
                [](const std::vector<int>& item, const std::vector<int>& target)
                  {
                      return item[0] < target[0];
                  });

            if (it != negative_items.end())
            {
                int index = it - negative_items.begin();
                answer[i] = dp[index];
            }
        }

        return answer;
    }
};
