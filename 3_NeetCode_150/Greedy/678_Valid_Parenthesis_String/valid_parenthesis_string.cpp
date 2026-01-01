#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    678) Valid Parenthesis String
    =============================

    ============
    Description:
    ============

    Given a string s containing only three types of characters: '(', ')' and
    '*', return true if s is valid.

    The following rules define a valid string:

        Any left parenthesis '(' must have a corresponding right parenthesis
        ')'.  Any right parenthesis ')' must have a corresponding left
        parenthesis '('.  Left parenthesis '(' must go before the corresponding
        right parenthesis ')'.  '*' could be treated as a single right
        parenthesis ')' or a single left parenthesis '(' or an empty string "".


    ==========================================
    FUNCTION: bool checkValidString(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "()"
    Output: true


    --- Example 2 ---
    Input: s = "(*)"
    Output: true


    --- Example 3 ---
    Input: s = "(*))"
    Output: true


    *** Constraints ***
    1 <= s.length <= 100
    s[i] is '(', ')' or '*'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    You could do it with DP and Memoization in O(n^3), but this "Greedy"
    approach is much more efficient and elegant.

    Though it is very very difficult to come up with this solution if you
    haven't seen it before.


    *** YOUTUBE ***
    I was really conflicted about why we reset leftMin whenever we fall below
    0, but then convinced myself with this argument:

    One way to think about this is we do -1 from leftMin only for ) and *

                And while ) is definitive, * can have 3 possible states. We
                always assume ) and if we are wrong, then it could be either of
                the other 2

                If c == ) and leftMin < 0, that would mean our assumption that
                previous * was ) is wrong and it could be "" or (

                Eg: (*) or (*))

                If c == * and leftMin < 0, that would mean our assumption that
                * was ) is wrong and it must be "" or )

*/

/* Time  Beats:   100% */
/* Space Beats: 32.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool checkValidString(string s)
    {
        int left_min = 0;
        int left_max = 0;

        for (char& c : s)
        {
            if (c == '(')
            {
                left_min++;
                left_max++;
            }
            else if (c == ')')
            {
                left_min--;
                left_max--;
            }
            else
            {
                left_min--;
                left_max++;
            }

            if (left_max < 0)
                return false;

            if (left_min < 0) // s = ( * ) (
                left_min = 0;
        }

        return left_min == 0;
    }
};
