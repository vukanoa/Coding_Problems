/*
    ============
    === EASY ===
    ============

    ========================================
    1221) Split a String in Balanced Strings
    ========================================

    ============
    Description:
    ============

    Balanced strings are those that have an equal quantity of 'L' and 'R'
    characters.

    Given a balanced string s, split it into some number of substrings such
    that:

        Each substring is balanced.

    Return the maximum number of balanced strings you can obtain.

    ============================================
    FUNCTION: int balancedStringSplit(string s);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "RLRRLLRLRL"
    Output: 4
    Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring
                 contains same number of 'L' and 'R'.

    --- Example 2 ---
    Input: s = "RLRRRLLRLL"
    Output: 2
    Explanation: s can be split into "RL", "RRRLLRLL", each substring contains
                 same number of 'L' and 'R'. Note that s cannot be split into
                 "RL", "RR", "RL", "LR", "LL", because the 2nd and 5th
                 substrings are not balanced.

    --- Example 3 ---
    Input: s = "LLLLRRRR"
    Output: 1
    Explanation: s can be split into "LLLLRRRR".

    *** Constraints ***
    2 <= s.length <= 1000
    s[i] is either 'L' or 'R'.
    s is a balanced string.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  4.10% */
/* Space Beats: 16.35% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int balancedStringSplit(string s)
    {
        const int N = s.size();
        const int BALANCED = 0;

        int substring_score = 0;

        int count = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'L') substring_score++;
            if (s[i] == 'R') substring_score--;

            if (substring_score == BALANCED)
                count++;
        }

        return count;
    }
};
