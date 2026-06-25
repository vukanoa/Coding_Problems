/*
    ============
    === EASY ===
    ============

    ===========================
    67) Add Binary
    ===========================

    ============
    Description:
    ============

    Given two binary strings a and b, return their sum as a binary string.

    ===============================================
    FUNCTION: string addBinary(string a, stirng b);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = "11", b = "1"
    Output: "100"


    --- Example 2 ---
    Input: a = "1010", b = "1011"
    Output: "10101"


    *** Constraints ***
    1 <= a.length, b.length <= 104
    a and b consist only of '0' or '1' characters.
    Each string does not contain leading zeros except for the zero itself.

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Just read the code carefully.

*/

/* Time  Beats: 22.17% */
/* Space Beats: 20.90% */

/* Time  Complexity: O(max(M, N)) */
/* Space Complexity: O(1)         */ // Result is not "extra" Space
class Solution {
public:
    string addBinary(string a, string b)
    {
        const int N = a.size();
        const int M = b.size();
        string result;
        result.reserve(max(N, M) + 1); // To prevent reallocations

        int i = N - 1;
        int j = M - 1;

        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0)
        {
            int a_bit = i >= 0 ? (a[i] - '0') : 0;
            int b_bit = j >= 0 ? (b[j] - '0') : 0;

            result += static_cast<char>(a_bit ^ b_bit ^ carry);

            carry = (a_bit & b_bit) | (a_bit & carry) | (b_bit & carry);

            // Decrement
            i--;
            j--;
        }

        /* Reverse */
        reverse(result.begin(), result.end());

        return result;
    }
};
