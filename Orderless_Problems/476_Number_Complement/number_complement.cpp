#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    476) Number Complement
    ===========================

    ============
    Description:
    ============

    The complement of an integer is the integer you get when you flip all the
    0's to 1's and all the 1's to 0's in its binary representation.

        For example, The integer 5 is "101" in binary and its complement is
        "010" which is the integer 2.

    Given an integer num, return its complement.

    ======================================
    FUNCTION: int findComplement(int num);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 5
    Output: 2
    Explanation: The binary representation of 5 is 101 (no leading zero bits),
                 and its complement is 010. So you need to output 2.

    --- Example 2 ---
    Input: num = 1
    Output: 0
    Explanation: The binary representation of 1 is 1 (no leading zero bits),
                 and its complement is 0. So you need to output 0.


    *** Constraints ***
    1 <= num < 2^31

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.08% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findComplement(int num) {

        // 00 00 00 ... 00 10  ==> Original "num"
        // 11 11 11 ... 11 01  ==> After using ~ on "num"

        int count = 0;
        int num_copy = num;

        while (num / 2 > 0)
        {
            count++;
            num = num / 2;
        }

        int and_val = (1 << count) - 1;

        return ~num_copy & and_val;
    }
};
