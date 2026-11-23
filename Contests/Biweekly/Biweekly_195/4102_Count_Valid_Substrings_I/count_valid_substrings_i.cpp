/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    4102) Count Valid Substrings I
    ==============================

    ============
    Description:
    ============

    You are given a string s consisting only of the characters 'a', 'b', and
    'c'.

    A string is called valid if it does not contain "abc" as a substring.

    Return the number of valid substrings in s. Substrings with different
    starting or ending indices are counted separately.

    ===================================================
    FUNCTION: long long countValidSubstrings(string s);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abac"
    Output: 10
    Explanation:
    The following substrings don't contain "abc" as a substring:
        s[0..0] = "a"
        s[0..1] = "ab"
        s[0..2] = "aba"
        s[0..3] = "abac"
        s[1..1] = "b"
        s[1..2] = "ba"
        s[1..3] = "bac"
        s[2..2] = "a"
        s[2..3] = "ac"
        s[3..3] = "c"
    Thus, the answer is 10.


    --- Example 2 ---
    Input: s = "abc"
    Output: 5
    Explanation:
    The following substrings don't contain "abc" as a substring:
        s[0..0] = "a"
        s[0..1] = "ab"
        s[1..1] = "b"
        s[1..2] = "bc"
        s[2..2] = "c"
    Thus, the answer is 5.


    --- Example 3 ---
    Input: s = "ac"
    Output: 3
    Explanation:
    All substrings in s don't contain "abc" as a substring . Thus, the answer
    is 3.


    *** Constraints ***
    1 <= s.length <= 10^5
    s only consists of 'a', 'b', and 'c' characters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.27% */
/* Space Beats: 97.75% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long countValidSubstrings(string s)
    {
        const int N = s.size();
        long long result = 0LL;

        int valid_substr_size = 0;
        for (int i = 0; i < N; i++)
        {
            ++valid_substr_size;

            if (i >= 2 && s[i-2] == 'a' && s[i-1] == 'b' && s[i] == 'c')
            {
                result += (1LL * (valid_substr_size-1) * valid_substr_size / 2) - 1;
                valid_substr_size = 2;
            }
        }
        result += 1LL * valid_substr_size * (valid_substr_size + 1) / 2;

        return result;
    }
};
