/*
    ============
    === HARD ===
    ============

    ============================================================================
    3734) Lexicographically Smallest Palindromic Permutation Greater Than Target
    ============================================================================

    ============
    Description:
    ============

    You are given two strings s and target, each of length n, consisting of
    lowercase English letters.

    Return the lexicographically smallest string that is both a palindromic
    permutation of s and strictly greater than target. If no such permutation
    exists, return an empty string.

    ====================================================================
    FUNCTION: string lexPalindromicPermutation(string s, string target);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "baba", target = "abba"
    Output: "baab"
    Explanation:
        The palindromic permutations of s (in lexicographical order) are "abba"
        and "baab". The lexicographically smallest permutation that is strictly
        greater than target is "baab".

    --- Example 2 ---
    Input: s = "baba", target = "bbaa"
    Output: ""
    Explanation:
        The palindromic permutations of s (in lexicographical order) are "abba"
        and "baab". None of them is lexicographically strictly greater than
        target. Therefore, the answer is "".

    --- Example 3 ---
    Input: s = "abc", target = "abb"
    Output: ""
    Explanation:
    s has no palindromic permutations. Therefore, the answer is "".

    --- Example 4 ---
    Input: s = "aac", target = "abb"
    Output: "aca"
    Explanation:
        The only palindromic permutation of s is "aca".
        "aca" is strictly greater than target. Therefore, the answer is "aca".


    *** Constraints ***
    1 <= n == s.length == target.length <= 300
    s and target consist of only lowercase English letters.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 6.15% */
/* Space Beats: 6.15% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    string lexPalindromicPermutation(string s, string target)
    {
        const int N = s.size();

        int freq[26] = {};

        if (N == 1)
        {
            // If size is 1 then direct compare
            if (s > target)
                return s;
            else
                return "";
        }

        for (const char& chr : s)
            ++freq[chr - 'a'];

        char mid = '#';
        int odd_count = 0;

        for (int i = 0; i < 26; i++)
        {
            if (freq[i] % 2)
            {
                // Odd count ---> this becomes the middle character
                mid = static_cast<char>(i + 'a');

                --freq[i];
                ++odd_count;
            }

            freq[i] /= 2;

            if (odd_count >= 2)
                return "";
        }

        const int HALF = N / 2;
        string result = "";
        string prefix = "";

        for (int i = 0; i < HALF; i++)
        {
            string curr = prefix;
            bool is_there_any = false;

            for (int j = 0; j < 26; j++)
            {
                if (freq[j])
                {
                    --freq[j];
                    curr += static_cast<char>(j + 'a');

                    string possible = is_possible(N, freq, curr, mid, target);

                    if (possible != "")
                    {
                        prefix = curr;
                        is_there_any = true;

                        if (result == "")
                            result = possible;
                        else
                            result = min(result, possible);

                        break;
                    }

                    ++freq[j];
                    curr.pop_back();
                }
            }

            if ( ! is_there_any)
                return "";
        }

        return result;
    }

private:
    string is_possible(const int N, int freq[26], string curr, char &mid, string& target)
    {
        int tmp_freq[26];
        copy(freq, freq + 26, tmp_freq);

        // This gives the max palindrome achievable with the current prefix
        // (descending order)
        for (int i = 25; i >= 0; i--)
        {
            while (tmp_freq[i])
            {
                curr += static_cast<char>(i + 'a');
                tmp_freq[i]--;
            }
        }

        if (mid != '#')
        {
            // Odd-length palindrome: left half + mid + reverse(left half)
            string tmp = curr;
            curr += mid;

            /* Reverse */
            reverse(tmp.begin(), tmp.end());

            curr.append(tmp.begin(), tmp.end());
        }
        else
        {
            // Even-length palindrome: left half + reverse(left half)
            string tmp = curr;

            /* Reverse */
            reverse(tmp.begin(), tmp.end());

            curr.append(tmp.begin(), tmp.end());
        }

        // Feasibility check: only valid if this (largest possible) candidate beats target
        return curr > target ? curr : "";
    }
};
