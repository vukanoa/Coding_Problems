/*
    ============
    === EASY ===
    ============

    ===================================
    3536) Maximum Product of Two Digits
    ===================================

    ============
    Description:
    ============

    You are given a positive integer n.

    Return the maximum product of any two digits in n.

    =====
    Note: You may use the same digit twice if it appears more than once in n.
    =====

    ================================
    FUNCTION: int maxProduct(int n);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 31
    Output: 3
    Explanation:
        The digits of n are [3, 1].
        The possible products of any two digits are: 3 * 1 = 3.
        The maximum product is 3.


    --- Example 2 ---
    Input: n = 22
    Output: 4
    Explanation:
        The digits of n are [2, 2].
        The possible products of any two digits are: 2 * 2 = 4.
        The maximum product is 4.


    --- Example 3 ---
    Input: n = 124
    Output: 8
    Explanation:
        The digits of n are [1, 2, 4].
        The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8.
        The maximum product is 8.


    *** Constraints ***
    10 <= n <= 10^9

*/

#include <cstdint>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  43.75% */

/* Time  Complexity: O(log10(N)) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int maxProduct(int n)
    {
        int one = 0;
        int two = 0;

        while (n > 0)
        {
            int digit = n % 10;
            n /= 10;

            if (digit >= one)
            {
                two = one;
                one = digit;
            }
            else if (digit >= two)
            {
                two = digit;
            }
        }

        return one * two;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We use one unsigned 64−bit integer as a frequency table for the digits.

    Each digit is assigned a 4−BIT BLOCK, allowing us to store its frequency
    independently.

          9    8    7    6    5    4    3    2    1
        0000 0000 0000 0000 0000 0000 0000 0000 0000
           ^                        ^    ^         ^
           |                        |    |         |
           |                        |    |         |
          36th          ...       16th  12th      0th
          bit                     bit   bit       bit



    For each extracted digit(i.e.: n % 10), we increase its counter by adding:

        1ULL << (4 * digit)

    Example:

        n = 87486538

    we increase the count for each digit:

        mask += 1ULL << (digit * 4) 

          9    8    7    6    5    4    3    2    1
        0000 0001 0000 0000 0000 0000 0000 0000 0000        n = 87486538
                ^                                                      #
                |
               32nd
               bit

          9    8    7    6    5    4    3    2    1
        0000 0001 0000 0000 0000 0000 0001 0000 0000        n = 8748653
                                         ^                            #
                                         |
                                        12th
                                        bit

          9    8    7    6    5    4    3    2    1
        0000 0001 0000 0000 0001 0000 0001 0000 0000        n = 874865
                               ^                                     #
                               |
                              24th
                              bit


          9    8    7    6    5    4    3    2    1
        0000 0001 0000 0001 0001 0000 0001 0000 0000        n = 87486
                          ^                                         #
                          |
                        28th
                         bit

          9    8    7    6    5    4    3    2    1
        0000 0010 0000 0001 0001 0000 0001 0000 0000        n = 8748
               ^                                                   #
               |
              33rd
              bit

          9    8    7    6    5    4    3    2    1
        0000 0011 0000 0001 0001 0001 0001 0000 0000        n = 874
                                    ^                             #
                                    |
                                   16th
                                   bit


          9    8    7    6    5    4    3    2    1
        0000 0011 0001 0001 0001 0001 0001 0000 0000        n = 87
                     ^                                           #
                     |
                    28th
                    bit

          9    8    7    6    5    4    3    2    1
        0000 0011 0001 0001 0001 0001 0001 0000 0000        n = 8
                ^                                               #
                |
               32rd
               bit



    After extracting ALL digits, the HIGHEST SET BIT belongs to the largest
    digit that appears in this mask.

    We extract this digit using it's bit length or (bit_width),

          9    8    7    6    5    4    3    2    1
        0000 0011 0001 0001 0001 0001 0001 0000 0000
             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                               |
                               |
                            bit length

    Then diving it by 4, we'll get 8 which is indeed a largest digit in n.

          9    8    7    6    5    4    3    2    1
        0000 0011 0001 0001 0001 0001 0001 0000 0000  
             ^^^^

    We then remove one occurrence of that digit by subtracting:

        1ULL << (4 * digit)

    and repeat the same process to obtain the second largest digit.
    In this case, that's also 8.

    At the end we just return the product of these two digits:

        return largest * second_largest;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.34% */

/* Time  Complexity: O(log10(N)) */
/* Space Complexity: O(1)        */
class Solution_Bit_manipulation {
public:
    int maxProduct(int n)
    {
        uint64_t mask = 0;

        while (n)
        {
            int digit = n % 10;
            mask += (1ULL << (digit * 4));
            n /= 10;
        }

        int largest        = (bit_width(mask) - 1) / 4;
        mask -= (1ULL << (largest * 4));
        int second_largest = (bit_width(mask) - 1) / 4;

        return largest * second_largest;
    }

    int bit_width(uint64_t x)
    {
        return x ? 64 - __builtin_clzll(x) : 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as two above, implemented differently.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.34% */

/* Time  Complexity: O(log10(N)) */
/* Space Complexity: O(1)        */
class Solution_Bit_manipulation_2 {
public:
    int maxProduct(int n)
    {
        uint64_t mask = 0;

        while (n)
        {
            int digit = n % 10;
            mask += (1ULL << (digit * 4));
            n /= 10;
        }

        // (63 - __builtin_clzll(mask))  returns an INDEX of a highest SET bit
        // (0-based):
        //
        //     1 (001) -> 0
        //     2 (010) -> 1
        //     3 (011) -> 1
        //     4 (100) -> 2
        int largest        = (63 - __builtin_clzll(mask)) / 4;
        mask -= (1ULL << (largest * 4));
        int second_largest = (63 - __builtin_clzll(mask)) / 4;

        return largest * second_largest;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as two above, implemented differently.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.34% */

/* Time  Complexity: O(log10(N)) */
/* Space Complexity: O(1)        */
class Solution_Bit_Manipulation_3 {
public:
    int maxProduct(int n)
    {
        uint64_t mask = 0;

        while (n)
        {
            int digit = n % 10;
            mask += (1ULL << (digit << 2));
            n /= 10;
        }

        int largest        = (63 - __builtin_clzll(mask)) >> 2;
        mask -= (1ULL << (largest << 2));
        int second_largest = (63 - __builtin_clzll(mask)) >> 2;

        return largest * second_largest;
    }
};
