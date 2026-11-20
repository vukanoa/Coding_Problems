/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    2546) Apply Bitwise Operations to Make Strings Equal
    ====================================================

    ============
    Description:
    ============

    You are given two 0-indexed binary strings s and target of the same length
    n. You can do the following operation on s any number of times:

        + Choose two different indices i and j where 0 <= i, j < n.

        + Simultaneously, replace s[i] with (s[i] OR s[j]) and s[j] with (s[i]
          XOR s[j]).

    For example, if s = "0110", you can choose i = 0 and j = 2, then
    simultaneously replace s[0] with (s[0] OR s[2] = 0 OR 1 = 1), and s[2] with
    (s[0] XOR s[2] = 0 XOR 1 = 1), so we will have s = "1110".

    Return true if you can make the string s equal to target, or false
    otherwise.

    =========================================================
    FUNCTION: bool makeStringsEqual(string s, string target);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1010", target = "0110"
    Output: true
    Explanation: We can do the following operations:
    - Choose i = 2 and j = 0. We have now s = "0010".
    - Choose i = 2 and j = 1. We have now s = "0110".
    Since we can make s equal to target, we return true.

    --- Example 2 ---
    Input: s = "11", target = "00"
    Output: false
    Explanation: It is not possible to make s equal to target with any number
                 of operations.


    *** Constraints ***
    n == s.length == target.length
    2 <= n <= 10^5
    s and target consist of only the digits 0 and 1.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  9.01% */
/* Space Beats: 45.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool makeStringsEqual(string s, string target)
    {
        if (s == target)
            return true;

        const int N = s.size();
        int ones_to_remove   = 0;
        int ones_to_preserve = 0;

        for (int i = 0; i < N; i++)
        {
            if (s[i] == '1')
            {
                if (target[i] == '0')
                    ++ones_to_remove;
                else
                    ++ones_to_preserve;
            }
        }

        for (int i = 0; i < N; i++)
        {
            if (s[i] == '0' && target[i] == '1' && (ones_to_remove > 0 || ones_to_preserve > 0))
                ++ones_to_preserve;
        }

        return ones_to_preserve > 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 83.78% */
/* Space Beats: 73.87% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Optimal {
public:
    bool makeStringsEqual(string s, string t)
    {
        return (s.find('1') != string::npos) ==
               (t.find('1') != string::npos);
    }
};
