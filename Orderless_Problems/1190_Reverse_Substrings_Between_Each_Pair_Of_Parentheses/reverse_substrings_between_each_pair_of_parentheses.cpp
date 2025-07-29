/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    1190) Reverse Substrings Between Each Pair of Parentheses
    =========================================================

    ============
    Description:
    ============

    You are given a string s that consists of lower case English letters and
    brackets.

    Reverse the strings in each pair of matching parentheses, starting from the
    innermost one.

    Your result should not contain any brackets.

    ==============================================
    FUNCTION: string reverseParentheses(string s); 
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(abcd)"
    Output: "dcba"

    --- Example 2 ---
    Input: s = "(u(love)i)"
    Output: "iloveu"
    Explanation: The substring "love" is reversed first, then the whole string
                 is reversed.

    --- Example 3 ---
    Input: s = "(ed(et(oc))el)"
    Output: "leetcode"
    Explanation: First, we reverse the substring "oc", then "etco", and
                 finally, the whole string.


    *** Constraints ***
    1 <= s.length <= 2000
    s only contains lower case English characters and parentheses.
    It is guaranteed that all parentheses are balanced.

*/

#include <vector>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.78% */
/* Space Beats: 90.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string reverseParentheses(string s)
    {
        string result;

        vector<int> opened;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                opened.push_back(result.length());
            }
            else if (s[i] == ')')
            {
                int j = opened.back();
                opened.pop_back();

                reverse(result.begin() + j, result.end());
            }
            else
            {
                result += s[i];
            }
        }
    }
};
