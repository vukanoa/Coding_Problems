#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =====================================
    1822) Sign of the Product of an Array
    =====================================

    ============
    Description:
    ============

    There is a function signFunc(x) that returns:

        1 if x is positive.
        -1 if x is negative.
        0 if x is equal to 0.

    You are given an integer array nums. Let product be the product of all
    values in the array nums.

    Return signFunc(product).

    ===========================================
    FUNCTION: int arraySign(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-1,-2,-3,-4,3,2,1]
    Output: 1
    Explanation: The product of all values in the array is 144, and
                 signFunc(144) = 1

    --- Example 2 ---
    Input: nums = [1,5,0,2,-3]
    Output: 0
    Explanation: The product of all values in the array is 0, and signFunc(0) =
                 0

    --- Example 3 ---
    Input: nums = [-1,1,-1,1,-1]
    Output: -1
    Explanation: The product of all values in the array is -1, and signFunc(-1)
                 = -1


    *** Constraints ***
    1 <= nums.length <= 1000
    -100 <= nums[i] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    If at any point of iterating through vector "nums", we stumble upon an
    element 0, then we must immediately return 0 as a result since product will
    always be 0.

    On the other hand, if there are no zeroes in vector "nums", then we must
    count how many negative integers are there.

    Since we need to return if the product of the entire array is positive or
    negative, we only flip the sign whenever we see a negative value.

    At the beggining "sign" variable is positive.

    Example:
        nums = [1, 2, -3, 2, -5]
                0  1   2  3   4

    We will flip the "sign" at index 3 to become -1(i.e. negative) and then we
    will, again, flip it once we reach index 5. Now it will become positive
    again(i.e. 1).

    We could improve this Solution by XOR-in with 0x01 instead of multiplying
    since "mul" operation is expensive.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int arraySign(vector<int>& nums)
    {
        int sign = 1;
        for (int& num : nums)
        {
            if (num == 0)
                return 0;
            else if (num < 0)
                sign *= -1; // "mul" operation in CPU(if not optimized)
        }

        return sign;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one should, in theory, run faster than the first Solution in this file
    since we are using "xor" operation instead of "mul" at the level of CPU.

    However, since the compiler will optimize, we don't have to worry about
    these kinds of things anymore.

*/

/* Time  Beats: 70.06% */
/* Space Beats:  5.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_XOR {
public:
    int arraySign(vector<int>& nums)
    {
        int sign = 1;
        for (int& num : nums)
        {
            if (num == 0)
                return 0;
            else if (num < 0)
                sign ^= 0x01; // "xor" operation in CPU(faster than "mul")
        }

        return sign > 0 ? 1 : -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one should, in theory, run faster because we are using "add" operation
    instead of "mul".

    However, since the compiler will optimize, we don't have to worry about
    these kinds of things anymore.

*/

/* Time  Beats: 70.06% */
/* Space Beats:  5.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Count_Negatives {
public:
    int arraySign(vector<int>& nums)
    {
        int negative_cnt = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
                return 0;
            else if (nums[i] < 0)
                negative_cnt++; // "add" operation in CPU (faster than "mul")
        }

        return negative_cnt % 2 == 0 ? 1 : -1;
    }
};
