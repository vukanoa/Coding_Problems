#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================================
    2264) Largest 3-Same-Digit Number in String
    ===========================================

    ============
    Description:
    ============

    You are given a string num representing a large integer. An integer is good
    if it meets the following conditions:

        + It is a substring of num with length 3.
        + It consists of only one unique digit.

    Return the maximum good integer as a string or an empty string "" if no
    such integer exists.

    =====
    Note: A substring is a contiguous sequence of characters within a string.
          There may be leading zeroes in num or a good integer.
    =====

    ================================================
    FUNCTION: string largestGoodInteger(string num);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "6777133339"
    Output: "777"
    Explanation: There are two distinct good integers: "777" and "333".
    "777" is the largest, so we return "777".

    --- Example 2 ---
    Input: num = "2300019"
    Output: "000"
    Explanation: "000" is the only good integer.

    --- Example 3 ---
    Input: num = "42352338"
    Output: ""
    Explanation: No substring of length 3 consists of only one unique digit.
                 Therefore, there are no good integers.


    *** Constraints ***
    3 <= num.length <= 1000
    num only consists of digits.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Find the largest digit that repeats contiguously 3 times.
    That's literally it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string largestGoodInteger(string num)
    {
        string result = "";
        int max_digit = -1;

        for (int i = 0; i < num.length() - 2; i++)
        {
            if (static_cast<int>(num[i]) > max_digit && num[i] == num[i+1] && num[i+1] == num[i+2])
            {
                max_digit = static_cast<int>(num[i]);
                result = num.substr(i, 3);
            }
        }

        return result;
    }
};
