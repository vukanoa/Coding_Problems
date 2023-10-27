#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===============================
    1768) Merge Strings Alternately
    ===============================

    ============
    Description:
    ============

    You are given two strings word1 and word2. Merge the strings by adding
    letters in alternating order, starting with word1. If a string is longer
    than the other, append the additional letters onto the end of the merged
    string.

    Return the merged string.

    ==============================================================
    FUNCTION: string mergeAlternately(string word1, string word2);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word1 = "abc", word2 = "pqr"
    Output: "apbqcr"
    Explanation: The merged string will be merged as so:
    word1:  a   b   c
    word2:    p   q   r
    merged: a p b q c r

    --- Example 2 ---
    Input: word1 = "ab", word2 = "pqrs"
    Output: "apbqrs"
    Explanation: Notice that as word2 is longer, "rs" is appended to the end.
    word1:  a   b
    word2:    p   q   r   s
    merged: a p b q   r   s

    --- Example 3 ---
    Input: word1 = "abcd", word2 = "pq"
    Output: "apbqcd"
    Explanation: Notice that as word1 is longer, "cd" is appended to the end.
    word1:  a   b   c   d
    word2:    p   q
    merged: a p b q c   d


    *** Constraints ***
    1 <= word1.length, word2.length <= 100
    word1 and word2 consist of lowercase English letters.

*/

/* Time  Beats:  100% */
/* Space Beats: 17.43% */

/* Time  Complexity: O(word1.length() + word2.length()) */
/* Space Complexity: O(word1.length() + word2.length()) */
class Solution {
public:
    string mergeAlternately(string word1, string word2)
    {
        std::ostringstream out;

        int n1 = word1.length();
        int n2 = word2.length();

        int i = 0;
        int j = 0;
        while (i < n1 && j < n2)
            out << word1[i++] << word2[j++];

        while (i < n1)
            out << word1[i++];

        while (j < n2)
            out << word2[j++];

        return out.str();
    }
};




/* Time  Beats:   100% */
/* Space Beats: 19.16% */

/* Time  Complexity: O(word1.length() + word2.length()) */
/* Space Complexity: O(word1.length() + word2.length()) */
class Solution {
public:
    std::string mergeAlternately(std::string word1, std::string word2)
    {
        std::ostringstream out;

        int i = 0;
        while (i < word1.size() || i < word2.size())
        {
            if (i < word1.length())
                out << word1[i];
            if (i < word2.length())
                out << word2[i];

            i++;
        }

        return out.str();
    }
};
