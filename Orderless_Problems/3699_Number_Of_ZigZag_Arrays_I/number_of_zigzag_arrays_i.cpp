/*
    ============
    === HARD ===
    ============

    ===============================
    3699) Number of ZigZag Arrays I
    ===============================

    ============
    Description:
    ============

    You are given three integers n, l, and r.

    A ZigZag array of length n is defined as follows:

        + Each element lies in the range [l, r].

        + No two adjacent elements are equal.

        + No three consecutive elements form a strictly increasing or strictly
          decreasing sequence.

    Return the total number of valid ZigZag arrays.

    Since the answer may be large, return it modulo 10^9 + 7.

    A sequence is said to be strictly increasing if each element is strictly
    greater than its previous one (if exists).

    A sequence is said to be strictly decreasing if each element is strictly
    smaller than its previous one (if exists).

    ================================================
    FUNCTION: int zigZagArrays(int n, int l, int r);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, l = 4, r = 5
    Output: 2
    Explanation: There are only 2 valid ZigZag arrays of length n = 3 using
                 values in the range [4, 5]:
                 [4, 5, 4] [5, 4, 5]


    --- Example 2 ---
    Input: n = 3, l = 1, r = 3
    Output: 10
    Explanation:
    There are 10 valid ZigZag arrays of length n = 3 using values in the range
    [1, 3]:
        [1, 2, 1], [1, 3, 1], [1, 3, 2]
        [2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
        [3, 1, 2], [3, 1, 3], [3, 2, 3]
    All arrays meet the ZigZag conditions.


    *** Constraints ***
    3 <= n <= 2000
    1 <= l < r <= 2000

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
/* Space Beats: 100.00% */

/* Time  Complexity: O(n * (r - l)) */
/* Space Complexity: O(r - l)       */
class Solution {
public:
    int zigZagArrays(int n, int l, int r)
    {
        const int MOD = 1e9 + 7;

        int effective_range = r - l;
        vector<int> dp(effective_range + 1, 1);

        for (int curr_idx = 1; curr_idx < n; curr_idx++)
        {
            int rolling_sum_previous = 0;
            int updated_value;

            if (curr_idx & 1) // curr_idx is odd
            {
                for (int current_value = 0; current_value <= effective_range; current_value++)
                {
                    updated_value = rolling_sum_previous + dp[current_value];
                    dp[current_value] = rolling_sum_previous;
                    rolling_sum_previous = updated_value % MOD;
                }
            }
            else // curr_idx is even
            {
                for (int num = effective_range; num >= 0; num--)
                {
                    updated_value = rolling_sum_previous + dp[num];
                    dp[num] = rolling_sum_previous;
                    rolling_sum_previous = updated_value % MOD;
                }
            }
        }

        int final_result_sum = 0;
        for (const int& current_value : dp)
            final_result_sum = (final_result_sum + current_value) % MOD;

        return (2 * final_result_sum) % MOD;
    }
};
