/*
    ============
    === EASY ===
    ============

    =============================================
    2164) Sort Even and Odd Indices Independently
    =============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. Rearrange the values of nums
    according to the following rules:

        + Sort the values at odd indices of nums in non-increasing order.
            For example, if nums = [4,1,2,3] before this step, it becomes
            [4,3,2,1] after. The values at odd indices 1 and 3 are sorted in
            non-increasing order.

        + Sort the values at even indices of nums in non-decreasing order.
            For example, if nums = [4,1,2,3] before this step, it becomes
            [2,1,4,3] after. The values at even indices 0 and 2 are sorted in
            non-decreasing order.

    Return the array formed after rearranging the values of nums.

    =====================================================
    FUNCTION: vector<int> sortEvenOdd(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,1,2,3]
    Output: [2,3,4,1]
    Explanation:
    First, we sort the values present at odd indices (1 and 3) in non-increasing order.
    So, nums changes from [4,1,2,3] to [4,3,2,1].
    Next, we sort the values present at even indices (0 and 2) in non-decreasing order.
    So, nums changes from [4,1,2,3] to [2,3,4,1].
    Thus, the array formed after rearranging the values is [2,3,4,1].

    --- Example 2 ---
    Input: nums = [2,1]
    Output: [2,1]
    Explanation:  Since there is exactly one odd index and one even index, no
    rearrangement of values takes place. The resultant array formed is [2,1],
    which is the same as the initial array.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanaory.

*/

/* Time  Beats: 12.01% */
/* Space Beats: 20.67% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> at_odd_indices;
        vector<int> at_even_indices;

        for (int i = 0; i < N; i++)
        {
            if (i & 1)
                at_odd_indices.push_back(nums[i]);
            else
                at_even_indices.push_back(nums[i]);
        }

        sort(at_odd_indices.begin(),  at_odd_indices.end(), greater<int>());
        sort(at_even_indices.begin(), at_even_indices.end());

        int idx = 0;
        for (int i = 0; i < N; i++)
        {
            if (i & 1)
                nums[i] = at_odd_indices[idx++];
            else
                nums[i] = at_even_indices[idx];
        }

        return nums;
    }
};
