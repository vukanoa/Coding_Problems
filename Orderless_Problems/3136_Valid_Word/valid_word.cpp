/*
    ============
    === EASY ===
    ============

    ===========================
    3136) Valid Word
    ===========================

    ============
    Description:
    ============


    A word is considered valid if:

        + It contains a minimum of 3 characters.

        + It contains only digits (0-9), and English letters
          (uppercase and lowercase).

        + It includes at least one vowel.

        + It includes at least one consonant.

    You are given a string word.

    Return true if word is valid, otherwise, return false.

    =====
    Note: 'a', 'e', 'i', 'o', 'u', and their uppercases are vowels.
          A consonant is an English letter that is not a vowel.
    =====

    ====================================
    FUNCTION: bool isValid(string word);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "234Adas"
    Output: true
    Explanation:
    This word satisfies the conditions.

    --- Example 2 ---
    Input: word = "b3"
    Output: false
    Explanation:
    The length of this word is fewer than 3, and does not have a vowel.

    --- Example 3 ---
    Input: word = "a3$e"
    Output: false
    Explanation:
    This word contains a '$' character and does not have a consonant.


    *** Constraints ***
    1 <= word.length <= 20
    word consists of English uppercase and lowercase letters, digits, '@', '#',
    and '$'.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isValid(string word)
    {
        const int N = word.length();

        unordered_set<int> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        int vows = 0;
        int cons = 0;
        for (const char& chr : word)
        {
            if ( ! isalnum(chr))
                return false;

            if (vowels.count(chr))
                vows++;
            else if ( ! isdigit(chr))
                cons++;
        }

        return N >= 3 && vows >= 1 && cons >= 1;
    }
};
