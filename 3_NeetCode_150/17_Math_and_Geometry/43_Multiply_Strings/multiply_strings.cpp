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

#include <string>
#include <vector>
using namespace std;

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
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0")
            return "0";

        int N = num1.size();
        int M = num2.size();

        vector<int> vec_result(N + M, 0);

        for (int i = N-1; i >= 0; i--)
        {
            for (int j = M-1; j >= 0; j--)
            {
                int product = (num1[i] - '0') * (num2[j] - '0');

                int sum = product + vec_result[i + j + 1];

                vec_result[i + j + 1]  = sum % 10;
                vec_result[i + j    ] += sum / 10;
            }
        }

        string str_result = "";
        str_result.reserve(N + M); // To prevent reallocations

        for (const int& num : vec_result)
        {
            if ( ! (str_result.empty() && num == 0))
                str_result += to_string(num);
        }

        return str_result.empty() ? "0" : str_result;
    }
};
