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

    TODO

*/

/* Time  Beats: 6.00% */
/* Space Beats: 5.00% */

/* Time  Complexity: O(min(N, M) * (N + M)) */
/* Space Complexity: O(N + M)               */
class Solution_Intuitive {
public:
    string gcdOfStrings(string str1, string str2)
    {
        int SIZE_LONGER  = str1.size();
        int SIZE_SHORTER = str2.size();

        if (SIZE_LONGER < SIZE_SHORTER)
        {
            swap(str1, str2);
            swap(SIZE_LONGER, SIZE_SHORTER);
        }

        for (int len = SIZE_SHORTER; len >= 1; len--)
        {
            if (SIZE_LONGER % len == 1 || SIZE_SHORTER % len == 1)
                continue;

            string part = str2.substr(0, len);

            /***********/
            /*** One ***/
            /***********/
            string full_one;
            full_one.reserve(SIZE_LONGER);

            int repeat = SIZE_LONGER / len;
            while (repeat > 0) // S
            {
                full_one += part;

                // Decrement
                repeat--;
            }

            /***********/
            /*** Two ***/
            /***********/
            string full_two;
            full_two.reserve(SIZE_SHORTER);

            repeat = SIZE_SHORTER / len;
            while (repeat > 0) // S
            {
                full_two += part;

                // Decrement
                repeat--;
            }

            if (full_one == str1 && full_two == str2)
                return part;
        }

        return "";
    }
};




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
/* Space Complexity: O(N + M) */
class Solution_Trick {
public:
    string gcdOfStrings(string str1, string str2)
    {
        if (str1 + str2 != str2 + str1)
            return "";

        int g = gcd(str1.size(), str2.size());

        return str1.substr(0, g);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.02% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(g)     */ // For the result
class Solution_Trick_Space_Optimized {
public:
    string gcdOfStrings(string str1, string str2)
    {
        const int SIZE_ONE = str1.size();
        const int SIZE_TWO = str2.size();

        int g = gcd(SIZE_ONE, SIZE_TWO);

        for (int i = 0; i < SIZE_ONE; i++)
        {
            if (str1[i] != str1[i % g])
                return "";
        }

        for (int i = 0; i < str2.size(); i++)
        {
            if (str2[i] != str1[i % g])
                return "";
        }

        return str1.substr(0, g);
    }
};
