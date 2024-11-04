#include <iostream>
#include <sstream>

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

/*
    ------------
    --- IDEA ---
    ------------

    I'm not sure where is the "problem" in this Problem. You literally have to
    do what you're told. You don't have to come up with a solution.

    Since we have to "construct" a string, it's a good idea, in C++, to use a
    ostringstream.

    Other than that the only "difficult" part is not to mess up indices in if
    and else-if cases. And to take care of the very last sequence of characters
    since they can be unprocessed.

*/

/* Time  Beats: 68.38% */
/* Space Beats: 67.50% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We don't want to count what we return as extra
class Solution {
public:
    string compressedString(string word)
    {
        ostringstream out;

        int L = 0;
        int R = 0;

        while (R < word.length())
        {
            if (word[L] != word[R])
            {
                out << R-L << word[L]; // It must be word[L]
                L = R;
            }
            else if (R-L+1 == 9)
            {
                out << R-L+1 << word[L];
                L = R+1;
            }

            R++;
        }

        if (L < word.length())
            out << R-L << word[L];

        return out.str();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one doesn't use ostringstream. Instead we're using basic string
    variable and appending to it.

    ostringstream is a more verbose and elegant solution in my opinion, but
    this one is, I guess, more common or more natural to most people.

*/

/* Time  Beats: 66.67% */
/* Space Beats: 77.92% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // We don't want to count what we return as extra
class Solution_2 {
public:
    string compressedString(string word)
    {
        string result = "";

        int n = word.length();

        int count = 1;
        char chr = word[0];

        for (int i = 1; i < n; i++)
        {
            if (word[i] == chr && count < 9)
                count++;
            else
            {
                result.push_back(count + '0'); // 4 + 48 == 52 ---> '4'
                result.push_back(chr);

                chr = word[i];
                count = 1;
            }
        }
        result.push_back(count+'0');
        result.push_back(chr);

        return result;
    }
};
