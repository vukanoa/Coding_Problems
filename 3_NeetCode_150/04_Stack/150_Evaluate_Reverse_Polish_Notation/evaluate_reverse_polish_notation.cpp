/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    150) Evaluate Reverse Polish Notation
    ======================================

    ============
    Description:
    ============

    You are given an array of strings tokens that represents an arithmetic
    expression in a Reverse Polish Notation.

    Evaluate the expression. Return an integer that represents the value of the expression.

    =====
    Node:
          1. The valid operators are '+', '-', '*', and '/'.

          2. Each operand may be an integer or another expression.

          3. The division between two integers always truncates toward zero.

          4. There will not be any division by zero.

          5. The input represents a valid arithmetic expression in a reverse
             polish notation.

          6. The answer and all the intermediate calculations can be
             represented in a 32-bit integer.
    =====

    ==============================================
    FUNCTION: int evalRPN(vector<string>& tokens);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tokens = ["2","1","+","3","*"]
    Output: 9
    Explanation: ((2 + 1) * 3) = 9

    --- Example 2 ---
    Input: tokens = ["4","13","5","/","+"]
    Output: 6
    Explanation: (4 + (13 / 5)) = 6

    --- Example 3 ---
    Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
    Output: 22
    Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
    = ((10 * (6 / (12 * -11))) + 17) + 5
    = ((10 * (6 / -132)) + 17) + 5
    = ((10 * 0) + 17) + 5
    = (0 + 17) + 5
    = 17 + 5
    = 22

    *** Constraints ***
    1 <= tokens.length <= 104
    tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].

*/

#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most basic use of the Stack. A Simulation Problem.

*/

/* Time  Beats: 50.95% */
/* Space Beats: 14.98% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int evalRPN(vector<string>& tokens)
    {
        const int N = tokens.size();

        unordered_set<string> operators = {"+", "-", "*", "/"};
        stack<int> stack;

        for (const string& token : tokens) // O(N)
        {
            if (operators.count(token)) // O(1)
            {
                int b = stack.top(); // O(1)
                stack.pop();         // O(1)
                int a = stack.top(); // O(1)
                stack.pop();         // O(1)

                if (token == "+")
                {
                    stack.push(a + b); // O(1)
                }
                else if (token == "-")
                {
                    stack.push(a - b); // O(1)
                }
                else if (token == "*")
                {
                    stack.push(a * b); // O(1)
                }
                else // str == "/"
                {
                    stack.push(a / b); // O(1)
                }
            }
            else // Number
            {
                stack.push(stoi(token)); // O(1)
            }
        }

        return stack.top(); // O(1)
    }
};
