/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    2785) Sort Vowels in a String
    =============================

    ============
    Description:
    ============

    Given a 0-indexed string s, permute s to get a new string t such that:

        + All consonants remain in their original places. More formally, if
          there is an index i with 0 <= i < s.length such that s[i] is a
          consonant, then t[i] = s[i].

        + The vowels must be sorted in the nondecreasing order of their ASCII
          values. More formally, for pairs of indices i, j with
          0 <= i < j < s.length such that s[i] and s[j] are vowels, then
          t[i] must not have a higher ASCII value than t[j].

    Return the resulting string.

    The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in
    lowercase or uppercase. Consonants comprise all letters that are not vowels

    ======================================
    FUNCTION: string sortVowels(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "lEetcOde"
    Output: "lEOtcede"
    Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd'
                 are all consonants. The vowels are sorted according to their
                 ASCII values, and the consonants remain in the same places.

    --- Example 2 ---
    Input: s = "lYmpH"
    Output: "lYmpH"
    Explanation: There are no vowels in s (all characters in s are consonants),
                 so we return "lYmpH".

    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of letters of the English alphabet in uppercase and lowercase.
*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 21.11% */
/* Space Beats: 16.70% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    string sortVowels(string s)
    {
        if (s.length() == 1)
            return s;

        unordered_set<char> uset_vowels = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
        vector<char> vec_vowels;

        string result_str = "";

        for (const char& chr : s)
        {
            if (uset_vowels.count(chr))
                vec_vowels.push_back(chr);
        }

        /* Sort */
        sort(vec_vowels.begin(), vec_vowels.end());

        int idx = 0;
        for (const char& chr : s)
        {
            if (uset_vowels.count(chr))
            {
                result_str += vec_vowels[idx];
                idx++;
            }
            else
                result_str += chr;
        }

        return result_str;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.85% */
/* Space Beats: 14.79% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Counting_Sort {
public:
    string sortVowels(string s)
    {
        string result_str;

        unordered_set<char> uset_vowels = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
        unordered_map<char, int> vowel_freq;

        // Store the frequencies for each vowel
        for (const char& chr : s)
        {
            if (uset_vowels.count(chr))
                vowel_freq[chr]++;
        }

        string sorted_vowels = "AEIOUaeiou";

        int vowel_idx = 0;
        for (int i = 0; i < static_cast<int>(s.length()); i++)
        {
            if (uset_vowels.count(s[i])) // Vowel
            {
                // Skip to the leftmost available vowel
                while (vowel_freq[sorted_vowels[vowel_idx]] == 0)
                    vowel_idx++;

                result_str += sorted_vowels[vowel_idx];
                vowel_freq[sorted_vowels[vowel_idx]]--;
            }
            else // Consonant
                result_str += s[i];
        }

        return result_str;
    }
};
