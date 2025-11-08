/*
    ============
    === EASY ===
    ============

    ==============================================================
    1909) Remove One Element to Make the Array Strictly Increasing
    ==============================================================

    ============
    Description:
    ============

    Given a 0-indexed integer array nums, return true if it can be made
    strictly increasing after removing exactly one element, or false otherwise.
    If the array is already strictly increasing, return true.

    The array nums is strictly increasing if nums[i - 1] < nums[i] for each
    index (1 <= i < nums.length).

    ==================================================
    FUNCTION: bool canBeIncreasing(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,10,5,7]
    Output: true
    Explanation: By removing 10 at index 2 from nums, it becomes [1,2,5,7].
    [1,2,5,7] is strictly increasing, so return true.

    --- Example 2 ---
    Input: nums = [2,3,1,2]
    Output: false
    Explanation:
    [3,1,2] is the result of removing the element at index 0.
    [2,1,2] is the result of removing the element at index 1.
    [2,3,2] is the result of removing the element at index 2.
    [2,3,1] is the result of removing the element at index 3.
    No resulting array is strictly increasing, so return false.

    --- Example 3 ---
    Input: nums = [1,1,1]
    Output: false
    Explanation: The result of removing any element is [1,1].
    [1,1] is not strictly increasing, so return false.


    *** Constraints ***
    2 <= nums.length <= 1000
    1 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This one seems easier than it is.

    When we find a "valley", we MUST check if the current number nums[i] is
    greater than the number before the previous one, i.e. nums[i - 2].

        1. If it is, then the number nums[i - 1] needs to be removed.

        2. Else, the current number needs to be removed (nums[i]).

    For simplicity, we can just assign the previous value to the current number

        (nums[i] = nums[i - 1]).

    We could immediately stop if we find "removals" to be > 1 at any point,
    but I like to go through entire array and then check if "removals" <= 1.

    It doesn't matter very much, although stopping immediately is indeed a
    little bit more efficient.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  75.11% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canBeIncreasing(vector<int>& nums)
    {
        const int N = nums.size();
        int removals = 0;

        for (int i = 1; i < N; i++)
        {
            if (nums[i] <= nums[i - 1])
            {
                removals++;

                // If removing nums[i-1] doesn't help, remove nums[i]
                if (i > 1 && nums[i-2] >= nums[i])
                    nums[i] = nums[i - 1];
            }
        }

        return removals <= 1;
    }
};
