#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ============================================
    1684) Count the Number of Consistent Strings
    ============================================

    ============
    Description:
    ============

    You are given a string allowed consisting of distinct characters and an
    array of strings words. A string is consistent if all characters in the
    string appear in the string allowed.

    Return the number of consistent strings in the array words.

    ============================================================================
    FUNCTION: int countConsistentStrings(string allowed, vector<string>& words);
    ============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
    Output: 2
    Explanation: Strings "aaab" and "baa" are consistent since they only
                 contain characters 'a' and 'b'.

    --- Example 2 ---
    Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
    Output: 7
    Explanation: All strings are consistent.

    --- Example 3 ---
    Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
    Output: 4
    Explanation: Strings "cc", "acd", "ac", and "d" are consistent.


    *** Constraints ***
    1 <= words.length <= 10^4
    1 <= allowed.length <= 26
    1 <= words[i].length <= 10
    The characters in allowed are distinct.
    words[i] and allowed contain only lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    What's the easiest way to see if a character is present in some string?

    Since only "lowercase English letters" are allowed, it's not super
    inefficient to iterate every time over those, potentially, 26 characters in
    string allowed.

    The overall Time Complexity wouldn't change because constants are
    "ignored", but the "Wall Time clock" would be more inefficient than if we
    could truly see if some character is present in string allowed in a true
    O(1).


    We have two options:
        1. Create a vector of 26 booleans where index 0 value will indicate if
           character 'a' is present, index 1 will indicate if character 'b' is
           present and so on.

        2. Create a HashSet, i.e. unordered_set in C++.

    Either solution is fine. They both equally optimal. I chose unordered_set,
    because I can initialize it immediately in the constructor, whereas I'd
    have to iterate through and entire allowed string to set flags in the
    the vector.

    Now it's self-explanatory.

    Go through every word, if at any point some letter in the word is NOT
    present in our HashSet, we break and we do not count that word as a
    "consistent" one, as they noted in the Description.

*/

/* Time  Beats: 61.36% */
/* Space Beats: 27.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words)
    {
        int result = 0;
        unordered_set<char> uset_allowed(allowed.begin(), allowed.end());

        for (int i = 0; i < words.size(); i++)
        {
            bool all_chars_exist = true;

            for (const char& chr : words[i])
            {
                if (uset_allowed.find(chr) == uset_allowed.end()) // Doesn't exit
                {
                    all_chars_exist = false;
                    break;
                }
            }

            result += all_chars_exist ? 1 : 0;
        }

        return result;
    }
};
