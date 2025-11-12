/*
    ============
    === EASY ===
    ============

    ============================
    804) Unique Morse Code Words
    ============================

    ============
    Description:
    ============

    International Morse Code defines a standard encoding where each letter is
    mapped to a series of dots and dashes, as follows:

        'a' maps to ".-",
        'b' maps to "-...",
        'c' maps to "-.-.", and so on.

    For convenience, the full table for the 26 letters of the English alphabet
    is given below:

    [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]

    Given an array of strings words where each word can be written as a concatenation of the Morse code of each letter.

        + For example, "cab" can be written as "-.-..--...", which is the
          concatenation of "-.-.", ".-", and "-...". We will call such a
          concatenation the transformation of a word.

    Return the number of different transformations among all words we have.

    ================================================================
    FUNCTION: int uniqueMorseRepresentations(vector<string>& words);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["gin","zen","gig","msg"]
    Output: 2
    Explanation: The transformation of each word is:
    "gin" -> "--...-."
    "zen" -> "--...-."
    "gig" -> "--...--."
    "msg" -> "--...--."
    There are 2 different transformations: "--...-." and "--...--.".

    --- Example 2 ---
    Input: words = ["a"]
    Output: 1


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 12
    words[i] consists of lowercase English letters.

*/

#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Almost a Simulation problem.

*/

/* Time  Beats: 27.15% */
/* Space Beats: 75.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words)
    {
        vector<string> codes = {".-",    // a
                                "-...",  // b
                                "-.-.",  // c
                                "-..",   // d
                                ".",     // e
                                "..-.",  // f
                                "--.",   // g
                                "....",  // h
                                "..",    // i
                                ".---",  // j
                                "-.-",   // k
                                ".-..",  // l
                                "--",    // m
                                "-.",    // n
                                "---",   // o
                                ".--.",  // p
                                "--.-",  // q
                                ".-.",   // r
                                "...",   // s
                                "-",     // t
                                "..-",   // u
                                "...-",  // v
                                ".--",   // w
                                "-..-",  // x
                                "-.--",  // y
                                "--.."}; // z

        unordered_set<string> uset;
        for (const auto& word : words)
        {
            string coded_str;
            for (const char& chr : word)
                coded_str += codes[chr - 'a'];

            uset.insert(coded_str);
        }

        return uset.size();
    }
};
