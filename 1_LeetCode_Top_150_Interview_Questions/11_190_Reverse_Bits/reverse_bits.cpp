#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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


/* Time  Beats: 55.10% */
/* Space Beats:  5.73% */

/*
    Time  Complexity: O(1)
    Since it's always 32 bits. We always have to go through the 32 bits no
    matter how big is the input, since we are told it is within the bounds of
    an unsigned integer.
*/
/* Space Complexity: O(n) */
class Solution {
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t sum = 0;
        int degree = 31;

        std::vector<int> bits;

        while (degree >= 0)
        {
            if (sum + std::pow(2, degree) <= n)
            {
                sum += std::pow(2, degree);
                bits.push_back(1);
            }
            else
                bits.push_back(0);

            degree--;
        }


        std::reverse(bits.begin(), bits.end());


        degree = 31;
        uint32_t value = 0;

        for (int i = 0; i < 32; i++)
        {
            if (bits[i] == 1)
                value += bits[i] * std::pow(2, degree);

            degree--;
        }

        return value;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Idea is pretty simple, but you have to go through the code and you'll get
    it. No amount of explanation will explain it better.

*/

/* Time  Beats: 100% */
/* Space Beats: 71.9% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    uint32_t reverseBits(uint32_t n)
    {
        uint32_t rev = 0;

        for (int i = 0; i < 32; i++)
        {
            rev <<= 1;
            rev += n % 2;

            n >>= 1;
        }

        return rev;
    }
};
