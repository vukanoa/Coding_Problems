/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    537) Complex Number Multiplication
    ==================================

    ============
    Description:
    ============

    A complex number can be represented as a string on the form
    "real+imaginaryi" where:

        + real is the real part and is an integer in the range [-100, 100].

        + imaginary is the imaginary part and is an integer in the range [-100,
          100].

        + i2 == -1.

    Given two complex numbers num1 and num2 as strings, return a string of the
    complex number that represents their multiplications.

    =================================================================
    FUNCTION: string complexNumberMultiply(string num1, string num2);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = "1+1i", num2 = "1+1i"
    Output: "0+2i"
    Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert
                 it to the form of 0+2i.

    --- Example 2 ---
    Input: num1 = "1+-1i", num2 = "1+-1i"
    Output: "0+-2i"
    Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need
                 convert it to the form of 0+-2i.


    *** Constraints ***
    num1 and num2 are valid complex numbers.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You just need to know how to convert from String to Integer and vice-versa.
    And how to search and split numbers in string.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.38% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    string complexNumberMultiply(string num1, string num2)
    {
        int idx_of_plus_in_num1 = num1.find('+');
        int idx_of_plus_in_num2 = num2.find('+');

        string str_real_1 = num1.substr(0, idx_of_plus_in_num1);
        string str_real_2 = num2.substr(0, idx_of_plus_in_num2);

        string str_imag_1 = num1.substr(idx_of_plus_in_num1 + 1, num1.find('i') - idx_of_plus_in_num1);
        string str_imag_2 = num2.substr(idx_of_plus_in_num2 + 1, num2.find('i') - idx_of_plus_in_num2);


        int real = stoi(str_real_1) * stoi(str_real_2) +
                   stoi(str_imag_1) * stoi(str_imag_2) * (-1);

        int imag = stoi(str_real_1) * stoi(str_imag_2) +
                   stoi(str_real_2) * stoi(str_imag_1);

        return to_string(real) + "+" + to_string(imag) + "i";
    }
};
