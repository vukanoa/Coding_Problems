#include <iostream>
#include <functional>
#include <sstream>

/*
    ============
    === EASY ===
    ============

    ===========================
    415) Add Strings
    ===========================

    ============
    Description:
    ============

    Given two non-negative integers, num1 and num2 represented as string,
    return the sum of num1 and num2 as a string.

    You must solve the problem without using any built-in library for handling
    large integers (such as BigInteger). You must also not convert the inputs
    to integers directly.

    =====================================================================
    FUNCTION: std::string addStrings(std::string num1, std::string num2);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = "11", num2 = "123"
    Output: "134"

    --- Example 2 ---
    Input: num1 = "456", num2 = "77"
    Output: "533"

    --- Example 3 ---
    Input: num1 = "0", num2 = "0"
    Output: "0"


    *** Constraints ***
    1 <= num1.length, num2.length <= 10^4
    num1 and num2 consist of only digits.
    num1 and num2 don't have any leading zeros except for the zero itself.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a messy, but straightforward approach. I wanted to have it here as
    well, since it's the most basic "raw" idea that is possible for this
    problem.

    It's really self-explanatory.

*/

/* Time  Beats: 66.65% */
/* Space Beats: 34.70% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Messy_Implementation {
public:
    string addStrings(string num1, string num2)
    {
        std::ostringstream out;

        int i = num1.length() - 1;
        int j = num2.length() - 1;

        int carry = 0;
        while (i >= 0 && j >= 0)
        {
            int digit;

            digit = ((num1[i] - '0') + (num2[j] - '0') + carry) % 10;
            carry = ((num1[i] - '0') + (num2[j] - '0') + carry) / 10;

            out << digit;

            i--;
            j--;
        }

        std::string remaining_str = out.str();
        std::reverse(remaining_str.begin(), remaining_str.end());

        std::string result;

        if (i >= 0)
        {
            std::string first_part(num1.begin(), num1.begin() + i + 1);
            std::ostringstream tmp_out;

            while (i >= 0)
            {
                int digit;

                digit = ((num1[i] - '0') + carry) % 10;
                carry = ((num1[i] - '0') + carry) / 10;

                tmp_out << digit;

                i--;
            }

            if (carry != 0)
                tmp_out << carry;

            result = tmp_out.str();
            std::reverse(result.begin(), result.end());
        }
        else if (j >= 0)
        {
            std::string first_part(num2.begin(), num2.begin() + j + 1);
            std::ostringstream tmp_out;

            while (j >= 0)
            {
                int digit;

                digit = ((num2[j] - '0') + carry) % 10;
                carry = ((num2[j] - '0') + carry) / 10;

                tmp_out << digit;

                j--;
            }

            if (carry != 0)
                tmp_out << carry;

            result = tmp_out.str();
            std::reverse(result.begin(), result.end());
        }
        else if (carry != 0)
            result = std::to_string(carry);


        result += remaining_str;
        return result;
    }
};
