#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    1888) Minimum Number of Flips to Make The Binary String Alternating
    ===================================================================

    ============
    Description:
    ============

    You are given a binary string s. You are allowed to perform two types of
    operations on the string in any sequence:

        Type-1: Remove the character at the start of the string s and append it
        to the end of the string.

        Type-2: Pick any character in s and flip its
        value, i.e., if its value is '0' it becomes '1' and vice-versa.

    Return the minimum number of type-2 operations you need to perform such
    that s becomes alternating.

    The string is called alternating if no two adjacent characters are equal.

        For example, the strings "010" and "1010" are alternating, while the
        string "0100" is not.

    =================================
    FUNCTION: int minFlips(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "111000"
    Output: 2
    Explanation: Use the first operation two times to make s = "100011".  Then,
                 use the second operation on the third and sixth elements to
                 make s = "101010".


    --- Example 2 ---
    Input: s = "010"
    Output: 0
    Explanation: The string is already alternating.


    --- Example 3 ---
    Input: s = "1110"
    Output: 1
    Explanation: Use the second operation on the second element to make s =
                 "1010".


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Very clever approach.

    TODO

*/

/* Time  Beats: 48.95% */
/* Space Beats: 57.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minFlips(std::string s)
    {
        int n_half = s.length();

        s = s + s;
        int n = s.length();

        std::string alt_1;
        std::string alt_2;

        alt_1.reserve(n);
        alt_2.reserve(n);

        for (int i = 0; i < n; i++)
        {
            alt_1 += i & 1 ? '1' : '0';
            alt_2 += i & 1 ? '0' : '1';
        }

        int result = INT_MAX;
        int diff_1 = 0;
        int diff_2 = 0;

        int left  = 0;
        int right = 0;
        while (right < n)
        {
            if (s[right] != alt_1[right])
                diff_1++;

            if (s[right] != alt_2[right])
                diff_2++;

            if ((right - left + 1) > n_half)
            {
                if (s[left] != alt_1[left])
                    diff_1--;

                if (s[left] != alt_2[left])
                    diff_2--;

                left++;
            }

            if ((right - left + 1) == n_half)
                result = std::min({result, diff_1, diff_2});

            right++;
        }

        return result;
    }
};
