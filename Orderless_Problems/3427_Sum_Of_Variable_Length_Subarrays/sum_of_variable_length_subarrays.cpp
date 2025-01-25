/*
    ============
    === EASY ===
    ============

    ======================================
    3427) Sum of Variable Length Subarrays
    ======================================

    ============
    Description:
    ============

    You are given an integer array nums of size n. For each index i where
    0 <= i < n, define a subarray nums[start ... i] where
    start = max(0, i - nums[i]).

    Return the total sum of all elements from the subarray defined for each
    index in the array.

    =============================================
    FUNCTION: int subarraySum(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,1]
    Output: 11
    Explanation:
    i           Subarray                    Sum
    0           nums[0] = [2]                2
    1           nums[0 ... 1] = [2, 3]       5
    2           nums[1 ... 2] = [3, 1]       4
    Total Sum         11


    --- Example 2 ---
    Input: nums = [3,1,1,2]
    Output: 13
    Explanation:
    i           Subarray                    Sum
    0           nums[0] = [3]                3
    1           nums[0 ... 1] = [3, 1]       4
    2           nums[1 ... 2] = [1, 1]       2
    3           nums[1 ... 3] = [1, 1, 2]    4
    Total Sum         13

    The total sum is 13. Hence, 13 is the output.


    *** Constraints ***
    1 <= n == nums.length <= 100
    1 <= nums[i] <= 1000

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simply do the PartialSum of "nums".

        PartialSum of [3, 5, 1, 3] is [3, 8, 9, 12].
        PrefixSum essentially.

    Now literally code what you're told in the Description. You don't have to
    think about anything.

    Use this "PrefixSum" to obtain the sum of some subarray in "nums".
    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int subarraySum(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> prefix_sum = nums;
        partial_sum(prefix_sum.begin(), prefix_sum.end(), prefix_sum.begin());

        for (int i = 0; i < N; i++)
        {
            int start = max(0, i - nums[i]);

            result += prefix_sum[i] - (start > 0 ? prefix_sum[start-1] : 0);
        }

        return result;
    }
};
