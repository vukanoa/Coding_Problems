#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1838) Frequency of the Most Frequent Element
    ============================================

    ============
    Description:
    ============

    The frequency of an element is the number of times it occurs in an array.

    You are given an integer array nums and an integer k. In one operation, you
    can choose an index of nums and increment the element at that index by 1.

    Return the maximum possible frequency of an element after performing at
    most k operations.

    =====================================================
    FUNCTION: int maxFrequency(vector<int>& nums, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,4], k = 5
    Output: 3
    Explanation: Increment the first element three times and the second element
                 two times to make nums = [4,4,4].  4 has a frequency of 3.


    --- Example 2 ---
    Input: nums = [1,4,8,13], k = 5
    Output: 2
    Explanation: There are multiple optimal solutions:
    - Increment the first element three times to make nums = [4,4,8,13]. 4 has
      a frequency of 2.
    - Increment the second element four times to make nums = [1,8,8,13]. 8 has
      a frequency of 2.
    - Increment the third element five times to make nums = [1,4,13,13]. 13 has
      a frequency of 2.


    --- Example 3 ---
    Input: nums = [3,9,6], k = 2
    Output: 1


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= k <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    The crux of this Solution is:

    Valid Window:
        (nums[right] * (right - left + 1)) <= (total + k)

    Invalid Window:
        (nums[right] * (right - left + 1)) >  (total + k)


    Consider this example:
        nums = [1, 1, 1, 2, 2, 4], k = 2
                L        R

    nums[R] * (R - L + 1) <= total + k
      2     *      4      <=   5   + 2

    It's invalid, therefore we move left pointers until it becomes valid again.
    We repeat this and each time we move a "R" pointer, we calculate the max
    window length which we'll return at the very end.

*/

/* Time  Beats: 74.28% */
/* Space Beats: 77.02% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Or O(n) depending on the sort

using ULL = unsigned long long;

class Solution {
public:
    int maxFrequency(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int max_freq = 0;

        int left  = 0;
        int right = 0;

        unsigned long long total = 0;
        while (right < nums.size())
        {
            total += nums[right];

            while ((ULL)((ULL)nums[right] * (ULL)(right - left + 1)) > (ULL)(total + k)) // while Invalid Window
                total -= nums[left++];

            max_freq = std::max(max_freq, right - left + 1);
            right++;
        }

        return max_freq;
    }
};
