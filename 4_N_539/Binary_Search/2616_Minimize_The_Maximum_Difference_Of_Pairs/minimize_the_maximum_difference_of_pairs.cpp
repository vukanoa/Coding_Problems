#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    2616) Minimize the Maximum Difference of Pairs
    ==============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums and an integer p. Find p pairs
    of indices of nums such that the maximum difference amongst all the pairs
    is minimized. Also, ensure no index appears more than once amongst the p
    pairs.

    Note that for a pair of elements at the index i and j, the difference of
    this pair is |nums[i] - nums[j]|, where |x| represents the absolute value
    of x.

    Return the minimum maximum difference among all p pairs. We define the
    maximum of an empty set to be zero.

    ====================================================
    FUNCTION: int minimizeMax(vector<int>& nums, int p);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,1,2,7,1,3], p = 2
    Output: 1
    Explanation: The first pair is formed from the indices 1 and 4, and the
                 second pair is formed from the indices 2 and 5.  The maximum
                 difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) =
                 max(0, 1) = 1. Therefore, we return 1.


    --- Example 2 ---
    Input: nums = [4,2,1,2], p = 1
    Output: 0
    Explanation: Let the indices 1 and 3 form a pair. The difference of that
                 pair is |2 - 2| = 0, which is the minimum we can attain.


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9
    0 <= p <= (nums.length)/2

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Down there are two Solutions. The bottom one is a lot faster.

*/

/* Time  Beats: 5.36% */
/* Space Beats: 79.96% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    int minimizeMax(std::vector<int>& nums, int p)
    {
        if (p == 0)
            return 0;

        std::function<bool(int)> valid = [&](int threshold) -> bool
        {
            int count = 0;

            int i = 0;
            while (i < nums.size()-1)
            {
                if (std::abs(nums[i] - nums[i+1]) <= threshold)
                {
                    count++;
                    i += 2;
                }
                else
                    i++;

                if (count == p)
                    return true;
            }

            return false;
        };

        std::sort(nums.begin(), nums.end());

        unsigned long long  left  = 0;
        unsigned long long  right = std::pow(10, 9);

        unsigned long long  result = std::pow(10, 9);

        while (left <= right)
        {
            unsigned long long mid = left + (right - left) / 2;

            if (valid(mid))
            {
                result = mid;
                right  = mid - 1;
            }
            else
                left   = mid + 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's the exact same idea, however it's much more efficient since we are
    not going from 10^9 as the right bound, but the maximum value in our sorted
    array "nums" which on average tends to be much less than 10^9 which is the
    upper bound in the contraints sections for nums[i] values.

*/

/* Time  Beats: 87.78% */
/* Space Beats: 31.40% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution_Efficient_Implementation {
public:
    int minimizeMax(std::vector<int>& nums, int p)
    {
        std::sort(nums.begin(), nums.end());

        int n = nums.size();
        int result = nums[n-1] - nums[0];

        int left  = 0;
        int right = result;

        while(left <= right)
        {
            int mid = (left + right) / 2;
            int count = 0;
            int k = 0;

            while(k < n-1)
            {
                if(nums[k+1] - nums[k] <= mid)
                {
                    count++;
                    k += 2;
                }
                else
                    k++;
            }

            if(count >= p)
            {
                result = mid;
                right = mid - 1;
            }
            else
                left  = mid + 1;
        }

        return result;
    }
};
