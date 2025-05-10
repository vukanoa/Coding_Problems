/*
    ============
    === EASY ===
    ============

    =================================
    1668) Maximum Repeating Substring
    =================================

    ============
    Description:
    ============

    For a string sequence, a string word is k-repeating if word concatenated k
    times is a substring of sequence. The word's maximum k-repeating value is
    the highest value k where word is k-repeating in sequence. If word is not a
    substring of sequence, word's maximum k-repeating value is 0.

    Given strings sequence and word, return the maximum k-repeating value of
    word in sequence.

    =========================================================
    FUNCTION: int maxRepeating(string sequence, string word);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sequence = "ababc", word = "ab"
    Output: 2
    Explanation: "abab" is a substring in "ababc".

    --- Example 2 ---
    Input: sequence = "ababc", word = "ba"
    Output: 1
    Explanation: "ba" is a substring in "ababc". "baba" is not a substring in
                 "ababc".

    --- Example 3 ---
    Input: sequence = "ababc", word = "ac"
    Output: 0
    Explanation: "ac" is not a substring in "ababc".


    *** Constraints ***
    1 <= sequence.length <= 100
    1 <= word.length <= 100
    sequence and word contains only lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------


    Start with k = 1, and construct word * k.

    Keep checking if the repeated word is a substring of sequence.

    As long as it is, increment k and try the next repetition.

    When it fails, return the last successful k.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.87% */

/* Time  Complexity: O(N * K) */
/* Space Complexity: O(K * M) */
class Solution {
public:
    int maxRepeating(string sequence, string word)
    {
        int result = 0;
        string repeated = word;

        while (sequence.find(repeated) != string::npos)
        {
            repeated += word;
            result++;
        }

        return result;
    }
};
