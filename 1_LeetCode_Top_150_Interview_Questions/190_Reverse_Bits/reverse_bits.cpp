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

    Idea is pretty simple, but you have to go through the code and you'll get
    it. No amount of explanation will explain it better.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.45% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
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
