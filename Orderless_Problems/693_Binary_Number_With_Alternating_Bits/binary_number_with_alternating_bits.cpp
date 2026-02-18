/*
    ============
    === EASY ===
    ============

    ========================================
    693) Binary Number with Alternating Bits
    ========================================

    ============
    Description:
    ============

    Given a positive integer, check whether it has alternating bits: namely, if
    two adjacent bits will always have different values.

    =========================================
    FUNCTION: bool hasAlternatingBits(int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: true
    Explanation: The binary representation of 5 is: 101

    --- Example 2 ---
    Input: n = 7
    Output: false
    Explanation: The binary representation of 7 is: 111.

    --- Example 3 ---
    Input: n = 11
    Output: false
    Explanation: The binary representation of 11 is: 1011.


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/


#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Initially set the "prev_bit" to be the OPPOSITE of the LSB(Least
    Significant Bit), that way our while loop won't break immediately.

    Then the "curr_bit" is always obtained by doing: n & 1.

    If prev_bit and curr_bit are the same, then immediately return false.

    Otherwise, set prev_bit to be curr_bit and right-shift our n.

    Thath's all.

*/

/* Time  Complexity: O(1) */ // Because log(2^32 - 1) is ~10
/* Space Complexity: O(1) */
class Solution {
public:
    bool hasAlternatingBits(int n)
    {
        int prev_bit = ! (n & 1); // Initially it's the OPPOSITE of LSB

        while (n > 0)
        {
            int curr_bit = n & 1;

            if (curr_bit == prev_bit)
                return false;

            prev_bit = curr_bit;
            n >>= 1;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we first form a binary string, then we find the index of the leftmost
    set bit.

    Then simply check if that string has alternating characters.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  7.04% */

/* Time  Complexity: O(1) */ // Because log(2^32 - 1) is ~10
/* Space Complexity: O(1) */
class Solution_String {
public:
    bool hasAlternatingBits(int n)
    {
        string bin_str;
        bin_str.reserve(32); // To prevent reallocations

        for (int i = 31; i >= 0; i--)
            bin_str += (n & (1 << i)) ? '1' : '0';

        /* We don't actually need to reverse it. Think about it.  */

        int leftmost_set_bit_idx = bin_str.find('1');
        leftmost_set_bit_idx++;

        for (unsigned i = leftmost_set_bit_idx; i < bin_str.length(); i++)
        {
            if (bin_str[i-1] == bin_str[i])
                return false;
        }

        return true;
    }
};
