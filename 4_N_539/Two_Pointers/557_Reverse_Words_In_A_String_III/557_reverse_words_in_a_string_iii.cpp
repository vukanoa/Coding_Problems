#include <iostream>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ==================================
    557) Reverse Words in a String III
    ==================================

    ============
    Description:
    ============

    Given a string s, reverse the order of characters in each word within a
    sentence while still preserving whitespace and initial word order.

    ========================================
    FUNCTION: string reverseWords(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "Let's take LeetCode contest"
    Output: "s'teL ekat edoCteeL tsetnoc"

    --- Example 2 ---
    Input: s = "Mr Ding"
    Output: "rM gniD"


    *** Constraints ***
    1 <= s.length <= 5 * 10^4
    s contains printable ASCII characters.
    s does not contain any leading or trailing spaces.
    There is at least one word in s.
    All the words in s are separated by a single space.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.16% */
/* Space Beats: 67.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string reverseWords(string s)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int right = s.length()-1;
        int left  = s.length()-1;

        while (left >= 0)
        {
            while (left >= 0 && s[left] != ' ')
                left--;

            reverse(s.begin() + left + 1, s.begin() + right + 1);

            right = left-1;
            left  = left-1;
        }

        return s;
    }
};
