#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    241) Different Ways to Add Parentheses
    ======================================

    ============
    Description:
    ============

    Given a string expression of numbers and operators, return all possible
    results from computing all the different possible ways to group numbers and
    operators. You may return the answer in any order.

    The test cases are generated such that the output values fit in a 32-bit
    integer and the number of different results does not exceed 104.

    ===========================================================
    FUNCTION: vector<int> diffWaysToCompute(string expression);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: expression = "2-1-1"
    Output: [0,2]
    Explanation:
    ((2-1)-1) = 0
    (2-(1-1)) = 2

    --- Example 2 ---
    Input: expression = "2*3-4*5"
    Output: [-34,-14,-10,-10,10]
    Explanation:
    (2*(3-(4*5))) = -34
    ((2*3)-(4*5)) = -14
    ((2*(3-4))*5) = -10
    (2*((3-4)*5)) = -10
    (((2*3)-4)*5) = 10


    *** Constraints ***
    1 <= expression.length <= 20
    expression consists of digits and the operator '+', '-', and '*'.
    All the integer values in the input expression are in the range [0, 99].

*/

/*
    ------------
    --- IDEA ---
    ------------

    + The problem becomes easier when we think about these expressions as
      expression trees.

    + We can traverse over the experssion and whenever we encounter an
      operator, we recursively divide the expression into left and right part
      and evaluate them seperately until we reach a situation where our
      expression is purely a number and in this case we can simply return that
      number.

    + Since there can be multiple ways to evaluate an expression (depending on
      which operator you take first) we will get a list of reults from left and
      the right part.

    + Now that we have all the possible results from the left and the right
      part, we can use them to find out all the possible results for the
      current operator.

    The following drawings show all the possible expression trees for the
    expression "2*3-4*5"


    1) Answer = -34
                                    *(MUL)
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       2                         -(MINUS)
                                               /   \
                                              /     \
                                             /       \
                                            /         \
                                           /           \
                                          3             *(MUL)
                                                       / \
                                                      /   \
                                                     /     \
                                                    4       5




    2) Answer = -10
                                    *(MUL)
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       2                         *(MUL)
                                               /   \
                                              /     \
                                             /       \
                                            /         \
                                           /           \
                                          -(MIN)        5
                                         / \
                                        /   \
                                       /     \
                                      3       4



    3) Answer = -14
                                    -(MINUS)
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       *(MUL)                    *(MUL)
                     /   \                     /   \
                    /     \                   /     \
                   /       \                 /       \
                  /         \               /         \
                 /           \             /           \
                2             3           4             5



    4) Answer = 10
                                    *(MUL)
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       -(MINUS)                  5
                     /   \
                    /     \
                   /       \
                  /         \
                 /           \
                *(MUL)        4
               / \
              /   \
             /     \
            2       3





    5) Answer = -10
                                    *(MUL)
                                  /   \
                                 /     \
                                /       \
                               /         \
                              /           \
                             /             \
                            /               \
                           /                 \
                          /                   \
                         /                     \
                        /                       \
                       *(MUL)                    5
                      /   \
                     /     \
                    /       \
                   /         \
                  /           \
                 2             -(MINUS)
                              / \
                             /   \
                            /     \
                           3       4




*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.44% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> diffWaysToCompute(std::string exp)
    {
        std::vector<int> results;
        bool is_number = 1;

        for(int i = 0; i < exp.length(); i++)
        {
            // Check if current character is an operator
            if( ! std::isdigit(exp[i]))
            {
                // If current character is not a digit then exp is not purely a
                // number
                is_number = 0;

                // List of first operands
                std::vector<int> left = diffWaysToCompute(exp.substr(0, i));

                // List of second operands
                std::vector<int> right = diffWaysToCompute(exp.substr(i + 1));

                // Performing operations
                for(int num1 : left)
                {
                    for(int num2 : right)
                    {
                        int val = perform(num1, num2, exp[i]);
                        results.push_back(val);
                    }
                }

            }
        }

        if(is_number == 1)
            results.push_back(stoi(exp));

        return results;
    }

private:

    // Function to get the result of the operation
    int perform(int& num1, int& num2, char& op)
    {
        if(op == '+') return num1 + num2;
        if(op == '-') return num1 - num2;
        if(op == '*') return num1 * num2;

        return 0;
    }
};
