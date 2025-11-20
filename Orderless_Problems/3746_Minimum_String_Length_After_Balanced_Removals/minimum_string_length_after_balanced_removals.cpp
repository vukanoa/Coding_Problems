/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3746) Minimum String Length After Balanced Removals
    ===================================================

    ============
    Description:
    ============

    You are given a string s consisting only of the characters 'a' and 'b'.

    You are allowed to repeatedly remove any substring where the number of 'a'
    characters is equal to the number of 'b' characters. After each removal,
    the remaining parts of the string are concatenated together without gaps.

    Return an integer denoting the minimum possible length of the string after
    performing any number of such operations.

    ===============================================
    FUNCTION: int minLengthAfterRemovals(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aabbab"
    Output: 0
    Explanation:
    The substring "aabbab" has three 'a' and three 'b'. Since their counts are
                  equal, we can remove the entire string directly. The minimum
                  length is 0.

    --- Example 2 ---
    Input: s = "aaaa"
    Output: 4
    Explanation: Every substring of "aaaa" contains only 'a' characters. No
                 substring can be emoved as a result, so the minimum length
                 remains 4.

    --- Example 3 ---
    Input: s = "aaabb"
    Output: 1
    Explanation: First, remove the substring "ab", leaving "aab". Next, remove
                 the new substring "ab", leaving "a". No further removals are
                 possible, so the minimum length is 1.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either 'a' or 'b'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 61.12% */
/* Space Beats: 88.86% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minLengthAfterRemovals(string s)
    {
        const int N = s.length();
        int result = 0;

        int a = 0;
        int b = 0;
        for (const char& chr : s)
        {
            if (chr == 'a')
                a++;
            else
                b++;
        }

        return N - 2 * min(a, b);
    }
};
