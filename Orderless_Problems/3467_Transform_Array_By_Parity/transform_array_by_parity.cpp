/*
    ============
    === EASY ===
    ============

    ===============================
    3467) Transform Array By Parity
    ===============================

    ============
    Description:
    ============

    You are given an integer array nums. Transform nums by performing the
    following operations in the exact order specified:

        + Replace each even number with 0.
        + Replace each odd numbers with 1.
        + Sort the modified array in non-decreasing order.

    Return the resulting array after performing these operations.

    ========================================================
    FUNCTION: vector<int> transformArray(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,1]
    Output: [0,0,1,1]
    Explanation:
        Replace the even numbers (4 and 2) with 0 and the odd numbers (3 and 1)
        with 1. Now, nums = [0, 1, 0, 1].
        After sorting nums in non-descending order, nums = [0, 0, 1, 1].

    --- Example 2 ---
    Input: nums = [1,5,1,4,2]
    Output: [0,0,1,1,1]
    Explanation:
        Replace the even numbers (4 and 2) with 0 and the odd numbers
        (1, 5 and 1) with 1. Now, nums = [1, 1, 1, 0, 0].
        After sorting nums in non-descending order, nums = [0, 0, 1, 1, 1].


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  7.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> transformArray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int even = 0;
        for (int i = 0; i < N; i++)
        {
            if (nums[i] % 2 == 0)
                even++;
        }

        for (int i = 0; i < N; i++)
        {
            if (i < even)
                nums[i] = 0;
            else
                nums[i] = 1;
        }

        return nums;
    }
};
