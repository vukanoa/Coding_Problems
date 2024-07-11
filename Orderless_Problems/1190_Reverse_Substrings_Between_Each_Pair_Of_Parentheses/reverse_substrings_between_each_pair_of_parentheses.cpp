#include <iostream>

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 49.64% */
/* Space Beats: 37.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string reverseParentheses(std::string s)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        int i = 0;
        return helper(s, i);
    }

private:
    std::string helper(std::string& s, int& i)
    {
        std::string result;

        while (i < s.length())
        {
            if (s[i] == ')')
            {
                i++;
                std::reverse(result.begin(), result.end());
                return result;
            }
            else if (s[i] == '(')
            {
                i++;
                string st = helper(s, i);
                result += st;
            }
            else
            {
                result += s[i];
                i++;
            }
        }

        return result;
    }
};
