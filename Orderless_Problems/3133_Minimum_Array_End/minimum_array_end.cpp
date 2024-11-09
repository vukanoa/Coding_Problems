#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3133) Minimum Array End
    ===========================

    ============
    Description:
    ============

    You are given two integers n and x. You have to construct an array of
    positive integers nums of size n where for every 0 <= i < n - 1, nums[i +
    1] is greater than nums[i], and the result of the bitwise AND operation
    between all elements of nums is x.

    Return the minimum possible value of nums[n - 1].

    =========================================
    FUNCTION: long long minEnd(int n, int x);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, x = 4
    Output: 6
    Explanation:
    nums can be [4,5,6] and its last element is 6.

    --- Example 2 ---
    Input: n = 2, x = 7
    Output: 15
    Explanation:
    nums can be [7,15] and its last element is 15.


    *** Constraints ***
    1 <= n, x <= 10^8

*/

class Solution_TLE {
public:
    long long minEnd(int n, int x)
    {
        vector<int> nums;
        nums.push_back(x);

        vector<int> set_bit_idx;
        for (int i = 0; i < 32; i++)
        {
            if (x & (1 << i))
                set_bit_idx.push_back(i);
        }

        int i = 1;
        while (nums.size() < n)
        {
            int curr_num = x + i;

            int has_all_needed_set_bits = true;
            for (int j = 0; j < set_bit_idx.size(); j++)
            {
                if ( ! (curr_num & (1 << set_bit_idx[j])) )
                {
                    has_all_needed_set_bits = false;
                    break;
                }
            }

            if (has_all_needed_set_bits)
                nums.push_back(curr_num);

            i++;
        }

        return nums[n-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.80% */

/* Time  Complexity: O(1) (O(b) but integers have a fixes size (32 or 64)) */
/* Space Complexity: O(1)                                                  */
class Solution {
public:
    long minEnd(int n, int x)
    {
        long result    = x;
        long remaining = n - 1;
        long position  = 1;

        while (remaining)
        {
            if ( ! (x & position))
            {
                result |= (remaining & 1) * position;
                remaining >>= 1;
            }

            position <<= 1;
        }

        return result;
    }
};
