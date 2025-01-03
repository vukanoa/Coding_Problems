/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3350) Adjacent Increasing Subarrays Detection II
    ================================================

    ============
    Description:
    ============

    Given an array nums of n integers, your task is to find the maximum value
    of k for which there exist two adjacent subarrays of length k each, such
    that both subarrays are strictly increasing. Specifically, check if there
    are two subarrays of length k starting at indices a and b (a < b), where:

    Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly
    increasing. The subarrays must be adjacent, meaning b = a + k.

    Return the maximum possible value of k.

    A subarray is a contiguous non-empty sequence of elements within an array.

    ========================================================
    FUNCTION: int maxIncreasingSubarrays(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,5,7,8,9,2,3,4,3,1]
    Output: 3
    Explanation:
        The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
        The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
        These two subarrays are adjacent, and 3 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.


    --- Example 2 ---
    Input: nums = [1,2,3,4,4,4,4,5,6,7]
    Output: 2
    Explanation:
        The subarray starting at index 0 is [1, 2], which is strictly increasing.
        The subarray starting at index 2 is [3, 4], which is also strictly increasing.
        These two subarrays are adjacent, and 2 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.


    *** Constraints ***
    2 <= nums.length <= 2 * 10^5
    -10^9 <= nums[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Once you draw yourself the Example, it becomes painfully obvious:


    Input: nums = [2, 5, 7, 8, 9, 2, 3, 4, 3, 1]
                   0  1  2  3  4  5  6  7  8  9




        9              X
        8           X
        7        X
        6
        5     X
        4                       X
        3                    X
        2  X              X
        1                             X
        ---0--1--2--3--4--5--6--7--8--9---  // Indices


    It becomes obvious that the biggest ADJACENT INCREASING subarrays is of
    size 3.

    Now just code that idea up. It's straightforward. There are no "tricks".

*/

/* Time  Beats: 84.54% */
/* Space Beats: 77.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;

        int up = 1;
        int left_prev  = 0;
        int right_prev = 0;

        for (int i = 1; i < n; i++)
        {
            if (nums[i-1] < nums[i])
            {
                up++;
            }
            else
            {
                up = 1;
                left_prev = right_prev;
                right_prev = i;
            }

            result = max(result, up / 2);

            if (left_prev != right_prev)
            {
                // Either "up" or "i - right_prev + 1"
                result = max(result, min(right_prev - left_prev, up));
            }
            
        }

        return result;
    }
};
