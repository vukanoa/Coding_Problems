#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    43) Multiply Strings
    ===========================

    ============
    Description:
    ============

    Given two non-negative integers num1 and num2 represented as strings,
    return the product of num1 and num2, also represented as a string.

    =====
    Node: You must not use any built-in BigInteger library or convert the
          inputs to integer directly.
    =====

    ====================================================
    FUNCTION: string multiply(string num1, string num2);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = "2", num2 = "3"
    Output: "6"


    --- Example 2 ---
    Input: num1 = "123", num2 = "456"
    Output: "56088"


    *** Constraints ***
    1 <= num1.length, num2.length <= 200
    num1 and num2 consist of digits only.
    Both num1 and num2 do not contain any leading zero, except the number 0
    itself.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    
*/

/* Time  Beats: 72.99% */
/* Space Beats: 33.18% */

/* Time  Complexity: O(M * N) */
/* Space Complexity: O(M + N) */
class Solution {
public:
    std::string multiply(std::string num1, std::string num2)
    {
        if (num1[0] == '0' || num2[0] == '0')
            return "0";

        int M = num1.length();
        int N = num2.length();

        std::vector<int> result(M + N, 0);
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int x = (num1[i] - '0') * (num2[j] - '0');

                result[i + j]     += x;
                result[i + j + 1] += (result[i + j] / 10);
                result[i + j]     %= 10;
            }
        }

        // Get rid of the "Leading" Zeroes
        while (result.back() == 0)
            result.pop_back();

        std::reverse(result.begin(), result.end());
        std::ostringstream out;

        for (int& digit : result)
            out << digit;

        return out.str();
    }
};
