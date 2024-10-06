#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    1813) Sentence Similarity III
    =============================

    ============
    Description:
    ============

    You are given two strings sentence1 and sentence2, each representing a
    sentence composed of words. A sentence is a list of words that are
    separated by a single space with no leading or trailing spaces. Each word
    consists of only uppercase and lowercase English characters.

    Two sentences s1 and s2 are considered similar if it is possible to insert
    an arbitrary sentence (possibly empty) inside one of these sentences such
    that the two sentences become equal. Note that the inserted sentence must
    be separated from existing words by spaces.

    For example,

        + s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal
          by inserting "my name is" between "Hello" and "Jane" in s1.

        + s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since
          although there is a sentence "s are" inserted into s1, it is not
          separated from "Frog" by a space.

    Given two sentences sentence1 and sentence2, return true if sentence1 and
    sentence2 are similar. Otherwise, return false.

    =======================================================================
    FUNCTION: bool areSentencesSimilar(string sentence1, string sentence2);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
    Output: true
    Explanation: sentence2 can be turned to sentence1 by inserting "name is"
                 between "My" and "Haley".


    --- Example 2 ---
    Input: sentence1 = "of", sentence2 = "A lot of words"
    Output: false
    Explanation: No single sentence can be inserted inside one of the sentences
                 to make it equal to the other.


    --- Example 3 ---
    Input: sentence1 = "Eating right now", sentence2 = "Eating"
    Output: true
    Explanation: sentence2 can be turned to sentence1 by inserting "right now"
                 at the end of the sentence.


    *** Constraints ***
    1 <= sentence1.length, sentence2.length <= 100
    sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
    The words in sentence1 and sentence2 are separated by a single space.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.09% */
/* Space Beats: 47.93% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(n + m) */
class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2)
    {
        const int n1 = s1.size();
        const int n2 = s2.size();

        auto s1 = toStringVec(sentence1);
        auto s2 = toStringVec(sentence2);

        if (n1 > n2)
        {
            swap(n1, n2);
            swap(s1, s2);
        }

        int l  = 0;
        int r2 = n2-1;
        int r1 = n1-1;

        for (; l < n1  && s1[l]  == s2[l];  l++);
        for (; r1 >= 0 && s1[r1] == s2[r2]; r2--, r1--);

        return r1 < l;
    }

private:
    vector<string> toStringVec(string& s)
    {
        stringstream ss(s);
        vector<string> result;
        string w;

        while (ss >> w)
            result.push_back(w);

        ss.clear();
        return result;
    }
};
