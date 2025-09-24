/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    166) Fraction to Recurring Decimal
    ==================================

    ============
    Description:
    ============

    Given two integers representing the numerator and denominator of a
    fraction, return the fraction in string format.

    If the fractional part is repeating, enclose the repeating part in
    parentheses.

    If multiple answers are possible, return any of them.

    It is guaranteed that the length of the answer string is less than 104 for
    all the given inputs.

    ===================================================================
    FUNCTION: string fractionToDecimal(int numerator, int denominator);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numerator = 1, denominator = 2
    Output: "0.5"

    --- Example 2 ---
    Input: numerator = 2, denominator = 1
    Output: "2"

    --- Example 3 ---
    Input: numerator = 4, denominator = 333
    Output: "0.(012)"


    *** Constraints ***
    -2^31 <= numerator, denominator <= 2^31 - 1
    denominator != 0

*/

#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 34.19% */
/* Space Beats: 36.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator)
    {
        if (numerator == 0)
            return "0";        

        string str_fraction;
        if ((numerator < 0) ^ (denominator < 0))
            str_fraction += "-";        

        long long dividend = llabs(static_cast<long long>(numerator));
        long long divisor  = llabs(static_cast<long long>(denominator));

        str_fraction += to_string(dividend / divisor);
        long long remainder = dividend % divisor;

        if (remainder == 0)
            return str_fraction;

        str_fraction += ".";
        unordered_map<long long, int> umap;
        while (remainder != 0)
        {
            if (umap.count(remainder))
            {
                int repeat_start_idx = umap[remainder];

                // O(n) since all the elements AFTER repeat_start_idx SHIFT
                str_fraction.insert(repeat_start_idx, "(");

                // Enclose & break
                str_fraction += ")";
                break;
            }

            umap[remainder] = str_fraction.size();
            remainder *= 10;

            str_fraction += to_string(remainder / divisor);
            remainder %= divisor;
        }

        return str_fraction;
    }
};
