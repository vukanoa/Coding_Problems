/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3305) Count of Substrings Containing Every Vowel and K Consonants I
    ===================================================================

    ============
    Description:
    ============

    You are given a string word and a non-negative integer k.

    Return the total number of substrings of word that contain every vowel
    ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.

    ====================================================
    FUNCTION: int countOfSubstrings(string word, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "aeioqq", k = 1
    Output: 0
    Explanation:
    There is no substring with every vowel.

    --- Example 2 ---
    Input: word = "aeiou", k = 0
    Output: 1
    Explanation: The only substring with every vowel and zero consonants is
                 word[0..4], which is "aeiou".

    --- Example 3 ---
    Input: word = "ieaouqqieaouqq", k = 1
    Output: 3
    Explanation:
    The substrings with every vowel and one consonant are:
        word[0..5], which is "ieaouq".
        word[6..11], which is "qieaou".
        word[7..12], which is "ieaouq".


    *** Constraints ***
    5 <= word.length <= 250
    word consists only of lowercase English letters.
    0 <= k <= word.length - 5

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.00% */
/* Space Beats: 18.99% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countOfSubstrings(string word, int k)
    {
        const int N = word.length();
        const int VOWELS_SIZE = 5;
        int result = 0;

        unordered_set<char> uset_vowels = {'a', 'e', 'i', 'o', 'u'};

        for (int i = 0; i < N; i++)
        {
            unordered_map<char,int> umap_vowels;
            int consonants = 0;

            for (int x = i; x < N; x++)
            {
                if (uset_vowels.count(word[x]))
                    umap_vowels[word[x]]++;
                else
                    consonants++;

                if (umap_vowels.size() == VOWELS_SIZE && consonants == k)
                    result++;

                // if (consonants > k)
                //     break;
            }
        }

        return result;
    }
};
