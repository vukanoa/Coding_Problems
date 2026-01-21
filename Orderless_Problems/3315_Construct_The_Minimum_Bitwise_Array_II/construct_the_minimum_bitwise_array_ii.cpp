/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3315) Construct the Minimum Bitwise Array II
    ============================================

    ============
    Description:
    ============

    You are given an array nums consisting of n prime integers.

    You need to construct an array ans of length n, such that, for each
    index i, the bitwise OR of ans[i] and ans[i] + 1 is equal to nums[i], i.e.
    ans[i] OR (ans[i] + 1) == nums[i].

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
    2 <= nums[i] <= 10^9
    nums[i] is a prime number.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    I solved this problem by noticing a pattern in the given examples:

        Input | Answer | Input | Answer
        -------------------------------
        2           -1      10
        3            1      11       1
        5            4     101     100
        7            3     111      11
        11           9    1011    1001
        13          12    1101    1100
        31          15   11111    1111

    + If the binary ends in 01 (like 5 and 13), then the answer is to just
      subtract 1.

    + If the binary consists of all 1s (like 7 and 31), the answer is to remove
      the leftmost 1.

    + "11" is the only one that doesn't fit into the above. I noticed that the
      answer involves removing that 2nd 1 from the right (1011 -> 1001). And in
      general, the approach is to remove the leftmost 1 of the longest chain of
      trailing 1s. So for 11, we remove the 2nd 1 to make it 1001, because if
      we add a 1, it can be ORed back to 11:

           1001
        OR 1010
           ----
           1011

    This holds true for all numbers except for 2.



    Some more examples:

    1111111 (127) would become 0111111 | 1000000 (63 | 64).

       0111111
    OR 1000000
       -------
       1111111

    11101111 (239) would become 11100111 | 11101000 (231 | 232).


       11100111
    OR 11101000
       --------
       11101111

    1110001 (113) would become 1110000 | 1110001 (112 | 113).


       1110000
    OR 1110001
       -------
       1110001

    Approach

    If the number is 2, add -1 to the answer array. Else, start checking the
    bits from the right. Move left everytime there is a 1. When the first 0 is
    found, remove the 1 to the right. This minimizes the number as much as
    possible.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.71% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(1)        */
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> ans(N);

        for (int i = 0; i < nums.size(); i++)
        {
            int num = nums[i];

            if (num == 2)
            {
                ans[i] = -1;
                continue;
            }

            int num_copy = num;
            int count = 0;

            // Count consecutive 1s from the right
            while ((num & 1) == 1)
            {
                count++;
                num >>= 1;
            }

            // [count]th bit is the position of the last 1, like 100111 (count = 3)
            // Subtract the bit                                     ^
            ans[i] = num_copy - (1 << (count - 1));
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
/* Space Beats:  83.50% */

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
