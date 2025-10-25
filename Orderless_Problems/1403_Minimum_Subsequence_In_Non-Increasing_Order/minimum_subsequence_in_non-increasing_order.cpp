/*
    ============
    === EASY ===
    ============

    =================================================
    1403) Minimum Subsequence in Non-Increasing Order
    =================================================

    ============
    Description:
    ============

    Given the array nums, obtain a subsequence of the array whose sum of
    elements is strictly greater than the sum of the non included elements in
    such subsequence. 

    If there are multiple solutions, return the subsequence with minimum size
    and if there still exist multiple solutions, return the subsequence with
    the maximum total sum of all its elements. A subsequence of an array can be
    obtained by erasing some (possibly zero) elements from the array. 

    =====
    Note: that the solution with the given constraints is guaranteed to be
          unique. Also return the answer sorted in non-increasing order.
    =====

    ========================================================
    FUNCTION: vector<int> minSubsequence(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,10,9,8]
    Output: [10,9] 
    Explanation: The subsequences [10,9] and [10,8] are minimal such that the
                 sum of their elements is strictly greater than the sum of
                 elements not included. However, the subsequence [10,9] has the
                 maximum total sum of its elements. 

    --- Example 2 ---
    Input: nums = [4,4,7,6,7]
    Output: [7,7,6] 
    Explanation: The subsequence [7,7] has the sum of its elements equal to 14
                 which is not strictly greater than the sum of elements not
                 included (14 = 4 + 4 + 6). Therefore, the subsequence [7,6,7]
                 is the minimal satisfying the conditions. Note the subsequence
                 has to be returned in non-increasing order.  


    *** Constraints ***
    1 <= nums.length <= 500
    1 <= nums[i] <= 100

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

/* Time  Beats: 100.00% */
/* Space Beats:  25.60% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result;

        /* Sort in ASCENDING order */
        sort(nums.begin(), nums.end());

        vector<int> prefix_sum(N);
        prefix_sum[0] = nums[0];
        for (int i = 1; i < N; i++)
        {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i];
        }

        for (int i = N - 1; i >= 0; i--)
        {
            int sum_subsequence = prefix_sum[N - 1] - (i > 0 ? prefix_sum[i - 1] : 0);
            int sum_rest = (i > 0 ? prefix_sum[i - 1] : 0);

            if (sum_subsequence > sum_rest)
            {
                result.insert(result.end(), nums.begin() + i, nums.end());
                break;
            }
        }

        /* Sort in DESCENDING order */
        sort(result.begin(), result.end(), greater<int>());

        return result;
    }
};
