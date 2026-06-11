/*
    ============
    === HARD ===
    ============

    ==============================
    1681) Minimum Incompatibillity
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k. You are asked to
    distribute this array into k subsets of equal size such that there are no
    two equal elements in the same subset.

    A subset's incompatibility is the difference between the maximum and
    minimum elements in that array.

    Return the minimum possible sum of incompatibilities of the k subsets after
    distributing the array optimally, or return -1 if it is not possible.

    A subset is a group integers that appear in the array with no particular
    order.

    ===============================================================
    FUNCTION: int minimumIncompatibility(vector<int>& nums, int k);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,4], k = 2
    Output: 4
    Explanation: The optimal distribution of subsets is [1,2] and [1,4].
    The incompatibility is (2-1) + (4-1) = 4.
    Note that [1,1] and [2,4] would result in a smaller sum, but the first
    subset contains 2 equal elements.

    --- Example 2 ---
    Input: nums = [6,3,8,1,3,1,2,2], k = 4
    Output: 6
    Explanation: The optimal distribution of subsets is [1,2], [2,3], [6,8],
    and [1,3]. The incompatibility is (2-1) + (3-2) + (8-6) + (3-1) = 6.

    --- Example 3 ---
    Input: nums = [5,3,3,6,3,3], k = 3
    Output: -1
    Explanation: It is impossible to distribute nums into 3 subsets where no
    two elements are equal in the same subset.


    *** Constraints ***
    1 <= k <= nums.length <= 16
    nums.length is divisible by k
    1 <= nums[i] <= nums.length

*/

#include <climits>
#include <set>
#include <vector>
using namespace std;

class Solution {
private:
    static const int MAXN = 16;
    static const int TOTAL_MASKS = 1 << MAXN;

    int subset_incompatibillity[TOTAL_MASKS];

public:
    int minimumIncompatibility(vector<int>& nums, int k)
    {
        const int N = nums.size();
        const int FULL_MASK = (1 << N) - 1;

        const int INF = INT_MAX / 2;

        for (int mask = 0; mask < (1 << N); mask++)
        {
            subset_incompatibillity[mask] = -1;
        }

        for (int mask = 0; mask < (1 << N); mask++)
        {
            set<int> subsets;
            bool ok = true;

            for (int i = 0; i < N; i++)
            {
                if (mask & (1 << i))
                {
                    if (subsets.count(nums[i]))
                    {
                        ok = false;
                        break;
                    }

                    subsets.insert(nums[i]);
                }
            }

            if (ok && subsets.size() == N / k)
            {
                auto it1 = subsets.begin();
                auto it2 = subsets.end();
                --it2;

                subset_incompatibillity[mask] = *it2 - *it1;
            }
        }

        vector<int> dp(1 << N, INF);
        dp[0] = 0;

        for (int mask = 0; mask <= FULL_MASK; mask++)
        {
            if (dp[mask] == INF)
                continue;

            for (int sub = 0; sub <= FULL_MASK; sub++)
            {
                if (subset_incompatibillity[sub] == -1)
                    continue;

                if (mask & sub)
                    continue;

                int new_mask = mask | sub;
                dp[new_mask] = min(dp[new_mask], dp[mask] + subset_incompatibillity[sub]);
            }
        }

        return (dp[FULL_MASK] == INF ? -1 : dp[FULL_MASK]);
    }
};
