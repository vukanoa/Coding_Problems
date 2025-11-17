/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    524) Longest Word in Dictionary Through Deleting
    ================================================

    ============
    Description:
    ============

    Given a string s and a string array dictionary, return the longest string
    in the dictionary that can be formed by deleting some of the given string
    characters. If there is more than one possible result, return the longest
    word with the smallest lexicographical order. If there is no possible
    result, return the empty string.

    =======================================================================
    FUNCTION: string findLongestWord(string s, vector<string>& dictionary);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
    Output: "apple"

    --- Example 2 ---
    Input: s = "abpcplea", dictionary = ["a","b","c"]
    Output: "a"


    *** Constraints ***
    1 <= s.length <= 1000
    1 <= dictionary.length <= 1000
    1 <= dictionary[i].length <= 1000
    s and dictionary[i] consist of lowercase English letters.

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

/* Time  Beats: 58.88% */
/* Space Beats: 22.80% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(1)     */
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary)
    {
        string result = "";

        for (const string& word : dictionary) {

            if (can_form_by_deleting(word, s))
            {
                if (word.size() > result.size() || (word.size() == result.size() && word < result))
                    result = word;
            }
        }

        return result;
    }

private:
    bool can_form_by_deleting(string word, string s)
    {
        int word_idx = 0;
        int s_idx    = 0;

        while (word_idx < word.size() && s_idx < s.size())
        {
            if (word[word_idx] == s[s_idx])
                word_idx++;

            s_idx++;
        }

        return word_idx == word.size();
    }
};
