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

    Doing a '&"(i.e. bitwise-AND operation) on the very last bit(i.e. LSB)
    gives us whether the number is ODD or EVEN.

    If the number is ODD, i.e. LSB is Set, i.e. LSB is 1, then count it in our
    "result" variable.

    If it's an EVEN number, then the result of doing a bitwise-AND will be 0.
    If we add 0 to our result then nothing will change and that's exactly the
    desired behavior.

    Before doing next iteration, we do a LOGICAL SHIFT of "n" to the RIGHT by
    one position, which is equvalent to dividing a number by 2.

    We do this 32 times since the input is type "int"which is--on most 64-bit
    architectures--exactly 32 bits.

    Therefore, in order to process every single bit we have to process the
    LSB (Least Significant Bit) and then do a LSR (Logical Shift Right).

        Example:  21
            0 0 0 1    0 1 0 1
            ^                ^
            |                |
          MSB               LSB


    MSB (Most Significant Bit)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.56% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int hammingWeight(int n)
    {
        int hamming_weight = 0;

        for (int i = 0; i < 32; i++)
        {
            hamming_weight += n & 1;

            n >>= 1; // LSR (Logical Shift Right) by one
        }

        return hamming_weight;
    }
};
