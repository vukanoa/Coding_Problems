/*
    ============
    === HARD ===
    ============

    ====================================================
    3892) Minimum Operations to Achieve At Least K Peaks
    ====================================================

    ============
    Description:
    ============

    You are given a circular integer array nums of length n.

    An index i is a peak if its value is strictly greater than its neighbors:

        + The previous neighbor of i is nums[i - 1] if i > 0    , otherwise nums[n - 1].
        + The next     neighbor of i is nums[i + 1] if i < n - 1, otherwise nums[0].

    You are allowed to perform the following operation any number of times:

        + Choose any index i and increase nums[i] by 1.

    Return an integer denoting the minimum number of operations required to
    make the array contain at least k peaks. If it is impossible, return -1.

    ======================================================
    FUNCTION: int minOperations(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,2], k = 1
    Output: 1
    Explanation:
        + To achieve at least k = 1 peak, we can increase nums[2] = 2 to 3.
        + After this operation, nums[2] = 3 is strictly greater than its
          neighbors nums[0] = 2 and nums[1] = 1.

        Therefore, the minimum number of operations required is 1.


    --- Example 2 ---
    Input: nums = [4,5,3,6], k = 2
    Output: 0
    Explanation:
        + The array already contains at least k = 2 peaks with zero operations.
        + Index 1: nums[1] = 5 is strictly greater than its neighbors nums[0] = 4 and nums[2] = 3.
        + Index 3: nums[3] = 6 is strictly greater than its neighbors nums[2] = 3 and nums[0] = 4.

        Therefore, the minimum number of operations required is 0.


    --- Example 3 ---
    Input: nums = [3,7,3], k = 2
    Output: -1
    Explanation:
    It is impossible to have at least k = 2 peaks in this array. Therefore, the
    answer is -1.



    *** Constraints ***
    2 <= n == nums.length <= 5000
    -10^5 <= nums[i] <= 10^5
    0 <= k <= n

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Very similar to "House Robber II", but with additiona k-dimension.

    If you're really comfortable with "House Robber 2" and generally with 2DP
    DP problems, then you should be able to solve htis one.

    It's not that baad considering it's a Q4 problem.

*/

/* Time  Beats: 52.94% */
/* Space Beats: 20.59% */

/* Time  Complexity: O(N * k) */
/* Space Complexity: O(N * k) */
class Solution {
private:
    int N;

public:
    int minOperations(vector<int>& nums, int k)
    {
        N = nums.size();

        if (k == 0)
            return 0;

        if (k > N / 2)
            return -1;

        if (N == 2)
            return nums[0] == nums[1] ? 1 : 0;

        nums.push_back(nums[0]); // To remove the need for weird MOD arithmetic

        vector<int> cost(N);
        for (int i = 0; i < N; i++)
        {
            int left  = (i == 0) ? nums[N-1] : nums[i-1];
            int right = nums[i+1];

            cost[i] = max(0,
                          1 + max(left, right) - nums[i]);
        }

        long long skip_0 = INT_MAX;
        long long take_0 = INT_MAX;

        // Case 1: Skip index 0
        skip_0 = solve(1, N-1, k, cost);

        // Case 2: Take index 0
        if (k >= 1)
            take_0 = cost[0] + solve(2, N-2, k-1, cost);

        nums.pop_back(); // Pop nums[0] that we've appended at the beginning

        int result = min(skip_0, take_0);
        return result == INT_MAX ? -1 : result;
    }

private:
    long long solve(int start, int end, int k, vector<int>& cost)
    {
        // INT_MAX at index [i][j] means that you CANNOT create 'j' peaks
        // starting at index 'i', therefore it's IMPOSSIBLE, i.e. "INT_MAX"
        vector<vector<long long>> dp(N + 2, vector<long long>(k + 1, INT_MAX));

        dp[end + 1][0] = 0;
        dp[end + 2][0] = 0;

        for (int i = end; i >= start; i--)
        {
            for (int j = 0; j <= k; j++)
            {
                // Skip current
                dp[i][j] = min(dp[i    ][j],
                               dp[i + 1][j]);

                // Take current
                if (j > 0 && dp[i + 2][j - 1] != INT_MAX)
                {
                    dp[i][j] = min(dp[i    ][j    ],
                                   dp[i + 2][j - 1] + cost[i]);
                }
            }
        }

        return dp[start][k];
    }
};
