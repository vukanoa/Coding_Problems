/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3618) Split Array by Prime Indices
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Split nums into two arrays A and B using the following rule:

        Elements at prime indices in nums must go into array A.
        All other elements must go into array B.

    Return the absolute difference between the sums of the two arrays:
    |sum(A) - sum(B)|.

    A prime number is a natural number greater than 1 with only two factors,
    1 and itself.

    =====
    Note: An empty array has a sum of 0.
    =====

    ==================================================
    FUNCTION: long long splitArray(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,4]
    Output: 1
    Explanation: The only prime index in the array is 2, so nums[2] = 4 is
                 placed in array A. The remaining elements, nums[0] = 2 and
                 nums[1] = 3 are placed in array B. sum(A) = 4,
                 sum(B) = 2 + 3 = 5. The absolute difference is |4 - 5| = 1.


    --- Example 2 ---
    Input: nums = [-1,5,7,0]
    Output: 3
    Explanation: The prime indices in the array are 2 and 3, so nums[2] = 7 and
                 nums[3] = 0 are placed in array A. The remaining elements,
                 nums[0] = -1 and nums[1] = 5 are placed in array B.
                 sum(A) = 7 + 0 = 7, sum(B) = -1 + 5 = 4. The absolute
                 difference is |7 - 4| = 3.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

*/

#include <cmath>
#include <cstdlib>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.86% */
/* Space Beats:  7.14% */

/* Time  Complexity: O(N * sqrt(max_element(nums))) */
/* Space Complexity: O(1)                           */
class Solution {
public:
    long long splitArray(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        long long sum_A = 0LL;
        long long sum_B = accumulate(nums.begin(), nums.end(), 0LL);

        for (int i = 0; i < N; i++)
        {
            if (i > 1 && is_prime(i))
            {
                sum_B -= nums[i];
                sum_A += nums[i];
            }
        }

        return abs(sum_A - sum_B);
    }

private:
    bool is_prime(int& num)
    {
        if (num == 1)
            return false;

        for (int factor = 2; factor <= std::sqrt(num); factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};
