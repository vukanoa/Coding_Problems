/*
    ============
    === EASY ===
    ============

    ===========================================
    3314) Construct the Minimum Bitwise Array I
    ===========================================

    ============
    Description:
    ============

    You are given an array nums consisting of n prime integers.

    You need to construct an array ans of length n, such that, for each index
    i, the bitwise OR of ans[i] and ans[i] + 1 is equal to nums[i], i.e. ans[i]
    OR (ans[i] + 1) == nums[i].

    Additionally, you must minimize each value of ans[i] in the resulting
    array.

    If it is not possible to find such a value for ans[i] that satisfies the
    condition, then set ans[i] = -1.

    =========================================================
    FUNCTION: vector<int> minBitwiseArray(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,5,7]
    Output: [-1,1,4,3]
    Explanation:
        For i = 0, as there is no value for ans[0] that satisfies ans[0] OR (ans[0] + 1) = 2, so ans[0] = -1.
        For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 3 is 1, because 1 OR (1 + 1) = 3.
        For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 5 is 4, because 4 OR (4 + 1) = 5.
        For i = 3, the smallest ans[3] that satisfies ans[3] OR (ans[3] + 1) = 7 is 3, because 3 OR (3 + 1) = 7.


    --- Example 2 ---
    Input: nums = [11,13,31]
    Output: [9,12,15]
    Explanation:
        For i = 0, the smallest ans[0] that satisfies ans[0] OR (ans[0] + 1) = 11 is 9, because 9 OR (9 + 1) = 11.
        For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 13 is 12, because 12 OR (12 + 1) = 13.
        For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 31 is 15, because 15 OR (15 + 1) = 31.


    *** Constraints ***
    1 <= nums.length <= 100
    2 <= nums[i] <= 1000
    nums[i] is a prime number.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since the most optimal Solution is far from intuitive, especially for an
    EASY problem and especially for beginners, it's always good to try and do
    the "Brute Force" that is allowed according to the Constraints.

    In this case, since we're told that ans[i] needs to be MINIMIZED, we start
    from 1 and go up until nums[i](non-inclusive) and try to do a bitwise OR
    for every number. As soon as we find:

            ((num | (num + 1)) == nums[i])

    we stop and put it in ans[i].

*/

/* Time  Beats: 23.67% */
/* Space Beats: 26.63% */

/* Time  Complexity: O(M * N) */ // Where 'M' is the value of nums[i]
/* Space Complexity: O(1)     */ // "result" is not EXTRA space usually
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> ans(N, -1);

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 2) // '2' is the ONLY even primer-number
                continue;

            for (int num = 1; num < nums[i]; num++)
            {
                if ((num | (num + 1)) == nums[i])
                {
                    ans[i] = num;
                    break;
                }
            }
        }

        return ans;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The very first thing we must take note of is that for any number X, if we
    add 1 to it, then bitwise-speaking we're flipping the first 0 from the
    right(i.e. the lowest 0 bit, i.e. the LSB that is NOT set) and everything
    before it(to the right of it, i.e. all 1s to the right) is flipped to 0.

    Let's see it practically as it's much easier to follow:

                                   ---- rightmost 0
                                   |
                                   |
                                   v
        X   = 134     -->  1000 0110
        X+1 = 135     -->  1001 0111

            or
                                ---- rightmost 0
                                |
                                |
                                v
        X   = 167      --> 1010 0111
        X+1 = 168      --> 1010 1000

    Once we flip the the rightmost 0, everything to the right of it is also
    flipped. (Note that everything to the right of the RIGHTMOST 0, is always
    all 1s)

    That's the first thing we need to understand.


    Now that implies that for any set-bit(i.e. 1-bit) that appears BEFORE the
    first 0-bit(from LEAST significant bits to MOST significant bits) in the
    binary representation of nums[i], changing that 1-bit to 0-bit will produce
    a valid X(i.e. ans[i]) such that:

        X | (X + 1) == nums[i]

            i.e.

        ans[i] | (ans[i] + 1) == nums[i]


    Since the problem asks for the SMALLEST "ans[i]", we ONLY need to locate
    the position "pos" of the first 0-bit from the right and flip ALL of the
    bits from "pos" until the end.



    The implementation of the "while loop" is crucial in this Solution.

    <Check out the detailed comment in within the code>

*/

/* Time  Beats: 100.00% */
/* Space Beats:  55.03% */

