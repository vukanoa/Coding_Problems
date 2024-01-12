#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ===========================
    290) Word Pattern
    ===========================

    ============
    Description:
    ============

    Given a pattern and a string s, find if s follows the same pattern.

    Here follow means a full match, such that there is a bijection between a
    letter in pattern and a non-empty word in s.

    =====================================================
    FUNCTION: bool wordPattern(string pattern, string s);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: pattern = "abba", s = "dog cat cat dog"
    Output: true

    --- Example 2 ---
    Input: pattern = "abba", s = "dog cat cat fish"
    Output: false

    --- Example 3 ---
    Input: pattern = "aaaa", s = "dog cat cat dog"
    Output: false


    *** Constraints ***
    1 <= pattern.length <= 300
    pattern contains only lower-case English letters.
    1 <= s.length <= 3000
    s contains only lowercase English letters and spaces ' '.
    s does not contain any leading or trailing spaces.
    All the words in s are separated by a single space.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:   100% */
/* Space Beats: 95.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool wordPattern(string pattern, string s)
    {
        std::vector<std::string> words;

        int start = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
            {
                words.push_back(s.substr(start, i-start));
                start = i+1; // Since there are no "trailing whitespaces";
            }
        }
        words.push_back(s.substr(start, s.length() - start));

        if (pattern.length() != words.size())
            return false; // Breaks surjection

        std::unordered_map<char, std::string> umap;
        std::unordered_set<std::string> uset;
        for (int i = 0; i < pattern.length(); i++)
        {
            if (umap.find(pattern[i]) == umap.end()) // Doesn't exist
            {
                if (uset.find(words[i]) != uset.end()) // It would not be injectivity therefore would break bijectivity
                    return false;

                umap.insert({pattern[i], words[i]});
                uset.insert(words[i]);
            }
            else
            {
                if (umap.at(pattern[i]) != words[i]) // It would break bijection
                    return false;
            }
        }

        return true;
    }
};