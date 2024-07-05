#include <iostream>

/*
    ============
    === EASY ===
    ============

    ====================================
    405) Convert a Number to Hexadecimal
    ====================================

    ============
    Description:
    ============

    Given an integer num, return a string representing its hexadecimal
    representation. For negative integers, two’s complement method is used.

    All the letters in the answer string should be lowercase characters, and
    there should not be any leading zeros in the answer except for the zero
    itself.

    Note: You are not allowed to use any built-in library method to directly
    solve this problem.

    ================================
    FUNCTION: string toHex(int num);
    ================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 26
    Output: "1a"

    --- Example 2 ---
    Input: num = -1
    Output: "ffffffff"

    *** Constraints ***
    -2^31 <= num <= 2^31 - 1

*/

/* Time  Beats: 100.00% */
/* Space Beats:  24.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string toHex(int num)
    {
        // To handle negative numbers
        unsigned int our_num = num;

        std::string result_str;

        // We will pick from this set of characters
        char all_hexa_values[17] = "0123456789abcdef";

        // While our number exists, convert it into base 16.
        // We are going from left to right, so we need to reverse our result
        // when we return it.
        do {
            result_str += all_hexa_values[our_num % 16];
            our_num /= 16;
        } while (our_num);

        return {result_str.rbegin(), result_str.rend()};
    }
};
