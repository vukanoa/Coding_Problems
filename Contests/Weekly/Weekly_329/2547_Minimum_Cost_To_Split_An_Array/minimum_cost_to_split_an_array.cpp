/*
    ============
    === HARD ===
    ============

    ====================================
    2547) Minimum Cost to Split an Array
    ====================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Split the array into some number of non-empty subarrays. The cost of a
    split is the sum of the importance value of each subarray in the split.

    Let trimmed(subarray) be the version of the subarray where all numbers
    which appear only once are removed.

        For example, trimmed([3,1,2,4,3,4]) = [3,4,3,4].

    The importance value of a subarray is k + trimmed(subarray).length.

        For example, if a subarray is [1,2,3,3,3,4,4], then
        trimmed([1,2,3,3,3,4,4]) = [3,3,3,4,4].The importance value of this
        subarray will be k + 5.

    Return the minimum possible cost of a split of nums.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ================================================
    FUNCTION: int minCost(vector<int>& nums, int k);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,2,1,3,3], k = 2
    Output: 8
    Explanation: We split nums to have two subarrays: [1,2], [1,2,1,3,3].
    The importance value of [1,2] is 2 + (0) = 2.
    The importance value of [1,2,1,3,3] is 2 + (2 + 2) = 6.
    The cost of the split is 2 + 6 = 8. It can be shown that this is the minimum possible cost among all the possible splits.

    --- Example 2 ---
    Input: nums = [1,2,1,2,1], k = 2
    Output: 6
    Explanation: We split nums to have two subarrays: [1,2], [1,2,1].
    The importance value of [1,2] is 2 + (0) = 2.
    The importance value of [1,2,1] is 2 + (2) = 4.
    The cost of the split is 2 + 4 = 6. It can be shown that this is the minimum possible cost among all the possible splits.

    --- Example 3 ---
    Input: nums = [1,2,1,2,1], k = 5
    Output: 10
    Explanation: We split nums to have one subarray: [1,2,1,2,1].
    The importance value of [1,2,1,2,1] is 5 + (3 + 2) = 10.
    The cost of the split is 10. It can be shown that this is the minimum possible cost among all the possible splits.


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] < nums.length
    1 <= k <= 10^9

*/

#include <climits>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODo

*/

/* Time  Beats: 39.24% */
/* Space Beats: 53.80% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N + U) */ // 'U' is the number of UNIQUE values in nums
class Solution_Bottom_Up__Tabulation {
public:
    int minCost(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<int> dp(N+1, INT_MAX);
        dp[N] = 0;
        for (int start = N-1; start >= 0; start--)
        {
            int total = 0;
            int elems_that_appear_once = 0;

            unordered_map<int,int> freq;
            for (int end = start; end < N; end++)
            {
                ++total;
                
                ++freq[nums[end]];
                if (freq[nums[end]] == 1)
                    ++elems_that_appear_once;

                if (freq[nums[end]] == 2)
                    --elems_that_appear_once;

                int trim_len = total - elems_that_appear_once;
                dp[start] = min(dp[start], k + trim_len + dp[end + 1]);
            }
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

/* Time  Beats: 17.09% */
/* Space Beats: 50.63% */

/* Time  Complexity: O(N^2)   */
/* Space Complexity: O(N + U) */ // 'U' is the number of UNIQUE values in nums
class Solution_Top_Down__Memoization {
private:
    static constexpr int MAX_N = 1000;
    int memo[MAX_N];

public:
    int minCost(vector<int>& nums, int k)
    {
        const int N = nums.size();

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* Solve */
        return solve(0, nums, k, N);
    }

private:
    int solve(int start, const vector<int>& nums, int k, const int N)
    {
        if (start == N)
            return 0;

        if (memo[start] != -1)
            return memo[start];

        int result = INT_MAX;

        int total = 0;
        int elems_that_appear_once = 0;

        unordered_map<int,int> freq;
        for (int end = start; end < N; end++)
        {
            ++total;

            ++freq[nums[end]];
            if (freq[nums[end]] == 1)
                ++elems_that_appear_once;

            if (freq[nums[end]] == 2)
                --elems_that_appear_once;

            int trim_len = total - elems_that_appear_once;
            result = min(result, k + trim_len + solve(end + 1, nums, k, N));
        }

        return memo[start] = result;
    }
};
