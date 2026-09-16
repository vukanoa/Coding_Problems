/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    2447) Number of Subarrays With GCD Equal to K
    =============================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return the number of
    subarrays of nums where the greatest common divisor of the subarray's
    elements is k.

    A subarray is a contiguous non-empty sequence of elements within an array.

    The greatest common divisor of an array is the largest integer that evenly
    divides all the array elements.

    ====================================================
    FUNCTION: int subarrayGCD(vector<int>& nums, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [9,3,1,2,6,3], k = 3
    Output: 4
    Explanation: The subarrays of nums where 3 is the greatest common divisor
                 of all the subarray's elements are:
    - [9,3,1,2,6,3]
    - [9,3,1,2,6,3]
    - [9,3,1,2,6,3]
    - [9,3,1,2,6,3]


    --- Example 2 ---
    Input: nums = [4], k = 7
    Output: 0
    Explanation: There are no subarrays of nums where 7 is the greatest common
                 divisor of all the subarray's elements.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i], k <= 10^9

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force.

*/

/* Time  Beats: 15.61% */
/* Space Beats: 98.87% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution_Brute_Force {
public:
    int subarrayGCD(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        for (int start = 0; start < N; start++)
        {
            int curr_gcd = 0;
            for (int j = start; j < N; j++)
            {
                curr_gcd = std::gcd(curr_gcd, nums[j]);
    
                if (curr_gcd == k)
                    ++result;
            }
        }

        return result;
    }
};
