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

/* Time  Beats: 100.00% */
/* Space Beats:  79.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string smallestSubsequence(string str)
    {
        int  freq[26] = {0};
        bool seen[26] = {false}; // seen <==> currently_present_in_the_stack

        string mono_stack; // Monotonically INCREASING Stack, by ASCII values

        for (const char& chr : str)
            freq[chr - 'a']++;

        for (const char& chr : str)
        {
            freq[chr - 'a']--;

            if (seen[chr - 'a'])
                continue;

            while ( ! mono_stack.empty() && mono_stack.back() > chr && freq[mono_stack.back() - 'a'] > 0)
            {
                seen[mono_stack.back() - 'a'] = false;
                mono_stack.pop_back();
            }

            mono_stack.push_back(chr);
            seen[chr - 'a'] = true;
        }

        return mono_stack;
    }
};
