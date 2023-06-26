#include <iostream>
#include <vector>

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


/*
	------------
	--- IDEA ---
	------------

	The most basic use of the Stack.

	Though, I've used a vector, since it faster.
*/

/* Time  Beats: 97.20% */
/* Space Beats: 83.98% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens)
    {
        std::vector<int> stack;

        for(const std::string& s : tokens)
        {
            if (s == "+" || s == "-" || s == "*" || s == "/")
            {
                int b = stack.back();
                stack.pop_back();

                int a = stack.back();
                stack.pop_back();

                if (s == "+")
                    a = a + b;
                else if (s == "-")
                    a = a - b;
                else if (s == "*")
                    a = a * b;
                else if (s == "/")
                    a = a / b;

                stack.push_back(a);
            }
            else
                stack.push_back(std::stoi(s));
        }

        return stack.back();
    }
};


int main()
{
	Solution sol;


	/* Example 1 */
	// std::vector<std::string> tokens = {"2","1","+","3","*"};

	/* Example 2 */
	// std::vector<std::string> tokens = {"4","13","5","/","+"};

	/* Example 3 */
	std::vector<std::string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};

	std::cout << "\n\t========================================";
	std::cout << "\n\t=== EVALUATE REVERSE POLISH NOTATION ===";
	std::cout << "\n\t========================================\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tTokens: [";
	for (auto x: tokens)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	int result = sol.evalRPN(tokens);


	/* Write Output */
	std::cout << "\n\tOutput: " << result << "\n\n";


	return 0;
}
