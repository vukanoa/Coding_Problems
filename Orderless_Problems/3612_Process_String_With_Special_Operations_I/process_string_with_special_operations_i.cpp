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

    If you don't understand why the Time Complexity is O(2^N), then consider
    this:

        s = "a#####"

    The size of result will grow exponenntially. Look at the sizes after each
    iteration:

        1 2 4 8 16 32

*/

/* Time  Beats: 100.00% */
/* Space Beats:  15.15% */

/* Time  Complexity: O(2^N) */
/* Space Complexity: O(2^N) */
class Solution {
public:
    string processStr(string s)
    {
        const int N = s.size();

        string result;
        result.reserve(1 << N); // To prevent reallocations

        for (const char& chr : s)
        {
            if (islower(chr))
            {
                result += chr;
            }
            else if (chr == '*')
            {
                if ( ! result.empty())
                result.pop_back();
            }
            else if (chr == '#')
            {
                result += result;
            }
            else
            {
                reverse(result.begin(), result.end());
            }
        }

        return result;
    }
};
