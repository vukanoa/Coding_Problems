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

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 6.33% */
/* Space Beats: 5.27% */

/* Time  Complexity: O(N * logN  +  Q) */
/* Space Complexity: O(N * logN)       */
class Solution {
private:
    vector<vector<int>> sparse_table;
    int LOG_N;

public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries)
    {
        const int N = items.size();
        const int Q = queries.size();

        vector<int> answer(Q, 0);

        /* Sort in ASCENDING order */
        sort(items.begin(), items.end());

        // floor(log2(N)) + 1
        LOG_N = 0;
        while ((1 << LOG_N) <= N)
            ++LOG_N;

        sparse_table = vector<vector<int>>(N, vector<int>(LOG_N));
        initialize_sparse_table(items);

        for (int j = 0; j < Q; j++)
        {

            int R = upper_bound(items.begin(), items.end(), queries[j], [](int value, const vector<int>& item) {
                return value < item[0];
            }) - items.begin();

            --R; // Move to the LAST item with queries[j]

            if (R >= 0)
                answer[j] = RMQ_on_range(0, R);
        }

        return answer;
    }

private:
    void initialize_sparse_table(vector<vector<int>>& items)
    {
        const int N = items.size();

        /* Max beauty of size=1 (i.e. size=2^0) subarrays */
        for (int i = 0; i < N; i++)
        {
            sparse_table[i][0] = items[i][1]; // [0] --> price, [1] --> beauty
        }

        for (int power = 1; power < LOG_N; power++)
        {
            for (int i = 0; (i + (1 << power) - 1) < N; i++)
            {
                int half_power = power - 1;

                sparse_table[i][power] = max(sparse_table[i                    ][half_power],
                                             sparse_table[i + (1 << half_power)][half_power]);
            }
        }
    }

    int RMQ_on_range(int L, int R)
    {
        if (R-L+1 == 0) // Because "__builtin_clz(0)" gives Undefined Behavior
            return sparse_table[L][0];

        int power = 31 - __builtin_clz(R - L + 1);

        return max(sparse_table[L                   ][power],
                   sparse_table[R - (1 << power) + 1][power]);
    }
};
