/*
    ============
    === HARD ===
    ============

    ===============================================
    3614) Process String with Special Operations II
    ===============================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters and the
    special characters: '*', '#', and '%'.

    You are also given an integer k.

    Build a new string result by processing s according to the following rules
    from left to right:

        If the letter is a lowercase English letter append it to result.
        A '*' removes the last character from result, if it exists.
        A '#' duplicates the current result and appends it to itself.
        A '%' reverses the current result.

    Return the kth character of the final string result. If k is out of the
    bounds of result, return '.'.

    =================================================
    FUNCTION: char processStr(string s, long long k);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "a#b%*", k = 1
    Output: "a"
    Explanation:
    The final result is "ba". The character at index k = 1 is 'a'.

    --- Example 2 ---
    Input: s = "cd%#*#", k = 3
    Output: "d"
    Explanation:
    The final result is "dcddcd". The character at index k = 3 is 'd'.

    --- Example 3 ---
    Input: s = "z*#", k = 0
    Output: "."
    Explanation:
    The final result is "". Since index k = 0 is out of bounds, the output is
    '.'.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only lowercase English letters and special characters '*', '#', and '%'.
    0 <= k <= 10^15
    The length of result after processing s will not exceed 1015.

*/

#include <cmath>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is NOT intuitive at all, but once you've seen a few similar problems
    you well equipped to tackle a problem with a similar approach.

    The solution works in two passes:

        1. Forward Pass

            + Simulate only the length of the final string
            + Track how operations affect the length (add, delete, double).
            + This avoids building the entire string.



        2. Backward Pass

            + Undo each operation in reverse.
            + Adjust k when needed (e.g., on #, %).
            + When a letter matches the current k, return it.


    Essentially, try to simulate the process in normal forward manner, then
    once you locate the character that is the answer, realize that is MUST come
    from some literal character that is inserted at some point.

    Therefore, once you locate the result, try to "follow it" by doing the
    operations BACKWARDS.

    You'll realize that's possible and then--Voila, just go through the length
    you got from going forward and counting the length, then just go backwards
    and do the operations.

    Once we've done all the operations we'll end up with the character that is
    the result.

*/

/* Time  Beats: 86.74% */
/* Space Beats: 98.02% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    char processStr(string s, long long k)
    {
        const int N = s.length();
        long long effective_string_length = 0;

        // Forward
        for (const char& chr : s)
        {
            if (chr == '*')
            {
                effective_string_length = fmax(0LL, effective_string_length - 1);
            }
            else if (chr == '#')
            {
                effective_string_length *= 2; // Double the length
            }
            else if (chr == '%')
            {
                continue;
            }
            else
            {
                effective_string_length++;
            }
        }

        if (k >= effective_string_length)
            return '.';

        // Backward
        for (int i = N-1; i >= 0; i--)
        {
            char chr = s[i];

            if (chr == '*')
            {
                effective_string_length++;
            }
            else if (chr == '#')
            {
                effective_string_length /= 2; // Half the length

                if (k >= effective_string_length)
                    k -= effective_string_length; // Adjust 'k'
            }
            else if (chr == '%')
            {
                k = effective_string_length-1 - k; // Invert (0-based)
            }
            else
            {
                effective_string_length--;

                if (effective_string_length == k)
                    return chr;
            }
        }

        return '.';
    }
};
