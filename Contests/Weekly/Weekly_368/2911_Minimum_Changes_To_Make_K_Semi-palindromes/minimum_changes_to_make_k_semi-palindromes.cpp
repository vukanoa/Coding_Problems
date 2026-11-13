/*
    ============
    === HARD ===
    ============

    ================================================
    2911) Minimum Changes to Make K Semi-palindromes
    ================================================

    ============
    Description:
    ============


    Given a string s and an integer k, partition s into k substrings such that
    the letter changes needed to make each substring a semi-palindrome are
    minimized.

    Return the minimum number of letter changes required.

    A semi-palindrome is a special type of string that can be divided into
    palindromes based on a repeating pattern. To check if a string is a
    semi-palindrome:​

        + Choose a positive divisor d of the string's length. d can range from
          1 up to, but not including, the string's length. For a string of
          length 1, it does not have a valid divisor as per this definition,
          since the only divisor is its length, which is not allowed.

        + For a given divisor d, divide the string into groups where each group
          contains characters from the string that follow a repeating pattern
          of length d. Specifically, the first group consists of characters at
          positions 1, 1 + d, 1 + 2d, and so on; the second group includes
          characters at positions 2, 2 + d, 2 + 2d, etc.

        + The string is considered a semi-palindrome if each of these groups
        forms a palindrome.


    + Consider the string "abcabc":

        The length of "abcabc" is 6. Valid divisors are 1, 2, and 3.
        For d = 1: The entire string "abcabc" forms one group. Not a palindrome.
        For d = 2:
            Group 1 (positions 1, 3, 5): "acb"
            Group 2 (positions 2, 4, 6): "bac"
            Neither group forms a palindrome.
        For d = 3:
            Group 1 (positions 1, 4): "aa"
            Group 2 (positions 2, 5): "bb"
            Group 3 (positions 3, 6): "cc"
            All groups form palindromes. Therefore, "abcabc" is a semi-palindrome.

    ================================================================
    FUNCTION: int minimumChanges(const string &s, int k, int i = 0);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcac", k = 2
    Output: 1
    Explanation: Divide s into "ab" and "cac". "cac" is already
    semi-palindrome. Change "ab" to "aa", it becomes semi-palindrome with d =
    1.

    --- Example 2 ---
    Input: s = "abcdef", k = 2
    Output: 2
    Explanation: Divide s into substrings "abc" and "def". Each needs one
    change to become semi-palindrome.

    --- Example 3 ---
    Input: s = "aabbaa", k = 3
    Output: 0
    Explanation: Divide s into substrings "aa", "bb" and "aa". All are already
    semi-palindromes.


    *** Constraints ***
    2 <= s.length <= 200
    1 <= k <= s.length / 2
    s contains only lowercase English letters.

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.31% */

/* Time  Complexity: O(N^3 + N^2 * K) */
/* Space Complexity: O(N^2 + N * K)   */
class Solution {
private:
    int memo[201][101] = {};

    int memo_s[201][201];
    int memo_d[201][201];

public:
    int minimumChanges(const string &s, int k, int i = 0)
    {
        const int N = s.size();

        /* Memset */
        memset(memo_s, 1, sizeof(memo_s)); // Minimum is 2, i.e. 1 is INVALID!

        for (int d = 1; d <= N/2; d++)
        {
            /* Memset */
            memset(memo_d, 0, sizeof(memo_d)); // Minimum is 1, i.e. 0 is INVALID!

            for (int len = 2 * d; len <= N; len += d)
            {
                for (int idx = 0; idx + len <= N; idx++)
                {
                    int ops = 0;
                    for (int offset = 0; offset < d; offset++)
                        ops += s[idx + offset] != s[idx + len - (d - offset)];

                    memo_d[idx][len] = ops + memo_d[idx + d][len - 2 * d];
                    memo_s[idx][len] = min(memo_s[idx][len],
                                           memo_d[idx][len]);
                }

            }
        }

        return solve(0, k, s);
    }

private:
    int solve(int idx, int k, const string& s)
    {
        const int N = s.size();

        if (idx >= N || k <= 0)
            return (idx == N && k == 0) ? 0 : 10000;

        if (memo[idx][k] == 0)
        {
            memo[idx][k] = 10000;

            for (int len = 2; idx + len <= s.size(); ++len)
            {
                int result = 1 + memo_s[idx][len] + solve(idx + len, k - 1, s);

                memo[idx][k] = min(memo[idx][k], result);
                                   
            }
        }

        return memo[idx][k] - 1; // Since "pos" are 1-based
    }
};
