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

#include <bitset>
#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 69.02% */
/* Space Beats: 71.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_p {
public:
    bool hasAllCodes(string s, int k)
    {
        const int N = s.size();

        if (N < (1 << k))
            return false;

        unordered_set<string> uset;
        for (int i = 0; i < N - k + 1; i++)
            uset.insert(s.substr(i, k));

        return uset.size() == (1 << k);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.29% */
/* Space Beats: 99.46% */

/* Time  Complexity: O(N)   */
/* Space Complexity: O(2^k) */
class Solution_Rolling_Hash {
public:
    bool hasAllCodes(string s, int k)
    {
        const int N = s.size();
        const int MAX_POSSIBLE_CODES = 1 << 20; // 2^20

        int remaining_required_substrings = 1 << k;

        bitset<MAX_POSSIBLE_CODES> seen;

        int mask = remaining_required_substrings - 1;
        int hash = 0;

        for (int i = 0; i < N; ++i)
        {
            hash = ((hash << 1) & mask) | (s[i] & 1);

            if ((i+1 >= k) && ( ! seen[hash]))
            {
                seen[hash] = 1;
                remaining_required_substrings--;

                if (remaining_required_substrings == 0)
                    return true;
            }
        }

        return false;
    }
};
