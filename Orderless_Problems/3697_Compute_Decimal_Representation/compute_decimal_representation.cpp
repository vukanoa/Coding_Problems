/*
    ============
    === EASY ===
    ============

    ====================================
    3697) Compute Decimal Representation
    ====================================

    ============
    Description:
    ============

    You are given a positive integer n.

    A positive integer is a base-10 component if it is the product of a single
    digit from 1 to 9 and a non-negative power of 10. For example, 500, 30, and
    7 are base-10 components, while 537, 102, and 11 are not.

    Express n as a sum of only base-10 components, using the fewest base-10
    components possible.

    Return an array containing these base-10 components in descending order.

    ===================================================
    FUNCTION: vector<int> decimalRepresentation(int n);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 537
    Output: [500,30,7]
    Explanation: We can express 537 as 500 + 30 + 7. It is impossible to
                 express 537 as a sum using fewer than 3 base-10 components.

    --- Example 2 ---
    Input: n = 102
    Output: [100,2]
    Explanation: We can express 102 as 100 + 2. 102 is not a base-10 component,
                 which means 2 base-10 components are needed.

    --- Example 3 ---
    Input: n = 6
    Output: [6]
    Explanation: 6 is a base-10 component.


    *** Constraints ***
    1 <= n <= 10^9

*/

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  38.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Result is usually no considered EXTRA, but w/e
class Solution {
public:
    vector<int> decimalRepresentation(int n)
    {
        vector<int> result;

        int i = 0;
        while (n > 0)
        {
            int digit = n % 10;

            if (digit > 0)
                result.push_back(digit * pow(10, i));

            n /= 10;
            i++;
        }

        /* Sort */
        reverse(result.begin(), result.end());


        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A slightly different way of implementing it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.94% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // Result is usually no considered EXTRA, but w/e
class Solution_2 {
public:
    vector<int> decimalRepresentation(int n)
    {
        vector<int> result;

        long long mul = 1;
        while (n > 0)
        {
            int digit = n % 10;

            if (digit > 0)
                result.push_back(static_cast<int>(digit * mul));


            n   /= 10;
            mul *= 10;
        }

        /* Sort */
        reverse(result.begin(), result.end());


        return result;
    }
};
