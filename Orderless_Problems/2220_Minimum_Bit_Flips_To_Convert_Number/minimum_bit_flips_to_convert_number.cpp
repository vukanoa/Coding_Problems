#include <iostream>

/*
    ============
    === EASY ===
    ============

    ==========================================
    2220) Minimmum Bit Flips to Convert Number
    ==========================================

    ============
    Description:
    ============

    A bit flip of a number x is choosing a bit in the binary representation of
    x and flipping it from either 0 to 1 or 1 to 0.

        For example, for x = 7, the binary representation is 111 and we may
        choose any bit (including any leading zeros not shown) and flip it. We
        can flip the first bit from the right to get 110, flip the second bit
        from the right to get 101, flip the fifth bit from the right (a leading
        zero) to get 10111, etc.

    Given two integers start and goal, return the minimum number of bit flips
    to convert start to goal.

    ===============================================
    FUNCTION: int minBitFlips(int start, int goal);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: start = 10, goal = 7
    Output: 3
    Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
    - Flip the first bit from the right: 1010 -> 1011.
    - Flip the third bit from the right: 1011 -> 1111.
    - Flip the fourth bit from the right: 1111 -> 0111.
    It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.


    --- Example 2 ---
    Input: start = 3, goal = 4
    Output: 3
    Explanation: The binary representation of 3 and 4 are 011 and 100 respectively. We can convert 3 to 4 in 3 steps:
    - Flip the first bit from the right: 011 -> 010.
    - Flip the second bit from the right: 010 -> 000.
    - Flip the third bit from the right: 000 -> 100.
    It can be shown we cannot convert 3 to 4 in less than 3 steps. Hence, we return 3.


    *** Constraints ***
    0 <= start, goal <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    If you don't know what is "bitwise XOR operator", learn about that first.

    XOR explanation:

             0  -------->  bit_1                    1  -------->  bit_1
        XOR  0  -------->  bit_2               XOR  1  -------->  bit_2
        ------                                 ------
             0  ---> Result                         0  ---> Result





             1  -------->  bit_1                     0  -------->  bit_1
        XOR  0  -------->  bit_2                XOR  1  -------->  bit_2
        ------                                  ------
             1  ---> Result                          1  ---> Result




    If two bits are EQUAL,     the result is 0.
    If two bits are DIFFERENT, the result is 1.


    Each time we XOR two NUMBER(not specific bits, but whole numbers), if that
    new number that we got as a result is an ODD number, then that means the
    LAST bit is certainly 1.

    If it's an EVEN number, that means that the last bit is certainly 0.


    So we can XOR the both numbers and we'll check if the last bit is EQUAL or
    different.

    After that we do a Logical Shift Right(meaning the new leftmost bit is
    always 0 after the shift to the right)

        Example:

                101011 |
            >>
            ------------
                010101 | 1
                ^        ^
                |        |
                |       This one is OUT
                |
            This one is the new leftmost bit. It's always 0 after the shift.



*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

    start = 1010    // 10
    goal  = 0111    // 7


    ==========================================================================

            1010   // 10
      XOR   0111   // 7
      ----------
            1101   // 13, since it is an ODD number we know that start's and
                          goal's last bit DIFFER, therefore: count++;


           1010   // 10
      >>
      ----------
           0101   // 5(but don't worry about the human value)


           0111   // 10
      >>
      ----------
           0011   // 3(but don't worry about the human value)

    ==========================================================================

            0101   // 5
      XOR   0111   // 3
      ----------
            0010   // 2, since it is an EVEN number we know that start's and
                         goal's last bit are EQUAL, therefore don't do anything


           0101   // 5
      >>
      ----------
           0010   // 2(but don't worry about the human value)


           0011   // 3
      >>
      ----------
           0001   // 1(but don't worry about the human value)

    ==========================================================================

    You get the idea.
    Once you look at the code, everything will be clear.

    int is a 4B, i.e. 32-bit size on most 64-bit architectures.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.87% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minBitFlips(int start, int goal) {

        int count = 0;

        for (int i = 0; i < 32; i++)
        {
            count += (start ^ goal) % 2 ? 1 : 0;

            start >>= 1;
            goal  >>=1;
        }

        return count; // 44.87
    }
};
