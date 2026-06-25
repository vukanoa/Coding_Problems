/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3133) Minimum Array End
    ===========================

    ============
    Description:
    ============

    You are given two integers n and x. You have to construct an array of
    positive integers nums of size n where for every 0 <= i < n - 1, nums[i +
    1] is greater than nums[i], and the result of the bitwise AND operation
    between all elements of nums is x.

    Return the minimum possible value of nums[n - 1].

    =========================================
    FUNCTION: long long minEnd(int n, int x);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, x = 4
    Output: 6
    Explanation:
    nums can be [4,5,6] and its last element is 6.

    --- Example 2 ---
    Input: n = 2, x = 7
    Output: 15
    Explanation:
    nums can be [7,15] and its last element is 15.


    *** Constraints ***
    1 <= n, x <= 10^8

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Can be considered a "Brute Force". Kind of.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Linear_Simple {
public:
    long long minEnd(int n, int x)
    {
        long long result = x;

        while (--n > 0) // Loop will execute exactly (n-1) times
            result = (result + 1) | x;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    #################
    ### Intuition ###
    #################

    The idea is much simpler than you would think.

    First it's obvious that we're NOT allowed to change ANY of the
    SET-bits(i.e. 1s) of x because in order to have x as a result of bitwise
    AND-ing all of the numbers, you need all the SET-bits of x in EACH number
    to also be SET-bits(i.e. 1s).

    That's why we assign result to be x, at the beginning.

    We want to encode the number (n-1), in its binary form, within the ALLOWED
    slots, i.e. the slots of x that are 0.

    Now we only need to go through 64 bits(slots) of x from the LSB (Least
    Significant Bit) to MSB (Most Significant Bit) and any time a certain bit
    of x is SET(i.e. 1) we SKIP doing anything to result since that bit
    MUST(!!) remain unchanged!

    However, if the i-th bit of x is ineed 0, then we can fill it with the last
    bit of (n-1) that we still haven't encoded yet.

    Let's see an example:

          x = 23  (000.. 0001 0111)
          n = 38
        n-1 = 37  (000.. 0010 0101)

    (n-1) = 37, i.e. (000.. 0010 0101) is what we are trying to encode within
    the ALLOWED slots of x.

    Character '#' represents the slot(bit) of x we must NOT change! 
    (since it is a SET-bit)

    0000  ...  0000  00#0  0###
                       ^    ^^^
                       |    |||
                       |    |||
                       --------
                         |
                      These bits must NOT be changed!

    Now you tell me--How do we simly encode the number (n-1)=37 in binary
    within the ALLOWED slots?

    In the same exact way as any binary representation! We just encode the bits
    of (n-1)=37 into these ALLOWED slots of x, i.e. of the result.



    ################
    ### Approach ###
    ################

    We go through 64 bits of x starting from LSB and going to MSB and if a bit
    is SET(i.e. 1), we skip doing anything since we're NOT allowed to change
    that bit of the result.

    However, if i-th bit of x is CLEAR-bit(i.e. 0), then we encode the last bit
    of the binary representation of (n-1) and we shift (n-1) to the right by 1
    since we have just encoded this bit and can proceed to the next one.

    At the end just return the result.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  82.63% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation__Elegant {
public:
    long long minEnd(int n, int x)
    {
        long long goal = 1LL * n - 1; // The number we're trying to encode in
                                      // ALLOWED slots

        long long result = x;
        for (int i = 0; i < 64; i++)
        {
            if (x & (1LL << i))
                continue; // Since those SET-bits must remain UNCHANGED!

            result |= (goal & 1) << i;
            goal >>= 1;
        }

        return result;
    }
};
