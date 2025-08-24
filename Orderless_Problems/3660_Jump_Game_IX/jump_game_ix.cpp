/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3660) Jump Game IX
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums.

    From any index i, you can jump to another index j under the following rules:

        + Jump to index j where j > i is allowed only if nums[j] < nums[i].
        + Jump to index j where j < i is allowed only if nums[j] > nums[i].

    For each index i, find the maximum value in nums that can be reached by
    following any sequence of valid jumps starting at i.

    Return an array ans where ans[i] is the maximum value reachable starting
    from index i.

    ==================================================
    FUNCTION: vector<int> maxValue(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3]
    Output: [2,2,3]
    Explanation:
        For i = 0: No jump increases the value.
        For i = 1: Jump to j = 0 as nums[j] = 2 is greater than nums[i].
        For i = 2: Since nums[2] = 3 is the maximum value in nums, no jump
        increases the value.
    Thus, ans = [2, 2, 3].


    --- Example 2 ---
    Input: nums = [2,3,1]
    Output: [3,3,3]
    Explanation:
        For i = 0: Jump forward to j = 2 as nums[j] = 1 is less than
                   nums[i] = 2, then from i = 2 jump to j = 1 as nums[j] = 3
                   is greater than nums[2].

        For i = 1: Since nums[1] = 3 is the maximum value in nums, no jump
                   increases the value.

        For i = 2: Jump to j = 1 as nums[j] = 3 is greater than nums[2] = 1.
    Thus, ans = [3, 3, 3].


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 6.25% */
/* Space Beats: 6.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> maxValue(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> result(N, 0);
        result[0] = nums[0];

        for (int i = 1; i < N; i++)
            result[i] = max(result[i-1], nums[i]);


        stack<int> monotonic_stack;
        monotonic_stack.push(nums.back());

        unordered_map<int,int> val_to_idx;
        val_to_idx.insert( {nums.back(), N-1} );

        for (int i = N-2; i >= 0; i--)
        {
            while ( ! monotonic_stack.empty() && monotonic_stack.top() >= result[i])
                monotonic_stack.pop();

            if ( ! monotonic_stack.empty())
            {
                int idx = val_to_idx[monotonic_stack.top()];
                result[i] = max(result[i], result[idx]);
            }

            monotonic_stack.push(nums[i]);
            val_to_idx.insert( {nums[i], i} );
        }

        return result;
    }
};
