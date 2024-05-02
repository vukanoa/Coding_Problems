#include <iostream>
#include <vector>
#include <bitset>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    318) Maximum Product Of Word Lengths
    ====================================

    ============
    Description:
    ============

    Given a string array words, return the maximum value of length(word[i]) *
    length(word[j]) where the two words do not share common letters. If no such
    two words exist, return 0.

    =====================================================
    FUNCTION: int maxProduct(std::vector<string>& words);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
    Output: 16
    Explanation: The two words can be "abcw", "xtfn".

    --- Example 2 ---
    Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
    Output: 4
    Explanation: The two words can be "ab", "cd".

    --- Example 3 ---
    Input: words = ["a","aa","aaa","aaaa"]
    Output: 0
    Explanation: No such pair of words.


    *** Constraints ***
    2 <= words.length <= 1000
    1 <= words[i].length <= 1000
    words[i] consists only of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 30.51% */
/* Space Beats: 33.66% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int maxProduct(std::vector<std::string>& words)
    {
        const int n = words.size();
        int result = 0;

        std::vector<std::vector<int>> letters_for_word(n, std::vector<int>(26, 0));

        for (int i = 0; i < n; i++)
        {
            for (const char& chr : words[i])
                letters_for_word[i][chr - 'a']++;

            for (int j = 0; j < i; j++)
            {
                if ( ! common_chars(letters_for_word[i], letters_for_word[j]))
                {
                    int size = words[i].size() * words[j].size();
                    result   = std::max(result, size);
                }
            }
        }

        return result;
    }

private:
    bool common_chars(std::vector<int>& a, std::vector<int>& b)
    {
        for (int i = 0; i < 26; i++)
        {
            if (a[i] > 0 && b[i] > 0)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.37% */
/* Space Beats:  8.90% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution_Bitsets {
public:
    int maxProduct(std::vector<std::string>& words)
    {
        std::bitset<32> all_zeroes(0x0);
        std::vector<std::bitset<32>> vec_bitsets;
        std::vector<std::string> bit_words;

        for (const std::string& word : words)
        {
            std::vector<bool> letters(26, false);

            for (int i = 0; i < word.length(); i++)
                letters[word[i] - 'a'] = true;

            std::ostringstream out;
            for (int i = 0; i < 26; i++)
            {
                if (letters[i])
                    out << 1;
                else
                    out << 0;
            }

            std::bitset<32> bitset(out.str());
            vec_bitsets.push_back(bitset);
        }

        unsigned long max_product = 0;
        for (int i = 0; i < vec_bitsets.size()-1; i++)
        {
            for (int j = i+1; j < vec_bitsets.size(); j++)
            {
                if ((vec_bitsets[i] & vec_bitsets[j]) == all_zeroes)
                    max_product = std::max(max_product, words[i].length() * words[j].length());
            }
        }

        int result = max_product;

        return result;
    }
};
