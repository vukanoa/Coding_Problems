/*
    ============
    === HARD ===
    ============

    =============================================
    3117) Minimum Sum of Values by Dividing Array
    =============================================

    ============
    Description:
    ============

    You are given two arrays nums and andValues of length n and m respectively.

    The value of an array is equal to the last element of that array.

    You have to divide nums into m disjoint contiguous such that for the ith
    subarray [li, ri], the bitwise AND of the subarray elements is equal to
    andValues[i], in other words, nums[li] & nums[li + 1] & ... & nums[ri] ==
    andValues[i] for all 1 <= i <= m, where & represents the bitwise AND
    operator.

    Return the minimum possible sum of the values of the m subarrays nums is
    divided into. If it is not possible to divide nums into m subarrays
    satisfying these conditions, return -1.

    =========================================================================
    FUNCTION: int minimumValueSum(vector<int>& nums, vector<int>& andValues);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,3,3,2], andValues = [0,3,3,2]
    Output: 12
    Explanation:
    The only possible way to divide nums is:
        [1,4] as 1 & 4 == 0.
        [3] as the bitwise AND of a single element subarray is that element itself.
        [3] as the bitwise AND of a single element subarray is that element itself.
        [2] as the bitwise AND of a single element subarray is that element itself.
    The sum of the values for these subarrays is 4 + 3 + 3 + 2 = 12.

    --- Example 2 ---
    Input: nums = [2,3,5,7,7,7,5], andValues = [0,7,5]
    Output: 17
    Explanation:
    There are three ways to divide nums:
        [[2,3,5],[7,7,7],[5]] with the sum of the values 5 + 7 + 5 == 17.
        [[2,3,5,7],[7,7],[5]] with the sum of the values 7 + 7 + 5 == 19.
        [[2,3,5,7,7],[7],[5]] with the sum of the values 7 + 7 + 5 == 19.
    The minimum possible sum of the values is 17.

    --- Example 3 ---
    Input: nums = [1,2,3,4], andValues = [2]
    Output: -1
    Explanation:
    The bitwise AND of the entire array nums is 0. As there is no possible way
    to divide nums into a single subarray to have the bitwise AND of elements
    2, return -1.


    *** Constraints ***
    1 <= n == nums.length <= 10^4
    1 <= m == andValues.length <= min(n, 10)
    1 <= nums[i] < 10^5
    0 <= andValues[j] < 10^5

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You need to be very good with a few technqiues all at once.

    That's why its COMPLICATED--It consists of MANY parts.

*/

/* Time  Beats:  5.22% */
/* Space Beats: 98.51% */

/* Time  Complexity: O(M * N * logN * B) */
/* Space Complexity: O(M * N  +  N * B)  */
class Solution_Top_Down__Memoization {
private:
    static constexpr int MAX_BITS = 20;

    int memo[10][10000];
    int prefix_sum[10001][MAX_BITS];

public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues)
    {
        const int N = nums.size();

        /* Memset */
        memset(prefix_sum, 0, sizeof(prefix_sum));

        for (int idx = 1; idx <= N; idx++)
        {
            for (int bit = 0; bit < MAX_BITS; bit++)
            {
                if (nums[idx - 1] & (1 << bit))
                    prefix_sum[idx][bit]++;
            }

            for (int bit = 0; bit < MAX_BITS; bit++)
                prefix_sum[idx][bit] += prefix_sum[idx - 1][bit];
        }

        /* Memset */
        memset(memo, -1, sizeof(memo));

        int minimum_sum = solve(0, 0, nums, andValues);

        return minimum_sum == INT_MAX ? -1 : minimum_sum;
    }

private:
    int get_range_and(int left, int right)
    {
        int current_and = 0;

        for (int bit = 0; bit < MAX_BITS; bit++)
        {
            if (prefix_sum[right][bit] - prefix_sum[left][bit] == right - left)
                current_and |= (1 << bit);
        }

        return current_and;
    }

    int solve(int idx, int and_idx, vector<int>& nums, vector<int>& andValues)
    {
        const int N = nums.size();
        const int M = andValues.size();

        if (idx == N)
            return and_idx == M ? 0 : INT_MAX;

        if (and_idx == M)
        {
            if ((nums[idx] & andValues[and_idx - 1]) == andValues[and_idx - 1])
            {
                int next_sum = solve(idx + 1, and_idx, nums, andValues);

                if (next_sum != INT_MAX)
                    return next_sum - nums[idx - 1] + nums[idx];
            }

            return INT_MAX;
        }

        if (memo[and_idx][idx] != -1)
            return memo[and_idx][idx];

        int minimum_sum = INT_MAX;

        // Continue Current Segment
        if (and_idx > 0 && (andValues[and_idx - 1] & nums[idx]) == andValues[and_idx - 1])
        {
            int next_sum = solve(idx + 1, and_idx, nums, andValues);

            if (next_sum != INT_MAX)
            {
                minimum_sum = min(minimum_sum, next_sum
                                               + nums[idx]
                                               - nums[idx - 1]);
            }
        }

        // Start New Segment using Binary Search
        int low  = idx + 1;
        int high = N;
        int segment_end = N + 1;

        while (low < high)
        {
            int middle = low + (high - low) / 2;

            int current_and = get_range_and(idx, middle);

            if (current_and <= andValues[and_idx])
                high = middle;
            else
                low = middle + 1;
        }

        if (low <= N && get_range_and(idx, low) == andValues[and_idx])
            segment_end = low;

        if (segment_end < N + 1)
        {
            int next_sum = solve(segment_end, and_idx + 1, nums, andValues);

            if (next_sum != INT_MAX)
                minimum_sum = min(minimum_sum, next_sum + nums[segment_end - 1]);
        }

        return memo[and_idx][idx] = minimum_sum;
    }
};
