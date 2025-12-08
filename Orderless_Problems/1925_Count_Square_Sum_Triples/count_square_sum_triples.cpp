/*
    ============
    === EASY ===
    ============

    ==============================
    1925) Count Square Sum Triples
    ==============================

    ============
    Description:
    ============

    A square triple (a,b,c) is a triple where a, b, and c are integers and
    a2 + b2 = c2.

    Given an integer n, return the number of square triples such that 1 <= a,
    b, c <= n.

    ==================================
    FUNCTION: int countTriples(int n);
    ==================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: 2
    Explanation: The square triples are (3,4,5) and (4,3,5).

    --- Example 2 ---
    Input: n = 10
    Output: 4
    Explanation: The square triples are (3,4,5), (4,3,5), (6,8,10), and
                 (8,6,10).


    *** Constraints ***
    1 <= n <= 250

*/

#include <numeric>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  21.68% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countTriples(int n)
    {
        int result = 0;

        for (int m = 2; m * m <= n; m++)
        {
            for (int k = 1; k < m; k++)
            {
                // Opposite parity check and coprime check
                if ((~(m - k) & 1) || gcd(m, k) != 1)
                    continue;

                int hypotenuse = m * m + k * k;
                if (hypotenuse > n)
                    continue;

                result += (n / hypotenuse) << 1;
            }
        }

        return result;
    }
};
