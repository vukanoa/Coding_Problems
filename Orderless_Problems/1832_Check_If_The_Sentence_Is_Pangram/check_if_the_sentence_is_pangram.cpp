/*
    ============
    === EASY ===
    ============

    ======================================
    1832) Check if the Sentence is Pangram
    ======================================

    ============
    Description:
    ============

    A pangram is a sentence where every letter of the English alphabet appears
    at least once.

    Given a string sentence containing only lowercase English letters, return
    true if sentence is a pangram, or false otherwise.

    ===============================================
    FUNCTION: bool checkIfPangram(string sentence);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
    Output: true
    Explanation: sentence contains at least one of every letter of the English
                 alphabet.

    --- Example 2 ---
    Input: sentence = "leetcode"
    Output: false


    *** Constraints ***
    1 <= sentence.length <= 1000
    sentence consists of lowercase English letters.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  6.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkIfPangram(string sentence)
    {
        unordered_set<char> uset(sentence.begin(), sentence.end());

        return uset.size() == 26;
    }
};
