/*
    ============
    === EASY ===
    ============

    =========================================
    2423) Remove Letter To Equalize Frequency
    =========================================

    ============
    Description:
    ============


    You are given a 0-indexed string word, consisting of lowercase English
    letters. You need to select one index and remove the letter at that index
    from word so that the frequency of every letter present in word is equal.

    Return true if it is possible to remove one letter so that the frequency of
    all letters in word are equal, and false otherwise.

    =====
    Note: The frequency of a letter x is the number of times it occurs in the
          string.

          You must remove exactly one letter and cannot choose to do nothing.
    =====

    ===========================================
    FUNCTION: bool equalFrequency(string word);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abcc"
    Output: true
    Explanation: Select index 3 and delete it: word becomes "abc" and each
                 character has a frequency of 1.

    --- Example 2 ---
    Input: word = "aazz"
    Output: false
    Explanation: We must delete a character, so either the frequency of "a" is
                 1 and the frequency of "z" is 2, or vice versa. It is
                 impossible to make all present letters have equal frequency.


    *** Constraints ***
    2 <= word.length <= 100
    word consists of lowercase English letters only.

*/

#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool equalFrequency(string word)
    {
        const int N = word.length();

        bool all_same = true;

        vector<int> freq(26, 0);
        for (const char& chr : word)
        {
            freq[chr - 'a']++;

            if (word[0] != chr)
                all_same = false;
        }

        if (all_same)
            return true;

        // So that the lower one is first
        // However, since we will have at most 2 elements in it, we do NOT
        // have to count its O(logN) insertion time, since N is going to be 2
        // in the worst case.
        map<int,int> my_map;
        for (int i = 0; i < 26; i++)
        {
            if (freq[i] > 0)
            {
                my_map[freq[i]]++;
            }

            if (my_map.size() == 3)
                return false;
        }

        // All have a frequency of 1, therefore we can remove any one of them
        if (my_map.size() == 1 && my_map.begin()->first == 1)
            return true;

        auto first_iter  = my_map.begin();
        auto second_iter = std::next(my_map.begin());


        const auto& first_iter_freq     = first_iter->first;
        const auto& first_iter_how_many = first_iter->second;

        const auto& second_iter_freq     = second_iter->first;
        const auto& second_iter_how_many = second_iter->second;

        if (first_iter_freq == 1 && first_iter_how_many == 1)
            return true;


        if (first_iter_freq + 1 == second_iter_freq && second_iter_how_many == 1)
            return true;

        return false;
    }
};
