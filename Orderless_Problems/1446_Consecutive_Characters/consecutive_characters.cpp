/*
    ============
    === EASY ===
    ============

    ============================
    1446) Consecutive Characters
    ============================

    ============
    Description:
    ============

    The power of the string is the maximum length of a non-empty substring that
    contains only one unique character.

    Given a string s, return the power of s.

    =================================
    FUNCTION: int maxPower(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcode"
    Output: 2
    Explanation: The substring "ee" is of length 2 with the character 'e' only.

    --- Example 2 ---
    Input: s = "abbcccddddeeeeedcba"
    Output: 5
    Explanation: The substring "eeeee" is of length 5 with the character 'e'
                 only.

    *** Constraints ***
    1 <= s.length <= 500
    s consists of only lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxPower(string s)
    {
        const int N = s.length();
        int result = 0;

        int start = 0;
        int end   = 1;
        while (end < N)
        {
            if (s[end-1] != s[end])
            {
                result = max(result, end - start);
                start = end;
            }

            // Increment
            end++;
        }

        result = max(result, end - start);

        return result;
    }
};
