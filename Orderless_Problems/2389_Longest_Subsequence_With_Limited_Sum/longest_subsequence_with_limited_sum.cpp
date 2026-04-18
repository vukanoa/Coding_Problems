/*
    ============
    === EASY ===
    ============

    ==========================================
    2389) Longest Subsequence with Limited Sum
    ==========================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, and an integer array
    queries of length m.

    Return an array answer of length m where answer[i] is the maximum size of a
    subsequence that you can take from nums such that the sum of its elements
    is less than or equal to queries[i].

    A subsequence is an array that can be derived from another array by
    deleting some or no elements without changing the order of the remaining
    elements.

    =============================================================================
    FUNCTION: vector<int> answerQueries(vector<int>& nums, vector<int>& queries);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,5,2,1], queries = [3,10,21]
    Output: [2,3,4]
    Explanation: We answer the queries as follows:
    - The subsequence [2,1] has a sum less than or equal to 3. It can be proven
      that 2 is the maximum size of such a subsequence, so answer[0] = 2.

    - The subsequence [4,5,1] has a sum less than or equal to 10. It can be
      proven that 3 is the maximum size of such a subsequence, so answer[1] =
      3.

    - The subsequence [4,5,2,1] has a sum less than or equal to 21. It can be
      proven that 4 is the maximum size of such a subsequence, so answer[2] = 4


    --- Example 2 ---
    Input: nums = [2,3,4,5], queries = [1]
    Output: [0]
    Explanation: The empty subsequence is the only subsequence that has a sum
                 less than or equal to 1, so answer[0] = 0.


    *** Constraints ***
    n == nums.length
    m == queries.length
    1 <= n, m <= 1000
    1 <= nums[i], queries[i] <= 10^6

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

/* Time  Beats: 50.71% */
/* Space Beats: 31.96% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries)
    {
        const int N = nums.size();
        const int Q = queries.size();

        /* Sort */
        sort(nums.begin(), nums.end());

        vector<int> prefix_sum = {nums[0]};

        /* Partial Sum */
        for (int i = 1; i < N; i++)
            prefix_sum.push_back(prefix_sum.back() + nums[i]);

        vector<int> answer(Q, 0);
        for (int i = 0; i < Q; i++)
            answer[i] = my_upper_bound(0, N, queries[i], prefix_sum);

        return answer;
    }

private:
    int my_lower_bound(int low, int high, int target, vector<int>& prefix_sum)
    {
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left(low)-leaning

            if (target <= prefix_sum[mid])
                high = mid;
            else
                low = mid+1;
        }

        return low; // Or "high"
    }

    int my_upper_bound(int low, int high, int target, vector<int>& prefix_sum)
    {
        return my_lower_bound(low, high, target+1, prefix_sum);
    }
};
