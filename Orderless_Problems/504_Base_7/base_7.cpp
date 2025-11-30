/*
    ============
    === EASY ===
    ============

    ===========================
    507) Base 7
    ===========================

    ============
    Description:
    ============

    Given an integer num, return a string of its base 7 representation.

    =========================================
    FUNCTION: string convertToBase7(int num);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = 100
    Output: "202"

    --- Example 2 ---
    Input: num = -7
    Output: "-10"


    *** Constraints ***
    -10^7 <= num <= 10^7

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 39.60% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    string convertToBase7(int num)
    {
        if (num == 0)
            return "0";

        string result;
        bool negative = num < 0;

        num = abs(num);
        while (num > 0)
        {
            result = to_string(num % 7) + result;
            num /= 7;
        }

        return negative ? "-" + result : result;
    }
};
