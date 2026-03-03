/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    1545) Find Kth Bit in Nth Binary String
    =======================================

    ============
    Description:
    ============

    Given two positive integers n and k, the binary string Sn is formed as
    follows:

        S1 = "0"
        Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1

    Where + denotes the concatenation operation, reverse(x) returns the
    reversed string x, and invert(x) inverts all the bits in x (0 changes to 1
    and 1 changes to 0).

    For example, the first four strings in the above sequence are:

        S1 = "0"
        S2 = "011"
        S3 = "0111001"
        S4 = "011100110110001"

    Return the kth bit in Sn. It is guaranteed that k is valid for the given n.

    ========================================
    FUNCTION: char findKthBit(int n, int k);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, k = 1
    Output: "0"
    Explanation: S3 is "0111001".
    The 1st bit is "0".

    --- Example 2 ---
    Input: n = 4, k = 11
    Output: "1"
    Explanation: S4 is "011100110110001".
    The 11th bit is "1".


    *** Constraints ***
    1 <= n <= 20
    1 <= k <= 2n - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  64.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    char findKthBit(int n, int k)
    {
        // Base case: When n = 1, the binary string is "0"
        if (n == 1)
            return '0';

        // Find the length of the current string Sn, which is 2^n - 1
        int length = (1 << n) - 1;

        // Find the middle position
        int mid = length / 2 + 1;

        // If k is the middle position, return '1'
        if (k == mid)
            return '1';

        // If k is in the first half, find the bit in Sn-1
        if (k < mid)
            return findKthBit(n - 1, k);

        // If k is in the second half, find the bit in Sn-1 and invert it
        return findKthBit(n - 1, length - k + 1) == '0' ? '1' : '0';
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.07% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation {
public:
    char findKthBit(int n, int k)
    {
        // Find the position of the rightmost set bit in k
        // This helps determine which "section" of the string we're in
        int position_in_section = k & -k;

        // Determine if k is in the inverted part of the string
        // This checks if the bit to the left of the rightmost set bit is 1
        bool is_inverted_part = ((k / position_in_section) >> 1 & 1) == 1;

        // Determine if the original bit (before any inversion) would be 1
        // This is true if k is even (i.e., its least significant bit is 0)
        bool original_bit_is_one = (k & 1) == 0;

        if (is_inverted_part)
        {
            // If we're in the inverted part, we need to flip the bit
            return original_bit_is_one ? '0' : '1';
        }

        // If we're NOT in the inverted part, return the original bit
        return original_bit_is_one ? '1' : '0';
    }
};
