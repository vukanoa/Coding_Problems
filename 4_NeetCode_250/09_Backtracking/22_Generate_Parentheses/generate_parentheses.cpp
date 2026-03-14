/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    22) Generate Parentheses
    ===========================

    ============
    Description:
    ============

    Given "n" pairs of parentheses, write a function to generate all
    combinations of well-formed parenthesis.

    ==============================================================
    FUNCTION: std::vector<std::string> generateParenthesis(int n);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  n = 3
    Output: ["((()))", "(()())", "(())()", "()(())", "()()()"]

    --- Example 2 ---
    Input: n = 1
    Output: ["()"]

    *** Constraints ***
    1 <= n <= 8

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Vector of strings "result" is going to store every valid combination we
    bump upon.

    str is a string until this moment down this backtrack path.

    Since every valid combination will have exactly 2 * n characters, we check
    if our variable "str" at this moment is of length 2 * n. If it is then we
    push "str" into our vector of strings "result" and start returning from the
    back.

    However if we still haven't formed a valid combination, meaning our
    variable "str" doesn't hold up a valid combination of length 2 * n then
    first check if all the opened parentheses are used, that is:

    if "open" is less than "n", since valid combination is going to be 2 * n,
    that means that we will have exactly "n" opened and "n" closed parentheses.

    So if not all opened parentheses were used, append our current string "str"
    and backtrack with a newly formed string "str" and with a +1 value in
    variable "open".

    If all the open parentheses were used, then check if a variable "close" is
    less than "open"(not n, this is SUPER IMPORTANT to emphasize) to indicate
    that 'there is indeed something to close', if that is the case then append
    a "str" with a closing parenthesis and call this function with newly formed
    string "str" and with a +1 in variable "close".

    The best advice is to try and go through forming of first 3-4 result to get
    a "feel" of how this works.

    Again, second if:
        if (opened > closed)

    is REALLY important. It's not (closed < n), but (opened > closed).

*/


/*
    N = 3, all 5/5 combinations in order of forming

    1. ((()))
    2. (()())
    3. (())()
    4. ()(())
    5. ()()()
*/

/* Time  Beats: 80.29% */
/* Space Beats: 22.11% */

//                               (2n)
// n-th Catalan number 1/(n + 1) ( n)
/* Time  Complexity: O(4^n/sqrt(n)) */
/* Space Complexity: O(4^n/sqrt(n)) */
class Solution {
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        string str;
        backtrack(result, str, 0, 0, n);

        return result;
    }

    void backtrack(vector<string>& valid_combinations, string curr_str, int open, int close, int n)
    {
        if (curr_str.length() == n * 2)
        {
            valid_combinations.push_back(curr_str);
            return;
        }

        if (open < n)
        {
            curr_str.append("(");
            backtrack(valid_combinations, curr_str, open + 1, close, n);
            curr_str.pop_back();
        }

        if (close < open)
        {
            curr_str.append(")");
            backtrack(valid_combinations, curr_str, open, close + 1, n);
            curr_str.pop_back();
        }
    }
};
