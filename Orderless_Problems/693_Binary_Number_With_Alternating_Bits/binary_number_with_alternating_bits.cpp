/*
    ============
    === EASY ===
    ============

    ========================================
    693) Binary Number with Alternating Bits
    ========================================

    ============
    Description:
    ============

    Given a positive integer, check whether it has alternating bits: namely, if
    two adjacent bits will always have different values.

    =========================================
    FUNCTION: bool hasAlternatingBits(int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5
    Output: true
    Explanation: The binary representation of 5 is: 101

    --- Example 2 ---
    Input: n = 7
    Output: false
    Explanation: The binary representation of 7 is: 111.

    --- Example 3 ---
    Input: n = 11
    Output: false
    Explanation: The binary representation of 11 is: 1011.


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  7.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Because max value of n is 10^9, i.e. 10 digits
class Solution {
public:
    bool hasAlternatingBits(int n)
    {
        ostringstream out;
        for (int i = 31; i >= 0; i--)
        {
            if (n & (1 << i))
                out << 1;
            else
                out << 0;
        }
        string bin_str = out.str();

        int idx = bin_str.find('1');
        idx++;

        for (unsigned i = idx; i < bin_str.length(); i++)
        {
            if (bin_str[i-1] == bin_str[i])
                return false;
        }

        return true;
    }
};
