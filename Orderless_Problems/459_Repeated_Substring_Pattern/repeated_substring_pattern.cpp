#include <iostream>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===============================
    459) Repeated Substring Pattern
    ===============================

    ============
    Description:
    ============

    Given a string s, check if it can be constructed by taking a substring of
    it and appending multiple copies of the substring together.

    ==================================================
    FUNCTION: bool repeatedSubstringPattern(string s);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abab"
    Output: true
    Explanation: It is the substring "ab" twice.

    --- Example 2 ---
    Input: s = "aba"
    Output: false

    --- Example 3 ---
    Input: s = "abcabcabcabc"
    Output: true
    Explanation: It is the substring "abc" four times or the substring "abcabc"
                 twice.


    *** Constraints ***
    1 <= s.length <= 10^4
    s consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.47% */
/* Space Beats: 10.18% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool repeatedSubstringPattern(string s)
    {
        const int n = s.length();
        std::unordered_set<std::string> umap;

        for (int i = 0; i < n/2; i++)
        {
            int substr_length = i+1;
            umap.insert(s.substr(0, substr_length));

            for(int j = substr_length; j < n;)
            {
                if (umap.find(s.substr(j,substr_length)) != umap.end() && j+substr_length == n)
                    return true;
                else if (umap.find(s.substr(j, substr_length)) == umap.end()) // Not found
                {
                    umap.clear();
                    break;
                }
                else
                    j = j + substr_length;
            }
        }

        return false;
    }
};
