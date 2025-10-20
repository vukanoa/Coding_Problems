/*
    ============
    === EASY ===
    ============

    ===================================
    2269) Find the K-Beauty of a Number
    ===================================

    ============
    Description:
    ============

    The k-beauty of an integer num is defined as the number of substrings of
    num when it is read as a string that meet the following conditions:

        + It has a length of k.
        + It is a divisor of num.

    Given integers num and k, return the k-beauty of num.


    =====
    Note: Leading zeros are allowed. 0 is not a divisor of any value.
          A substring is a contiguous sequence of characters in a string.
    =====

    ================================================
    FUNCTION: int divisorSubstrings(int num, int k);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 240, k = 2
    Output: 2
    Explanation: The following are the substrings of num of length k:
    - "24" from "240": 24 is a divisor of 240.
    - "40" from "240": 40 is a divisor of 240.
    Therefore, the k-beauty is 2.

    --- Example 2 ---
    Input: num = 430043, k = 2
    Output: 2
    Explanation: The following are the substrings of num of length k:
    - "43" from "430043": 43 is a divisor of 430043.
    - "30" from "430043": 30 is not a divisor of 430043.
    - "00" from "430043": 0 is not a divisor of 430043.
    - "04" from "430043": 4 is not a divisor of 430043.
    - "43" from "430043": 43 is a divisor of 430043.
    Therefore, the k-beauty is 2.


    *** Constraints ***
    1 <= num <= 10^9
    1 <= k <= num.length (taking num as a string)

*/

/*
    ------------
    --- IDEA ---
    ------------

    Scan the string from left right, digit by digit using modulo, i.e. num % 10
    Use those digits to create k digit numbers.

    Construct k digit numbers using (k-1) digit numbers constructed earlier
    (multiply kth digit by pow10 and k-1 digit number)

    Check for divisibility of num by k digit number constructed above

    We use Pow10 to construct the k digit numbers.

    Note that once you create the first k digit number, you need to change
    pow10 at all. Just Divide by the earlier k digit number by 10 so that least
    significant digit goes away and add most significant digit from right
    (multiply the new digit by pow10 and add it to the k-1 digit number)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int divisorSubstrings(int num, int k)
    {
        int beauty = 0;

        int divisor = 0;
        int pow10 = 1;

        for (int i = num; i > 0;  i /= 10)
        {
            divisor += (i % 10) * pow10;

            if (--k > 0)
            {
                pow10 *= 10;
            }
            else
            {
                beauty += (divisor > 0) && (num % divisor == 0) ? 1 : 0;
                divisor /= 10;
            }
        }

        return beauty;
    }
};
