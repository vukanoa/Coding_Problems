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

    This one is peculiar, but it makes sense once you get the hang of it.

    We have n different words in vectors called "words". We are going to make
    another vector, of size n as well, but this one is going to have n bitsets.

    Why bitsets?

    Since we're told we are allowed to multiply only those words that do NOT
    have a single letter in common, the easiest way is to have a binary
    representation and that do a bitwise AND operation to determine that.

    For example, if we have words = ["abc", "abd", "def"]

    Then bitsets that will correspond to each letter will be as following:

    position 0 (character 'a')                     position 25(character 'z')
             |                                               |
             |______                              ___________|
                   |                              |
                   |                              |
                   v                              v
        1. "abc" - 1110 0000 0000 0000 0000 0000 00

        2. "abd" - 1101 0000 0000 0000 0000 0000 00

        3. "def" - 0001 1100 0000 0000 0000 0000 00


    Once you see this, it becomes painfully obvious if any two words have any
    character in common.

    To be explicit - To check whether two words have any characters in common,
    all we have to do is do a bitwise AND operation. If the result is:

        0000 0000 0000 0000 0000 0000 00       // 0x0 in Hexa

    Then that means that those two words do NOT have any character in common.
    Any other result, meaning anything other than 0x0, indicates that the two
    words do have at least one character in common.


    Therefore, the crux of this solution is to transform:

        words = ["abc", "abd", "def"]

    into:
        vec_bitsets = [
                       1110 0000 0000 0000 0000 0000 00,   // This is "abc"
                       1101 0000 0000 0000 0000 0000 00,   // This is "abd"
                       0001 1100 0000 0000 0000 0000 00    // This is "def"
                      ]

    After that, just do a "bitwise AND" operation on any two words and if the
    result bitset is 0x0, then take the max out of:

        max_product = std::max(max_product, word1.length() * word2.length());

    That's the entire IDEA.

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
