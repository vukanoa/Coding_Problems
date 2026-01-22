/*
    ============
    === EASY ===
    ============

    ==========================================
    3507) Minimum Pair Removal to Sort Array I
    ==========================================

    ============
    Description:
    ============

    Given an array nums, you can perform the following operation any number of
    times:

        + Select the adjacent pair with the minimum sum in nums. If multiple
          such pairs exist, choose the leftmost one.

        + Replace the pair with their sum.

    Return the minimum number of operations needed to make the array
    non-decreasing.

    An array is said to be non-decreasing if each element is greater than or
    equal to its previous element (if it exists).

    =====
    Note: Please do not copy the description during the contest to maintain the
          integrity of your submissions.©leetcode
    =====

    ====================================================
    FUNCTION: int minimumPairRemoval(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,2,3,1]
    Output: 2
    Explanation:
        The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
        The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
    The array nums became non-decreasing in two operations.
    Note: Please do not copy the description during the contest to maintain the
    integrity of your submissions.©leetcode


    --- Example 2 ---
    Input: nums = [1,2,2]
    Output: 0
    Explanation:
    The array nums is already sorted.©leetcode


    *** Constraints ***
    1 <= nums.length <= 50
    -1000 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This must be done in a "Brute Force" way. There's no other way around it.
    That's why we're given small Constraints.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.14% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums)
    {
        const int N = nums.size();
        int removed_pairs = 0;

        // O(N^2) (entire block)
        while (removed_pairs < N-1) // O(N)
        {
            if (sorted_non_decreasing(nums, N-1 - removed_pairs)) // O(N)
                break;

            int smallest_pair_sum_left_idx = 0; // pair = {left_idx, right_idx}
            int smallest_sum = nums[0] + nums[1];

            // O(N) (entire block)
            for (int i = 1; i < N-1 - removed_pairs; i++)
            {
                if (nums[i] + nums[i+1] < smallest_sum)
                {
                    smallest_sum = nums[i] + nums[i+1];
                    smallest_pair_sum_left_idx = i;
                }
            }

            // O(N) (entire block)
            nums[smallest_pair_sum_left_idx] = smallest_sum;
            for (int i = smallest_pair_sum_left_idx + 1; i < N-1 - removed_pairs; i++)
            {
                nums[i] = nums[i+1];
            }

            removed_pairs++;
        }

        return removed_pairs;
    }

private:
    bool sorted_non_decreasing(vector<int>& nums, int last_idx)
    {
        for (int i = 1; i <= last_idx; i++)
        {
            if (nums[i-1] > nums[i])
                return false;
        }

        return true;
    }
};
