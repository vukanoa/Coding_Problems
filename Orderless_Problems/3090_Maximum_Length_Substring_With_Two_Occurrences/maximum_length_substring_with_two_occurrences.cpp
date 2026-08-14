/*
    ============
    === EASY ===
    ============

    ===================================================
    3090) Maximum Length Substring With Two Occurrences
    ===================================================

    ============
    Description:
    ============

    Given a string s, return the maximum length of a  such that it contains at
    most two occurrences of each character.

    ===============================================
    FUNCTION: int maximumLengthSubstring(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "bcbbbcba"
    Output: 4
    Explanation: The following substring has a length of 4 and contains at most
                 two occurrences of each character: "bcbbbcba".

    --- Example 2 ---
    Input: s = "aaaa"
    Output: 2
    Explanation: The following substring has a length of 2 and contains at most
                 two occurrences of each character: "aaaa".


    *** Constraints ***
    2 <= s.length <= 100
    s consists only of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explantory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumLengthSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        int freq[26] = {0}; // On the Stack

        int L = 0;
        int R = 0;
        while (R < N)
        {
            ++freq[s[R] - 'a'];

            while (freq[s[R] - 'a'] > 2)
            {
                --freq[s[L] - 'a'];

                // Increment
                ++L;
            }

            result = max(result, R - L + 1);

            // Incrment
            ++R;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a small "trick" with indexing both lowercase and upperase English
    letters.



    Both 'a' = 97 and 'A' = 65 will result in 1 when we BITIWSE AND with 31.
    Then we just subtract by 1 and voila, we get 0-based indexing.

    ---------------------
    --- lowercase 'a' ---
    ---------------------

        97 = 0110 0001
        31 = 0001 1111  & (Bitwise AND)
       ---------------
         1 = 0000 0001
         1 = 0000 0001  - (Minus)
       ---------------
         0 = 0000 0000  <-- Final index of of: 'a' = 97


    ---------------------
    --- uppercase 'A' ---
    ---------------------

        64 = 0100 0001
        31 = 0001 1111  & (Bitwise AND)
       ---------------
         1 = 0000 0001
         1 = 0000 0001  - (Minus)
       ---------------
         0 = 0000 0000  <-- Final index of of: 'A' = 65



    Now:
        + both 'A' and 'a' will be indexed at 0.
        + both 'B' and 'b' will be indexed at 1.
        + ...
        + both 'Y' and 'y' will be indexed at 24
        + both 'Z' and 'z' will be indexed at 25.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bit_Trick {
public:
    int maximumLengthSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        int freq[26] = {0}; // On the Stack

        int L = 0;
        int R = 0;
        while (R < N)
        {
            ++freq[(s[R] & 31) - 1];

            while (freq[(s[R] & 31) - 1] > 2)
            {
                --freq[(s[L] & 31) - 1];

                // Increment
                ++L;
            }

            result = max(result, R - L + 1);

            // Incrment
            ++R;
        }

        return result;
    }
};
