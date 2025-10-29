/*
    ============
    === EASY ===
    ============

    =======================================
    3370) Smallest Number With All Set Bits
    =======================================

    ============
    Description:
    ============

    You are given a positive number n.

    Return the smallest number x greater than or equal to n, such that the
    binary representation of x contains only set bits

    ====================================
    FUNCTION: int smallestNumber(int n);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: 7
    Explanation:
    The binary representation of 7 is "111".

    --- Example 2 ---
    Input: n = 10
    Output: 15
    Explanation:
    The binary representation of 15 is "1111".

    --- Example 3 ---
    Input: n = 3
    Output: 3
    Explanation:
    The binary representation of 3 is "11".


    *** Constraints ***
    1 <= n <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    It's very important to check Constraints here:

        1 <= n <= 1000

    Since maximum possible value 'n' can be is 1000, that means that the
    "farthest" set bit can be at index 9(0-based, starting from the right).

    Number n=1000 is in biary:  11 1110 1000
                                98 7654 3210 // Indices

    That means all I have to do is start from index 9 and go until i is >= 0
    and in each iteration I'm going to do this:

        Try to do a bitwise-AND operation with i-th bit of number 'n'.
        We care only about the first one since we're going from:

            MSB(Most Significant Bits) to LSB(Less Significant Bits)

        (Remember that the index of that bit is 0based. That is VERY important)

        Once we found that all we have to do is return:

            2^(idx + 1) - 1

        Why 2^(idx + 1) and not just 2^(idx)?

        Let's look at some smaller example of 'n', for example n=5

            n=5 is in binary: 1 0 1
                              2 1 0 // Indices

        The Most Significant Bit in number 5 is located at index 2(0-based)
        That means the answer should be 7. So, how are we going to get 7 if
        we only have this current index=2?

        Simply: 2^(index + 1), i.e. 2^3 which is 8.
        However, since 8 is not the answer, we need to subtract it by 1.

    And that's the entire problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.55% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int smallestNumber(int n)
    {
        int idx_of_farthest_set_bit;
        for (int i = 9; i >= 0; i--)
        {
            if (n & (1 << i))
            {
                idx_of_farthest_set_bit = i;
                break;
            }
        }


        return (1 << (idx_of_farthest_set_bit + 1)) - 1;
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.59% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_2 {
public:
    int smallestNumber(int n)
    {
        int x = 1;
        while (x <= n)
            x <<= 1;

        return x-1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution_3 {
public:
    int smallestNumber(int n)
    {
        int x = 0;
        while (n > 0)
        {
            n >>= 1;
            x++;
        }

        return (1 << x) - 1;
    }
};
