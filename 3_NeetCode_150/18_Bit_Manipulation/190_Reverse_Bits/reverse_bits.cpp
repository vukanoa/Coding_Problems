/*
    ============
    === EASY ===
    ============

    ===========================
    190) Reverse Bits
    ===========================

    ============
    Description:
    ============

    Reverse bits of a given 32 bits unsigned integer.

    Follow up:
    If this function is called many times, how would you optimize it?

    ===========================================
    FUNCTION: uint32_t reverseBits(uint32_t n);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 00000010100101000001111010011100
    Output:    964176192 (00111001011110000010100101000000)
    Explanation: The input binary string 00000010100101000001111010011100
    represents the unsigned integer 43261596, so return 964176192 which its
    binary representation is 00111001011110000010100101000000


    --- Example 2 ---
    Input: n = 11111111111111111111111111111101
    Output:   3221225471 (10111111111111111111111111111111)
    Explanation: The input binary string 11111111111111111111111111111101
    represents the unsigned integer 4294967293, so return 3221225471 which its
    binary representation is 10111111111111111111111111111111


    --- Example 3 ---


    *** Constraints ***
    The input must be a binary string of length 32

*/

/*
    ------------
    --- IDEA ---
    ------------

    THe most straightforward Solution out of all inside this file.

*/

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_0 {
public:
    int reverseBits(int n)
    {
        int result = 0;
        for (int ith_bit = 31; ith_bit >= 0; ith_bit--)
        {
            if (n & (1 << ith_bit))                // if (ith_bit in n is SET)
                result |= (1 << (31 - ith_bit));
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Idea is pretty simple, but you have to go through the code and you'll get
    it. No amount of explanation will explain it better.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.45% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
#include <cstdint>
class Solution_1 {
public:
    int reverseBits(int n)
    {
        int result = 0x00000000; // "int" is 32-bit on 64bit architecture

        for (int i = 0; i < 32; i++)
        {
            int last_bit = n & 1;

            result <<= 1;
            result |= last_bit;

            n >>= 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.20% */
/* Space Beats: 72.86% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int reverseBits(int n)
    {
        return my_reversal(n, 32);
    }

private:
    uint32_t my_reversal(int n, int bits)
    {
        if (bits == 1)
            return n & 1U;

        int half = bits >> 1;

        uint32_t mask = (1U << half) - 1U;

        uint32_t low  = n & mask;
        uint32_t high = n >> half;

        return (my_reversal(low, half) << half) | my_reversal(high, half);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/


/* Time  Beats: 100.00% */
/* Space Beats:  73.73% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int reverseBits(int n)
    {
        int result = 0;

        for (int i = 0; i < 32; i++)
        {
            result = result | ((n & 1) << (31 - i));

            n >>= 1; // Right shift
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_4 {
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t result = n;
        result = (result >> 16) | (result << 16);
        result = ((result & 0xff00ff00) >> 8) | ((result & 0x00ff00ff) << 8);
        result = ((result & 0xf0f0f0f0) >> 4) | ((result & 0x0f0f0f0f) << 4);
        result = ((result & 0xcccccccc) >> 2) | ((result & 0x33333333) << 2);
        result = ((result & 0xaaaaaaaa) >> 1) | ((result & 0x55555555) << 1);

        return result;
    }
};
