/*
    ============
    === EASY ===
    ============

    ===================================
    1021) Remove Outer Most Parentheses
    ===================================

    ============
    Description:
    ============

    A valid parentheses string is either empty "", "(" + A + ")", or A + B,
    where A and B are valid parentheses strings, and + represents string concatenation.

        For example, "", "()", "(())()", and "(()(()))" are all valid
        parentheses strings.

    A valid parentheses string s is primitive if it is nonempty, and there does
    not exist a way to split it into s = A + B, with A and B nonempty valid
    parentheses strings.

    Given a valid parentheses string s, consider its primitive decomposition:
    s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.

    Return s after removing the outermost parentheses of every primitive string
    in the primitive decomposition of s.

    ==================================================
    FUNCTION: string removeOuterParentheses(string s);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(()())(())"
    Output: "()()()"
    Explanation:
    The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
    After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

    --- Example 2 ---
    Input: s = "(()())(())(()(()))"
    Output: "()()()()(())"
    Explanation:
    The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
    After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

    --- Example 3 ---
    Input: s = "()()"
    Output: ""
    Explanation:
    The input string is "()()", with primitive decomposition "()" + "()".
    After removing outer parentheses of each part, this is "" + "" = "".


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '(' or ')'.
    s is a valid parentheses string.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  23.39% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string removeOuterParentheses(string s)
    {
        const int N = s.length();
        string result = "";

        int open = 0;

        for (int i = 0; i < N; i++)
        {
            if (s[i] == ')')
            {
                open--;

                if (open > 0)
                    result += s[i];
            }
            else
            {
                if (open > 0)
                    result += s[i];

                open++;
            }
        }

        return result;
    }
};
