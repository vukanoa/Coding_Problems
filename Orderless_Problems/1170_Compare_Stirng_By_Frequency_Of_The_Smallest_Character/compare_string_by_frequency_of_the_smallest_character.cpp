/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    1170) Compare Strings by Frequency of the Smallest Character
    ============================================================

    ============
    Description:
    ============

    Let the function f(s) be the frequency of the lexicographically smallest
    character in a non-empty string s. For example, if s = "dcce" then f(s) = 2
    because the lexicographically smallest character is 'c', which has a
    frequency of 2.

    You are given an array of strings words and another array of query strings
    queries. For each query queries[i], count the number of words in words such
    that f(queries[i]) < f(W) for each W in words.

    Return an integer array answer, where each answer[i] is the answer to the
    ith query.

    ============================================================================================
    FUNCTION: vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words);
    ============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: queries = ["cbd"], words = ["zaaaz"]
    Output: [1]
    Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so
                 f("cbd") < f("zaaaz").

    --- Example 2 ---
    Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
    Output: [1,2]
    Explanation: On the first query only f("bbb") < f("aaaa"). On the second
                 query both f("aaa") and f("aaaa") are both > f("cc").


    *** Constraints ***
    1 <= queries.length <= 2000
    1 <= words.length <= 2000
    1 <= queries[i].length, words[i].length <= 10
    queries[i][j], words[i][j] consist of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.19% */
/* Space Beats: 30.52% */

/* Time  Complexity: O((Q + W) * L  +  W * logW) */
/* Space Complexity: O(W)                        */
class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words)
    {
        vector<int> result;

        vector<int> word_freqs;
        for (const string& word : words)
        {
            int freq = compute_smallest_character_frequency(word);
            word_freqs.push_back(freq);
        }

        /* Sort */
        sort(word_freqs.begin(), word_freqs.end());
        unsigned size = word_freqs.size();
        
        for (const auto &query : queries)
        {
            int freq = compute_smallest_character_frequency(query);

            auto iter = upper_bound(word_freqs.begin(), word_freqs.end(), freq);
            int idx   = distance(word_freqs.begin(), iter);

            result.push_back(size - idx);
        }
        
        return result;
    }

private:
    int compute_smallest_character_frequency(const string &word)
    {
        const int ALPHABET_LETTERS = 26;
        vector<int> character_freq(ALPHABET_LETTERS, 0);

        for (const char& chr : word)
            character_freq[chr - 'a']++;

        for (int i = 0; i < ALPHABET_LETTERS; i++)
        {
            if (character_freq[i] != 0)
                return character_freq[i];
        }

        return -1;
    }
};
