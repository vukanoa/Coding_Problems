/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    3081) Replace Question Marks in String to Minimize Its Value
    ============================================================

    ============
    Description:
    ============

    You are given a string s. s[i] is either a lowercase English letter or '?'.

    For a string t having length m containing only lowercase English letters,
    we define the function cost(i) for an index i as the number of characters
    equal to t[i] that appeared before it, i.e. in the range [0, i - 1].

    The value of t is the sum of cost(i) for all indices i.

    For example, for the string t = "aab":

        + cost(0) = 0
        + cost(1) = 1
        + cost(2) = 0
        + Hence, the value of "aab" is 0 + 1 + 0 = 1.

    Your task is to replace all occurrences of '?' in s with any lowercase
    English letter so that the value of s is minimized.

    Return a string denoting the modified string with replaced occurrences of
    '?'. If there are multiple strings resulting in the minimum value, return
    the lexicographically smallest one.

    ===============================================
    FUNCTION: string minimizeStringValue(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

#include <algorithm>
#include <climits>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 83.06% */
/* Space Beats: 87.98% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(log)      */ // Because of C++'s Sort
class Solution {
public:
    string minimizeStringValue(string s)
    {
        const int N = s.length();
        vector<int> freq(26, 0);

        string str_tmp = "";
        for (const auto& chr : s)
        {
            if (chr != '?')
                freq[chr - 'a']++;
        }

        for (int idx = 0; idx < N; idx++)
        {
            if (s[idx] != '?')
                continue;

            int min_freq_idx = 0;
            int min_freq = INT_MAX;

            for (int i = 0; i < 26; ++i)
            {
                if (freq[i] < min_freq)
                {
                    min_freq = freq[i];
                    min_freq_idx = i;
                }
            }

            str_tmp += char('a' + min_freq_idx);
            freq[min_freq_idx]++;
        }

        /* Sort */
        sort(str_tmp.begin(), str_tmp.end());

        int j = 0;
        for (int i = 0; i < N; ++i)
        {
            if (s[i] == '?')
                s[i] = str_tmp[j++];
        }

        return s;
    }
};
