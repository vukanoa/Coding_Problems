/*
    ============
    === EASY ===
    ============

    =============================================
    3349) Adjacent Increasing Subarrays Detection
    =============================================

    ============
    Description:
    ============

    Given an array nums of n integers and an integer k, determine whether there
    exist two adjacent subarrays of length k such that both subarrays are
    strictly increasing. Specifically, check if there are two subarrays
    starting at indices a and b (a < b), where:

    Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly
    increasing. The subarrays must be adjacent, meaning b = a + k.

    Return true if it is possible to find two such subarrays, and false
    otherwise.

    ===========================================================================
    FUNCTION: bool hasIncreasingSubarrays(const std::vector<int>& nums, int k);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3
    Output: true
    Explanation:
        The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
        The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
        These two subarrays are adjacent, so the result is true.


    --- Example 2 ---
    Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5
    Output: false


    *** Constraints ***
    2 <= nums.length <= 100
    1 < 2 * k <= nums.length
    -1000 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.63% */
/* Space Beats: 22.10% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(1)     */
class Solution {
public:
    bool hasIncreasingSubarrays(const std::vector<int>& nums, int k)
    {
        const int N = nums.size();

        auto helper = [&](int idx) -> bool
        {
            for (int i = idx+1; i < idx + k; ++i)
            {
                if (nums[i-1] >= nums[i])
                    return false;
            }

            return true;
        };

        for (int idx = 0; idx <= N - 2*k; idx++)
        {
            if (helper(idx) && helper(idx + k))
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 70.00% */
/* Space Beats: 54.55% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k)
    {
        const int N = nums.size();

        int L = 0;
        int R = 1;

        bool can_reuse = false;
        while (R < N)
        {
            if ((R - L) == 2 * k)
                break;

            if ((R - L) == k)
            {
                if (nums[R-1] < nums[R])
                    can_reuse = true;
            }
            else if (nums[R-1] >= nums[R])
            {
                if (can_reuse)
                {
                    can_reuse = false;
                    L = R - k; // Reuse part of the left and part of the right subarray
                }
                else
                {
                    L = R; // Start all over again
                }
            }


            // Increment
            R++;
        }

        return (R - L) == 2 * k;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.09% */
/* Space Beats: 23.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_3 {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<int> increasing_lengths;
        int L = 0;
        int R = 1;

        while (R < N)
        {
            if (nums[R-1] >= nums[R])
            {
                increasing_lengths.push_back(R - L);
                L = R;
            }

            // Increment
            R++;
        }
        increasing_lengths.push_back(R - L);

        if (increasing_lengths[0] >= 2 * k)
            return true;

        for (unsigned i = 1; i < increasing_lengths.size(); i++)
        {
            if (increasing_lengths[i] >= 2 * k)
                return true;

            if (min(increasing_lengths[i-1], increasing_lengths[i]) >= k)
                return true;
        }

        return false;
    }
};
