/*
    ============
    === HARD ===
    ============

    ============================
    76) Minimum Window Substring
    ============================

    ============
    Description:
    ============

    Given two strings 's' and 't' lengths 'm' and 'n' respectively, return the
    minimum window substring of 's' such that every character in 't'(including
    duplicates) is included in the window. If there is no such substring,
    return the empty string "".

    =====
    Node: The testcases will be generated such that the answer is unique.
    =====

    ================================================
    FUNCTION: string minWindow(string s, string t);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "ADOBECODEBANC", t = "ABC"
    Output: "BANC"

    --- Example 2 ---
    Input:  s = "a", t = "a"
    Output: "a"

    --- Example 3 ---
    Input:  s = "a", t = "aa"
    Output: ""

    *** Constraints ***
    m == s.length
    n == t.length
    1 <= m, n <= 10^5
    s and t consist of uppercase and lowercase English letters.

*/

#include <climits>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Sliding Window" technique. Even if this is "HARD" officially, it's
    a basic use of this technique.

    If you don't understand it, try with some "EASY" and "MEDIUM" ones first,
    then come back and this'll be a breeze.

*/

/* Time  Beats: 23.66% */
/* Space Beats: 42.90% */

/* Time  Complexity: O(M + N * 128) --> O(M + N) */
/* Space Complexity: O(128) --> O(1)             */
class Solution {
public:
    string minWindow(string s, string t)
    {
        const int M = s.size();
        const int N = t.size();
        int substr_idx_start = -1;
        int substr_len = INT_MAX;

        if (M < N)
            return "";

        int ascii_s[128] = {0};
        int ascii_t[128] = {0};

        for (const char& chr : t)
            ascii_t[chr]++;

        int L = 0;
        int R = 0;
        while (R < M)
        {
            ascii_s[s[R]]++;

            while (L <= R && valid(ascii_s, ascii_t))
            {
                if ((R - L + 1) < substr_len)
                {
                    substr_len = R - L + 1;
                    substr_idx_start = L;
                }

                ascii_s[s[L]]--;
                L++;
            }

            // Increment
            R++;
        }

        return substr_idx_start == -1 ? "" : s.substr(substr_idx_start, substr_len);
    }

private:
    bool valid(int (& ascii_s)[128], int (& ascii_t)[128])
    {
        for (int i = 0; i < 128; i++)
        {
            if (ascii_s[i] < ascii_t[i])
                return false;
        }

        return true;
    }
};
