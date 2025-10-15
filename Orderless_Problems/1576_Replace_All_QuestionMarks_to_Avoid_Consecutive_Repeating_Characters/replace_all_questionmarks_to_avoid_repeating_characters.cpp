/*
    ============
    === EASY ===
    ============

    ===============================================================
    1576) Replace All ?'s to Avoid Consecutive Repeating Characters
    ===============================================================

    ============
    Description:
    ============

    Given a string s containing only lowercase English letters and the '?'
    character, convert all the '?' characters into lowercase letters such that
    the final string does not contain any consecutive repeating characters.
    You cannot modify the non '?' characters.

    It is guaranteed that there are no consecutive repeating characters in the
    given string except for '?'.

    Return the final string after all the conversions (possibly zero) have been
    made. If there is more than one solution, return any of them. It can be
    shown that an answer is always possible with the given constraints.

    ========================================
    FUNCTION: string modifyString(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "?zs"
    Output: "azs"
    Explanation: There are 25 solutions for this problem. From "azs" to "yzs",
    all are valid. Only "z" is an invalid modification as the string will
    consist of consecutive repeating characters in "zzs".

    --- Example 2 ---
    Input: s = "ubv?w"
    Output: "ubvaw"
    Explanation: There are 24 solutions for this problem. Only "v" and "w" are
                 invalid modifications as the strings will consist of
                 consecutive repeating characters in "ubvvw" and "ubvww".


    *** Constraints ***
    1 <= s.length <= 100
    s consist of lowercase English letters and '?'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.37% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string modifyString(string s)
    {
        const int N = s.size();

        for (auto i = 0; i < N; ++i)
        {
            if (s[i] == '?')
            {
                for (s[i] = 'a'; s[i] <= 'c'; ++s[i])
                {
                    if ((i == 0 || s[i - 1] != s[i]) && (i == N-1 || s[i + 1] != s[i]))
                        break;
                }
            }

        }

        return s;
    }
};
