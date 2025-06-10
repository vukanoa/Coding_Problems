/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3578) Count Partitions With Max-Min Difference at Most K
    ========================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k. Your task is to
    partition nums into one or more non-empty contiguous segments such that in
    each segment, the difference between its maximum and minimum elements is at
    most k.

    Return the total number of ways to partition nums under this condition.

    Since the answer may be too large, return it modulo 109 + 7.

    ========================================================
    FUNCTION: int countPartitions(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [9,4,1,3,7], k = 4
    Output: 6
    Explanation:
    There are 6 valid partitions where the difference between the maximum and
    minimum elements in each segment is at most k = 4:
        [[9], [4], [1], [3], [7]]
        [[9], [4], [1], [3, 7]]
        [[9], [4], [1, 3], [7]]
        [[9], [4, 1], [3], [7]]
        [[9], [4, 1], [3, 7]]
        [[9], [4, 1, 3], [7]]


    --- Example 2 ---
    Input: nums = [3,3,4], k = 0
    Output: 2
    Explanation:
    There are 2 valid partitions that satisfy the given conditions:
        [[3], [3], [4]]
        [[3, 3], [4]]


    --- Example 3 ---
    *** Constraints ***
    2 <= nums.length <= 5 * 10^4
    1 <= nums[i] <= 10^9
    0 <= k <= 10^9

*/

#include <deque>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.40% */
/* Space Beats: 94.88% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countPartitions(vector<int>& nums, int k)
    {
        const int N   = nums.size();
        const int MOD = 1e9 + 7;

        int sum_of_ways = 1;

        vector<int> dp(N + 1, 0);
        dp[0] = 1;

        deque<int> minq;
        deque<int> maxq;
        int L = 0;
        for (int R = 0; R < N; R++)
        {
            while ( ! maxq.empty() && nums[R] > nums[maxq.back()])
                maxq.pop_back();
            maxq.push_back(R);

            while ( ! minq.empty() && nums[R] < nums[minq.back()])
                minq.pop_back();
            minq.push_back(R);

            while (nums[maxq.front()] - nums[minq.front()] > k)
            {
                sum_of_ways = (sum_of_ways - dp[L++] + MOD) % MOD;

                if (minq.front() < L)
                    minq.pop_front();

                if (maxq.front() < L)
                    maxq.pop_front();
            }

            dp[R + 1] = sum_of_ways;
            sum_of_ways = (sum_of_ways + dp[R + 1]) % MOD;
        }

        return dp[N];
    }
};
