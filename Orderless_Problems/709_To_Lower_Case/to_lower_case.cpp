#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    709) To Lower Case
    ===========================

    ============
    Description:
    ============

    Given a string s, return the string after replacing every uppercase letter
    with the same lowercase letter.

    =======================================
    FUNCTION: string toLowerCase(string s); 
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "Hello"
    Output: "hello"

    --- Example 2 ---
    Input: s = "here"
    Output: "here"

    --- Example 3 ---
    Input: s = "LOVELY"
    Output: "lovely"


    *** Constraints ***
    1 <= s.length <= 100
    s consists of printable ASCII characters. 

*/

/*
    ------------
    --- IDEA ---
    ------------

    If you've ever heard of ASCII, that's the solution. If not, read about it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string toLowerCase(std::string s)
    {
        for (char& chr :  s)
        {
            if (chr >= 'A' && chr <= 'Z')
                chr += 32;
        }

        return s;
    }
};
