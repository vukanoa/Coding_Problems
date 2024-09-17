#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ======================================
    884) Uncommon Words From Two Sentences
    ======================================

    ============
    Description:
    ============

    A sentence is a string of single-space separated words where each word
    consists only of lowercase letters.

    A word is uncommon if it appears exactly once in one of the sentences, and
    does not appear in the other sentence.

    Given two sentences s1 and s2, return a list of all the uncommon words. You
    may return the answer in any order.

    =====================================================================
    FUNCTION: vector<string> uncommonFromSentences(string s1, string s2);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "this apple is sweet", s2 = "this apple is sour"
    Output: ["sweet","sour"]
    Explanation: The word "sweet" appears only in s1, while the word "sour"
                 appears only in s2.


    --- Example 2 ---
    Input: s1 = "apple apple", s2 = "banana"
    Output: ["banana"]


    *** Constraints ***
    1 <= s1.length, s2.length <= 200
    s1 and s2 consist of lowercase English letters and spaces.
    s1 and s2 do not have leading or trailing spaces.
    All the words in s1 and s2 are separated by a single space.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  44.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        string s = s1 + " " + s2;
        stringstream str(s);

        unordered_map<string,int> umap;
        string tmp;

        while (str >> tmp)
            umap[tmp]++;

        vector<string> result;
        for (auto& val : umap)
        {
            if (val.second == 1)
                result.emplace_back(val.first);
        }

        return result;
    }
};
