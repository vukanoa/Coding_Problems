#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ===========================
    41) First Missing Positive
    ===========================

    ============
    Description:
    ============

    Given an unsorted integer array nums. Return the smallest positive integer
    that is not present in nums.

    You must implement an algorithm that runs in O(n) time and uses O(1)
    auxiliary space.

    ======================================================
    FUNCTION: int firstMissingPositive(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,0]
    Output: 3
    Explanation: The numbers in the range [1,2] are all in the array

    --- Example 2 ---
    Input: nums = [3,4,-1,1]
    Output: 2
    Explanation: 1 is in the array but 2 is missing.

    --- Example 3 ---
    Input: nums = [7,8,9,11,12]
    Output: 1
    Explanation: The smallest positive integer 1 is missing.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.71% */
/* Space Beats: 95.00% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums)
    {
        const int n = size(nums);

        for (int i = 0; i < n; i++)
        {
            int curr_elem = nums[i]; // curr_elem = current element

            // curr_elem >= 1 && curr_elem <= n : to check if curr_elem is in range[1, n]

            // curr_elem != i+1 : skip if at indecurr_elem i correct element is present.
            // nums[curr_elem-1]!=curr_elem: skip if at indecurr_elem curr_elem-1 correct element is present

            while (curr_elem >= 1 && curr_elem <= n && curr_elem != i+1 && nums[curr_elem-1] != curr_elem)
            {
                swap(nums[curr_elem-1], nums[i]);
                curr_elem = nums[i];
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (nums[i] == i+1)
                continue;

            return i+1;
        }

        return n+1;
    }
};
