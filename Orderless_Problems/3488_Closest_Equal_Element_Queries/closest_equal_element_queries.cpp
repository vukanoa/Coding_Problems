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
#include <cstdlib>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.47% */
/* Space Beats: 58.71% */

/* Time  Complexity: O(N  +  Q * logN) */
/* Space Complexity: O(N  +  Q)        */
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries)
    {
        const int N = nums.size();
        const int Q = queries.size();
        vector<int> answer;
        answer.reserve(Q);

        // O(N) (entire block)
        unordered_map<int, vector<int>> umap;
        for (int i = 0; i < N; i++)
            umap[nums[i]].push_back(i);

        // O(Q * logN)
        for (int i = 0; i < Q; i++)
        {
            int j    = queries[i];
            int elem = nums[j];

            const int SIZE = umap[elem].size();
            if (SIZE == 1)
            {
                answer.push_back(-1);
                continue;
            }

            // O(logN)
            auto it = lower_bound(umap[elem].begin(), umap[elem].end(), j);
            int umap_idx_of_j = distance(umap[elem].begin(), it);

            int umap_idx_of_prev = (umap_idx_of_j - 1 + SIZE) % SIZE;
            int umap_idx_of_next = (umap_idx_of_j + 1)        % SIZE;

            int diff_prev = INT_MAX;
            if (umap_idx_of_prev != umap_idx_of_j)
            {
                diff_prev = abs(umap[elem][umap_idx_of_j] - umap[elem][umap_idx_of_prev]);

                /* Because the array is CIRCULAR */
                diff_prev = min(diff_prev, N - diff_prev);
            }

            int diff_next = INT_MAX;
            if (umap_idx_of_next != umap_idx_of_j)
            {
                diff_next = abs(umap[elem][umap_idx_of_j] - umap[elem][umap_idx_of_next]);

                /* Because the array is CIRCULAR */
                diff_next = min(diff_next, N - diff_next);
            }

            if (diff_prev == INT_MAX && diff_next == INT_MAX)
                answer.push_back(-1);
            else
                answer.push_back(min(diff_prev, diff_next));
        }

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.77% */
/* Space Beats: 30.35% */

/* Time  Complexity: O(N + Q) */
/* Space Complexity: O(N + Q) */
class Solution_Linear {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries)
    {
        const int N = nums.size();
        const int Q = queries.size();

        vector<int> answer;
        answer.reserve(Q);

        unordered_map<int, vector<int>> umap; // num -> sorted indices
        vector<int> indices(N);               // i -> index in indices[nums[i]]

        for (int i = 0; i < N; i++)
        {
            indices[i] = umap[nums[i]].size();
            umap[nums[i]].push_back(i);
        }

        for (int i = 0; i < Q; i++)
        {
            int query = queries[i];
            int elem  = nums[query];

            vector<int>& query_indices = umap[elem];
            const int SIZE = query_indices.size();

            if (SIZE == 1)
            {
                answer.push_back(-1);
                continue;
            }

            int j    = indices[query];
            int curr = query_indices[j];

            int prev = query_indices[(j - 1 + SIZE) % SIZE];
            int next = query_indices[(j + 1)        % SIZE];

            int diff_next = (next - curr + N) % N;
            int diff_prev = (curr - prev + N) % N;

            answer.push_back(min(diff_next, diff_prev));
        }

        return answer;
    }
};
