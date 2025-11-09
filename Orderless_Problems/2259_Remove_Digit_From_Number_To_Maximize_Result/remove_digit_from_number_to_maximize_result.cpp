/*
    ============
    === EASY ===
    ============

    ================================================
    2259) Remove Digi From Number to Maximize Result
    ================================================

    ============
    Description:
    ============

    You are given a string number representing a positive integer and a
    character digit.

    Return the resulting string after removing exactly one occurrence of digit
    from number such that the value of the resulting string in decimal form is
    maximized. The test cases are generated such that digit occurs at least
    once in number.

    ========================================================
    FUNCTION: string removeDigit(string number, char digit);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: number = "123", digit = "3"
    Output: "12"
    Explanation: There is only one '3' in "123". After removing '3', the result
                 is "12".

    --- Example 2 ---
    Input: number = "1231", digit = "1"
    Output: "231"
    Explanation: We can remove the first '1' to get "231" or remove the second '1' to get "123".
    Since 231 > 123, we return "231".

    --- Example 3 ---
    Input: number = "551", digit = "5"
    Output: "51"
    Explanation: We can remove either the first or second '5' from "551".
    Both result in the string "51".


    *** Constraints ***
    2 <= number.length <= 100
    number consists of digits from '1' to '9'.
    digit is a digit from '1' to '9'.
    digit occurs at least once in number.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.89% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string removeDigit(string number, char digit)
    {
        const int N = number.length();

        for (int i = 0; i < N-1; ++i)
        {
            if (number[i] == digit && number[i] < number[i + 1])
                return number.substr(0, i) + number.substr(i + 1);
        }

        int idx_of_rightmost_digit = number.rfind(digit);

        return number.substr(0, idx_of_rightmost_digit) + number.substr(idx_of_rightmost_digit + 1);
    }
};
