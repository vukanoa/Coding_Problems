/*
    ============
    === EASY ===
    ============

    ===========================
    125) Valid Palindrome
    ===========================

    ============
    Description:
    ============

    A phrase is a palindrome if, after converting all uppercase letters into
    lowercase letters and removing all non-alphanumeric characters, it reads
    the same forward and backward. Alphanumeric characters include letters and
    numbers.

    Given a string s, return true if it is a palindrome, or false otherwise.

    =================================
    FUNCTION: isPalindrome(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "A man, a plan, a canal: Panama"
    Output: true
    Explanation: "amanaplanacanalpanama" is a palindrome.


    --- Example 2 ---
    Input: s = "race a car"
    Output: false
    Explanation: "raceacar" is not a palindrome.


    --- Example 3 ---
    Input: s = " "
    Output: true
    Explanation: s is an empty string "" after removing non-alphanumeric
    characters. Since an empty string reads the same forward and backward, it
    is a palindrome.

    *** Constraints ***
    1 <= s.length <= 2 * 105
    s consists only of printable ASCII characters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Two-Pointers technique.

    Begin at both sides and skipp all non-alphanumeric characters.
    Once both 'L' and 'R' indices are at character that ARE alpha-numeric,
    pass them through "tolower" function so that we removing eventual
    capitalization.

    Capitalization of digits is impossible, therefore, passing a character '0'
    or '9' wouldn't change anything.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isPalindrome(string s)
    {
        const int N = s.size();

        int L = 0;
        int R = N-1;

        while (L < R)
        {
            while (L < R && ! isalnum(s[L]))
                L++;

            while (L < R && ! isalnum(s[R]))
                R--;

            // If we pass a digit into "tolower()", it will still be a digit
            if (tolower(s[L]) != tolower(s[R]))
                return false;

            L++; // Increment
            R--; // Decrement
        }

        return true;
    }
};
