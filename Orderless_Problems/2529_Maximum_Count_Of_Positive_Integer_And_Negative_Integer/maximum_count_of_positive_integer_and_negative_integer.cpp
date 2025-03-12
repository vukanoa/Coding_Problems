/*
    ============
    === EASY ===
    ============

    ==========================================================
    2529) Maxim Count of Positive Integer and Negative Integer
    ==========================================================

    ============
    Description:
    ============

    Given an array nums sorted in non-decreasing order, return the maximum
    between the number of positive integers and the number of negative integers

        + In other words, if the number of positive integers in nums is pos and
        the number of negative integers is neg, then return the maximum of pos
        and neg.

    =====
    Note: that 0 is neither positive nor negative.
    =====


    ---------------
    -- Follow Up --
    ---------------

    Can you solve the problem in O(log(n)) time complexity?


    ==============================================
    FUNCTION: int maximumCount(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-2,-1,-1,1,2,3]
    Output: 3
    Explanation: There are 3 positive integers and 3 negative integers. The
                 maximum count among them is 3.


    --- Example 2 ---
    Input: nums = [-3,-2,-1,0,0,1,2]
    Output: 3
    Explanation: There are 2 positive integers and 3 negative integers. The
                  maximum count among them is 3.


    --- Example 3 ---
    Input: nums = [5,20,66,1314]
    Output: 4
    Explanation: There are 4 positive integers and 0 negative integers. The
                 maximum count among them is 4.


    *** Constraints ***
    1 <= nums.length <= 2000
    -2000 <= nums[i] <= 2000
    nums is sorted in a non-decreasing order.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumCount(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        if (N == 1)
            return nums[0] == 0 ? 0 : 1;

        int neg = -1;
        int pos = -1;

        for (int i = 0; i < N; i++)
        {
            if (neg == -1 && nums[i] >= 0)
                neg = i;

            if (nums[i] > 0)
            {
                pos = N - i;
                break;
            }
        }

        if (neg == -1 && pos == -1)
            return N;

        return max(neg, pos);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic Binary Search. Instead of writing Binary Search yourself, which is
    indeed challenging, you can use C++'s "lower_bound" and "upper_bound"
    implementations.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  75.85% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_Follow_Up {
public:
    int maximumCount(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        auto leftmost_zero_or_pos_iter = lower_bound(nums.begin(), nums.end(), 0);
        auto leftmost_pos_iter         = upper_bound(nums.begin(), nums.end(), 0);

        int pos = -1;
        int neg = -1;

        if (leftmost_zero_or_pos_iter == nums.end())
        {
            neg = N;
        }
        else
        {
            neg = leftmost_zero_or_pos_iter - nums.begin();

            if (*leftmost_zero_or_pos_iter > 0)
                pos = nums.end() - leftmost_zero_or_pos_iter;
            else
            {
                pos = nums.end() - leftmost_pos_iter;
            }
        }

        return max(neg, pos);
    }
};
