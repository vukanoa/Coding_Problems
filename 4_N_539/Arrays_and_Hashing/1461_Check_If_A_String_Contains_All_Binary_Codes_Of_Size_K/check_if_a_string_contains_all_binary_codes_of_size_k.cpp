#include <iostream>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    1461) Check If a String Contains All Binary Codes of Size K
    ===========================================================

    ============
    Description:
    ============

    Given a binary string s and an integer k, return true if every binary code
    of length k is a substring of s. Otherwise, return false.

    ============================================
    FUNCTION: bool hasAllCodes(string s, int k);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "00110110", k = 2
    Output: true
    Explanation: The binary codes of length 2 are "00", "01", "10" and "11".
                 They can be all found as substrings at indices 0, 1, 3 and 2
                 respectively.

    --- Example 2 ---
    Input: s = "0110", k = 1
    Output: true
    Explanation: The binary codes of length 1 are "0" and "1", it is clear that
                 both exist as a substring

    --- Example 3 ---
    Input: s = "0110", k = 2
    Output: false
    Explanation: The binary code "00" is of length 2 and does not exist in the
                 array.


    *** Constraints ***
    1 <= s.length <= 5 * 10^5
    s[i] is either '0' or '1'.
    1 <= k <= 20

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 72.98% */
/* Space Beats: 71.43% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(2^k) */
class Solution {
public:
    bool hasAllCodes(string s, int k)
    {
        if (s.length() < 1<<k)
            return false;

        std::unordered_set<std::string> uset;
        for (int i = 0; i < s.length() - k + 1; i++)
            uset.insert(s.substr(i, k));

        return uset.size() == 1<<k;
    }
};
