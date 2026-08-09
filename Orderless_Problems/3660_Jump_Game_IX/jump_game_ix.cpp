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

#include <climits>
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.20% */
/* Space Beats: 46.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Prefix_Suffix {
public:
    vector<int> maxValue(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> prefix_max(N);
        vector<int> suffix_min(N);

        prefix_max[0]   = nums[0];
        suffix_min[N-1] = nums[N-1];

        for (int i = 1; i < N; i++)
        {
            prefix_max[i]       = max(prefix_max[i-1],       nums[i]      );
            suffix_min[N-1 - i] = min(suffix_min[N-1 - i+1], nums[N-1 - i]);
        }

        vector<int> result(N);
        result[N-1] = prefix_max[N-1];

        for (int i = N-2; i >= 0; i--)
        {
            if (prefix_max[i] > suffix_min[i+1])
                result[i] = result[i+1];
            else
                result[i] = prefix_max[i];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Optimized above Solution. We do not need to have both "prefix" and "suffix"
    vectors. We can calculate "suffix" one while we go, thus reducing the total
    required Space, although the Space Complexity is the same in BigO notation.

*/

/* Time  Beats: 68.10% */
/* Space Beats: 86.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Prefix_Suffix__Optimized{
public:
    vector<int> maxValue(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result(N);

        vector<int> prefix_max(N);
        prefix_max[0] = nums[0];

        for (int i = 1; i < N; i++)
            prefix_max[i] = max(prefix_max[i - 1], nums[i]);

        int suffix_min = INT_MAX;

        // Traverse from right to left
        for (int i = N-1; i >= 0; i--)
        {
            if (prefix_max[i] > suffix_min)
                result[i] = result[i + 1];
            else
                result[i] = prefix_max[i];

            suffix_min = min(suffix_min, nums[i]);
        }

        return result;
    }
};
