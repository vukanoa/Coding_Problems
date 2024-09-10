#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    191) Number Of 1 Bits
    ===========================

    ============
    Description:
    ============

    Write a function that takes the binary representation of an unsigned
    integer and returns the number of '1' bits it has (also known as the
    Hamming weight)

    Follow up: If this function is called many times, how would you optimize
    it?

    ========================================
    FUNCTION: int hammingWeight(uint32_t n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 00000000000000000000000000001011
    Output: 3
    Explanation: The input binary string
    00000000000000000000000000001011 has a total of three '1' bits.

    --- Example 2 ---
    Input: n = 00000000000000000000000010000000
    Output: 1
    Explanation: The input binary string
    00000000000000000000000010000000 has a total of one '1' bit.

    --- Example 3 ---
    Input: n = 11111111111111111111111111111101
    Output: 31
    Explanation: The input binary string
    11111111111111111111111111111101 has a total of thirty one '1' bits.

    *** Constraints ***
    The input must be a binary string of length 32.

*/




/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanaotry. Just look at the code.

    How do we know if the last bit is 1 or 0?
    We simple do a "%" operation and if the result is 1, the number certainly
    has bit 1 at the LowestSignificantBit.

    If that's the case, add 1 to "num" which we'll return at the very end.
    If that's NOT the case, add 0 to "num", i.e. do nothing.

    Before doing next iteration, we do a LOGICAL SHIFT of "n" to the right by
    one position.

    We do this 32 times since the input is type "int" which is on most 64bit
    architectures 32bits.

    Therefore, in order to process every single digit we have to process the
    LSB and then do a LSR.

    LSB - Least Significant Bit
    LSR - Logical Shift Right


        Example:  21
            0 0 0 1    0 1 0 1
            ^                ^
            |                |
          MSB               LSB


    MSB - Most Significant Bit

*/

/* Time  Beats:  100% */
/* Space Beats: 74.56% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int num = 0;

        for (int i = 0; i < 32; i++)
        {
            num += n % 2 ? 1 : 0;
            n >>= 1;
        }

        return num;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/


/* Time  Beats:   100% */
/* Space Beats: 28.56% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int hammingWeight(uint32_t n)
    {
        int count = 0;

        while (n)
        {
            count += n & 1;
            n >>= 1;
        }

        return count;
    }
};
