#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // For memset

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    646) Maximum Length of Pair Chain
    =================================

    ============
    Description:
    ============

    You are given an array of n pairs pairs where pairs[i] = [lefti, righti]
    and lefti < righti.

    A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs
    can be formed in this fashion.

    Return the length longest chain which can be formed.

    You do not need to use up all the given intervals. You can select pairs in
    any order.

    ===========================================================
    FUNCTION: int findLongestChain(vector<vector<int>>& pairs);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: pairs = [[1,2],[2,3],[3,4]]
    Output: 2
    Explanation: The longest chain is [1,2] -> [3,4].

    --- Example 2 ---
    Input: pairs = [[1,2],[7,8],[4,5]]
    Output: 3
    Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].

    *** Constraints ***
    n == pairs.length
    1 <= n <= 1000
    -1000 <= lefti < righti <= 1000

*/


/*
    Down below are 3 Solutions:
        1) Time Complexity: O(n^2)
        2) Time Complexity: O(n * logn)
        3) Time Complexity: O(n)

*/


/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_1 {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs)
    {
        const int n = pairs.size();

        std::vector<int> dp(n, 1);
        int longest_chain = 1;

        // Sort
        sort(pairs.begin(), pairs.end());

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (pairs[i][0] > pairs[j][1] && 1 + dp[j] > dp[i])
                    dp[i] = 1 + dp[j];
            }

            if (dp[i] >= longest_chain)
                longest_chain = dp[i];
        }

        return longest_chain;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.09% */
/* Space Beats: 28.99% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_2 {
public:
    int findLongestChain(vector<vector<int>>& pairs)
    {
        const int n = pairs.size();
        sort(pairs.begin(), pairs.end());

        vector<int> dp(n, 1);

        for (int i = n-2; i >= 0; i--)
        {
            int target = 1 + pairs[i][1];
            auto it = lower_bound(pairs.begin(), pairs.end(), vector<int>{target, INT_MIN},
                [](const vector<int>& a, const vector<int>& b) {
                    return a[0] < b[0];
                });


            if (it != pairs.end())
                dp[i] = max(dp[it - pairs.begin()] + 1, dp[i+1]);
            else
                dp[i] = max(1, dp[i+1]);

        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.61% */
/* Space Beats: 30.90% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */
class Solution_2_Second_Way {
public:
    int findLongestChain(vector<vector<int>>& pairs)
    {
        // Sort by "end" value
        sort(pairs.begin(), pairs.end(), [](vector<int>& a, vector<int>& b){
            return a[1] < b[1];
        });

        int result = 1;

        vector<int>dp_prev = pairs[0];
        for (const auto vec : pairs)
        {
            if (dp_prev[1] < vec[0])
            {
                result++;
                dp_prev = vec;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.93% */
/* Space Beats: 83.80% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int dp[2002];
    int end_to_min_len[2002];

    int findLongestChain(vector<vector<int>>& pairs)
    {
        memset(dp, 0, sizeof(dp));
        memset(end_to_min_len, 0, sizeof(end_to_min_len));

        int pair_max = -1001;
        int pair_min = 1001;
        for (const auto& p : pairs)
        {
            end_to_min_len[p[1] + 1000] = end_to_min_len[p[1] + 1000] == 0 ? p[1] - p[0] :
            min(end_to_min_len[p[1] + 1000], p[1] - p[0]);

            pair_min = min(p[0], pair_min);
            pair_max = max(p[1], pair_max);
        }

        for (int i = pair_min; i <= pair_max; i++)
        {
            dp[i+1001] = dp[i+1000];

            if (end_to_min_len[i + 1000])
                dp[i + 1001] = max(dp[i + 1001], dp[i + 1000-end_to_min_len[i + 1000]] + 1);
        }

        return dp[pair_max + 1001];
    }
};
