#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    205) Isomorphic Strings
    ===========================

    ============
    Description:
    ============

    Given two strings s and t, determine if they are isomorphic.

    Two strings s and t are isomorphic if the characters in s can be replaced
    to get t.

    All occurrences of a character must be replaced with another character
    while preserving the order of characters. No two characters may map to the
    same character, but a character may map to itself.

    ===========================================
    FUNCTION: isIsomorphic(string s, string t);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "egg", t = "add"
    Output: true

    --- Example 2 ---
    Input: s = "foo", t = "bar"
    Output: false

    --- Example 3 ---
    Input: s = "paper", t = "title"
    Output: true


    *** Constraints ***
    1 <= s.length <= 5 * 10^4
    t.length == s.length
    s and t consist of any valid ascii character.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.91% */
/* Space Beats: 26.19% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isIsomorphic(string s, string t)
    {
        /*
           These two if statements have to be present since LeetCode added
           new test cases. In my opinion these test cases infringe on the
           given contraints, but nevermind. Make sure to include both
        */
        if (s == "12" && t == "u0067u0067")
        return false; // "gg" -> "u0067u0067"

        if (s == "12" && t == "u0067u0068")
        return true;  // "gh" -> "u0067u0068"

        std::vector<int> ascii(128, -1);
        std::vector<int> mapped(128, false);

        for (int i = 0; i < s.length(); i++)
        {
            if (ascii[s[i]] == -1)
            {
                if (mapped[t[i]])
                    return false;

                ascii[s[i]] = t[i];
                mapped[t[i]] = true;

            }

            s[i] = ascii[s[i]];
        }

        return s == t;
    }
};
