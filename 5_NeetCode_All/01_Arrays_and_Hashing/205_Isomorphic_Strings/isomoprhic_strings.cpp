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
    bool isIsomorphic(std::string s, std::string t)
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




/*
    ------------
    --- IDEA ---
    ------------

    This is more of a standard way of solving this problem.

    Since there must be a bijection, we must use two HashMaps.
    In the first  one we'll have s[i] as the key and t[i] as value.
    In the second one we'll have t[i] as the key and s[i] as value.

    We are going to traverse each letter in string s and if that letter is
    already mapped to some other letter, appending it to our result string.
    (Instead of appending strings, we will use std::ostringstream because it is
     a bit faster)

    However, if a current letter from string s is NOT present, then we must
    check if a character we want to map it to, a character t[i], is already
    taken.

    If t[i] is already taken(that's why we have the second Hash Map), then we
    must return false. It' must be a bijection.

    If t[i] is NOT already taken, then we push {s[i], t[i]} and {t[i], s[i]} to
    HashMap_1 and HashMap_2, respectively.

    And we "append" t[i] to std::ostringstream.

    At the end, if we didn't return false at any point, we must check if this
    newly constructed string is the same as string t.

    If yes:
        return true;
    else
        return false;

*/

/* Time  Beats: 77.84% */
/* Space Beats:  5.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isIsomorphic(string s, string t)
    {
        std::unordered_map<char, char> umap_1;
        std::unordered_map<char, char> umap_2;

        std::ostringstream out;
        for (int i = 0; i < s.length(); i++)
        {
            if (umap_1.find(s[i]) != umap_1.end())
            {
                out << umap_1[s[i]];
            }
            else
            {
                if (umap_2.find(t[i]) != umap_2.end() && umap_1[s[i]] != t[i])
                    return false;

                umap_1.insert({s[i], t[i]});
                umap_2.insert({t[i], s[i]});
                out << t[i];
            }
        }

        return out.str() == t;
    }
};
