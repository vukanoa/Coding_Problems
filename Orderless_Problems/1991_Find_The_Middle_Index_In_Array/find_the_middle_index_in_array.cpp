/*
    ============
    === EASY ===
    ============

    ====================================
    1991) Find the Middle Index in Array
    ====================================

    ============
    Description:
    ============

    Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e.,
    the smallest amongst all the possible ones).

    A middleIndex is an index where nums[0] + nums[1] + ... +
    nums[middleIndex-1] == nums[middleIndex+1] + nums[middleIndex+2] + ... +
    nums[nums.length-1].

    If middleIndex == 0, the left side sum is considered to be 0. Similarly, if
    middleIndex == nums.length - 1, the right side sum is considered to be 0.

    Return the leftmost middleIndex that satisfies the condition, or -1 if
    there is no such index.

    =================================================
    FUNCTION: int findMiddleIndex(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,-1,8,4]
    Output: 3
    Explanation: The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
    The sum of the numbers after index 3 is: 4 = 4

    --- Example 2 ---
    Input: nums = [1,-1,4]
    Output: 2
    Explanation: The sum of the numbers before index 2 is: 1 + -1 = 0
    The sum of the numbers after index 2 is: 0

    --- Example 3 ---
    Input: nums = [2,5]
    Output: -1
    Explanation: There is no valid middleIndex.

    *** Constraints ***
    1 <= nums.length <= 100
    -1000 <= nums[i] <= 1000

*/

#include <numeric>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    ~~~~~~~~
    ~ Note ~ This question is the same as 724:
                 https://leetcode.com/problems/find-pivot-index/
    ~~~~~~~~

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  80.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findMiddleIndex(vector<int>& nums)
    {
        const int N = nums.size();

        int total_sum = accumulate(nums.begin(), nums.end(), 0LL);

        int left_sum  = 0;
        int right_sum = total_sum - nums[0];

        if (left_sum == right_sum)
            return 0;

        for (int i = 1; i < N; i++)
        {
            left_sum  += nums[i-1];
            right_sum -= nums[i];

            if (left_sum == right_sum)
                return i;
        }

        return -1;
    }
};
