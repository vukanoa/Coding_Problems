#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    1071) Greatest Common Divisor of Strings
    ========================================

    ============
    Description:
    ============

    For two strings s and t, we say "t divides s" if and only if s = t + ... +
    t (i.e., t is concatenated with itself one or more times).

    Given two strings str1 and str2, return the largest string x such that x
    divides both str1 and str2.

    ========================================================
    FUNCTION: string gcdOfStrings(string str1, string str2);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: str1 = "ABCABC", str2 = "ABC"
    Output: "ABC"

    --- Example 2 ---
    Input: str1 = "ABABAB", str2 = "ABAB"
    Output: "AB"

    --- Example 3 ---
    Input: str1 = "LEET", str2 = "CODE"
    Output: ""


    *** Constraints ***
    1 <= str1.length, str2.length <= 1000
    str1 and str2 consist of English uppercase letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100% */
/* Space Beats: 57.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string gcdOfStrings(std::string str1, std::string str2)
    {
        return (str1 + str2 == str2 + str1) ? str1.substr(0, std::gcd(str1.length(), str2.length())) : "";
    }
};
