/*
    ============
    === EASY ===
    ============

    ===========================
    925) Long Pressed Game
    ===========================

    ============
    Description:
    ============

    Your friend is typing his name into a keyboard. Sometimes, when typing a
    character c, the key might get long pressed, and the character will be
    typed 1 or more times.

    You examine the typed characters of the keyboard. Return True if it is
    possible that it was your friends name, with some characters
    (possibly none) being long pressed.

    ============================================================
    FUNCTION: bool isLongPressedName(string name, string typed);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: name = "alex", typed = "aaleex"
    Output: true
    Explanation: 'a' and 'e' in 'alex' were long pressed.

    --- Example 2 ---
    Input: name = "saeed", typed = "ssaaedd"
    Output: false
    Explanation: 'e' must have been pressed twice, but it was not in the typed
                 output.


    *** Constraints ***
    1 <= name.length, typed.length <= 1000
    name and typed consist of only lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  75.60% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isLongPressedName(string name, string typed)
    {
        const int N = name.length();
        const int M = typed.length();

        int i = 0;
        for (int j = 0; j < M; ++j)
        {
            if (i < N && name[i] == typed[j])
                i++;
            else if (!j || typed[j] != typed[j - 1])
                return false;
        }

        return i == N;
    }
};
