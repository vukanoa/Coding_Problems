#include <iostream>
#include <vector>

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
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.93% */
/* Space Beats: 83.80% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
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
