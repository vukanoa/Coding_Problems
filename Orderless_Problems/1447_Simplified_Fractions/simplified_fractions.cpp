/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1447) Simplified Fractions
    ===========================

    ============
    Description:
    ============

    Given an integer n, return a list of all simplified fractions between 0 and
    1 (exclusive) such that the denominator is less-than-or-equal-to n. You can
    return the answer in any order.

    ====================================================
    FUNCTION: vector<string> simplifiedFractions(int n);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2
    Output: ["1/2"]
    Explanation: "1/2" is the only unique fraction with a denominator
                 less-than-or-equal-to 2.

    --- Example 2 ---
    Input: n = 3
    Output: ["1/2","1/3","2/3"]

    --- Example 3 ---
    Input: n = 4
    Output: ["1/2","1/3","1/4","2/3","3/4"]
    Explanation: "2/4" is not a simplified fraction because it can be
                 simplified to "1/2".


    *** Constraints ***
    1 <= n <= 100

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 21.57% */
/* Space Beats: 58.26% */

/* Time  Complexity: O(n^2 * logn) */
/* Space Complexity: O(n^2)        */
class Solution {
public:
    vector<string> simplifiedFractions(int n)
    {
        vector<string> result;

        for (int i = 1; i <= n; i++)
        {
            for (int j = i+1; j <= n; j++)
            {
                string str = to_string(i) + '/' + to_string(j);

                if (i/j >= 0 && i/j <= 1 && my_gcd(i, j) == 1)
                    result.push_back(str);
            }
        }

        return result;
    }

private:
    int my_gcd(int a, int b)
    {
        return b == 0 ? a : my_gcd(b, a % b);
    }
};
