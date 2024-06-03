#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    2486) Append Characters to String to Make Subsequence
    =====================================================

    ============
    Description:
    ============

    You are given two strings s and t consisting of only lowercase English
    letters.

    Return the minimum number of characters that need to be appended to the end
    of s so that t becomes a subsequence of s.

    A subsequence is a string that can be derived from another string by
    deleting some or no characters without changing the order of the remaining
    characters.

    ===================================================
    FUNCTION: int appendCharacters(string s, string t);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "coaching", t = "coding"
    Output: 4
    Explanation: Append the characters "ding" to the end of s so that s =
    "coachingding".  Now, t is a subsequence of s ("coachingding").  It can be
    shown that appending any 3 characters to the end of s will never make t a
    subsequence.


    --- Example 2 ---
    Input: s = "abcde", t = "a"
    Output: 0
    Explanation: t is already a subsequence of s ("abcde").


    --- Example 3 ---
    Input: s = "z", t = "abcde"
    Output: 5
    Explanation: Append the characters "abcde" to the end of s so that s =
    "zabcde".  Now, t is a subsequence of s ("zabcde").  It can be shown that
    appending any 4 characters to the end of s will never make t a subsequence.


    *** Constraints ***
    1 <= s.length, t.length <= 10^5
    s and t consist only of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 59.76% */
/* Space Beats: 97.58% */

/* Time  Complexity: O( min(n, m) ) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int appendCharacters(std::string s, std::string t)
    {
        int t_idx = 0;

        for (int s_idx = 0; s_idx < s.length(); s_idx++)
        {
            if (s[s_idx] == t[t_idx])
                t_idx++;

            if (t_idx == t.length())
                break;
        }

        return t.length() - t_idx;
    }
};
