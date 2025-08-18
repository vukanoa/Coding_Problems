/*
    ============
    === EASY ===
    ============

    ==================================
    2765) Longest Alternating Subarray
    ==================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. A subarray s of length m is
    called alternating if:

        m is greater than 1.
        s1 = s0 + 1.
        The 0-indexed subarray s looks like [s0, s1, s0, s1,...,s(m-1) % 2].
        In other words, s1 - s0 = 1, s2 - s1 = -1, s3 - s2 = 1, s4 - s3 = -1,
        and so on up to s[m - 1] - s[m - 2] = (-1)m.

    Return the maximum length of all alternating subarrays present in nums or
    -1 if no such subarray exists.

    A subarray is a contiguous non-empty sequence of elements within an array.

    =====================================================
    FUNCTION: int alternatingSubarray(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,4,3,4]
    Output: 4
    Explanation:
    The alternating subarrays are [2, 3], [3,4], [3,4,3], and [3,4,3,4]. The
    longest of these is [3,4,3,4], which is of length 4.

    --- Example 2 ---
    Input: nums = [4,5,6]
    Output: 2
    Explanation:
    [4,5] and [5,6] are the only two alternating subarrays. They are both of
    length 2.

    *** Constraints ***
    2 <= nums.length <= 100
    1 <= nums[i] <= 10^4
*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Sliding Window" technique.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.43% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int alternatingSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;
        
        int left  = 0;
        int right = 0;
        while (right < N)
        {
            if ((right - left) & 1)
            {
                if (nums[left] + 1 != nums[right])
                    left = right;
            }
            else
            {
                if (nums[left] != nums[right])
                {
                    if (nums[right - 1] + 1 == nums[right])
                        left = right - 1;
                    else
                        left = right;
                }
            }

            result = max(result, right - left + 1);
            
            // Increment
            right++;
        }

        return result < 2 ? -1 : result;
    }
};
