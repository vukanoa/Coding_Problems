/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    3362) Zero Array Transformation III
    ===================================

    ============
    Description:
    ============

    You are given an integer array nums of length n and a 2D array queries
    where queries[i] = [li, ri].

    Each queries[i] represents the following action on nums:

        + Decrement the value at each index in the range [li, ri] in nums by at
          most 1.

        + The amount by which the value is decremented can be chosen
          independently for each index.

    A Zero Array is an array with all its elements equal to 0.

    Return the maximum number of elements that can be removed from queries,
    such that nums can still be converted to a zero array using the remaining
    queries. If it is not possible to convert nums to a zero array, return -1.

    ==========================================================================
    FUNCTION: int maxRemoval(vector<int>& nums, vector<vector<int>>& queries);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
    Output: 1
    Explanation:
    After removing queries[2], nums can still be converted to a zero array.
        Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
        Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.

    --- Example 2 ---
    Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
    Output: 2
    Explanation:
    We can remove queries[2] and queries[3].

    --- Example 3 ---
    Input: nums = [1,2,3,4], queries = [[0,3]]
    Output: -1
    Explanation:
    nums cannot be converted to a zero array even after using all the queries.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 2
    0 <= li <= ri < nums.length

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

/* Time  Beats: 98.31% */
/* Space Beats: 12.77% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(N + M)    */
class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();

        // Sweep line structure: For each index, store all query end-points that start at this index
        static vector<vector<int>> sweep_line_query_ends(100005);
        for (int i = 0; i < N; i++)
        {
            sweep_line_query_ends[i].clear();
        }

        for (int i = 0; i < M; i++)
        {
            int start_idx = queries[i][0];
            int end_idx   = queries[i][1];

            sweep_line_query_ends[start_idx].push_back(end_idx);
        }

        priority_queue<int> max_heap;

        // Count of how many queries are currently active up to each position
        vector<int> active_query_delta(N + 1, 0);
        int total_decrement = 0;

        for (int i = 0; i < N; i++)
        {
            int curr_val = nums[i];

            // Update active queries ending before or at this point
            total_decrement += active_query_delta[i];

            // Add all queries that start at this point
            for (int query_end : sweep_line_query_ends[i])
            {
                max_heap.push(query_end);
            }

            int farthest_query_end;

            // While the current number can still be decremented
            // and we have available queries spanning this index
            while (curr_val > total_decrement && !max_heap.empty() && (farthest_query_end = max_heap.top()) >= i)
            {
                total_decrement++;
                active_query_delta[farthest_query_end + 1]--;
                max_heap.pop();
            }

            // If we couldn't decrement `current_value` enough, return failure
            if (total_decrement < curr_val)
            {
                return -1;
            }
        }

        // Remaining queries in the heap are those unused
        return static_cast<int>(max_heap.size());
    }
};
