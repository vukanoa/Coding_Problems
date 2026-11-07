/*
    ============
    === EASY ===
    ============

    ===================================
    3783) Mirror Distance Of An Integer
    ===================================

    ============
    Description:
    ============

    You are given an integer n.

    Define its mirror distance as: abs(n - reverse(n)) where reverse(n) is the
    integer formed by reversing the digits of n.

    Return an integer denoting the mirror distance of n.

    abs(x) denotes the absolute value of x.

    ====================================
    FUNCTION: int mirrorDistance(int n);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 25
    Output: 27
    Explanation:
        reverse(25) = 52.
        Thus, the answer is abs(25 - 52) = 27.

    --- Example 2 ---
    Input: n = 10
    Output: 9
    Explanation:
        reverse(10) = 01 which is 1.
        Thus, the answer is abs(10 - 1) = 9.

    --- Example 3 ---
    Input: n = 7
    Output: 0
    Explanation:
        reverse(7) = 7.
        Thus, the answer is abs(7 - 7) = 0.


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <cstdlib>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  60.81% */

/* Time  Complexity: O(log10(n)) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int mirrorDistance(int n)
    {
        int rev = 0;
        for (int num = n; num > 0; num /= 10)
            rev = rev * 10 + (num % 10);

        return abs(n - rev);
    }
};
