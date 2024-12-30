/*
    ============
    === EASY ===
    ============

    ======================================
    3330) Find the Original Typed String I
    ======================================

    ============
    Description:
    ============

    Alice is attempting to type a specific string on her computer. However, she
    tends to be clumsy and may press a key for too long, resulting in a
    character being typed multiple times.

    Although Alice tried to focus on her typing, she is aware that she may
    still have done this at most once.

    You are given a string word, which represents the final output displayed on
    Alice's screen.

    Return the total number of possible original strings that Alice might have
    intended to type.

    ===============================================
    FUNCTION: int possibleStringCount(string word);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "abbcccc"
    Output: 5
    Explanation:
    The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".

    --- Example 2 ---
    Input: word = "abcd"
    Output: 1
    Explanation:
    The only possible string is "abcd".

    --- Example 3 ---
    Input: word = "aaaa"
    Output: 4


    *** Constraints ***
    1 <= word.length <= 100
    word consists only of lowercase English letters.

*/

#include <string>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  20.23% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int possibleStringCount(string word)
    {
        const int N = word.length();
        int result = 1;

        int consecutive = 1;
        for (int i = 1; i < N; i++)
        {
            if (word[i-1] != word[i])
            {
                result += consecutive-1;
                consecutive = 1;
            }
            else
                consecutive++;
        }
        result += consecutive-1;

        return result;
    }
};
