/*
    ============
    === HARD ===
    ============

    =====================================
    3691) Maximum Total Subarray Value II
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and an integer k.

    You must select exactly k distinct nums[l..r] of nums. Subarrays may
    overlap, but the exact same subarray (same l and r) cannot be chosen more
    than once.

    The value of a subarray nums[l..r] is defined as: max(nums[l..r]) -
    min(nums[l..r]).

    The total value is the sum of the values of all chosen subarrays.

    Return the maximum possible total value you can achieve.

    ============================================================
    FUNCTION: long long maxTotalValue(vector<int>& nums, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2], k = 2
    Output: 4
    Explanation:
    One optimal approach is:

        Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
        Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.

    Adding these gives 2 + 2 = 4.


    --- Example 2 ---
    Input: nums = [4,2,5,1], k = 3
    Output: 12
    Explanation:
    One optimal approach is:

        Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
        Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
        Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.

    Adding these gives 4 + 4 + 4 = 12.



    *** Constraints ***
    1 <= n == nums.length <= 5 * 10^4
    0 <= nums[i] <= 109
    1 <= k <= min(105, n * (n + 1) / 2)

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.34% */
/* Space Beats: 22.91% */

/* Time  Complexity: O(N * logN  +  k * logN) */
/* Space Complexity: O(N * logN             ) */
class Solution {
private:
    int LOG_N;
    vector<vector<int>> min_sparse;
    vector<vector<int>> max_sparse;

public:
    long long maxTotalValue(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = 0LL;

        // O(N * logN)
        initialize_sparse_table(nums);

        // O(N) for entire block
        priority_queue<tuple<int,int,int>> max_heap;
        for (int i = 0; i < N; i++)
        {
            max_heap.push( {value_in_range(i, N-1), i, N-1} );
        }

        // O(k * logN) for entire block
        while ( ! max_heap.empty() && k > 0)
        {
            auto [value, L, R] = max_heap.top();
            max_heap.pop();

            result += 1LL * value;

            if (L <= R-1)
                max_heap.push( {value_in_range(L, R-1), L, R-1} );

            // Decrement
            --k;
        }

        return result;
    }

private:
    void initialize_sparse_table(vector<int>& nums)
    {
        const int N = nums.size();
        if (N <= 0)
            return;

        // floor(log2(N)) + 1
        LOG_N = 0;
        while ((1 << LOG_N) <= N)
            ++LOG_N;

        min_sparse = vector<vector<int>>(N, vector<int>(LOG_N));
        max_sparse = vector<vector<int>>(N, vector<int>(LOG_N));

        /* Initialize subarrays of size=1 */
        for (int i = 0; i < N; i++)
        {
            min_sparse[i][0] = nums[i];
            max_sparse[i][0] = nums[i];
        }

        /* Initialize OTHER "power of two" size subarrays */
        for (int power = 1; power < LOG_N; power++)
        {
            for (int i = 0; (i + (1 << power) - 1) < N; i++)
            {
                int half_power = power - 1;

                min_sparse[i][power] = min(min_sparse[i                    ][half_power],
                                           min_sparse[i + (1 << half_power)][half_power]);

                max_sparse[i][power] = max(max_sparse[i                    ][half_power],
                                           max_sparse[i + (1 << half_power)][half_power]);
            }
        }
    }


    int min_rmq_in_range(int L, int R)
    {
        if (R-L+1 == 0)
            return min_sparse[L][0];

        int power = 31 - __builtin_clz(R-L+1);

        return min(min_sparse[L                   ][power],
                   min_sparse[R - (1 << power) + 1][power]);
    }


    int max_rmq_in_range(int L, int R)
    {
        if (R-L+1 == 0)
            return max_sparse[L][0];

        int power = 31 - __builtin_clz(R-L+1);

        return max(max_sparse[L                   ][power],
                   max_sparse[R - (1 << power) + 1][power]);
    }

    int value_in_range(int L, int R)
    {
        int min_val = min_rmq_in_range(L, R);
        int max_val = max_rmq_in_range(L, R);

        return max_val - min_val;
    }
};
