#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    316) Remove Duplicate Letters
    =============================

    ============
    Description:
    ============

    Given a string s, remove duplicate letters so that every letter appears
    once and only once. You must make sure your result is the smallest in
    lexicographical order among all possible results.

    =====
    Note: This question is the same as:
          1081 "Smallest Subsequence of Distinct Characters"
    =====

    ==================================================
    FUNCTION: string removeDuplicateLetters(string s);
    ==================================================

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
    1 <= s.length <= 10^4
    s consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string removeDuplicateLetters(std::string s)
    {
        int n = s.size();

        std::vector<bool> used(26);         // Avoids the letter duplications
        std::vector<int> last_seen_idx(26);
        std::string output = "";            // Stores the result string

        // Map the letters with their index at which they're seen at last
        for(int i = 0; i < n; i++)
            last_seen_idx[s[i] - 'a'] = i;

        for(int i = 0; i < n; i++)
        {
            // If its possible to take the current letter (ith letter)
            if( ! used[s[i] - 'a'])
            {
                // Pop all the letters smaller than the ith letter
                while( ! output.empty()                       &&
                       last_seen_idx[output.back() - 'a'] > i &&
                       output.back() > s[i])
                {
                    used[output.back() - 'a'] = false;
                    output.pop_back();
                }

                // Push the ith letter to the "output".
                output.push_back(s[i]);

                // Mark the ith letter untakable for the next time, as we are
                // aiming for the distinct letters
                used[s[i] - 'a'] = true;
            }
        }

        // Return the result string
        return output;
    }
};
