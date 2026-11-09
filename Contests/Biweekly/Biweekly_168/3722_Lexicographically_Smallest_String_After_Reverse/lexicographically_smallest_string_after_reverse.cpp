/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3722) Lexicographically Smallest String After Reverse
    =====================================================

    ============
    Description:
    ============

    You are given a string s of length n consisting of lowercase English
    letters.

    You must perform exactly one operation by choosing any integer k such that
    1 <= k <= n and either:

        + reverse the first k characters of s, or
        + reverse the last k characters of s.

    Return the lexicographically smallest string that can be obtained after
    exactly one such operation.

    =======================================
    FUNCTION: string lexSmallest(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "dcab"
    Output: "acdb"
    Explanation:
        Choose k = 3, reverse the first 3 characters.
        Reverse "dca" to "acd", resulting string s = "acdb", which is the
        lexicographically smallest string achievable.


    --- Example 2 ---
    Input: s = "abba"
    Output: "aabb"
    Explanation:
        Choose k = 3, reverse the last 3 characters.
        Reverse "bba" to "abb", so the resulting string is "aabb", which is the
        lexicographically smallest string achievable.


    --- Example 3 ---
    Input: s = "zxy"
    Output: "xzy"
    Explanation:
        Choose k = 2, reverse the first 2 characters.
        Reverse "zx" to "xz", so the resulting string is "xzy", which is the
        lexicographically smallest string achievable.


    *** Constraints ***
    1 <= n == s.length <= 1000
    s consists of lowercase English letters.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 38.10% */
/* Space Beats: 68.25% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    string lexSmallest(string s)
    {
        const int N = s.size();
        string result = s;

        for (int j = N-1; j > 0; j--)
        {
            string copy = s;

            reverse(copy.begin(), copy.begin() + j + 1);

            if (copy < result)
                result = copy;
        }

        for (int i = 0; i < N-1; i++)
        {
            string copy = s;

            reverse(copy.begin() + i, copy.end());

            if (copy < result)
                result = copy;
        }

        return result;
    }
};
