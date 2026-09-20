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

    (Sparse Tables are NOT explained here. You need to know that before hand
    since it's not that difficult. THe explanation is mainly due to the
    additional complexity of this problem)

    We are told we CANNOT select the same subarray more than once.

    How can we find the maximum possible total value for k unique subarrays?
                                                         ~~~~~~~~~~~~~~~~~~
                                          ________________________|
                                          |
                0  1  2  3  4  5          v
        nums = [1, 2, 5, 3, 6, 4]         k = 7


    We know that in every array, of size N, there are exactly N^2 subarrays.
    Also, keep in mind what is considered a "value" in this problem.:


        The value of a subarray nums[l..r] is defined as:

            max(nums[l..r]) - min(nums[l..r]).



    So let's "draw" a table with ALL the VALUES(!!) for EACH and every subarray.


                                        RIGHT

                           0     1     2     3     4     5
                        +-----+-----+-----+-----+-----+-----+
                     0  |  0  |  1  |  4  |  4  |  5  |  5  |
                        +-----+-----+-----+-----+-----+-----+
                     1  |     |  0  |  3  |  3  |  3  |  4  |
                        +-----+-----+-----+-----+-----+-----+
                     2  |     |     |  0  |  2  |  3  |  3  |
           LEFT         +-----+-----+-----+-----+-----+-----+
                     3  |     |     |     |  0  |  3  |  3  |
                        +-----+-----+-----+-----+-----+-----+
                     4  |     |     |     |     |  0  |  2  |
                        +-----+-----+-----+-----+-----+-----+
                     5  |     |     |     |     |     |  0  |
                        +-----+-----+-----+-----+-----+-----+



    If you're confused about how to read this table, let's pick a random
    subarray from our nums:

                                0  1  2  3  4  5
                        nums = [1, 2, 5, 3, 6, 4]
                                   ^^^^^^^
                                   L     R

    So our subarray is from L=1, up to and including R=3.
    This subarray has a value of:

        max(L, R) - min(L, R) ==> 5 - 2 = 3

    And in our table above that's at [L][R].



    Now, there's something VERY interesting that you may not notice and it's
    this:

        The VALUES in each ROW, of this table, are sorted in ASCENDING order!


    This is a HUGE thing.
    But why is that the case?
    It's because subarrays values MONOTONICALLY increase as the range expands
    to the right.

    And why is THAT the case?
    Because as we move to the right, i.e. expand our subarray, we can either
    have a:

        + New LARGEST  element
        + New SMALLEST element
        + An element that is already between our SMALLEST and LARGEST

    So in the WORST case every LONGER subarray for each row (i.e. for each
    starting index) will have the SAME value as previous subarray.

    And if it's not the WORST case then the value will INCREASE!
    Either because we've found a new LARGEST element or a new SMALLEST element
    within this new subarray.


    So, how can this help us?
    We don't need to calculate and recompute every value.

    As we've said--The subarray spanning from L to the very end of nums, i.e.
    up to and including index n−1, is GUARANTEED to contain the MAXIMUM VALUE
    for that ROW, so we "reveal" or compute these values using a constant time
    lookup data structure, called "Sparse Table":


                                                     MAX FOR EACH ROW
                                                          |
                                        RIGHT             |
                                                          v
                           0     1     2     3     4     5
                        +-----+-----+-----+-----+-----+-----+
                     0  |  ?  |  ?  |  ?  |  ?  |  ?  |  5  |
                        +-----+-----+-----+-----+-----+-----+
                     1  |     |  ?  |  ?  |  ?  |  ?  |  4  |
                        +-----+-----+-----+-----+-----+-----+
                     2  |     |     |  ?  |  ?  |  ?  |  3  |
           LEFT         +-----+-----+-----+-----+-----+-----+
                     3  |     |     |     |  ?  |  ?  |  3  |
                        +-----+-----+-----+-----+-----+-----+
                     4  |     |     |     |     |  ?  |  2  |
                        +-----+-----+-----+-----+-----+-----+
                     5  |     |     |     |     |     |  0  |
                        +-----+-----+-----+-----+-----+-----+

    The computed values will be inserted into a max_heap to identify the
    LARGEST VALUE that is currently available.

                        +-----+-----+-----+-----+-----+-----+
            max_heap    |  5  |  4  |  3  |  3  |  2  |  0  |
                        +-----+-----+-----+-----+-----+-----+




    We know that the entire array itself containts the first maximum value,
    (which also corresponds the current max value in the max_heap)

    We add this LARGEST VALUE to the out result.
            |
            |                           RIGHT
            |
            |              0     1     2     3     4     5
            |           +-----+-----+-----+-----+-----+-----+
            |        0  |  ?  |  ?  |  ?  |  ?  |  ?  |  5  |
            |           +-----+-----+-----+-----+-----+-----+
       _____|        1  |     |  ?  |  ?  |  ?  |  ?  |  4  |
       |                +-----+-----+-----+-----+-----+-----+
       |             2  |     |     |  ?  |  ?  |  ?  |  3  |
       |   LEFT         +-----+-----+-----+-----+-----+-----+
       |             3  |     |     |     |  ?  |  ?  |  3  |
       |                +-----+-----+-----+-----+-----+-----+
       |             4  |     |     |     |     |  ?  |  2  |
       |                +-----+-----+-----+-----+-----+-----+
       |             5  |     |     |     |     |     |  0  |
       |                +-----+-----+-----+-----+-----+-----+
       |
       |                +-----+-----+-----+-----+-----+-----+
       |    max_heap    |  5  |  4  |  3  |  3  |  2  |  0  |
       |                +-----+-----+-----+-----+-----+-----+
       |                   ^
       |___________________|


    and after selecting it, we "reveal" the next_candidate.
    How do we do that "reveal" exactly?

    We know that the next largest for that ROW (i.e. starting index) is from a
    subarray with size ONE LESS than the previous one.

    If the previous one was [0, N-1], the next_candidate value comes from the
    subarray [0, N-2].


    Or in genera--If the previous one was [L, R], then next comes from [L, R-1]

    We'll always have N elents in our Heap and we'll keep taking the top one
    each time.

    We'll take at most k such values. And each time we take a value we will
    "reveal" the next_candiate as explained above.


    At the end we simply return the total value that is stored in "result".

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
