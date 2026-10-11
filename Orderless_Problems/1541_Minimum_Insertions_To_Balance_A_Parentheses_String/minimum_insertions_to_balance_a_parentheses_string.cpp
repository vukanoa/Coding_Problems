/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    1541) Minimum Insertions to Balance a Parentheses String
    ========================================================

    ============
    Description:
    ============

    Given a parentheses string s containing only the characters '(' and ')'. A
    parentheses string is balanced if:

        + Any left parenthesis '(' must have a corresponding two consecutive
          right parenthesis '))'.

        + Left parenthesis '(' must go before the corresponding two consecutive
          right parenthesis '))'.

    In other words, we treat '(' as an opening parenthesis and '))' as a
    closing parenthesis.

        + For example, "())", "())(())))" and "(())())))" are balanced, ")()",
          "()))" and "(()))" are not balanced.

    You can insert the characters '(' and ')' at any position of the string to
    balance it if needed.

    Return the minimum number of insertions needed to make s balanced.

    =======================================
    FUNCTION: int minInsertions(string& s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(()))"
    Output: 1
    Explanation: The second '(' has two matching '))', but the first '(' has
                 only ')' matching. We need to add one more ')' at the end of
                 the string to be "(())))" which is balanced.

    --- Example 2 ---
    Input: s = "())"
    Output: 0
    Explanation: The string is already balanced.


    --- Example 3 ---
    Input: s = "))())("
    Output: 3
    Explanation: Add '(' to match the first '))', Add '))' to match the last
                 '('.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of '(' and ')' only.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 17.27% */
/* Space Beats: 98.56% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minInsertions(string& s)
    {
        int required_closing_parentheses = 0;
        int insertions = 0;

        for (const char& chr : s)
        {
            if (chr == '(')
            {
                required_closing_parentheses += 2;

                if (required_closing_parentheses & 1)
                {
                    ++insertions;
                    --required_closing_parentheses;
                }
            }
            else
            {
                --required_closing_parentheses;

                if (required_closing_parentheses < 0)
                {
                    ++insertions;
                    required_closing_parentheses += 2;
                }
            }
        }

        return required_closing_parentheses + insertions;
    }
};
