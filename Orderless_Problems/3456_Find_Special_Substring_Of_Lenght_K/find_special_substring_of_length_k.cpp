/*
    ============
    === EASY ===
    ============

    ========================================
    3456) Find Special Substring of Length K
    ========================================

    ============
    Description:
    ============

    You are given a string s and an integer k.

    Determine if there exists a substring of length exactly k in s that
    satisfies the following conditions:

        1. The substring consists of only one distinct character
           (e.g., "aaa" or "bbb").

        2. If there is a character immediately before the substring, it must be
           different from the character in the substring.

        3. If there is a character immediately after the substring, it must
           also be different from the character in the substring.

    Return true if such a substring exists. Otherwise, return false.

    ====================================================
    FUNCTION: bool hasSpecialSubstring(string s, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaabaaa", k = 3
    Output: true
    Explanation:
    The substring s[4..6] == "aaa" satisfies the conditions.
        It has a length of 3.
        All characters are the same.
        The character before "aaa" is 'b', which is different from 'a'.
        There is no character after "aaa".


    --- Example 2 ---
    Input: s = "abc", k = 2
    Output: false
    Explanation: There is no substring of length 2 that consists of one
                 distinct character and satisfies the conditions.


    *** Constraints ***
    1 <= k <= s.length <= 100
    s consists of lowercase English letters only.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    As long as you have the same characters, increment the "cnt". At each
    iteration check if "cnt" is equal to k, if that's the case, then check if
    'i' is the last index in string s, or if it's not check if the adjacent
    one is different from from the counted sequence.

    If all of those cases are true -- return true.

    However, if at any point--before cnt becomes k--we stumble upon a non-same
    character, we should reset our cnt to 1. Why not to 0? Because any
    character has a length of 1.

    Read through the code and I'm sure you'll get it.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool hasSpecialSubstring(string s, int k)
    {
        const int N = s.length();

        int start = 0;
        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[start] == s[i])
                cnt++;
            else
            {
                start = i;
                cnt = 1;
            }

            if (cnt == k && (i == N-1 || s[i] != s[i+1]))
                return true;
        }

        return false;
    }
};
