#include <iostream>
#include <sstream>

/*
    ============
    === EASY ===
    ============

    ============================================
    1957) Delete Characters to Make Fancy String
    ============================================

    ============
    Description:
    ============

    A fancy string is a string where no three consecutive characters are equal.

    Given a string s, delete the minimum possible number of characters from s
    to make it fancy.

    Return the final string after the deletion. It can be shown that the answer
    will always be unique.

    ===========================================
    FUNCTION: string makeFancyString(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leeetcode"
    Output: "leetcode"
    Explanation:
    Remove an 'e' from the first group of 'e's to create "leetcode".
    No three consecutive characters are equal, so return "leetcode".

    --- Example 2 ---
    Input: s = "aaabaaaa"
    Output: "aabaa"
    Explanation:
    Remove an 'a' from the first group of 'a's to create "aabaaaa".
    Remove two 'a's from the second group of 'a's to create "aabaa".
    No three consecutive characters are equal, so return "aabaa".

    *** Constraints ***
    Input: s = "aab"
    Output: "aab"
    Explanation: No three consecutive characters are equal, so return "aab".

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is pretty easy. What you intuitively believe is the solution
    actually is the solution. It's not more difficult than the first thought.

    Have three pointers, one next to the other, and only if they're ALL the
    same, only then don't output it to stream "out" which is an ostringstream
    which will, at the very end, be converted to string using .str() method.

    But there is only a single thing we have to worry about:
    What if the very last three characters are the same?

    In that case we cannot continue the same loop since we'd get a OutOfBound
    error since index 'R' is out of bounds.

    When you consider such an example you'll quickly realize that it doesn't
    matter if they're equal or not, we MUST, in both situations append the last
    two characters. No matter if we've skipped the third from the back or not.

    That's why this line is crucial and the only "tricky" part:

        out << s.substr(L);

    We append from the new 'L' index(inclusive) until the end of the string.
    And we return out.str();

    That's it.

*/

/* Time  Beats: 83.12% */
/* Space Beats:  5.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string makeFancyString(string s)
    {
        if (s.length() < 3)
            return s;

        int L = 0; // Left
        int M = 1; // Mid
        int R = 2; // Right

        ostringstream out;
        while (R < s.length())
        {
            if (s[L] != s[M] || s[M] != s[R]) // If they're not three-way equal
                out << s[L];

            L++;
            M++;
            R++;
        }

        out << s.substr(L);

        return out.str();
    }
};
