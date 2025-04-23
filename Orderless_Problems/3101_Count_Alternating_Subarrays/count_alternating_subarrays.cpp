/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    3101) Count Alternating Subarrays
    =================================

    ============
    Description:
    ============


    You are given a binary array nums.

    We call a subarray alternating if no two adjacent elements in the subarray
    have the same value.

    Return the number of alternating subarrays in nums.

    =================================================================
    FUNCTION: long long countAlternatingSubarrays(vector<int>& nums);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,1,1]
    Output: 5
    Explanation: The following subarrays are alternating:
                 [0], [1], [1], [1], and [0,1].

    --- Example 2 ---
    Input: nums = [1,0,1,0]
    Output: 10
    Explanation: Every subarray of the array is alternating. There are 10
                 possible subarrays that we can choose.


    *** Constraints ***
    1 <= nums.length <= 10^5
    nums[i] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Sliding Window" technique.

*/

/* Time  Beats: 55.38% */
/* Space Beats: 61.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = N;

        int L = 0;
        int R = 1;

        while (R < N)
        {
            if (nums[R-1] != nums[R])
            {
                result += R - L;
            }
            else
                L = R;

            // Increment
            R++;
        }

        return result;
    }
};
