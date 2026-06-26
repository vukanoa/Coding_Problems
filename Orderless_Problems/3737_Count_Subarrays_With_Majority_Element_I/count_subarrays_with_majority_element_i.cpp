/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3737) Count Subarrays With Majority ELement I
    =============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer target.

    Return the number of subarrays of nums in which target is the majority
    element.

    The majority element of a subarray is the element that appears strictly
    more than half of the times in that subarray.

    ====================================================================
    FUNCTION: int countMajoritySubarrays(vector<int>& nums, int target);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,3], target = 2
    Output: 5
    Explanation:
    Valid subarrays with target = 2 as the majority element:
        nums[1..1] = [2]
        nums[2..2] = [2]
        nums[1..2] = [2,2]
        nums[0..2] = [1,2,2]
        nums[1..3] = [2,2,3]
    So there are 5 such subarrays.

    --- Example 2 ---
    Input: nums = [1,1,1,1], target = 1
    Output: 10
    Explanation:
    All 10 subarrays have 1 as the majority element.

    --- Example 3 ---
    Input: nums = [1,2,3], target = 4
    Output: 0
    Explanation:
    target = 4 does not appear in nums at all. Therefore, there cannot be any
    subarray where 4 is the majority element. Hence the answer is 0.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^9
    1 <= target <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.90% */
/* Space Beats: 75.32% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target)
    {
        const int N = nums.size();

        int result = 0;
        for (int i = 0; i < N; i++)
        {
            int count = 0;

            for (int j = i; j < N; j++)
            {
                count += (nums[j] == target) ? 1 : -1;

                if (count > 0)
                    result++;
            }
        }

        return result;
    }
};
