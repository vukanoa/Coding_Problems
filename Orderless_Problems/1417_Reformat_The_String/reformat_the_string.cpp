/*
    ============
    === EASY ===
    ============

    ===========================
    1417) Reformat the String
    ===========================

    ============
    Description:
    ============

    You are given an alphanumeric string s. (Alphanumeric string is a string
    consisting of lowercase English letters and digits).

    You have to find a permutation of the string where no letter is followed by
    another letter and no digit is followed by another digit. That is, no two
    adjacent characters have the same type.

    Return the reformatted string or return an empty string if it is impossible
    to reformat the string.

    ====================================
    FUNCTION: string reformat(string s);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "a0b1c2"
    Output: "0a1b2c"
    Explanation: No two adjacent characters have the same type in "0a1b2c".
                 "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.

    --- Example 2 ---
    Input: s = "leetcode"
    Output: ""
    Explanation: "leetcode" has only characters so we cannot separate them by
                 digits.

    --- Example 3 ---
    Input: s = "1229857369"
    Output: ""
    Explanation: "1229857369" has only digits so we cannot separate them by
                 characters.

    *** Constraints ***
    1 <= s.length <= 500
    s consists of only lowercase English letters and/or digits.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string reformat(string s)
    {
        const int N = s.length();

        if (N == 1)
            return s;

        int digits = 0;
        for (const char& chr : s)
            digits += isdigit(chr) ? 1 : 0;

        int alphas = N - digits;

        if (abs(digits - alphas) > 1)
            return ""; // Emptry string. Impossible permutation

        int L = 0;
        int R = 0;
        while (R < N)
        {
            if (L % 2 == 0) // Even idx
            {
                if (digits >= alphas)
                {
                    while (R < N && !isdigit(s[R]))
                        R++;
                }
                else
                {
                    while (R < N && !isalpha(s[R]))
                        R++;
                }
            }
            else // Odd idx
            {
                if (digits >= alphas)
                {
                    while (R < N && !isalpha(s[R]))
                        R++;
                }
                else
                {
                    while (R < N && !isdigit(s[R]))
                        R++;
                }
            }

            swap(s[L], s[R]);

            // Increment
            L++;
            if (R < L)
                R = L;
        }

        return s;
    }
};
