/*
    ============
    === EASY ===
    ============

    =============================
    1108) Defanging an IP Address
    =============================

    ============
    Description:
    ============

    Given a valid (IPv4) IP address, return a defanged version of that IP
    address.

    A defanged IP address replaces every period "." with "[.]".

    ==============================================
    FUNCTION: string defangIPaddr(string address);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: address = "1.1.1.1"
    Output: "1[.]1[.]1[.]1"

    --- Example 2 ---
    Input: address = "255.100.50.0"
    Output: "255[.]100[.]50[.]0"


    *** Constraints ***
    The given address is a valid IPv4 address.

*/

#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 27.17% */
/* Space Beats: 13.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Result usually isn't count as "extra space".
class Solution {
public:
    string defangIPaddr(string address)
    {
        ostringstream out;

        for (const char& chr : address)
        {
            if (chr == '.')
            {
                out << "[";
                out << ".";
                out << "]";
            }
            else
                out << chr;
        }

        return out.str();
    }
};
