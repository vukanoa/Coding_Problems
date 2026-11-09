/*
    ============
    === HARD ===
    ============

    =====================================================================
    3915) Maximum Sum of Alternating Subsequence With Distance at Least K
    =====================================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and an integer k.

    Pick a subsequence with indices 0 <= i1 < i2 < ... < im < n such that:

        For every 1 <= t < m, it+1 - it >= k.
        The selected values form a strictly alternating sequence. In other
        words, either:

            + nums[i1] < nums[i2] > nums[i3] < ..., or
            + nums[i1] > nums[i2] < nums[i3] > ...

    A subsequence of length 1 is also considered strictly alternating. The
    score of a valid subsequence is the sum of its selected values.

    Return an integer denoting the maximum possible score of a valid
    subsequence.

    ================================================================
    FUNCTION: long long maxAlternatingSum(vector<int>& nums, int k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,4,2], k = 2
    Output: 7
    Explanation:
    An optimal choice is indices [0, 2], which gives values [5, 2].
        The distance condition holds because 2 - 0 = 2 >= k.
        The values are strictly alternating because 5 > 2.
    The score is 5 + 2 = 7.


    --- Example 2 ---
    Input: nums = [3,5,4,2,4], k = 1
    Output: 14
    Explanation:
    An optimal choice is indices [0, 1, 3, 4], which gives values [3, 5, 2, 4].
        + The distance condition holds because each pair of consecutive chosen
          indices differs by at least k = 1.

        + The values are strictly alternating since 3 < 5 > 2 < 4.
    The score is 3 + 5 + 2 + 4 = 14.


    --- Example 3 ---
    Input: nums = [5], k = 1
    Output: 5
    Explanation:
    The only valid subsequence is [5]. A subsequence with 1 element is always
    strictly alternating, so the score is 5.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= k <= n

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.45% */
/* Space Beats: 27.78% */

/* Time  Complexity: O(N * log(MAX)) */
/* Space Complexity: O(N + MAX     ) */
class Solution {
public:
    class BIT {
    private:
        vector<long long> fenwick;
        int n;

    public:
        BIT(int n) : n(n), fenwick(n+1, 0) {}

        void update(int idx, long long val)
        {
            for (int i = idx; i <= n; i += i & -i)
                fenwick[i] = max(fenwick[i], val);
        }

        long long query(int i)
        {
            long long maximum = 0;

            while (i > 0)
            {
                maximum = max(maximum, fenwick[i]);

                i -= i & -i;
            }

            return maximum;
        }
    };

    long long maxAlternatingSum(vector<int>& nums, int k)
    {
        const int N = nums.size();
        const int MAX = 1e5 + 5;

        vector<vector<long long>> dp(N, vector<long long>(2, 0LL));

        dp[0][0] = dp[0][1] = nums[0];

        BIT greater(MAX);
        BIT smaller(MAX);

        long long result = nums[0];

        for (int i = 1; i < N; i++)
        {
            dp[i][0] = dp[i][1] = nums[i];

            if (i-k >= 0)
            {
                greater.update(MAX - nums[i-k] + 1, dp[i-k][0]);
                smaller.update(nums[i-k]          , dp[i-k][1]);
            }

            dp[i][0] = max(dp[i][0], nums[i] + smaller.query(nums[i] - 1));
            dp[i][1] = max(dp[i][1], nums[i] + greater.query(MAX - nums[i]));

            result = max( {result, dp[i][0],   // ending at GREATER
                                   dp[i][1]}); // ending at SMALLER
        }

        return result;
    }
};
