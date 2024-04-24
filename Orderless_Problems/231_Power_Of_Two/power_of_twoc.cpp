#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    231) Power of Two
    ===========================

    ============
    Description:
    ============

    Given an integer n, return true if it is a power of two. Otherwise, return
    false.

    An integer n is a power of two, if there exists an integer x such that n ==
    2x.

    Follow up: Could you solve it without loops/recursion?

    ===================================
    FUNCTION: bool isPowerOfTwo(int n);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1
    Output: true
    Explanation: 20 = 1

    --- Example 2 ---
    Input: n = 16
    Output: true
    Explanation: 24 = 16

    --- Example 3 ---
    Input: n = 3
    Output: false


    *** Constraints ***
    -2^31 <= n <= 2^31 - 1

*/

/*

    ----------------------
    --- 2's COMPLEMENT ---
    ----------------------

    Positive:
        1     - 0000 0001
        2     - 0000 0010
        4     - 0000 0100
        8     - 0000 1000
        16    - 0001 0000
        32    - 0010 0000
        64    - 0100 0000
        128   - 1000 0000

    Negative:
        -1     - 1111 1111
        -2     - 1111 1110
        -4     - 1111 1100
        -8     - 1111 1000
        -16    - 1111 0000
        -32    - 1110 0000
        -64    - 1100 0000
        -128   - 1000 0000

*/

/*
    ------------
    --- IDEA ---
    ------------

    And operation between multiple of 2 and next lower number will always give
    0 and otherwise it will never be 0.

    example 1: 8 & 7
    1000(8) & 0111(7) => 0000(0)

    example 1: = 10 & 9
    1010(10) & 1001(9) => 1000(8)
*/

/*
    ------------
    --- IDEA ---
    ------------

    First important thing just in case you didn't know:

        NEGATIVE NUMBER ARE NOT(!!!) CONSIDERED POWER OF TWO.

        -4 or -2 or -8 are NOT considered powers of two.


    Easiest way to do it is by starting with num=1 and multiplying it by 2
    as long as num is strictly less than n.

    Once it becomes greater or equal to n, then the only thing we have to do is
    return num == n;

    If it was exactly n, then n is INDEED a power of two. If it is greater than
    n, then it's definitely not.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.73% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Loop_1 {
public:
    bool isPowerOfTwo(int n)
    {
        long long num = 1;

        while (num < n)
            num <<= 1; // num *= 2

        return num == n;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is 2's Complement:

        -2147483648 = 1000 0000 0000 0000 0000 0000 0000 0000

                 -1 = 1111 1111 1111 1111 1111 1111 1111 1111

                 -2 = 1111 1111 1111 1111 1111 1111 1111 1110

                 -3 = 1111 1111 1111 1111 1111 1111 1111 1101

                 -4 = 1111 1111 1111 1111 1111 1111 1111 1100

    However, we don't really have to worry about negative integers at all.
    Let's read the important part of Description CAREFULLY:

    An integer n is a power of two, if there exists an integer x such that:
        n == 2^x.

    Since integers can be both positive and negative, that means x can be both
    positive or negative.

    If an exponent is NEGATIVE, then it NEVER will be equal to an integer.
    Think about it:
        2^(-4) ==> 1/2^4 ==> 1/16 ==> 0.0625

    Any NEGATIVE EXPONENT leads to NON-integer, therefore we will only consider
    exponents that are POSITIVE.

    Also, one important thing: NEGATIVE NUMBERS ARE NOT(!!!) CONSIDERED A POWER
    OF TWO.

    Now, we just try every power of two from [0 to 31] (inclusive), and if any
    2 to the power of i(i is starting at 0 and then goes all the way to 31),
    then we've found our answer to be true.

    False otherwise.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.16% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Loop_2 {
public:
    bool isPowerOfTwo(int n)
    {
        for(int i = 0; i < 31 ; i++)
        {
            int ith_pow_of_two = (1 << i); // (1 << i) <==> pow(2,i)

            if (ith_pow_of_two == n)
                return true;
        }

        return false;
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    This one is not easy to come up with, but it's not too difficult.

    First, as we've concluded above: NEGATIVE NUMBER ARE NOT CONSIDERED A POWER
    OF TWO.

    Therefore we only need to check if n > 0.

    Let's take a look at some examples:

        8 = 0000 0000 0000 0000 0000 0000 0000 1000
       16 = 0000 0000 0000 0000 0000 0000 0001 0000
       32 = 0000 0000 0000 0000 0000 0000 0010 0000
       64 = 0000 0000 0000 0000 0000 0000 0100 0000

    Let's consider, for example, number 64:

       64 = 0000 0000 0000 0000 0000 0000 0100 0000

    If we can somehow get this number:

       ?? = 0000 0000 0000 0000 0000 0000 0011 1111

    and &&(bitiwse AND) it with 64, then and only then would we get a result 0.
    If we get a 0, only then are we sure n is indeed a power of two.

    But how can we get this other number?

    It's surprisingly simple. That number is simply n-1.

       n = 64

       64 = 0000 0000 0000 0000 0000 0000 0100 0000
       63 = 0000 0000 0000 0000 0000 0000 0011 1111  // 63 = n-1

    If we now bitise AND them:
        0000 0000 0000 0000 0000 0000 0100 0000
      & 0000 0000 0000 0000 0000 0000 0011 1111
        ---------------------------------------
        0000 0000 0000 0000 0000 0000 0000 0000



    Now let's consider some number that WASN'T a power of 2.
    For example:

       72 = 0000 0000 0000 0000 0000 0000 0100 1000

    n   = 72
    n-1 = 71


       72 = 0000 0000 0000 0000 0000 0000 0100 1000
       71 = 0000 0000 0000 0000 0000 0000 0100 0111

    If we now bitise AND them:

        0000 0000 0000 0000 0000 0000 0100 1000
      & 0000 0000 0000 0000 0000 0000 0100 0111
        ---------------------------------------
        0000 0000 0000 0000 0000 0000 0100 0000 // 64

    Since the result is NOT equal to 0, we conclude that n WASN'T a power of 2.


    Binary representation of a number-1 is found if you take all the 0's to the
    right of the rightmost 1 and flip them to 0's, while you flip only that
    rightmost 1 to 0.

                                               0's to the right of rightmost 1
                                                |||
                                                |||
                                                vvv
       72 = 0000 0000 0000 0000 0000 0000 0100 1000
                                           ^   ^
                              _____________|   |
                              |                |
             We don't touch this one         rightmost 1


       71 = 0000 0000 0000 0000 0000 0000 0100 0111

*/

/* Time  Beats: 100.00% */
/* Space Beats:  36.83% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Follow_Up {
public:
    bool isPowerOfTwo(int n)
    {
        return n > 0 && (n & (n-1)) == 0;
    }
};
