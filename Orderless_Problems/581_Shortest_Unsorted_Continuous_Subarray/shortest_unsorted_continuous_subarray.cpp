/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    581) Shortest Unsorted Continuous Subarray
    ==========================================

    ============
    Description:
    ============

    Given an integer array nums, you need to find one continuous subarray such
    that if you only sort this subarray in non-decreasing order, then the whole
    array will be sorted in non-decreasing order.

    Return the shortest such subarray and output its length.

    ======================================================
    FUNCTION: int findUnsortedSubarray(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,6,4,8,10,9,15]
    Output: 5
    Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make
                 the whole array sorted in ascending order.

    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: 0

    --- Example 3 ---
    Input: nums = [1]
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 10^4
    -10^5 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.96% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        
        int start = 0;
        int next = nums[N - 1];
        for (int i = N-2; i >= 0; i--)
        {
            if (nums[i] > next)
                start = i;
            else
                next = nums[i];
        }

        int end = -1;
        int prev = nums[0];
        for (int i = 1; i < N; i++)
        {
            if (prev > nums[i])
                end = i;
            else
                prev = nums[i];
        }

        return end - start + 1;
    }
};
