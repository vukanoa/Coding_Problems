/*
    ============
    === HARD ===
    ============

    ==========================================
    2014) Longest Subsequence Repeated K Times
    ==========================================

    ============
    Description:
    ============

    You are given a string s of length n, and an integer k. You are tasked to
    find the longest subsequence repeated k times in string s.

    A subsequence is a string that can be derived from another string by
    deleting some or no characters without changing the order of the remaining
    characters.

    A subsequence seq is repeated k times in the string s if seq * k is a
    subsequence of s, where seq * k represents a string constructed by
    concatenating seq k times.

        For example, "bba" is repeated 2 times in the string "bababcba",
        because the string "bbabba", constructed by concatenating "bba" 2
        times, is a subsequence of the string "bababcba".

    Return the longest subsequence repeated k times in string s. If multiple
    such subsequences are found, return the lexicographically largest one.

    If there is no such subsequence, return an empty string.

    ==============================================================
    FUNCTION: string longestSubsequenceRepeatedK(string s, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "letsleetcode", k = 2
    Output: "let"
    Explanation: There are two longest subsequences repeated 2 times: "let" and
                 "ete". "let" is the lexicographically largest one.

    --- Example 2 ---
    Input: s = "bb", k = 2
    Output: "b"
    Explanation: The longest subsequence repeated 2 times is "b".

    --- Example 3 ---
    Input: s = "ab", k = 2
    Output: ""
    Explanation: There is no subsequence repeated 2 times. Empty string is
                 returned.


    *** Constraints ***
    n == s.length
    2 <= n, k <= 2000
    2 <= n < k * 8
    s consists of lowercase English letters.

*/

#include <queue>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There is no fancy algorithm, just brute-force it.
    Look at the Constraints, we're allowed to do that.

*/

/* Time  Beats: 87.86% */
/* Space Beats: 70.71% */

/* Time  Complexity: O(N * (floor(n / k)!)) */
/* Space Complexity: O(N * (floor(n / k)!)) */
class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k)
    {
        vector<int> freq(26);
        for (const char& chr : s)
            freq[chr - 'a']++;

        vector<char> candidate;
        for (int i = 25; i >= 0; i--)
        {
            if (freq[i] >= k)
                candidate.push_back(i + 'a');
        }

        queue<string> queue;
        for (const char& chr : candidate)
            queue.push(string(1, chr));


        string result = "";
        while ( ! queue.empty())
        {
            string curr = queue.front();
            queue.pop();

            if (curr.size() > result.size())
                result = curr;

            // Generate the next candidate string
            for (const char& ch : candidate)
            {
                string next = curr + ch;
                if (is_k_repeated_subsequence(s, next, k))
                    queue.push(next);

            }
        }

        return result;
    }

private:
    bool is_k_repeated_subsequence(const string& s, const string& t, int k)
    {
        int idx = 0;
        int matched = 0;

        const int N = s.size();
        const int M = t.size();

        for (const char& chr : s)
        {
            if (chr == t[idx])
            {
                idx++;

                if (idx == M)
                {
                    idx = 0;
                    matched++;

                    if (matched == k)
                        return true;
                }
            }
        }

        return false;
    }
};
