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
    int lengthOfLastWord(std::string s)
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




/*
    ------------
    --- IDEA ---
    ------------

    Another way of thinking about it. This one makes more sense to me.

*/

/* Time  Beats:   100% */
/* Space Beats: 24.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int lengthOfLastWord(std::string s)
    {
        int i = s.length() - 1;

        while (i >= 0 && s[i] == ' ')
            i--;
        int last_chr_idx = i;

        while (i >=0 && s[i] != ' ')
            i--;
        int one_before_first_chr_idx = i;

        return last_chr_idx - one_before_first_chr_idx;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Third way of solving this problem. This one is reminiscent of the first
    Solution, however it's implemented all in one for loop. Some people find
    this Solution easier to read.

    I prefer the first one over this one.

*/

/* Time  Beats:   100% */
/* Space Beats: 24.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int lengthOfLastWord(std::string s)
    {
        int last_word_length = 0;

        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (s[i] == ' ')
            {
                if (last_word_length >= 1)
                    return last_word_length;
            }
            else
                last_word_length++;
        }

        return last_word_length;
    }
};
