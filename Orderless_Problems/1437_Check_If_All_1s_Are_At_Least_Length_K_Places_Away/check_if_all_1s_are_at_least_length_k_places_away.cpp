/*
    ============
    === EASY ===
    ============

    ========================================================
    1437) Check if All 1's Are at Least Length K Places Away
    ========================================================

    ============
    Description:
    ============

    Given an binary array nums and an integer k, return true if all 1's are at
    least k places away from each other, otherwise return false.

    ======================================================
    FUNCTION: bool kLengthApart(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,0,0,0,1,0,0,1], k = 2
    Output: true
    Explanation: Each of the 1s are at least 2 places away from each other.

    --- Example 2 ---
    Input: nums = [1,0,0,1,0,1], k = 2
    Output: false
    Explanation: The second 1 and third 1 are only one apart from each other.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= k <= nums.length
    nums[i] is 0 or 1

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
/* Space Beats:  76.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int prev_idx = -(N+1);

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 1)
            {
                if (i - prev_idx - 1 < k)
                    return false;

                prev_idx = i;
            }
        }

        return true;
    }
};
