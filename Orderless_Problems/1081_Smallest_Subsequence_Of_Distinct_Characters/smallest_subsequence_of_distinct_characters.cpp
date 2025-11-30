/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    1081) Smallest Subsequence of Distinct Characters
    =================================================

    ============
    Description:
    ============

    Given a string s, return the lexicographically smallest subsequence of s
    that contains all the distinct characters of s exactly once.

    ===============================================
    FUNCTION: string smallestSubsequence(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "bcabc"
    Output: "abc"

    --- Example 2 ---
    Input: s = "cbacdcbc"
    Output: "acdb"


    *** Constraints ***
    1 <= s.length <= 1000
    s consists of lowercase English letters.

*/

#include <string>
using namespace std;

// Note: This question is the same as 316:
// https://leetcode.com/problems/remove-duplicate-letters/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 20.69% */
/* Space Beats: 91.59% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string smallestSubsequence(string s)
    {
        const int N = s.size();

        string result = "";

        int last[26] = {};
        int seen[26] = {};

        for (int i = 0; i < N; ++i)
            last[s[i] - 'a'] = i;

        for (int i = 0; i < N; i++)
        {
            if (seen[s[i] - 'a']++ > 0)
                continue;

            while ( ! result.empty() && result.back() > s[i] && i < last[result.back() - 'a'])
            {
                seen[result.back() - 'a'] = 0;
                result.pop_back();
            }

            result.push_back(s[i]);
        }

        return result;
    }
};
