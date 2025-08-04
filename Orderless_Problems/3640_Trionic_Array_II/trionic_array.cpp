/*
    ============
    === HARD ===
    ============

    ===========================
    3640) Trionic Array II
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    A trionic subarray is a contiguous subarray nums[l...r]
    (with 0 <= l < r < n) for which there exist indices l < p < q < r such
    that:

        nums[l...p] is strictly increasing,
        nums[p...q] is strictly decreasing,
        nums[q...r] is strictly increasing.

    Return the maximum sum of any trionic subarray in nums.

    =====================================================
    FUNCTION: long long maxSumTrionic(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,-2,-1,-3,0,2,-1]
    Output: -4
    Explanation:
    Pick l = 1, p = 2, q = 3, r = 5:
        nums[l...p] = nums[1...2] = [-2, -1] is strictly increasing (-2 < -1).
        nums[p...q] = nums[2...3] = [-1, -3] is strictly decreasing (-1 > -3)
        nums[q...r] = nums[3...5] = [-3, 0, 2] is strictly increasing (-3 < 0 < 2).
        Sum = (-2) + (-1) + (-3) + 0 + 2 = -4.

    --- Example 2 ---
    Input: nums = [1,4,2,7]
    Output: 14
    Explanation:
    Pick l = 0, p = 1, q = 2, r = 3:
        nums[l...p] = nums[0...1] = [1, 4] is strictly increasing (1 < 4).
        nums[p...q] = nums[1...2] = [4, 2] is strictly decreasing (4 > 2).
        nums[q...r] = nums[2...3] = [2, 7] is strictly increasing (2 < 7).
        Sum = 1 + 4 + 2 + 7 = 14.


    *** Constraints ***
    4 <= n = nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    It is guaranteed that at least one trionic subarray exists.

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.92% */
/* Space Beats: 93.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums)
    {
        const long long N = nums.size();
        long long max_sum = LLONG_MIN;

        long long curr_sum = nums[0];

        int left   = 0;
        int peak   = 0;
        int valley = 0;
        for (int right = 1; right < N; right++)
        {
            curr_sum += nums[right];

            if (nums[right - 1] == nums[right])
            {
                left = right;
                curr_sum = nums[right];
            }
            else if (nums[right - 1] > nums[right]) // Decreasing
            {
                /*
                    If we've found a "peak", then we're somewhere in the middle
                    phase of a trionic:
                    increasing --> now decreasing --> waiting for next increase

                    But before we move on, we MUST clean up our window so that
                    it accurately reflects a valid trionic subarray starting
                    from "left" index.
                */
                if (right > 1 && nums[right - 2] < nums[right - 1]) // peak found
                {
                    peak = right - 1;

                    /*
                        We've previously saw a valley, of succesful or
                        unsucessful trionic subarray. (decreasing-to-increasing
                        switch).

                        Now we're at a new peak, which starts a new trionic
                        candidate.

                        But any elements from left up to valley are no longer
                        part of a valid candidate because they DON'T belong to
                        the new increasing-decreasing phase.

                        So this loop just slides left forward to "valley" index
                        trimming off the outdated part of the window and
                        subtracting its values from "curr_sum".
                    */
                    while (left < valley)
                    {
                        curr_sum -= nums[left++];
                    }

                    /*
                        Now that "left" is trimmed to a proper range, this loop
                        looks at any leading negative numbers in the current
                        window before the peak.

                        Why?

                        Because we want the MAXIMUM SUM.
                        If we can drop some negative numbers at the start of
                        the subarray (as long as we still have room before the
                        peak), we will CERTAINLY get a better total sum.

                        Therefore, get rid of thesee UNNECESSARY elements at
                        the beginning of this subarray. (It's VERY important
                        that these are UNNECESSARY elements. If all of the
                        elements that form an increasing part are negative,
                        then we CANNOT remove them because that would destroy
                        our increasing part we've previously found. Therefore,
                        we ONLY remove if nums[left] is NEGATIVE &&(AND!!!) 
                        left + 1 < peak)

                            left + 1 < peak

                        is CRUCIAL!

                    */
                    while (left + 1 < peak && nums[left] < 0)
                    {
                        curr_sum -= nums[left++];
                    }
                }
            }
            else // Increasing
            {

                if (right > 1 && nums[right - 2] > nums[right - 1]) // valley found
                {
                    valley = right - 1;
                }

                /*
                    If element BEFORE the current one is a "valley", then check
                    if we already formed increasing and decreasing parts.

                    If we have, then take the maximum for max_sum between
                    max_sum and curr_sum
                */
                if (left < peak && peak < valley)
                {
                    max_sum = max(max_sum, curr_sum);
                }
            }
        }

        return max_sum;
    }
};
