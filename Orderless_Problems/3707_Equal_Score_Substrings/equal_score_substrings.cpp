/*
    ============
    === EASY ===
    ============

    ============================
    3707) Equal Score Substrings
    ============================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    The score of a string is the sum of the positions of its characters in the
    alphabet, where 'a' = 1, 'b' = 2, ..., 'z' = 26.

    Determine whether there exists an index i such that the string can be split
    into two non-empty substrings s[0..i] and s[(i + 1)..(n - 1)] that have
    equal scores.

    Return true if such a split exists, otherwise return false.

    ======================================
    FUNCTION: bool scoreBalance(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "adcb"
    Output: true
    Explanation:
    Split at index i = 1:
        + Left substring = s[0..1] = "ad" with score = 1 + 4 = 5
        + Right substring = s[2..3] = "cb" with score = 3 + 2 = 5
    Both substrings have equal scores, so the output is true.

    --- Example 2 ---
    Input: s = "bace"
    Output: false
    Explanation:
    No split produces equal scores, so the output is false.


    *** Constraints ***
    2 <= s.length <= 100
    s consists of lowercase English letters.

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
/* Space Beats:  92.94% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool scoreBalance(string s)
    {
        const int N = s.length();

        int total_score = 0;
        for (const char& chr : s)
            total_score += chr - 'a' + 1;

        int curr_score = 0;
        for (int i = 0; i < N-1; i++)
        {
            curr_score += s[i] - 'a' + 1;

            if (2 * curr_score == total_score)
                return true;
        }

        return false;
    }
};
