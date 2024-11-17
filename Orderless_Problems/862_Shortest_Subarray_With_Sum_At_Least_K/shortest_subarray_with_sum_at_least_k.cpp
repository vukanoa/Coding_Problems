#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <deque>

/*
    ============
    === HARD ===
    ============

    ==========================================
    862) Shortest Subarray with Sum at Least K
    ==========================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the length of the
    shortest non-empty subarray of nums with a sum of at least k. If there is
    no such subarray, return -1.

    A subarray is a contiguous part of an array.

    =========================================================
    FUNCTION: int shortestSubarray(vector<int>& nums, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1], k = 1
    Output: 1

    --- Example 2 ---
    Input: nums = [1,2], k = 4
    Output: -1

    --- Example 3 ---
    Input: nums = [2,-1,2], k = 3
    Output: 3

    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5
    1 <= k <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Some good examples to consider:

        nums = [2, -1, 2, -3, 2, 1, -2, 2, -5, 3]
        nums = [5, -4, 2, 1, 9, -4, -3, 2]

*/

/* Time  Beats: 13.91% */
/* Space Beats: 18.41% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k)
    {
        const int n = nums.size();

        long long result = INT_MAX;
        long long curr_sum = 0;

        std::priority_queue<pair<long long,int>,
                            vector<pair<long long,int>>,
                            greater<pair<long long,int>>> min_heap;

        int right = 0;
        while (right < n)
        {
            curr_sum += nums[right];

            if (curr_sum >= k)
                result = min(result, static_cast<long long>(right + 1));

            while (!min_heap.empty() && curr_sum - min_heap.top().first >= k)
            {
                int prefix  = min_heap.top().first;
                int end_idx = min_heap.top().second;
                min_heap.pop();

                result = min(result, static_cast<long long>(right - end_idx));
            }

            min_heap.push( {curr_sum, right} );

            // Increment for while-loop
            right++;
        }

        return result == INT_MAX ? -1 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Before trying to solve the current one, try solving these one first:
        + Daily temperatures             (Monotonic Stack)
        + Largest Rectangle in Histogram (Monotonic Stack)
        + Sliding Window Maximum         (Sliding Window)

    Otherwise, you have no chance.

*/

/* Time  Beats: 39.24% */
/* Space Beats: 53.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k)
    {
        const int n = nums.size();

        long long result = INT_MAX;
        long long curr_sum = 0;

        // Monotonicly increasing deque
        deque<pair<long long,int>> deque;

        int right = 0;
        while (right < n)
        {
            curr_sum += nums[right];

            if (curr_sum >= k)
                result = min(result, static_cast<long long>(right + 1));

            // Find the minimum valid window that is ending at index "right"
            while ( !deque.empty() && curr_sum - deque.front().first >= k )
            {
                int prefix  = deque.front().first;
                int end_idx = deque.front().second;
                deque.pop_front();

                result = min(result, static_cast<long long>(right - end_idx));
            }

            // Validate the monotonic feature of the Deque
            while ( !deque.empty() && deque.back().first > curr_sum )
                deque.pop_back();

            deque.push_back( {curr_sum, right} );

            // Increment for while-loop
            right++;
        }

        return result == INT_MAX ? -1 : result;
    }
};
