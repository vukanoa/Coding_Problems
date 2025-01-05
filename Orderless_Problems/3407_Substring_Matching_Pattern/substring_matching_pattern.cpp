/*
    ============
    === EASY ===
    ============

    ================================
    3407) Substring Matching Pattern
    ================================

    ============
    Description:
    ============

    You are given a string s and a pattern string p, where p contains exactly
    one '*' character.

    The '*' in p can be replaced with any sequence of zero or more characters.

    Return true if p can be made a substring of s, and false otherwise.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ============================================
    FUNCTION: bool hasMatch(string s, string p);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcode", p = "ee*e"
    Output: true
    Explanation: By replacing the '*' with "tcod", the substring "eetcode"
                 matches the pattern.

    --- Example 2 ---
    Input: s = "car", p = "c*v"
    Output: false
    Explanation:
    There is no substring matching the pattern.

    --- Example 3 ---
    Input: s = "luck", p = "u*"
    Output: true
    Explanation:
    The substrings "u", "uc", and "uck" match the pattern.


    *** Constraints ***
    1 <= s.length <= 50
    1 <= p.length <= 50
    s contains only lowercase English letters.
    p contains only lowercase English letters and exactly one '*'

*/

#include <string>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This is a hard labour...

    First, notice that there are 3 possibilites:
        1. "*abcd"  // Begins with a '*'
        2. "abcd*'  // Ends   with a '*'
        3. "ab*cd"  // '*' is in the middle

    If it begins with a '*', then we only need to see if there is a substring
    "abcd"(string AFTER the '*') in stirng s.

    If it does NOT begin with a star, then first we must find the substring
    that is BEFORE the '*' in string p, somewhere in string s.

    If we do NOT find it, then return false immediately.

    If we've found the prefix, but string p ENDS with a '*', then we're done.
    We return true.

    If it doesn't end with a '*', then we need to match the remaining part of
    the string p in string s, but starting the the first character that is NOT
    a part of the prefix.

    Example:

             01234567          0123
        s = "leetcode" ,  p = "ee*e"
              ^^
          ____||______
          |          |
        beginning   end
          of        of
        prefix      prefix


    We need to begin the search for the remaining part of string p(string after
    the '*'), starting from index 3(character 't').

    It's kind of difficult not to make a mistake while writing this code, but
    try to write it slowly and I'm sure it'll be alright.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M)     */
class Solution_Brute_Force {
public:
    bool hasMatch(string s, string p)
    {
        const int N = s.length();
        const int M = p.length();

        if (N < M-1)
            return false;
        else if (M == 1)
            return true;

        if (p[0] == '*') // If it begins with '*' character
        {
            string substring_p = p.substr(1, M-1);

            if (s.find(substring_p) != string::npos)
                return true;

            return false;
        }


        for (int i = 0; i <= N-(M-1); i++)
        {
            if (s[i] != p[0])
                continue;

            bool found_star = false;
            int p_idx = 0;

            while (i + p_idx < N && s[i + p_idx] == p[p_idx])
            {
                if (p[p_idx + 1] == '*')
                {
                    found_star = true;
                    break;
                }

                p_idx++;
            }

            if ( ! found_star)
                continue;

            int star_idx = p_idx + 1;
            p_idx = star_idx + 1; // Skip to character after the '*'


            if (star_idx + 1 == M) // if '*' is the last character
                return true;

            for (int j = i + star_idx; j < N; j++)
            {
                if (s[j] != p[p_idx])
                    continue;

                int further_p_idx = p_idx;
                while (j + further_p_idx - (star_idx + 1) < N && further_p_idx < M &&
                        s[j + further_p_idx - (star_idx + 1)] == p[further_p_idx])
                {
                    further_p_idx++;
                }

                if (further_p_idx == M)
                    return true;
            }
        }

        return false;
    }
};
