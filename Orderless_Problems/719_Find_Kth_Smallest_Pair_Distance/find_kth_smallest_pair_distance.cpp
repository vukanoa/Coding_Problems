#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ====================================
    719) Find Kth Smallest Pair Distance
    ====================================

    ============
    Description:
    ============

    The distance of a pair of integers a and b is defined as the absolute
    difference between a and b.

    Given an integer array nums and an integer k, return the kth smallest
    distance among all the pairs nums[i] and nums[j] where 0 <= i < j <
    nums.length.

    =============================================================
    FUNCTION: int smallestDistancePair(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,1], k = 1
    Output: 0
    Explanation: Here are all the pairs:
    (1,3) -> 2
    (1,1) -> 0
    (3,1) -> 2
    Then the 1st smallest distance pair is (1,1), and its distance is 0.

    --- Example 2 ---
    Input: nums = [1,1,1], k = 2
    Output: 0

    --- Example 3 ---
    Input: nums = [1,6,1], k = 3
    Output: 5


    *** Constraints ***
    n == nums.length
    2 <= n <= 10^4
    0 <= nums[i] <= 10^6
    1 <= k <= n * (n - 1) / 2

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    This is waaaaaaaaaaaaaaaaaay to hard. I don't think it's realistic to get
    asked this question.

*/

/* Time  Beats: 98.95% */
/* Space Beats:  9.99% */

/*
    Time  Complexity: O(n*logn + n*logW)

    Where W is the range of possible distances (max element - min element).

    In the worst case, this is O(log M), where M is the maximum possible value
    in the array (10^6 according to the problem constraints).

*/
/*
    Space Complexity: O(1)
*/
class Solution {
public:
    int smallestDistancePair(std::vector<int>& nums, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        sort(nums.begin(), nums.end());

        int min_distance = 0;
        int max_distance = nums.back() - nums.front();

        while (min_distance < max_distance)
        {
            int mid_distance = min_distance + (max_distance - min_distance) / 2;

            if (count_pairs_within_distance(nums, mid_distance) < k)
                min_distance = mid_distance + 1;
            else
                max_distance = mid_distance;
        }

        return min_distance;
    }

private:
    int count_pairs_within_distance(vector<int>& nums, int target_distance)
    {
        int count = 0;

        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            while (nums[right] - nums[left] > target_distance)
                left++;

            count += right - left;

            right++;
        }

        return count;
    }
};