/* Time  Complexity: O(N * log(M)) */ // Where 'M' is the value of nums[i]
/* Space Complexity: O(1)          */ // "result" is not EXTRA space usually
class Solution_2 {
public:
    vector<int> minBitwiseArray(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> ans(N, -1); // Usually not considered EXTRA space

        // O(N * logM) (enire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            int smallest_valid_ans = -1;

            // O(logM) (enire block)
            int lowest_zero_bit_position = 0;
            // While lowest_zero_bit_position of nums[i] is SET(i.e. 1-bit)
            while ((nums[i] & (1 << lowest_zero_bit_position)) != 0)
            {
                /*
                    Flip only that bit of nums[i] and set it as a:

                        smallest_valid_ans

                    Why does this work?
                    Consider nums[i] == 31      -->  0001 1111
                                                     7654 3210

                    Since our "lowest_zero_bit_position" goes from 0 upwards,
                    flipping LOWER bits will result in BIGGER ans[i].

                        31 -->  0001 1111    // nums[i] = 31
                                7654 3210
                                        ^
                                        |
                                      __|
                                      |
                          if we flip this bit, we'll get:
                                        
                        30 -->  0001 1110    // ans[i] = 30
                                7654 3210


                    However, if we flip some HIGHER bit, we'll get LOWER ans[i]

                        31 -->  0001 1111    // nums[i] = 31
                                7654 3210
                                      ^
                                      |
                                      |
                                      |
                          if we flip this bit, we'll get:
                                        
                        27 -->  0001 1011    // ans[i] = 27
                                7654 3210


                    So, if we flip:

                    31 --> flip  (LOWER)bit at idx=0 --> ans[i] = 30 // BIGGER
                    31 --> flip (HIGHER)bit at idx=2 --> ans[i] = 27 // SMALLER

                    Therefore:
                        if we flip  LOWER bit, we'll get BIGGER  ans[i].
                        If we flip HIGHER bit, we'll get SMALLER ans[i].


                    However, we want to MINIMIZE ans[i].

                    Therefore, since we're going from the right, if we flip the
                    rightmost 1-bit, we'll have:

                               bit at position
                                    ____|
                                    |
                                    |
                                    v
                        31 & ~(1 << 0)     // Flip 1-bit at position 0

                    i.e.:
                        0001 1111   <-- 31
                     &  1111 1110   <-- ~(1 << 0)
                       ----------
                        0001 1110   <-- 30 // X == smallest_valid_ans

                    But how do we know that:

                        30 | (30 + 1) will be nums[i]?

                    Because we've noticed already that any number X ORed with
                    (X+1) will set the RIGHTMOST 0 of X to 1 and all the
                    trailing bits to the right of it, to 0s.

                    How does that guarantee that: X | (X+1) == nums[i]?

                    Because X, in our case, is "smallest_valid_ans" which is
                    gained from nums[i] itself:

                        X = nums[i] & ~(1 << bit_position_of_one_trailing_bit)

                    X in our case is LITERALLY "nums[i] with SINGLE 0-bit in
                                                one of its trailing 1-bits"

                    Look at this:

                        0001 1111   <-- 31 == nums[i]
                     &  1111 1110   <-- ~(1 << 0) <==> ~(1)
                       ----------
                        0001 1110   <-- 30 == X == smallest_valid_ans


                        0001 1111   <-- 31 == nums[i]
                        0001 1110   <-- 30 == X == smallest_valid_ans
                                ^
                                |
                                |
                         Only THIS bit DIFFERS(there's only a SINGLE "hole".
                                               Meaning X is nums[i] with a
                                               SINGLE "hole")


                    


                        0001 1111   <-- 31 == nums[i]
                     &  1111 1101   <-- ~(1 << 1)  <==> ~(2)
                       ----------
                        0001 1101   <-- 29


                        0001 1111   <-- 31 == nums[i]
                        0001 1101   <-- 29 == X
                               ^
                               |
                               |
                         Only THIS bit DIFFERS(there's only a SINGLE "hole".
                                               Meaning X is nums[i] with a
                                               SINGLE "hole")


                    And how do we know that (29 | (29 + 1)) == 31?

                    Remember the first thing we've noticed?

                                                   ---- rightmost 0-bit
                                                   |
                                                   |
                                                   v
                        X   = 134     -->  1000 0110
                        X+1 = 135     -->  1001 0111

                            or
                                                ---- rightmost 0-bit
                                                |
                                                |
                                                v
                        X   = 167      --> 1010 0111
                        X+1 = 168      --> 1010 1000


                    This means that EVERYTHING to the right of
                    lowest_zero_bit_position in X, when ORed, will "fill the
                    hole" that now exists in x.

                    Remember how:

                        0001 1111   <-- 31 == nums[i]
                        0001 1101   <-- 29 == X
                               ^
                               |
                               |
                         Only THIS bit DIFFERS(there's only a SINGLE "hole".
                                               Meaning X is nums[i] with a
                                               SINGLE "hole")

                    There is only a SINGLE "hole"!
                    We'll CERTAINLY fill that hole of X by doing:

                        X | (X+1)

                    And, thus, we'll return back to our "nums[i]".

                    And that is guaranteed because X is gained by making a
                    "hole" in one of the trailing 1-bits of nums[i].


                    So, since we're moving the position of
                    "lowest_zero_bit_position" from RIGHT to LEFT(i.e. from LSB
                    to MSB), we've already seen that:

                    (idx <==> lowest_zero_bit_position)

                    31 --> flip  (LOWER)bit at idx=0 --> ans[i] = 30 // BIGGER
                    31 --> flip (HIGHER)bit at idx=2 --> ans[i] = 27 // SMALLER


                    Therefore our X, i.e. our smallest_valid_ans, i.e. ans[i]
                    will be BIGGER at LOWER bits and will becomes SMALLER and
                    SMALLER as we move our lowest_zero_bit_position to the LEFT

                    That's why we're updating our "smallest_valid_ans" each
                    time.

                    Each iteration we know that we're flipping some MORE
                    SIGNIFICANT bit in the trailing 1-bits of nums[i], which
                    will produce SMALLER and SMALLER ans[i] each time.

                    Therefore, we're updating our "smallest_valid_ans" until
                    we get to the LEFTMOST(MSB) TRAILING(!!!) 1-bit of nums[i].

                    Read this sentence above again. That is the crux.

                */
                smallest_valid_ans = nums[i] & ~(1 << lowest_zero_bit_position);
                lowest_zero_bit_position++;
            }

            ans[i] = smallest_valid_ans;
        }

