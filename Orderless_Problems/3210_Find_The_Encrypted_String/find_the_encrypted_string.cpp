/*
    ============
    === EASY ===
    ============

    ===============================
    3210) Find the Encrypted String
    ===============================

    ============
    Description:
    ============

    You are given a string s and an integer k. Encrypt the string using the
    following algorithm:

        + For each character c in s, replace c with the kth character after c
          in the string (in a cyclic manner).

    Return the encrypted string.

    =====================================================
    FUNCTION: string getEncryptedString(string s, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "dart", k = 3
    Output: "tdar"
    Explanation:
        For i = 0, the 3rd character after 'd' is 't'.
        For i = 1, the 3rd character after 'a' is 'd'.
        For i = 2, the 3rd character after 'r' is 'a'.
        For i = 3, the 3rd character after 't' is 'r'.


    --- Example 2 ---
    Input: s = "aaa", k = 1
    Output: "aaa"
    Explanation: As all the characters are the same, the encrypted string will
                 also be the same.


    *** Constraints ***
    1 <= s.length <= 100
    1 <= k <= 10^4
    s consists only of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  74.53% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string getEncryptedString(string s, int k)
    {
        const int N = s.length();
        string result = "";

        k = k % N;

        for (int i = 0; i < N; i++)
        {
            result.push_back(s[(i + k) % N]);
        }

        return result;
    }
};
