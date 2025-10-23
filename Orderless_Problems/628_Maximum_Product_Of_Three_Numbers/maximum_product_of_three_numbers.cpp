/*
    ============
    === EASY ===
    ============

    =====================================
    628) Maximum Product of Three Numbers
    =====================================

    ============
    Description:
    ============

    Given an integer array nums, find three numbers whose product is maximum
    and return the maximum product.

    ================================================
    FUNCTION: int maximumProduct(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 6

    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: 24

    --- Example 3 ---
    Input: nums = [-1,-2,-3]
    Output: -6


    *** Constraints ***
    3 <= nums.length <= 10^4
    -1000 <= nums[i] <= 1000

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You probably missed this example:

        nums = [-100,-98,-1,2,3,4]

    You probably thought that the Output should be: 24, however it's

        Expected:  39200

    Why? How?
    What if you multiply (-100) * (-98) * 4?


    Oooh, so you need to take negative numbers into acount as well?
    Yes, but everyone knows that ODD number of negative numbers is always
    NEGATIVE, so in order to avoid that we know for a fact that the largest
    product is ether:

        1. The largest  POSITIVE numbers, or
        2. Two SMALLEST NEGATIVE numbers multiplied by largest POSITIVE number

    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumProduct(vector<int>& nums) 
    {
        int max_first  = INT_MIN;
        int max_second = INT_MIN;
        int max_third  = INT_MIN;

        int min_first  = INT_MAX;
        int min_second = INT_MAX;

        for (const int& num : nums) 
        {
            if (num > max_first) 
            {
                max_third  = max_second;
                max_second = max_first;
                max_first  = num;
            } 
            else if (num > max_second) 
            {
                max_third  = max_second;
                max_second = num;
            } 
            else if (num > max_third) 
            {
                max_third = num;
            }

            if (num < min_first) 
            {
                min_second = min_first;
                min_first  = num;
            } 
            else if (num < min_second) 
            {
                min_second = num;
            }
        }

        return max(max_first * max_second * max_third, min_first * min_second * max_first);
    }
};
