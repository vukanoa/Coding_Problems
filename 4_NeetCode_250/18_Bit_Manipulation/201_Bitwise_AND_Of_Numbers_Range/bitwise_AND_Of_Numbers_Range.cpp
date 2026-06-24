/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    201) Bitwise AND of Numbers Range
    =================================

    ============
    Description:
    ============

    Given two integers left and right that represent the range [left, right],
    return the bitwise AND of all numbers in this range, inclusive.

    ===================================================
    FUNCTION: int rangeBitwiseAnd(int left, int right);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: left = 5, right = 7
    Output: 4

    --- Example 2 ---
    Input: left = 0, right = 0
    Output: 0

    --- Example 3 ---
    Input: left = 1, right = 2147483647
    Output: 0


    *** Constraints ***
    0 <= left <= right <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    The answer is the common prefix of left and right in their binary
    representation:

    For example:

        0101 (left)
        0111 (right)
        0100 (answer)

    In a nutshell:
        Keep shifting right to find the common prefix

*/

/* Time  Beats: 81.50% */
/* Space Beats: 79.74% */

/* Time  Complexity: O(log(min(left, right))) */
/* Space Complexity: O(1)                     */
class Solution {
public:
    int rangeBitwiseAnd(int left, int right)
    {
        int shifts = 0;
        while (right != left)
        {
            right >>= 1;
            left  >>= 1;

            shifts++;
        }

        return left << shifts;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We actually do NOT need to be shifting both numbers, instead what we can do
    is simply keep clearing the rightmost set bit of "right" until it becomes
    LESS THAN OR EQUALS to the "left".

    To do this efficiently there is a trick for that:

        n & (n-1)

    clears the LOWEST SET BIT.

*/

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int rangeBitwiseAnd(int left, int right)
    {
        while (left < right)
            right &= (right - 1);

        return right;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    0th bit alternates every 1 number.
    1st bit alternates every 2 numbers.
    2nd bit alternates every 4 numbers.
    3rd bit alternates every 8 numbers.
    ...                      ^
                        _____|
                        |
                        |
                        |
    We'll call this gap_size.

    Now we need to see where inside the current gap we are. For example, if
    we look at the 3rd bit from the right(0-indexed) of number 5, it needs 3
    more numbers and then the bit flips.

    We'll call this "distance_until_alteration" and it's calculated by taking
    the "gap_size" and subtracting (left % gap_size).

    Now that we have "distance_until_alteration" we need to see if our input
    range is GREATER THAN OR EQUALS to the "distance_until_alteration".

    If it is within our input range, then this bit is destined to ALTERNATE,
    therefore this i-th bit will certainly be 0.

    Otherwise, we put which ever i-th bit is in our "left" number.

        0 0 0 0    0
        0 0 0 1    1
        0 0 1 0    2
        0 0 1 1    3
        0 1 0 0    4
        0 1 0 1    5        
        0 1 1 0    6        
        0 1 1 1    7        
        1 0 0 0    8        
        1 0 0 1    9        
        1 0 1 0   10       
        1 0 1 1   11       
        1 1 0 0   12       
        1 1 0 1   13       
        1 1 1 0   14       
        1 1 1 1   15       

*/

/* Time  Beats: 30.04% */
/* Space Beats: 47.17% */

/* Time  Complexity: O(31)  -->  O(1) */ // Formally O(log(min(left, right))) 
/* Space Complexity: O(1)             */
class Solution_3 {
public:
    int rangeBitwiseAnd(int left, int right)
    {
        if (left == right)
            return left;

        int result = 0;
        long long input_range = 1LL * right - left;

        for (int i = 1; i < 32; i++)
        {
            long long gap_size  = 1LL << i;
            long long distance_until_alteration = gap_size - (left % gap_size);

            if (input_range >= distance_until_alteration)
            {
                result = result | (0 << i); // Because this bit is ALTERNATING!
            }
            else
            {
                result |= left & (1 << i);
            }
        }

        return result;
    }
};
