/*
    ============
    === EASY ===
    ============

    ===============================================
    3602) Hexadecimal and Hexatrigesimal Conversion
    ===============================================

    ============
    Description:
    ============

    You are given an integer n.

    Return the concatenation of the hexadecimal representation of n2 and the
    hexatrigesimal representation of n3.

    A hexadecimal number is defined as a base-16 numeral system that uses the
    digits 0 – 9 and the uppercase letters A - F to represent values from 0 to
    15.

    A hexatrigesimal number is defined as a base-36 numeral system that uses
    the digits 0 – 9 and the uppercase letters A - Z to represent values from
    0 to 35.

    ====================================
    FUNCTION: string concatHex36(int n);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13
    Output: "A91P1"
    Explanation:
        n2 = 13 * 13 = 169. In hexadecimal, it converts to (10 * 16) + 9 = 169, which corresponds to "A9".
        n3 = 13 * 13 * 13 = 2197. In hexatrigesimal, it converts to (1 * 362) + (25 * 36) + 1 = 2197, which corresponds to "1P1".
        Concatenating both results gives "A9" + "1P1" = "A91P1".

    --- Example 2 ---
    Input: n = 36
    Output: "5101000"
    Explanation:
        n2 = 36 * 36 = 1296. In hexadecimal, it converts to (5 * 162) + (1 * 16) + 0 = 1296, which corresponds to "510".
        n3 = 36 * 36 * 36 = 46656. In hexatrigesimal, it converts to (1 * 363) + (0 * 362) + (0 * 36) + 0 = 46656, which corresponds to "1000".
        Concatenating both results gives "510" + "1000" = "5101000".


    *** Constraints ***
    1 <= n <= 1000

*/

#include <ios>
#include <string>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:      -% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string concatHex36(int n)
    {
        long long n2 = 1LL * n * n;
        long long n3 = 1LL * n * n * n;

        // Convert to hexadecimal (uppercase)
        string hex_part;
        {
            stringstream ss;
            ss << uppercase << hex << n2;
            ss >> hex_part;
        }

        // Convert to base-36 (uppercase)
        string base36_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string base36_part;

        while (n3 > 0)
        {
            base36_part = base36_chars[n3 % 36] + base36_part;
            n3 /= 36;
        }

        return hex_part + base36_part;
    }
};
