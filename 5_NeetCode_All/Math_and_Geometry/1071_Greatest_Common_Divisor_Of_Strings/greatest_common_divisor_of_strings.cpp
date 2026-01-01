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

    ********************************
    *** Explanation for the Code ***
    ********************************

    First we must check if (str1 + str2 == str2 + str1). Why?

    Consider this example:

    str1 = "LEETCODE"
    str2 = "LEET"

    "LEET"(str2) is indeed a substring of "LEETCODE"(str1), however we cannot
    say that str2 divides str1 because of the str1's suffix "CODE", therefore
    we must check if (str1 + str2 == str2 + str1), i.e.:

        str1 + str2 ==> "LEETCODE" + "LEET" ==> "LEETCODELEET"
        str2 + str1 ==> "LEET" + "LEETCODE" ==> "LEETLEETCODE"

    These are NOT equivalent, which further means that no part of the, shorter,
    string str2 can divide, longer, string str1 and as a result we return "".

    However, if we find that these concatenated are indeed equivalent, then we
    have to return the GCD of the length those two.

    Let's look at Example 2:
    str1 = "ABCABC"
    str2 = "ABC"

        str1 + str2 ==> "ABCABC" + "ABC" ==> "ABCABCABC"
        str2 + str1 ==> "ABC" + "ABCABC" ==> "ABCABCABC"

    These are INDEED equivalent, but the result should be the GCD of the length
    of the two strings.

    Fortunately, we don't have to write GCD function ourselves since STL has it
    built-in.

    Now we just return the substring of any of the two(since GCD will never
    exceed the length of the shorter one), starting from the beginning and
    taking first std::gcd(str1.length(), str2.length()) characters.

    For Example 2:
        std::gdc(6, 3) is 3

    therefore, we return str1.substr(0, 3), i.e. "ABCABC".substr(0, 3) = "ABC".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.86% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Easier_To_Read {
public:
    std::string gcdOfStrings(string str1, string str2)
    {
        if(str1 + str2 != str2 + str1)
            return "";

        return str1.substr(0, std::gcd(str1.length(), str2.length()));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but writte as a one-liner.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  57.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_One_Liner {
public:
    std::string gcdOfStrings(std::string str1, std::string str2)
    {
        return (str1 + str2 == str2 + str1) ? str1.substr(0, std::gcd(str1.length(), str2.length())) : "";
    }
};
