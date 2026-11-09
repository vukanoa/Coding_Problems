/*
    ============
    === HARD ===
    ============

    =============================================================
    3911) Kth Smallest Remaining Even Integer in Subarray Queries
    =============================================================

    ============
    Description:
    ============

    You are given an integer array nums where nums is strictly increasing.

    You are also given a 2D integer array queries, where queries[i] = [li, ri, ki].

    For each query [li, ri, ki]:

        + Consider the subarray nums[li..ri]

        + From the infinite sequence of all positive even integers:
            2, 4, 6, 8, 10, 12, 14, ...

        + Remove all elements that appear in the subarray nums[li..ri].

        + Find the kith smallest integer remaining in the sequence after the
          removals.

    Return an integer array ans, where ans[i] is the result for the ith query.

    ===========================================================================================
    FUNCTION: vector<int> kthRemainingInteger(vector<int>& nums, vector<vector<int>>& queries);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,7], queries = [[0,2,1],[1,1,2],[0,0,3]]
    Output: [2,6,6]

    --- Example 2 ---
    Input: nums = [2,5,8], queries = [[0,1,2],[1,2,1],[0,2,4]]
    Output: [6,2,12]

    --- Example 3 ---
    Input: nums = [3,6], queries = [[0,1,1],[1,1,3]]
    Output: [2,8]


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    nums is strictly increasing
    1 <= queries.length <= 10^5
    queries[i] = [li, ri, ki]
    0 <= li <= ri < nums.length
    1 <= ki <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.15% */
/* Space Beats: 34.98% */

/* Time  Complexity: O(N  +  Q * logN) */
/* Space Complexity: O(N)              */
class Solution {
public:
    vector<int> kthRemainingInteger(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        const int Q = queries.size();

        vector<int> result;
        result.reserve(Q); // To prevent repeated reallocations

        vector<int> prefix(N, 0);
        prefix[0] = (nums[0] % 2 == 0);

        for (int i = 1; i < N; i++)
            prefix[i] = prefix[i-1] + ((nums[i] % 2 == 0) ? 1 : 0);

        for (const auto& query : queries)
        {
            int l = query[0];
            int r = query[1];
            int k = query[2];

            int lower_idx = (nums[l] - 1) / 2; // idx of nums[l] in "Inf. Seq."
            int upper_idx = nums[r] / 2;       // idx of nums[r] in "Inf. Seq."

            int remove = prefix[r] - (l > 0 ? prefix[l-1] : 0);

            if (lower_idx >= k) // k is 1-based
            {
                result.push_back(2 * k);
                continue;
            }

            if (upper_idx - remove < k)
            {
                result.push_back(2 * (k + remove));
                continue;
            }

            int low  = l;
            int high = r + 1;

            while (low < high)
            {
                int mid = low + (high - low) / 2;

                int even_count_inclusive = nums[mid] / 2;
                int removals             = prefix[mid] - (l > 0 ? prefix[l-1] : 0);

                if (even_count_inclusive - removals < k)
                    low = mid + 1;
                else
                    high = mid;
            }

            result.push_back(2 * (k + (prefix[low-1] - (l > 0 ? prefix[l-1] : 0))));
        }

        return result;
    }
};
