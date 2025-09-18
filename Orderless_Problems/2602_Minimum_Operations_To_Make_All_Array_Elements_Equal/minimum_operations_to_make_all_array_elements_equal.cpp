/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2602) Minimum Operations to Make All Array Elements Equal
    =========================================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    You are also given an integer array queries of size m. For the ith query,
    you want to make all of the elements of nums equal to queries[i].
    You can perform the following operation on the array any number of times:

        + Increase or decrease an element of the array by 1.

    Return an array answer of size m where answer[i] is the minimum number of
    operations to make all elements of nums equal to queries[i].

    Note that after each query the array is reset to its original state.

    ===================================================================================
    FUNCTION: vector<long long> minOperations(vector<int>& nums, vector<int>& queries);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,6,8], queries = [1,5]
    Output: [14,10]
    Explanation: For the first query we can do the following operations:
    - Decrease nums[0] 2 times, so that nums = [1,1,6,8].
    - Decrease nums[2] 5 times, so that nums = [1,1,1,8].
    - Decrease nums[3] 7 times, so that nums = [1,1,1,1].
    So the total number of operations for the first query is 2 + 5 + 7 = 14.
    For the second query we can do the following operations:
    - Increase nums[0] 2 times, so that nums = [5,1,6,8].
    - Increase nums[1] 4 times, so that nums = [5,5,6,8].
    - Decrease nums[2] 1 time, so that nums = [5,5,5,8].
    - Decrease nums[3] 3 times, so that nums = [5,5,5,5].
    So the total number of operations for the second query is 2 + 4 + 1 + 3 = 10.

    --- Example 2 ---
    Input: nums = [2,9,6,3], queries = [10]
    Output: [20]
    Explanation: We can increase each value in the array to 10. The total
    number of operations will be 8 + 1 + 4 + 7 = 20.


    *** Constraints ***
    n == nums.length
    m == queries.length
    1 <= n, m <= 10^5
    1 <= nums[i], queries[i] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.37% */
/* Space Beats: 17.09% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();
        vector<long long> answer(M, 0LL);

        /* Sort */
        sort(nums.begin(), nums.end());

        vector<long long> prefix_sum = {nums[0]};
        for (int i = 1; i < N; i++)
            prefix_sum.push_back(prefix_sum.back() + nums[i]);

        for (int q = 0; q < M; q++)
        {
            long long target = 1LL * queries[q];

            auto first_large_than_target = upper_bound(nums.begin(), nums.end(), target);
            int idx = distance(nums.begin(), first_large_than_target);

            int L = 0LL;
            int R = 0LL;

            // Left side where elements are LESS THAN OR EQUAL TO k
            if (idx > 0)
            {
                long long sum = idx * target;
                answer[q] = sum - prefix_sum[idx - 1];
            }

            // Right side where elements are STRICTLY GREATER THAN k
            long long sum = (N - idx) * target;
            answer[q] += abs(sum - (prefix_sum[N-1] - (idx > 0 ? prefix_sum[idx - 1] : 0)));
        }

        return answer;
    }
};
