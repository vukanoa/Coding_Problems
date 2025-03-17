/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    3488) Closest Equal Element Queries
    ===================================

    ============
    Description:
    ============

    You are given a circular array nums and an array queries.

    For each query i, you have to find the following:

        The minimum distance between the element at index queries[i] and any
        other index j in the circular array, where nums[j] == nums[queries[i]].

        If no such index exists, the answer for that query should be -1.

    Return an array answer of the same size as queries, where answer[i]
    represents the result for query i.

    ============================================================================
    FUNCTION: vector<int> solveQueries(vector<int>& nums, vector<int>& queries);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
    Output: [2,-1,3]
    Explanation:
        Query 0: The element at queries[0] = 0 is nums[0] = 1.
        The nearest index with the same value is 2, and the distance between
        them is 2.

        Query 1: The element at queries[1] = 3 is nums[3] = 4.
        No other index contains 4, so the result is -1.

        Query 2: The element at queries[2] = 5 is nums[5] = 3.
        The nearest index with the same value is 1, and the distance between
        them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).



    --- Example 2 ---
    Input: nums = [1,2,3,4], queries = [0,1,2,3]
    Output: [-1,-1,-1,-1]
    Explanation: Each value in nums is unique, so no index shares the same
                 value as the queried element. This results in -1 for all
                 queries.



    *** Constraints ***
    1 <= queries.length <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    0 <= queries[i] < nums.length

*/

#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N + M * logN) */
/* Space Complexity: O(N)            */
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries)
    {
        const int N = nums.size();
        const int M = queries.size();
        vector<int> answer(M, -1);

        unordered_map<int, vector<int>> umap;
        for (int i = 0; i < N; i++)
            umap[nums[i]].push_back(i);

        for (int i = 0; i < M; i++)
        {
            int idx  = queries[i];
            int elem = nums[idx];

            if (umap[elem].size() == 1)
            {
                answer[i] = -1;
            }
            else
            {
                auto iter = lower_bound(umap[elem].begin(), umap[elem].end(), idx);
                int iter_idx = iter - umap[elem].begin();

                int size = umap[elem].size();
                int min_dist = INT_MAX;

                int prev_idx = iter_idx == 0      ? size-1 : iter_idx - 1;
                int next_idx = iter_idx == size-1 ?   0    : iter_idx + 1;

                int curr = umap[elem][iter_idx];
                int prev = umap[elem][prev_idx];
                int next = umap[elem][next_idx];

                if (prev < curr)
                {
                    min_dist = min(min_dist,     curr - prev);
                    min_dist = min(min_dist, N - curr + prev);
                }
                else
                {
                    min_dist = min(min_dist,     prev - curr);
                    min_dist = min(min_dist, N - prev + curr);
                }

                if (curr < next)
                {
                    min_dist = min(min_dist,     next - curr);
                    min_dist = min(min_dist, N - next + curr);
                }
                else
                {
                    min_dist = min(min_dist,     curr - next);
                    min_dist = min(min_dist, N - curr + next);
                }

                answer[i] = min_dist;
            }
        }

        return answer;
    }
};
