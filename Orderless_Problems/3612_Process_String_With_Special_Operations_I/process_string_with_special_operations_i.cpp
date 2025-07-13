/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    3612) Process String with Special Opeartions I
    ==============================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters and the
    special characters: *, #, and %.

    Build a new string result by processing s according to the following rules
    from left to right:

        If the letter is a lowercase English letter append it to result.
        A '*' removes the last character from result, if it exists.
        A '#' duplicates the current result and appends it to itself.
        A '%' reverses the current result.

    Return the final string result after processing all characters in s.

    ======================================
    FUNCTION: string processStr(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "a#b%*"
    Output: "ba"

    --- Example 2 ---
    Input: s = "z*#"
    Output: ""

    *** Constraints ***
    1 <= s.length <= 20
    s consists of only lowercase English letters and special characters *, #,
    and %.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem, nothing to think about, just code it up.

*/

/* Time  Beats: 14.29% */
/* Space Beats: 85.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Result string is not considered extra space
class Solution {
public:
    string processStr(string s)
    {
        string result = "";
        for (const char& chr : s)
        {
            if (chr >= 97 && chr <= 122)
                result += chr;
            else if (chr == '*')
            {
                if (result.length() > 0)
                    result.pop_back();
            }
            else if(chr == '#')
            {
                result += result;
            }
            else if (chr == '%')
            {
                reverse(result.begin(), result.end());
            }
        }

        return result;
    }
};
