/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    890) Find and Replace Pattern
    =============================

    ============
    Description:
    ============

    Given a list of strings words and a string pattern, return a list of
    words[i] that match pattern. You may return the answer in any order.

    A word matches the pattern if there exists a permutation of letters p so
    that after replacing every letter x in the pattern with p(x), we get the
    desired word.

    Recall that a permutation of letters is a bijection from letters to
    letters: every letter maps to another letter, and no two letters map to the
    same letter.

    ======================================================================================
    FUNCTION: vector<string> findAndReplacePattern(vector<string>& words, string pattern);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
    Output: ["mee","aqq"]
    Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
    "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.

    --- Example 2 ---
    Input: words = ["a","b","c"], pattern = "a"
    Output: ["a","b","c"]


    *** Constraints ***
    1 <= pattern.length <= 20
    1 <= words.length <= 50
    words[i].length == pattern.length
    pattern and words[i] are lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.66% */
/* Space Beats:  7.08% */

/* Time  Complexity: O(N * K) */ // Where 'K' is length of each word
/* Space Complexity: O(N)     */
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string> words, string pattern)
    {
        vector<string> result;
        for (const string& w : words)
        {
            if (p(w) == p(pattern))
                result.push_back(w);
        }
        return result;
    }

    string p(string word)
    {
        unordered_map<char, int> umap;
        for (const char& chr : word)
        {
            if ( ! umap.count(chr))
                umap[chr] = umap.size();
        }

        for (unsigned i = 0; i < word.length(); i++)
            word[i] = 'a' + umap[word[i]];

        return word;
    }
};
