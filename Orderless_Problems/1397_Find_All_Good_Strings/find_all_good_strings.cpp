/*
    ============
    === HARD ===
    ============

    ===========================
    1397) Find All Good Strings
    ===========================

    ============
    Description:
    ============

    Given the strings s1 and s2 of size n and the string evil, return the
    number of good strings.

    A good string has size n, it is alphabetically greater than or equal to s1,
    it is alphabetically smaller than or equal to s2, and it does not contain
    the string evil as a substring. Since the answer can be a huge number,
    return this modulo 10^9 + 7.

    ========================================================================
    FUNCTION: int findGoodStrings(int n, string s1, string s2, string evil);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
    Output: 51 
    Explanation: There are 25 good strings starting with 'a':
                 "aa","ac","ad",...,"az". Then there are 25 good strings
                 starting with 'c': "ca","cc","cd",...,"cz" and finally there
                 is one good string starting with 'd': "da". 

    --- Example 2 ---
    Input: n = 8, s1 = "leetcode", s2 = "leetgoes", evil = "leet"
    Output: 0 
    Explanation: All strings greater than or equal to s1 and smaller than or
                 equal to s2 start with the prefix "leet", therefore, there is
                 not any good string.

    --- Example 3 ---
    Input: n = 2, s1 = "gx", s2 = "gz", evil = "x"
    Output: 2


    *** Constraints ***
    s1.length == n
    s2.length == n
    s1 <= s2
    1 <= n <= 500
    1 <= evil.length <= 50
    All strings consist of lowercase English letters.

*/

#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you're comfortable with both:

        + KMP
        + DigitDP

    then it's not too bad. You just combine these two things.

*/

/* Time  Beats: 78.33% */
/* Space Beats: 73.33% */

/* Time  Complexity: O(n * M * 26) */ // N = pattern.size(), M = evil.size()
/* Space Complexity: O(n * M)      */

class KMP {
public:
    vector<int> calculate_LPS(string& pattern)
    {
        const int PATTERN_SIZE = pattern.size();

        vector<int> LPS(PATTERN_SIZE, 0);

        int prefix_len = 0;
        int i          = 1;

        while (i < PATTERN_SIZE)
        {
            if (pattern[prefix_len] == pattern[i])
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;
                i++;
            }
            else
            {
                if (prefix_len > 0)
                    prefix_len = LPS[prefix_len - 1];
                else
                    i++;
            }
        }

        return LPS;
    }
};

class Solution {
private:
    static constexpr int MOD = 1e9 + 7;

    int memo[501][51][2][2];

public:
    int findGoodStrings(int n, string s1, string s2, string evil)
    {
        KMP kmp;
        vector<int> LPS = kmp.calculate_LPS(evil);

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve(0, 0, true, true, n, s1, s2, evil, LPS);
    }

private:
    int solve(int idx,
              int evil_matched,
              bool lower_bound,
              bool upper_bound,
              int n,
              string& s1,
              string& s2,
              string& evil,
              vector<int>& LPS)
    {
        const int M = evil.size();

        if (evil_matched == M)
            return 0;

        if (idx == n)
            return 1;

        if (memo[idx][evil_matched][lower_bound][upper_bound] != -1)
            return memo[idx][evil_matched][lower_bound][upper_bound];

        char start_char = lower_bound ? s1[idx] : 'a';
        char end_char   = upper_bound ? s2[idx] : 'z';

        int result = 0;

        for (char curr_chr = start_char; curr_chr <= end_char; curr_chr++)
        {
            int next_evil_matched = evil_matched;

            while (next_evil_matched > 0 && evil[next_evil_matched] != curr_chr)
            {
                next_evil_matched = LPS[next_evil_matched - 1];
            }

            if (evil[next_evil_matched] == curr_chr)
                next_evil_matched++;

            result += solve(idx + 1,
                            next_evil_matched,
                            lower_bound && (curr_chr == start_char),
                            upper_bound && (curr_chr == end_char),
                            n,
                            s1,
                            s2,
                            evil,
                            LPS);

            result %= MOD;
        }

        return memo[idx][evil_matched][lower_bound][upper_bound] = result;
    }
};
