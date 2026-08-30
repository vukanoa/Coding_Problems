/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    3913) Solve Vowels By Frequency
    ===============================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English characters.

    Rearrange only the vowels in the string so that they appear in
    non-increasing order of their frequency.

    If multiple vowels have the same frequency, order them by the position of
    their first occurrence in s.

    Return the modified string.

    Vowels are 'a', 'e', 'i', 'o', and 'u'.

    The frequency of a letter is the number of times it occurs in the string.

    ======================================
    FUNCTION: string sortVowels(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcode"
    Output: "leetcedo"
    Explanation:
        Vowels in the string are ['e', 'e', 'o', 'e'] with frequencies: e = 3,
        o = 1.
        Sorting in non-increasing order of frequency and placing them back into
        the vowel positions results in "leetcedo".

    --- Example 2 ---
    Input: s = "aeiaaioooa"
    Output: "aaaaoooiie"
    Explanation:
        Vowels in the string are ['a', 'e', 'i', 'a', 'a', 'i', 'o', 'o', 'o',
        'a'] with frequencies: a = 4, o = 3, i = 2, e = 1.
        Sorting them in non-increasing order of frequency and placing them back
        into the vowel positions results in "aaaaoooiie".

    --- Example 3 ---
    Input: s = "baeiou"
    Output: "baeiou"
    Explanation:
        Each vowel appears exactly once, so all have the same frequency.
        Thus, they retain their relative order based on first occurrence, and
        the string remains unchanged.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters

*/

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.61% */
/* Space Beats: 23.73% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string sortVowels(string s)
    {
        const int N = s.size();

        int freq[26] = {};
        for (int i = 0; i < N; i++)
            ++freq[s[i] - 'a'];

        int first_occurrence[26] = {};
        for (int i = N-1; i >= 0; i--)
            first_occurrence[s[i] - 'a'] = i;


        unordered_set<int>  uset_vowels = {'a', 'e', 'i', 'o', 'u'};
        vector<vector<int>> vowel_info;

        for (int i = 0; i < 26; i++)
        {
            if (freq[i] == 0 || uset_vowels.count(static_cast<char>(i + 'a')) == 0)
                continue;

            vowel_info.push_back( {freq[i], first_occurrence[i], i} );
        }

        /* Sort */
        sort(vowel_info.begin(), vowel_info.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0])
            {
                return a[1] < b[1]; // Second by "first_occurrence" indx in ASC
            }
            
            return a[0] > b[0]; // First by "frequency" in DESC order
        });


        vector<int> vowel_indices;
        vowel_indices.reserve(N);

        for (int i = 0; i < N; i++)
        {
            if (uset_vowels.count(s[i]))
                vowel_indices.push_back(i);
        }

        int i = 0;
        for (const int& vowel_idx : vowel_indices)
        {
            s[vowel_idx] = static_cast<char>(vowel_info[i][2] + 'a');

            --vowel_info[i][0];        // Decrease Frequency
            if (vowel_info[i][0] == 0) // Frequency == 0?
                ++i;
        }

        return s;
    }
};
