/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3713) Longest Balanced Substring I
    ==================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    A substring of s is called balanced if all distinct characters in the
    substring appear the same number of times.

    Return the length of the longest balanced substring of s.

    ========================================
    FUNCTION: int longestBalanced(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abbac"
    Output: 4
    Explanation: The longest balanced substring is "abba" because both distinct
                 characters 'a' and 'b' each appear exactly 2 times.

    --- Example 2 ---
    Input: s = "zzabccy"
    Output: 4
    Explanation: The longest balanced substring is "zabc" because the distinct
                 characters 'z', 'a', 'b', and 'c' each appear exactly 1
                 time.

    --- Example 3 ---
    Input: s = "aba"
    Output: 2
    Explanation: One of the longest balanced substrings is "ab" because both
                 distinct characters 'a' and 'b' each appear exactly 1 time.
                 Another longest balanced substring is "ba".

    *** Constraints ***
    1 <= s.length <= 1000
    s consists of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.88% */
/* Space Beats: 96.34% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int longestBalanced(string s)
    {
        const int N = s.length();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int freq[26] = {};
            int max_freq = 0;
            int distinct_count = 0;

            for (int j = i; j < N; j++)
            {
                int idx = s[j] - 'a';

                if (freq[idx] == 0)
                    distinct_count++;

                max_freq = max(max_freq, ++freq[idx]);

                int curr_window_len = j - i + 1;

                if (curr_window_len == distinct_count * max_freq)
                    result = max(result, curr_window_len);
            }
        }

        return result;
    }
};
