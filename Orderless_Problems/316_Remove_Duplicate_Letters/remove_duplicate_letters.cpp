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

#include <vector>
#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.76% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string removeDuplicateLetters(string s)
    {
        int N = s.size();

        vector<bool> used(26);
        vector<int> last_seen_idx(26);
        string monotonic_stack_str = "";

        for (int i = 0; i < N; i++)
            last_seen_idx[s[i] - 'a'] = i;

        for(int i = 0; i < N; i++)
        {
            if ( ! used[s[i] - 'a'])
            {
                while( ! monotonic_stack_str.empty()                       &&
                       last_seen_idx[monotonic_stack_str.back() - 'a'] > i &&
                       monotonic_stack_str.back() > s[i])
                {
                    used[monotonic_stack_str.back() - 'a'] = false;
                    monotonic_stack_str.pop_back();
                }

                monotonic_stack_str.push_back(s[i]);

                used[s[i] - 'a'] = true;
            }
        }

        return monotonic_stack_str;
    }
};
