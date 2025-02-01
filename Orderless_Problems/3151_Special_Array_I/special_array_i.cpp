/*
    ============
    === EASY ===
    ============

    ===========================
    3151) Special Array I
    ===========================

    ============
    Description:
    ============

    An array is considered special if every pair of its adjacent elements
    contains two numbers with different parity.

    You are given an array of integers nums. Return true if nums is a special
    array, otherwise, return false.

    =================================================
    FUNCTION: bool isArraySpecial(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1]
    Output: true
    Explanation:
    There is only one element. So the answer is true.

    --- Example 2 ---
    Input: nums = [2,1,4]
    Output: true
    Explanation:
    There is only two pairs: (2,1) and (1,4), and both of them contain numbers
    with different parity. So the answer is true.

    --- Example 3 ---
    Input: nums = [4,3,1,6]
    Output: false
    Explanation:
    nums[1] and nums[2] are both odd. So the answer is false.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Description tries to obscure it, but they essentially want our array to
    be alternating by parity. That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  25.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isArraySpecial(vector<int>& nums)
    {
        const int N = nums.size();

        for (int i = 1; i < N; i++)
        {
            if (nums[i] % 2 != 0) // Odd
            {
                if (nums[i-1] % 2 != 0)
                    return false;
            }
            else // Even
            {
                if (nums[i-1] % 2 == 0)
                    return false;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can write the above approach in a much more concice and elegant way by
    using bitwise operations.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.67% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_XOR {
public:
    bool isArraySpecial(vector<int>& nums)
    {
        const int N = nums.size();

        for (int i = 1; i < N; i++)
        {
            if (((nums[i-1] & 1) ^ (nums[i] & 1)) == 0)
                return false;
        }

        return true;
    }
};
