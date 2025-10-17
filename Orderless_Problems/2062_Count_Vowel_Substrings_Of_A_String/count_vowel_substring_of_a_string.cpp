/*
    ============
    === EASY ===
    ============

    ========================================
    2062) Count Vowel Substrings of a String
    ========================================

    ============
    Description:
    ============

    A substring is a contiguous (non-empty) sequence of characters within a
    string.

    A vowel substring is a substring that only consists of vowels
    ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.

    Given a string word, return the number of vowel substrings in word.

    ================================================
    FUNCTION: int countVowelSubstrings(string word);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "aeiouu"
    Output: 2
    Explanation: The vowel substrings of word are as follows (underlined):
    - "aeiouu"
    - "aeiouu"

    --- Example 2 ---
    Input: word = "unicornarihan"
    Output: 0
    Explanation: Not all 5 vowels are present, so there are no vowel substrings.

    --- Example 3 ---
    Input: word = "cuaieuouac"
    Output: 7
    Explanation: The vowel substrings of word are as follows (underlined):
    - "cuaieuouac"
    - "cuaieuouac"
    - "cuaieuouac"
    - "cuaieuouac"
    - "cuaieuouac"
    - "cuaieuouac"
    - "cuaieuouac"

    *** Constraints ***
    1 <= word.length <= 100
    word consists of lowercase English letters only.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    This one is NOT easy at all. Do not let the "Difficulty" fool you.

    It's only easy because of the Constraints, i.e. because you can BruteForce
    it. However the optimal Solution is not trivial at all.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.84% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countVowelSubstrings(string s)
    {
        return at_most(s, 5) - at_most(s, 4);
    }

private:
    int at_most(string &s, int goal)
    {
        const int N = s.length();
        int result = 0;

        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        unordered_map<char, int> count;
        int L = 0;
        int R = 0;
        while (R < N)
        {
            if ( ! vowels.count(s[R]))
            {
                L = R + 1;
                count.clear();
                R++;
                continue;
            }

            count[s[R]]++;

            while (count.size() > goal)
            {
                count[s[L]]--;
                if (count[s[L]] == 0)
                    count.erase(s[L]);

                // Increment
                L++;
            }

            int curr_window_size = R - L + 1;

            // This window [L, R] is the maximum window ending at s[R] that
            // has at most "goal" number of unique vowels.
            result += curr_window_size;

            // Increment
            R++;
        }

        return result;
    }
};