        return ans;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    First, you need to know that 2 is THE ONLY even prime number.

    Now let's see a cool bitwise "tricks" when the number is ODD, i.e. it
    containts TRAILING 1-bits.

    ~~~~~~~~~~~~~~~~
    ~~~ Trick #1 ~~~
    ~~~~~~~~~~~~~~~~

        Adding 1 to some ODD number will FLIP all the bits from the RIGHTMOST
        0-bit all the way to the right(toward LSBs, i.e. Least Significant
        Bits)

                   23    0001 0111
                   24    0001 1000
                              ~~~~
                                ^
                                |
                                |
                           These are flipped


    ~~~~~~~~~~~~~~~~
    ~~~ Trick #2 ~~~
    ~~~~~~~~~~~~~~~~

        If we do a bitwise-OR on (X | (X+1)), we'll get Y.

            X      71    0100 0111
            X+1    72    0100 1000  OR
                   ---------------
            Y      79    0100 1111

        What is the relationship between X and Y now?

            X      71    0100 0111
            Y      79    0100 1111
                              ^
                              |
                              |______________________
                                                    |
        They differ at EXACTLY one bit, i.e. the LEFTMOST TRAILING 1-bit in Y
        They differ at EXACTLY one bit, i.e. the RIGHTMOST         0-bit in X.


        Therefore, since Y is nums[i] in our case, how do we find the "leftmost
        trailing 1-bit" in it?

            Y      79    0100 1111
                              ^
                              |
                              |_______
                                     |
        How do we find position of THIS bit efficiently?



    ~~~~~~~~~~~~~~~~
    ~~~ Trick #3 ~~~
    ~~~~~~~~~~~~~~~~

        To find the RIGHTMOST 1-bit:

            -q & q
            ^
            |
            |____
                |
               This is a NEGATIVE sign, not a tilde(bitwise-COMPLEMENT oper.)


    ~~~~~~~~~~~~~~~~
    ~~~ Trick #4 ~~~
    ~~~~~~~~~~~~~~~~

        To find the RIGHTMOST 0-bit:
            
            -(~q) & (~q)
            ^ ^      ^
            | |      |
        ____| |______|
        |         |
      NEGATIVE   Bitwise-NOT(aka Bitwise-COMPLEMENT)
        sign       operator


        However, we can simplify this because:

            -(~q)  <==> (q + 1)
            ^ ^
            | |
        ____| |____
        |         |
      NEGATIVE   Bitwise-NOT(aka Bitwise-COMPLEMENT)
        sign       operator


        We cam simplify it to:

            (q + 1) & (~q)
                       ^
                       |
                       |
                    Bitwise-NOT, aka Bitwise-COMPLEMENT operator

    ~~~~~~~~~~~~~~~~
    ~~~ Trick #5 ~~~
    ~~~~~~~~~~~~~~~~

        Leftmost trailing 1-bit

        To find the LEFTMOST trailing 1-bit of nums[i](i.e. of 'q') we'll
        have to do:

            (q + 1) & (~q)
                       ^
                       |
                       |
                    Bitwise-NOT, aka Bitwise-COMPLEMENT operator

        
        Let's consider our: Y == nums[i] == q == 79

           ~q     = 176    1011 0000
            q     = 79     0100 1111
            q + 1 = 80     0101 0000


        Now we do:

            (q + 1) & (~q)
                       ^
                       |
                       |
                    Bitwise-NOT, aka Bitwise-COMPLEMENT operator


            q + 1 = 80     0101 0000
           ~q     = 176    1011 0000  AND
                          ----------
                           0001 0000 // i.e. highest_trailing_set_bit_mask

        Since we want to to set this LEFTMOST TRAILING 1-bit of nums[i](i.e. q)
        to 0, we need to bitwise-AND it with COMPLEMENTED:

            highest_trailing_set_bit_mask


        There, we'll do:

            ans[i] = nums[i] & ~highest_trailing_set_bit_mask;


    And that's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  54.86% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Linear {
public:
    vector<int> minBitwiseArray(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> ans(N, -1);

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 2) // It's the only EVEN prime number
                continue;

            int highest_trailing_set_bit_mask = ((nums[i] + 1) & ~(nums[i])) >> 1;
            ans[i] = nums[i] & ~highest_trailing_set_bit_mask;
        }

        return ans;
    }
};
