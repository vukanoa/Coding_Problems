#include <iostream>
#include <vector>
#include <sstream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    648) Replace Words
    ===========================

    ============
    Description:
    ============

    In English, we have a concept called root, which can be followed by some
    other word to form another longer word - let's call this word derivative.
    For example, when the root "help" is followed by the word "ful", we can
    form a derivative "helpful".

    Given a dictionary consisting of many roots and a sentence consisting of
    words separated by spaces, replace all the derivatives in the sentence with
    the root forming it. If a derivative can be replaced by more than one root,
    replace it with the root that has the shortest length.

    Return the sentence after the replacement.

    ===========================================================================
    FUNCTION: string replaceWords(vector<string>& dictionary, string sentence);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled
           by the battery"
    Output: "the cat was rat by the bat"


    --- Example 2 ---
    Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab
           cadsfafs"
    Output: "a a b c"


    *** Constraints ***
    1 <= dictionary.length <= 1000
    1 <= dictionary[i].length <= 100
    dictionary[i] consists of only lower-case letters.
    1 <= sentence.length <= 106
    sentence consists of only lower-case letters and spaces.
    The number of words in sentence is in the range [1, 1000]
    The length of each word in sentence is in the range [1, 1000]
    Every two consecutive words in sentence will be separated by exactly one
    space.
    sentence does not have leading or trailing spaces.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 94.88% */
/* Space Beats: 69.18% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Trie {
public:
    Trie* children[26];
    bool is_end;

    Trie()
    {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;

        is_end = false;
    }
};

class Solution {
public:
    Trie* root;

    Solution() {
        root = new Trie();
    }

    void insert(string word) {
        Trie* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (node->children[i] == nullptr) {
                node->children[i] = new Trie();
            }
            node = node->children[i];
        }
        node->is_end = true;
    }

    std::string search(std::string word)
    {
        Trie* node = root;
        std::string result;

        for (char c : word)
        {
            int i = c - 'a';

            if (node->children[i] == nullptr)
                return word;

            result += c;
            if (node->children[i]->is_end)
                return result;

            node = node->children[i];
        }

        return word;
    }

    std::string replaceWords(std::vector<std::string>& dictionary, std::string sentence)
    {
        for (std::string word : dictionary)
            insert(word);

        std::stringstream ss(sentence);

        std::string word;
        std::string result;
        while (ss >> word)
        {
            if (!result.empty())
            {
                result += " ";
            }

            result += search(word);
        }

        return result;
    }
};
