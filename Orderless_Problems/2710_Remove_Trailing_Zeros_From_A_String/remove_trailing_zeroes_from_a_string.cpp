/*
    ============
    === EASY ===
    ============

    ==========================================
    2710) Remove Trailing Zeroes From a String
    ==========================================

    ============
    Description:
    ============

    Given a positive integer num represented as a string, return the integer
    num without trailing zeros as a string.

    =================================================
    FUNCTION: string removeTrailingZeros(string num);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "51230100"
    Output: "512301"
    Explanation: Integer "51230100" has 2 trailing zeros, we remove them and
                 return integer "512301".

    --- Example 2 ---
    Input: num = "123"
    Output: "123"
    Explanation: Integer "123" has no trailing zeros, we return integer "123".


    *** Constraints ***
    1 <= num.length <= 1000
    num consists of only digits.
    num doesn't have any leading zeros.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats:  9.02% */
/* Space Beats: 52.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string removeTrailingZeros(string num)
    {
        while ( ! num.empty() && num.back() == '0')
            num.pop_back();

        return num;
    }
};
