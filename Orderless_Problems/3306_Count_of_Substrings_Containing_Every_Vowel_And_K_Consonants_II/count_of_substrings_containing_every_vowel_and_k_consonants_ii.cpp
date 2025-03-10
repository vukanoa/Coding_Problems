/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================================
    3306) Count of Substrings Containing Every Vowel and K Consonants II
    ====================================================================

    ============
    Description:
    ============

    You are given a string word and a non-negative integer k.

    Return the total number of
    of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least
    once and exactly k consonants.

    =====================================================
    FUNCTION: long countOfSubstrings(string word, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "aeioqq", k = 1
    Output: 0
    Explanation:
    There is no substring with every vowe

    --- Example 2 ---
    Input: word = "aeiou", k = 0
    Output: 1
    Explanation:
    The only substring with every vowel and zero consonants is word[0..4],
    which is "aeiou".

    --- Example 3 ---
    Input: word = "ieaouqqieaouqq", k = 1
    Output: 3
    Explanation:
    The substrings with every vowel and one consonant are:
        word[0..5], which is "ieaouq".
        word[6..11], which is "qieaou".
        word[7..12], which is "ieaouq".


    *** Constraints ***
    5 <= word.length <= 2 * 10^5
    word consists only of lowercase English letters.
    0 <= k <= word.length - 5

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Sliding Window, however it uses "next_consonant" trick. Make sure to go
    through one example, such as this:

        word = "aeiouqqaeiouqqqq", k = 2

    using pen and paper and you'll get it.

    It's NOT intuitive, don't feel bad if you couldn't come up with it.

*/

/* Time  Beats: 37.81% */
/* Space Beats: 16.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long countOfSubstrings(string word, int k)
    {
        const int N = word.size();
        const int NUMBER_OF_VOWELS = 5;
        long result = 0;

        int L = 0;
        int R = 0;

        unordered_set<char> uset_vowels = {'a', 'e', 'i', 'o', 'u'};
        unordered_map<char, int> umap_vowels;
        int consonants = 0;

        /* Main "trick" to this problem */
        vector<int> next_consonant(N);
        int next_consonant_idx = N;
        for (int i = word.size() - 1; i >= 0; i--)
        {
            next_consonant[i] = next_consonant_idx;

            if ( ! uset_vowels.count(word[i]))
                next_consonant_idx = i;
        }

        /* Sliding Window */
        while (R < N)
        {
            char curr_chr = word[R];

            if (uset_vowels.count(curr_chr))
                umap_vowels[curr_chr]++;
            else
                consonants++;

            while (consonants > k)
            {
                char leftmost_chr = word[L];

                if (uset_vowels.count(leftmost_chr))
                {
                    umap_vowels[leftmost_chr]--;

                    if (umap_vowels[leftmost_chr] == 0)
                        umap_vowels.erase(leftmost_chr);
                }
                else
                    consonants--;

                L++;
            }

            while (L < R && umap_vowels.size() == NUMBER_OF_VOWELS && consonants == k)
            {
                result += next_consonant[R] - R;

                char leftmost_chr = word[L];

                if (uset_vowels.count(leftmost_chr))
                {
                    umap_vowels[leftmost_chr]--;

                    if (umap_vowels[leftmost_chr] == 0)
                        umap_vowels.erase(leftmost_chr);
                }
                else
                    consonants--;

                L++;
            }

            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is more in a spirit of "Sliding Window" technique, but it's a bit
    more UNINTUITIVE nonetheless.

    Unintuitiveness comes from this part:

        return at_least_k(word, k) - at_least_k(word, k + 1);

    and this:

        result += N - R; // This is the CRUX of this Solution


    The Explanation would be way too long and cumbersome and you wouldn't be
    able to understand it better than to take pen and paper and go through one
    example.

    That way you'll have the famous "Aha" moment. There's no other way around
    it.

*/

/* Time  Beats: 27.40% */
/* Space Beats: 50.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    long countOfSubstrings(string word, int k)
    {
        return at_least_k(word, k) - at_least_k(word, k + 1);
    }

private:
    long at_least_k(string word, int k)
    {
        const int N = word.size();
        const int NUMBER_OF_VOWELS = 5;
        long result = 0;

        int L = 0;
        int R = 0;

        unordered_set<char> uset_vowels = {'a', 'e', 'i', 'o', 'u'};
        unordered_map<char, int> umap_vowels;
        int consonants = 0;

        /* Sliding Window */
        while (R < word.length())
        {
            char curr_chr = word[R];

            if (uset_vowels.count(curr_chr))
                umap_vowels[curr_chr]++;
            else
                consonants++;

            // Shrink window while we have a valid substring.
            while (umap_vowels.size() == NUMBER_OF_VOWELS && consonants >= k)
            {
                result += N - R; // This is the CRUX of this Solution

                char leftmost_chr = word[L];

                if (uset_vowels.count(leftmost_chr))
                {
                    umap_vowels[leftmost_chr]--;

                    if (umap_vowels[leftmost_chr] == 0)
                        umap_vowels.erase(leftmost_chr);
                }
                else
                    consonants--;

                L++;
            }

            R++;
        }

        return result;
    }
};
