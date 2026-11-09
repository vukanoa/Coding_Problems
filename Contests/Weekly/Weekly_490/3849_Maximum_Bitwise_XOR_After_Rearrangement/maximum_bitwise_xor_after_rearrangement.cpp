/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3849) Maximum Bitwise XOR After Rearrangement
    =============================================

    ============
    Description:
    ============

    You are given two binary strings s and t, each of length n.

    You may rearrange the characters of t in any order, but s must remain
    unchanged.

    Return a binary string of length n representing the maximum integer value
    obtainable by taking the bitwise XOR of s and rearranged t.

    ================================================
    FUNCTION: string maximumXor(string s, string t);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "101", t = "011"
    Output: "110"
    Explanation:
        One optimal rearrangement of t is "011".
        The bitwise XOR of s and rearranged t is "101" XOR "011" = "110", which
        is the maximum possible.


    --- Example 2 ---
    Input: s = "0110", t = "1110"
    Output: "1101"
    Explanation:
        One optimal rearrangement of t is "1011".
        The bitwise XOR of s and rearranged t is "0110" XOR "1011" = "1101",
        which is the maximum possible.


    --- Example 3 ---
    Input: s = "0101", t = "1001"
    Output: "1111"
    Explanation:
        One optimal rearrangement of t is "1010".
        The bitwise XOR of s and rearranged t is "0101" XOR "1010" = "1111",
        which is the maximum possible.


    *** Constraints ***
    1 <= n == s.length == t.length <= 2 * 10^5
    s[i] and t[i] are either '0' or '1'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.16% */
/* Space Beats: 68.60% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string maximumXor(string s, string t)
    {
        const int N = s.size();
        string result;
        result.reserve(N); // To prevent repeated reallocations
        
        int freq[2] = {};
        for (const char& chr : t)
            ++freq[chr - '0'];

        for (int i = 0; i < N; i++)
        {
            if (s[i] == '0')
            {
                if (freq[1] > 0)
                {
                    result += '1';
                    --freq[1];
                }
                else
                {
                    result += '0';
                    --freq[0];
                }
            }
            else
            {
                if (freq[0] > 0)
                {
                    result += '1';
                    --freq[0];
                }
                else
                {
                    result += '0';
                    --freq[1];
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.98% */
/* Space Beats: 82.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Elegant {
public:
    string maximumXor(string s, string t)
    {
        const int N = s.size();
        string result;
        result.reserve(N); // To prevent reapeated reallocations

        int freq[2] = {};

        for (const char& chr : t)
            ++freq[chr - '0'];

        for (char chr : s)
        {
            int bit = (chr - '0') ^ 1;
            if (freq[bit] == 0)
                bit ^= 1;

            result += static_cast<char>((bit ^ (chr - '0')) + '0');
            --freq[bit];
        }

        return result;
    }
};
