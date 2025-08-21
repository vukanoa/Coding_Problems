/*
    ============
    === EASY ===
    ============

    ==============================
    2427) Number of Common Factors
    ==============================

    ============
    Description:
    ============

    Given two positive integers a and b, return the number of common factors of
    a and b.

    An integer x is a common factor of a and b if x divides both a and b.

    ==========================================
    FUNCTION: int commonFactors(int a, int b);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = 12, b = 6
    Output: 4
    Explanation: The common factors of 12 and 6 are 1, 2, 3, 6.

    --- Example 2 ---
    Input: a = 25, b = 30
    Output: 2
    Explanation: The common factors of 25 and 30 are 1, 5.


    *** Constraints ***
    1 <= a, b <= 1000

*/

#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  82.13% */

/* Time  Complexity: O(min(a, b)) */
/* Space Complexity: O(1)         */
class Solution {
public:
    int commonFactors(int a, int b)
    {
        int result = 0;
        int limit = min(a, b);
        
        for (int i = 1; i <= limit; i++)
        {
            if (a % i == 0 && b % i == 0)
                result++;
        }
        
        return result;
    }
};
