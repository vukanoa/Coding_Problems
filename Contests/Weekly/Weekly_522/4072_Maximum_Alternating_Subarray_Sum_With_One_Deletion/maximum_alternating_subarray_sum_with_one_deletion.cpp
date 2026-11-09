/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    4072) Maximum Alternating Subarray Sum With One Deletion
    ========================================================

    ============
    Description:
    ============


    You are given an integer array nums.

    You may delete at most one element from nums, then choose a subarray of the
    resulting array.

    Return the maximum possible alternating sum of the chosen subarray.

    The alternating sum of an array is the sum of its elements at even indices
    minus the sum of its elements at odd indices. The chosen subarray is
    reindexed starting from 0 before calculating its alternating sum.

    =========================================================
    FUNCTION: long long maxAlternatingSum(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,-5,1]
    Output: 11
    Explanation:
    Choose not to delete an element and select the entire array. Its
    alternating sum is 5 - (-5) + 1 = 11, which is the maximum possible.

    --- Example 2 ---
    Input: nums = [10,-5,-100]
    Output: 110
    Explanation:
    Delete nums[1] = -5 to obtain [10,-100], then select the entire resulting
    array. Its alternating sum is 10 - (-100) = 110, which is the maximum
    possible.

    --- Example 3 ---
    Input: nums = [4,7]
    Output: 7
    Explanation:
    Choose not to delete an element and select the subarray [7]. Its
    alternating sum is 7, which is the maximum possible.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5

*/

#include <climits>
#include <vector>
using namespace std;

/* Time  Beats: 31.45% */
/* Space Beats: 45.88% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    static constexpr int MAX_N = 1e5;
    long long memo[MAX_N+1][2][2];

public:
    long long maxAlternatingSum(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = LLONG_MIN;

        /* Memset */
        fill(&memo[0][0][0], &memo[0][0][0] + sizeof(memo) / sizeof(long long), LLONG_MIN);

        for (int i = 0; i < N; i++)
            result = max(result, 1LL * nums[i] + solve(i+1, 1, 0, nums));

        return result;
    }

private:
    long long solve(int idx, int parity, int used_deletion, vector<int>& nums)
    {
        const int N = nums.size();

        if (idx == N)
            return 0;

        if (memo[idx][parity][used_deletion] != LLONG_MIN)
            return memo[idx][parity][used_deletion];

        long long result = 0LL;

        long long val;
        if (parity == 0)
            val = 1LL * nums[idx];
        else
            val = -1LL * nums[idx];

        int next_parity = 1 - parity;

        long long skip = 0LL;
        long long take = 0LL;

        /* TAKE current element */
        take = val + solve(idx+1, next_parity, used_deletion, nums);

        /* DELETE current element */
        if (used_deletion == 0) // If it's NOT used yet, try deleting this one
            skip = solve(idx+1, parity, 1, nums);

        return memo[idx][parity][used_deletion] = max(take, skip);
    }
};
