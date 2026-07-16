/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    856) Score of PArentheses
    ===========================

    ============
    Description:
    ============

    Given a balanced parentheses string s, return the score of the string.

    The score of a balanced parentheses string is based on the following rule:

        + "()" has score 1.

        + AB has score A + B, where A and B are balanced parentheses strings.

        + (A) has score 2 * A, where A is a balanced parentheses string.

    ===========================================
    FUNCTION: int scoreOfParentheses(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "()"
    Output: 1

    --- Example 2 ---
    Input: s = "(())"
    Output: 2

    --- Example 3 ---
    Input: s = "()()"
    Output: 2


    *** Constraints ***
    2 <= s.length <= 50
    s consists of only '(' and ')'.
    s is a balanced parentheses string.

*/

#include <stack>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int scoreOfParentheses(string S)
    {
        stack<int> stack;

        int curr = 0;
        for (const char& chr : S)
        {
            if (chr == '(')
            {
                stack.push(curr);
                curr = 0;
            }
            else
            {
                curr += stack.top() + max(curr, 1);
                stack.pop();
            }
        }

        return curr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Space Optimized version.
    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  64.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Optimized {
public:
    int scoreOfParentheses(string S)
    {
        const int N = S.size();
        int result = 0;

        int L = 0;
        int R = 0;

        while (R < N)
        {
            if (S[R] == '(')
                L++;
            else
                L--;

            if (S[R] == ')' && S[R - 1] == '(')
                result += 1 << L;

            // Increment
            R++;
        }

        return result;
    }
};
