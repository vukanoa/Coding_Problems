/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    2749) Minimum Operations to Make the Integer Zero
    =================================================

    ============
    Description:
    ============

    You are given two integers num1 and num2.

    In one operation, you can choose integer i in the range [0, 60] and
    subtract 2i + num2 from num1.

    Return the integer denoting the minimum number of operations needed to make
    num1 equal to 0.

    If it is impossible to make num1 equal to 0, return -1.

    =====================================================
    FUNCTION: int makeTheIntegerZero(int num1, int num2);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = 3, num2 = -2
    Output: 3
    Explanation: We can make 3 equal to 0 with the following operations:
    - We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
    - We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
    - We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
    It can be proven, that 3 is the minimum number of operations that we need
    to perform.

    --- Example 2 ---
    Input: num1 = 5, num2 = 7
    Output: -1
    Explanation: It can be proven, that it is impossible to make 5 equal to 0
    with the given operation.


    *** Constraints ***
    1 <= num1 <= 10^9
    -10^9 <= num2 <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    __builtin_popcount()  is a built-in function of GCC/Clang compiler.
    This function is used to count the number of set bits in an unsigned
    integer. In other words, it counts the number of 1’s in the binary form of
    a positive integer.

    You do NOT have to include ANY header

        __builtin_popcount(unsigned int number);

    Essentially: Count the number of SET bits in a number in its binary
                 representation.


    Input: n = 5     // (5 == b0000..00101)
    Output: 2

*/

/* Time  Beats:  4.13% */
/* Space Beats: 85.95% */

/* Time  Complexity: O(log(num1)) */
/* Space Complexity: O(1)         */
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2)
    {
        int operation_count = 1;

        while (true)
        {
            long long remaining_val = num1 - static_cast<long long>(num2) * operation_count;

            if (remaining_val < operation_count)
                return -1;

            if (operation_count >= __builtin_popcountll(remaining_val))
                return operation_count;

            operation_count++;
        }

        return -1;
    }
};
