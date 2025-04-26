/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================================
    3106) Lexicographically Smallest String After Operations With Constraint
    ========================================================================

    ============
    Description:
    ============

    You are given a string s and an integer k.

    Define a function distance(s1, s2) between two strings s1 and s2 of the
    same length n as:

        + The sum of the minimum distance between s1[i] and s2[i] when the
          characters from 'a' to 'z' are placed in a cyclic order, for all i in
          the range [0, n - 1].

    For example, distance("ab", "cd") == 4, and distance("a", "z") == 1.

    You can change any letter of s to any other lowercase English letter, any
    number of times.

    Return a string denoting the
    string t you can get after some changes, such that distance(s, t) <= k.

    ====================================================
    FUNCTION: string getSmallestString(string s, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "zbbz", k = 3
    Output: "aaaz"
    Explanation: Change s to "aaaz". The distance between "zbbz" and "aaaz" is
                 equal to k = 3.

    --- Example 2 ---
    Input: s = "xaxcd", k = 4
    Output: "aawcd"
    Explanation:
    The distance between "xaxcd" and "aawcd" is equal to k = 4.

    --- Example 3 ---
    Input: s = "lol", k = 0
    Output: "lol"
    Explanation:
    It's impossible to change any character as k = 0.


    *** Constraints ***
    1 <= s.length <= 100
    0 <= k <= 2000
    s consists only of lowercase English letters.

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
/* Space Beats:  19.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution  {
public:
    string getSmallestString(string s, int k)
    {
        if (k == 0)
            return s;

        const int N = s.length();
        const int ALPHABET_LENGTH = 26;
        string result;

        int sum = 0;

        for (const char& curr_chr : s)
        {
            int  curr_chr_idx = curr_chr - 'a';

            // cout << "\n\tCurr_chr: " << curr_chr;
            for (int i = 0; i < ALPHABET_LENGTH; i++)
            {
                int mod  = mathematical_mod(i - curr_chr_idx);
                int mod2 = abs(i - curr_chr_idx);

                mod = min(mod, mod2);

                // cout << "  mod: " << mod;

                if (sum + mod <= k)
                {
                    result += char(i + 'a');
                    sum += mod;

                    break;
                }
            }
        }


        return result;
    }

private:
    int mathematical_mod(int num)
    {
        const int ALPHABET_LENGTH = 26;
        return (num % ALPHABET_LENGTH + ALPHABET_LENGTH) % ALPHABET_LENGTH;
    }
};
