/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    2730) Find the Longest Semi-Repetitive Substring
    ================================================

    ============
    Description:
    ============

    You are given a digit string s that consists of digits from 0 to 9.

    A string is called semi-repetitive if there is at most one adjacent pair
    of the same digit. For example, "0010", "002020", "0123", "2002", and
    "54944" are semi-repetitive while the following are not: "00101022"
    (adjacent same digit pairs are 00 and 22), and "1101234883"
    (adjacent same digit pairs are 11 and 88).

    Return the length of the longest semi-repetitive of s.

    =======================================================
    FUNCTION: int longestSemiRepetitiveSubstring(string s);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "52233"
    Output: 4
    Explanation:
    The longest semi-repetitive substring is "5223". Picking the whole string
    "52233" has two adjacent same digit pairs 22 and 33, but at most one is
    allowed.

    --- Example 2 ---
    Input: s = "5494"
    Output: 4
    Explanation:
    s is a semi-repetitive string.

    --- Example 3 ---
    Input: s = "1111111"
    Output: 2
    Explanation:
    The longest semi-repetitive substring is "11". Picking the substring "111"
    has two adjacent same digit pairs, but at most one is allowed.


    *** Constraints ***
    1 <= s.length <= 50
    '0' <= s[i] <= '9'

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding-Window techniqiue.

*/

/* Time  Beats: 53.97% */
/* Space Beats: 27.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s)
    {
        const int N = s.length();
        int result = 1;

        int L = 0;
        int R = 1;

        bool adjacent_used = false;
        while (R < N)
        {
            while (s[R-1] == s[R] && L < R && adjacent_used)
            {
                L++;
                if (s[L-1] == s[L])
                    adjacent_used = false;
            }

            if (s[R-1] == s[R])
                adjacent_used = true;

            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};
