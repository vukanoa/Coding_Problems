/*
    ============
    === EASY ===
    ============

    ===========================
    520) Detect Capital
    ===========================

    ============
    Description:
    ============

    We define the usage of capitals in a word to be right when one of the
    following cases holds:

        + All letters in this word are capitals, like "USA".
        + All letters in this word are not capitals, like "leetcode".
        + Only the first letter in this word is capital, like "Google".

    Given a string word, return true if the usage of capitals in it is right.

    =============================================
    FUNCTION: bool detectCapitalUse(string word);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "USA"
    Output: true

    --- Example 2 ---
    Input: word = "FlaG"
    Output: false


    *** Constraints ***
    1 <= word.length <= 100
    word consists of lowercase and uppercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool detectCapitalUse(string word)
    {
        const int N = word.length();

        if (N == 1)
            return true;

        if (word[0] < 97) // CAPITAL
        {
            if (word[1] < 97) // CAPITAL, then all need to be CAPITAL
            {
                for (int i = 2; i < N; i++)
                {
                    if (word[i] >= 97)
                        return false;
                }
            }
            else // Then all the remaining must be lowercase
            {
                for (int i = 2; i < N; i++)
                {
                    if (word[i] < 97)
                        return false;
                }
            }
        }
        else // word[0] is lowercase, then all the remaining must be lowercase
        {
            for (int i = 1; i < N; i++)
            {
                if (word[i] < 97)
                    return false;
            }
        }

        return true;
    }
};
