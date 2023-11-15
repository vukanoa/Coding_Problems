#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    58) Lenth Of Last Word
    ===========================

    ============
    Description:
    ============

    Given a string s consisting of words and spaces, return the length of the
    last word in the string.

    A word is a maximal
    substring
    consisting of non-space characters only.

    =========================================
    FUNCTION: int lengthOfLastWord(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "Hello World"
    Output: 5
    Explanation: The last word is "World" with length 5.

    --- Example 2 ---
    Input: s = "   fly me   to   the moon  "
    Output: 4
    Explanation: The last word is "moon" with length 4.

    --- Example 3 ---
    Input: s = "luffy is still joyboy"
    Output: 6
    Explanation: The last word is "joyboy" with length 6.


    *** Constraints ***
    1 <= s.length <= 10^4
    s consists of only English letters and spaces ' '.
    There will be at least one word in s.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats:   100% */
/* Space Beats: 90.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int lengthOfLastWord(string s)
    {
        int i = s.length() - 1;

        while(s[i] == ' ')
            i--;

        int length = 0;
        while (i >= 0 && s[i--] != ' ')
            length++;

        return length;
    }
};
