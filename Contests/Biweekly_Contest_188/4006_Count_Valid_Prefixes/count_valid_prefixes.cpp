/*
    ============
    === EASY ===
    ============

    ===========================
    4006) Count Valid Prefixes
    ===========================

    ============
    Description:
    ============

    You are given a binary string s.

    A prefix of s is considered valid if its characters can be rearranged to
    form an alternating string.

    Return the number of valid prefixes of s.

    A string is considered alternating if no two adjacent characters are equal.

    ===========================================
    FUNCTION: int countValidPrefixes(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "00101"
    Output: 3
    Explanation:
    The valid prefixes are:
        "0":     It is already an alternating string.

        "001":   It can be rearranged into "010", which is an alternating
                 string.

        "00101": It can be rearranged into "01010", which is an alternating
                 string.

    Thus, the answer is 3.


    --- Example 2 ---
    Input: s = "101"
    Output: 3
    Explanation:
    All prefixes of s = "101" are already alternating strings. Thus, the answer
    is 3.


    *** Constraints ***
    1 <= s.length <= 100
    s consists only of '0' and '1'.

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
/* Space Beats:  22.35% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countValidPrefixes(string s)
    {
        int result = 0;
        
        int zeroes = 0;
        int ones   = 0;
        for (const char& chr : s)
        {
            if (chr == '0')
                ++zeroes;
            else
                ++ones;

            if (abs(ones - zeroes) <= 1)
                ++result;
        }

        return result;
    }
};
