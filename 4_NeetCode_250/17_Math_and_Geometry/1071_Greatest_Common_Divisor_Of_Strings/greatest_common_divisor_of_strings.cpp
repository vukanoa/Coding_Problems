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

#include <numeric>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There is a "trick" here.

    If a common divisor string exists, then concatenating the two strings in
    either order MUST produce the same result:

        str1 + str2 == str2 + str1. 


    Consider this example:

        str1 = "LEETCODE"
        str2 = "LEET"

    "LEET"(str2) is indeed a substring of "LEETCODE"(str1), however we cannot
    say that str2 divides str1 because of the str1's suffix "CODE".

    Let's check it using our trick:

        str1 + str2 ==> "LEETCODE" + "LEET"     ==> "LEETCODELEET"
        str2 + str1 ==> "LEET"     + "LEETCODE" ==> "LEETLEETCODE"

    These are NOT equivalent, which further means that no part of the shorter
    string can divide longer string, therefore we return "".

    However, if we find that these concatenated are indeed equivalent, then we
    have to return the GCD of lengths those two strings.

    Let's look at Example 2:
    str1 = "ABCABC"
    str2 = "ABC"

        str1 + str2 ==> "ABCABC" + "ABC"    ==> "ABCABCABC"
        str2 + str1 ==> "ABC"    + "ABCABC" ==> "ABCABCABC"

    These are INDEED equivalent, but the result should be the GCD of the length
    of these two strings.

    Fortunately, we don't have to write GCD function ourselves since STL has it
    built-in. (C++17)

    Now we just return the substring of any of the two(since GCD will never
    exceed the length of the shorter one), starting from the beginning and
    taking first:

        gcd(str1.size(), str2.size())

    characters.

    For Example 2:
        gdc(6, 3) is 3

    therefore, we return str1.substr(0, 3), i.e.:

        "ABCABC".substr(0, 3) = "ABC".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.86% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */
class Solution {
public:
    string gcdOfStrings(string str1, string str2)
    {
        if (str1 + str2 != str2 + str1)
            return "";

        int g = gcd(str1.size(), str2.size());

        return str1.substr(0, g);
    }
};
