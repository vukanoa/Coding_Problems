#include <iostream>
#include <vector>
#include <numeric>

/*
    ============
    === EASY ===
    ============

    ===============================================
    1662) Check If Two String Arrays are Equivalent
    ===============================================

    ============
    Description:
    ============

    Given two string arrays word1 and word2, return true if the two arrays
    represent the same string, and false otherwise.

    A string is represented by an array if the array elements concatenated in
    order forms the string.

    ==================================================================================
    FUNCTION: bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
    Output: true
    Explanation:
    word1 represents string "ab" + "c" -> "abc"
    word2 represents string "a" + "bc" -> "abc"
    The strings are the same, so return true.

    --- Example 2 ---
    Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
    Output: false

    --- Example 3 ---
    Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
    Output: true


    *** Constraints ***
    1 <= word1.length, word2.length <= 10^3
    1 <= word1[i].length, word2[i].length <= 10^3
    1 <= sum(word1[i].length), sum(word2[i].length) <= 10^3
    word1[i] and word2[i] consist of lowercase letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    An elegant way of concatenating strings from vector, in C++;

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.01% */
/* Space Beats: 68.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2)
    {
        /* Index of word1 and word2, respectively */
        int w1 = 0;
        int w2 = 0;

        /* Index of char */
        int i = 0;
        int j = 0;

        while (w1 < word1.size() && w2 < word2.size())
        {
            if (word1[w1][i] != word2[w2][j])
                return false;

            i++;
            j++;

            if (i == word1[w1].length())
            {
                w1++;
                i = 0;
            }

            if (j == word2[w2].length())
            {
                w2++;
                j = 0;
            }
        }

        if (w1 != word1.size() || w2 != word2.size())
            return false;

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Efficient C++ way.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  27.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_CPP {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2)
    {
        std::string concatenated_word1 = std::accumulate(word1.begin(), word1.end(), std::string{});
        std::string concatenated_word2 = std::accumulate(word2.begin(), word2.end(), std::string{});

        return concatenated_word1 == concatenated_word2;
    }
};
