/*
    ============
    === EASY ===
    ============

    ====================================================
    3216) Lexicographically Smallest String After a Swap
    ====================================================

    ============
    Description:
    ============

    Given a string s containing only digits, return the

    that can be obtained after swapping adjacent digits in s with the same
    parity at most once.

    Digits have the same parity if both are odd or both are even. For example,
    5 and 9, as well as 2 and 4, have the same parity, while 6 and 9 do not.

    =============================================
    FUNCTION: string getSmallestString(string s);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "45320"
    Output: "43520"
    Explanation:
    s[1] == '5' and s[2] == '3' both have the same parity, and swapping them
    results in the lexicographically smallest string.

    --- Example 2 ---
    Input: s = "001"
    Output: "001"
    Explanation:
    There is no need to perform a swap because s is already the
    lexicographically smallest.


    *** Constraints ***
    2 <= s.length <= 100
    s consists only of digits.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  23.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string getSmallestString(string s)
    {
        const int N = s.length();

        for (int i = 0; i < N-1; i++)
        {
            if (s[i] <= s[i+1])
                continue;

            if ((s[i] % 2 == 1) && (s[i+1] % 2 == 1))
            {
                char tmp = s[i];
                s[i]   = s[i+1];
                s[i+1] = tmp;

                return s;
            }

            if ((s[i] % 2 == 0) && (s[i+1] % 2 == 0))
            {
                char tmp = s[i];
                s[i]   = s[i+1];
                s[i+1] = tmp;

                return s;
            }
        }

        return s;
    }
};
