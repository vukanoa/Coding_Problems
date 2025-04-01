/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    3163) String Compression III
    ============================

    ============
    Description:
    ============

    Given a string word, compress it using the following algorithm:

        Begin with an empty string comp. While word is not empty, use the
        following operation:
            + Remove a maximum length prefix of word made of a single character
              c repeating at most 9 times.

            + Append the length of the prefix followed by c to comp.

    Return the string comp.

    ===============================================
    FUNCTION: string compressedString(string word);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abcde"
    Output: "1a1b1c1d1e"
    Explanation:
    Initially, comp = "". Apply the operation 5 times, choosing "a", "b", "c",
    "d", and "e" as the prefix in each operation.
    For each prefix, append "1" followed by the character to comp.


    --- Example 2 ---
    Input: word = "aaaaaaaaaaaaaabb"
    Output: "9a5a2b"
    Explanation:
    Initially, comp = "". Apply the operation 3 times, choosing "aaaaaaaaa",
    "aaaaa", and "bb" as the prefix in each operation.
        For prefix "aaaaaaaaa", append "9" followed by "a" to comp.
        For prefix "aaaaa", append "5" followed by "a" to comp.
        For prefix "bb", append "2" followed by "b" to comp.


    *** Constraints ***
    1 <= word.length <= 2 * 10^5
    word consists only of lowercase English letters.

*/

#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    I'm not sure where is the "problem" in this Problem. You literally have to
    do what you're told. You don't have to come up with a solution.

    Since we have to "construct" a string, it's a good idea to use some kind of
    "String Builder". In C++ we have "std::ostringstream".

    Other than that the only "difficult" part is not to mess up indices.
    And to take care of the very last sequence of characters since they can be
    unprocessed.

*/

/* Time  Beats: 68.38% */
/* Space Beats: 67.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // We don't count what we return as extra Space
class Solution {
public:
    string compressedString(string word)
    {
        const int N = word.size();

        ostringstream out;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            if (R > 0 && (word[R-1] != word[R] || R - L >= 9) )
            {
                char chr = word[R-1];
                out << to_string(R - L) << chr;

                L = R;
            }

            // Increment
            R++;
        }

        if (L < N)
        {
            char chr = word[R-1];
            out << to_string(R - L) << chr;
        }

        return out.str();
    }
};
