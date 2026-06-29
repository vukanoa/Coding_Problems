/*
    ============
    === EASY ===
    ============

    =========================================================
    1967) Number of Strings That Appear as Substrings in Word
    =========================================================

    ============
    Description:
    ============

    Given an array of strings patterns and a string word, return the number of
    strings in patterns that exist as a substring in word.

    A substring is a contiguous sequence of characters within a string.

    ==================================================================
    FUNCTION: int numOfStrings(vector<string>& patterns, string word);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: patterns = ["a","abc","bc","d"], word = "abc"
    Output: 3
    Explanation:
    - "a" appears as a substring in "abc".
    - "abc" appears as a substring in "abc".
    - "bc" appears as a substring in "abc".
    - "d" does not appear as a substring in "abc".
    3 of the strings in patterns appear as a substring in word.

    --- Example 2 ---
    Input: patterns = ["a","b","c"], word = "aaaaabbbbb"
    Output: 2
    Explanation:
    - "a" appears as a substring in "aaaaabbbbb".
    - "b" appears as a substring in "aaaaabbbbb".
    - "c" does not appear as a substring in "aaaaabbbbb".
    2 of the strings in patterns appear as a substring in word.

    --- Example 3 ---
    Input: patterns = ["a","a","a"], word = "ab"
    Output: 3
    Explanation: Each of the patterns appears as a substring in word "ab".


    *** Constraints ***
    1 <= patterns.length <= 100
    1 <= patterns[i].length <= 100
    1 <= word.length <= 100
    patterns[i] and word consist of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.74% */

/* Time  Complexity: O(P * N * M) */ // Where P is patterns.size()
/* Space Complexity: O(1)         */
class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word)
    {
        int result = 0;
        for (const string& pattern : patterns)
            result += word.find(pattern) != string::npos ? 1 : 0;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The idea is the same, though this one does not use the built-in "find()",
    instead here I implemented my own KMP.

*/

/* Time  Beats: 11.17% */
/* Space Beats: 9.71% */

/* Time  Complexity: O(P * (N + M)) */ // Where P is patterns.size()
/* Space Complexity: O(M)           */
class Solution_KMP {
public:
    int numOfStrings(vector<string>& patterns, string word)
    {
        int result = 0;
        for (const string& pattern : patterns)
            result += is_matching(word, pattern) ? 1 : 0;

        return result;
    }

private:
    bool is_matching(string s, string pattern)
    {
        const int N = s.size();
        const int M = pattern.size();

        /* Populate LPS */
        vector<int> LPS = calculate_LPS(pattern);

        int i = 0;
        int j = 0;
        while (i < N && j < M)
        {
            if (s[i] == pattern[j])
            {
                i++;
                j++;
            }
            else
            {
                if (j > 0)
                    j = LPS[j - 1];
                else
                    i++;
            }
        }

        return j == M;
    }

    vector<int> calculate_LPS(const string& pattern)
    {
        const int M = pattern.size();

        /* Initialize with Zeroes */
        vector<int> LPS(M, 0);

        int prefix_len = 0;
        int i          = 1;
        while (i < M)
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
