/*
    ============
    === HARD ===
    ============

    =======================================
    2301) Match Substring After Replacement
    =======================================

    ============
    Description:
    ============

    You are given two strings s and sub. You are also given a 2D character
    array mappings where mappings[i] = [oldi, newi] indicates that you may
    perform the following operation any number of times:

    Replace a character oldi of sub with newi.

    Each character in sub cannot be replaced more than once.

    Return true if it is possible to make sub a substring of s by replacing
    zero or more characters according to mappings. Otherwise, return false.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ======================================================================================
    FUNCTION: bool matchReplacement(string s, string sub, vector<vector<char>>& mappings);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "fool3e7bar", sub = "leet", mappings = [["e","3"],["t","7"],["t","8"]]
    Output: true
    Explanation: Replace the first 'e' in sub with '3' and 't' in sub with '7'.
    Now sub = "l3e7" is a substring of s, so we return true.

    --- Example 2 ---
    Input: s = "fooleetbar", sub = "f00l", mappings = [["o","0"]]
    Output: false
    Explanation: The string "f00l" is not a substring of s and no replacements can be made.
    Note that we cannot replace '0' with 'o'.

    --- Example 3 ---
    Input: s = "Fool33tbaR", sub = "leetd", mappings = [["e","3"],["t","7"],["t","8"],["d","b"],["p","b"]]
    Output: true
    Explanation: Replace the first and second 'e' in sub with '3' and 'd' in sub with 'b'.
    Now sub = "l33tb" is a substring of s, so we return true.


    *** Constraints ***
    1 <= sub.length <= s.length <= 5000
    0 <= mappings.length <= 1000
    mappings[i].length == 2
    oldi != newi
    s and sub consist of uppercase and lowercase English letters and digits.
    oldi and newi are either uppercase or lowercase English letters or digits.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 60.74% */
/* Space Beats: 67.48% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(K)     */ // K = number of uniq (old_chr, old_new) pairs
class Solution {
private:
    unordered_map<char, unordered_set<char>> umap_replacement;

public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings)
    {
        const int N = s.size();
        const int M = sub.size();

        /* Populate Mapping */
        for (const auto& entry : mappings)
        {
            const char& old_chr = entry[0];
            const char& new_chr = entry[1];

            umap_replacement[old_chr].insert(new_chr);
        }

        for (int i = 0; i + M <= N; i++)
        {
            int j = 0;

            for (; j < M; j++)
            {
                if (s[i + j] != sub[j] && umap_replacement[sub[j]].count(s[i + j]) == 0)
                    break;
            }

            if (j == M)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.91% */
/* Space Beats: 82.82% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(1)     */
class Solution_Space_Efficient {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings)
    {
        const int N = s.size();
        const int M = sub.size();
        const int RANGE = 'z' - '0' + 1;

        bool multi_map[RANGE][RANGE] = {};

        /* Populate Multi Map */
        for (const auto& entry : mappings)
        {
            const char& old_chr = entry[0];
            const char& old_new = entry[1];

            multi_map[old_chr - '0'][old_new - '0'] = true;
        }

        for (int i = 0; i + M <= N; ++i)
        {
            int j = 0;

            while (j < M)
            {
                const char& s_chr   = s[i + j];
                const char& sub_chr = sub[j];

                if (s_chr != sub_chr && !multi_map[sub_chr - '0'][s_chr - '0'])
                    break;

                ++j;
            }

            if (j == M)
                return true;
        }

        return false;
    }
};
