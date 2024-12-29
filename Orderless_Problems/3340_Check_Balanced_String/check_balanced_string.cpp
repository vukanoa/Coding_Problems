/*
    ============
    === EASY ===
    ============

    ===========================
    3340) Check Balanced String
    ===========================

    ============
    Description:
    ============

    You are given a string num consisting of only digits. A string of digits is
    called balanced if the sum of the digits at even indices is equal to the
    sum of digits at odd indices.

    Return true if num is balanced, otherwise return false.

    ======================================
    FUNCTION: bool isBalanced(string num);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "1234"
    Output: false
    Explanation:
        The sum of digits at even indices is 1 + 3 == 4, and the sum of digits at odd indices is 2 + 4 == 6.
        Since 4 is not equal to 6, num is not balanced.


    --- Example 2 ---
    Input: num = "24123"
    Output: true
    Explanation:
        The sum of digits at even indices is 2 + 1 + 3 == 6, and the sum of digits at odd indices is 4 + 2 == 6.
        Since both are equal the num is balanced.


    *** Constraints ***
    2 <= num.length <= 100
    num consists of digits only

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
/* Space Beats:   6.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isBalanced(string num)
    {
        const int N = num.length();

        int even = 0;
        int odd  = 0;

        for (int i = 0; i < N; i++)
        {
            int digit = num[i] - '0';

            if (i % 2 == 0)
                even += digit;
            else
                odd +=  digit;
        }

        return even == odd;
    }
};
