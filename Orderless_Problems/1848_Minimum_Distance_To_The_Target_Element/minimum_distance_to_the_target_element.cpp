/*
    ============
    === EASY ===
    ============

    ============================================
    1848) Minimum Distance to the Target Element
    ============================================

    ============
    Description:
    ============

    Given an integer array nums (0-indexed) and two integers target and start,
    find an index i such that nums[i] == target and abs(i - start) is
    minimized. Note that abs(x) is the absolute value of x.

    Return abs(i - start).

    It is guaranteed that target exists in nums.

    =======================================================================
    FUNCTION: int getMinDistance(vector<int>& nums, int target, int start);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5], target = 5, start = 3
    Output: 1
    Explanation: nums[4] = 5 is the only value equal to target, so the answer
                 is abs(4 - 3) = 1.

    --- Example 2 ---
    Input: nums = [1], target = 1, start = 0
    Output: 0
    Explanation: nums[0] = 1 is the only value equal to target, so the answer
                 is abs(0 - 0) = 0.

    --- Example 3 ---
    Input: nums = [1,1,1,1,1,1,1,1,1,1], target = 1, start = 0
    Output: 0
    Explanation: Every value of nums is 1, but nums[0] minimizes
                 abs(i - start), which is abs(0 - 0) = 0.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 10^4
    0 <= start < nums.length
    target is in nums.

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  50.34% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start)
    {
        const int N = nums.size();

        int L = start;
        int R = start;
        while (L >= 0 || R < N)
        {
            if (nums[L] == target) return abs(L - start);
            if (nums[R] == target) return abs(R - start);

            L -= L >  0   ? 1 : 0;
            R += R <  N-1 ? 1 : 0;
        }

        return -1; // Unreachable
    }
};
