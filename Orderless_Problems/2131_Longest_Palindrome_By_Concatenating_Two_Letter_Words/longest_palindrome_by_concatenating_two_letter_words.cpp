/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    2131) Longest Palindrome by Concatenating Two Letter Words
    ==========================================================

    ============
    Description:
    ============

    You are given an array of strings words. Each element of words consists of
    two lowercase English letters.

    Create the longest possible palindrome by selecting some elements from
    words and concatenating them in any order. Each element can be selected at
    most once.

    Return the length of the longest palindrome that you can create. If it is
    impossible to create any palindrome, return 0.

    A palindrome is a string that reads the same forward and backward.

    =======================================================
    FUNCTION: int longestPalindrome(vector<string>& words);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["lc","cl","gg"]
    Output: 6
    Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of
                 length 6. Note that "clgglc" is another longest palindrome
                 that can be created.


    --- Example 2 ---
    Input: words = ["ab","ty","yt","lc","cl","ab"]
    Output: 8
    Explanation: One longest palindrome is:
                 "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8. Note that
                 "lcyttycl" is another longest palindrome that can be created.


    --- Example 3 ---
    Input: words = ["cc","ll","xx"]
    Output: 2
    Explanation: One longest palindrome is "cc", of length 2. Note that "ll" is
                 another longest palindrome that can be created, and so is "xx"


    *** Constraints ***
    1 <= words.length <= 10^5
    words[i].length == 2
    words[i] consists of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 80.25% */
/* Space Beats: 73.05% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int longestPalindrome(vector<string>& words)
    {
        const int N = words.size();
        const int LEN_OF_WORD = 2;
        int result = 0;

        unordered_map<string, int> umap_same;

        unordered_map<string, int> umap_small;
        unordered_map<string, int> umap_big;

        for (const string& word : words)
        {
            if (word[0] == word[1])
            {
                umap_same[word]++;
            }
            else if (word[0] < word[1])
            {
                umap_small[word]++;
            }
            else
            {
                umap_big[word]++;
            }
        }

        for (const auto& [word, freq] : umap_small)
        {
            int freq_of_big = 0;

            string mirror_word = "";
            mirror_word += word[1];
            mirror_word += word[0];

            // string mirror_word = string() + word[1] + word[0];
            // string mirror_word = string(1, word[1]) + word[0];

            if (umap_big.find(mirror_word) != umap_big.end())
            {
                freq_of_big = umap_big[mirror_word];
            }

            int minn = min(freq, freq_of_big);

            result += minn * 2 * LEN_OF_WORD;
        }

        vector<int> freqs_of_same;
        for (const auto& [word, freq] : umap_same)
        {
            freqs_of_same.push_back(freq);
        }

        sort(freqs_of_same.begin(), freqs_of_same.end(), greater<int>());


        bool odd_num_of_same = false;

        if ( ! freqs_of_same.empty())
        {
            result += freqs_of_same[0] * LEN_OF_WORD;

            if (freqs_of_same[0] & 1)
                odd_num_of_same = true;
        }

        for (size_t i = 1; i < freqs_of_same.size(); i++)
        {
            if (freqs_of_same[i] & 1)
            {
                if (odd_num_of_same == false)
                {
                    result += (freqs_of_same[i]) * LEN_OF_WORD;
                    odd_num_of_same = true;
                }
                else
                {
                    result += (freqs_of_same[i] - 1) * LEN_OF_WORD;
                }
            }
            else
                result += (freqs_of_same[i]) * LEN_OF_WORD;
        }

        return result;
    }
};
