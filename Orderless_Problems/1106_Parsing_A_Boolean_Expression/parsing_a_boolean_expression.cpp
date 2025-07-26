/*
    ============
    === HARD ===
    ============

    ==================================
    1106) Parsing a Boolean Expression
    ==================================

    ============
    Description:
    ============

    A boolean expression is an expression that evaluates to either true or
    false. It can be in one of the following shapes:

        + 't' that evaluates to true.

        + 'f' that evaluates to false.

        + '!(subExpr)' that evaluates to the logical NOT of the inner
           expression subExpr.

        + '&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical
           AND of the inner expressions subExpr1, subExpr2, ..., subExprn where
           n >= 1.

        + '|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical
          OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n
          >= 1.

    Given a string expression that represents a boolean expression, return the
    evaluation of that expression.

    It is guaranteed that the given expression is valid and follows the given
    rules.

    ================================================
    FUNCTION: bool parseBoolExpr(string expression);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: expression = "&(|(f))"
    Output: false
    Explanation: 
    First, evaluate |(f) --> f. The expression is now "&(f)".
    Then, evaluate &(f) --> f. The expression is now "f".
    Finally, return false.


    --- Example 2 ---
    Input: expression = "|(f,f,f,t)"
    Output: true
    Explanation: The evaluation of (false OR false OR false OR true) is true.


    --- Example 3 ---
    Input: expression = "!(&(f,t))"
    Output: true
    Explanation: 
    First, evaluate &(f,t) --> (false AND true) --> false --> f. The expression
    is now "!(f)". Then, evaluate !(f) --> NOT false --> true. We return true.


    *** Constraints ***
    1 <= expression.length <= 2 * 10^4
    expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.

*/

#include <stack>

/*
    ------------
    --- IDEA ---
    ------------

    TODO 

*/

/* Time  Beats: 100.00% */
/* Space Beats:  55.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool parseBoolExpr(string expression)
    {
        stack<char> stack;

        for (char curr_char : expression)
        {
            if (curr_char == ',' || curr_char == '(')
                continue;  

            if (curr_char == 't' || curr_char == 'f' || curr_char == '!' ||
                curr_char == '&' || curr_char == '|')
            {
                stack.push(curr_char);
            }
            else if (curr_char == ')')
            {
                bool has_true  = false;
                bool has_false = false;

                while (stack.top() != '!' && stack.top() != '&' && stack.top() != '|')
                {
                    char top_value = stack.top();
                    stack.pop();

                    if (top_value == 't')
                        has_true = true;

                    if (top_value == 'f')
                        has_false = true;
                }

                char op = stack.top();
                stack.pop();

                if (op == '!')
                    stack.push(has_true ? 'f' : 't');
                else if (op == '&')
                    stack.push(has_false ? 'f' : 't');
                else
                    stack.push(has_true ? 't' : 'f');
            }
        }

        return stack.top() == 't';
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Easier to come up with. It's less efficient, but much
    more realistic to come up with.

    TODO

*/

/* Time  Beats:  75.22% */
/* Space Beats:  11.42% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    bool parseBoolExpr(string expression)
    {
        int index = 0;
        return evaluate(expression, index);
    }

private:
    bool evaluate(string& expr, int& index)
    {
        char curr_char = expr[index++];

        if (curr_char == 't') return true;
        if (curr_char == 'f') return false;

        if (curr_char == '!')
        {
            index++;
            bool result = !evaluate(expr, index);
            index++;

            return result;
        }

        vector<bool> values;
        index++;
        while (expr[index] != ')')
        {
            if (expr[index] != ',')
                values.push_back(evaluate(expr, index));
            else
                index++;
        }
        index++;

        if (curr_char == '&')
        {
            for (const bool& v : values)
            {
                if (!v)
                return false;
            }

            return true;
        }

        if (curr_char == '|')
        {
            for (const bool& v : values)
            {
                if (v)
                    return true;
            }

            return false;
        }

        return false;
    }
};
