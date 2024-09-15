#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    1371) Find the Longest Substring Containing Vowels in Even Counts
    =================================================================

    ============
    Description:
    ============

    Given the string s, return the size of the longest substring containing
    each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u'
    must appear an even number of times.

    ================================================
    FUNCTION: int findTheLongestSubstring(string s);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "eleetminicoworoep"
    Output: 13
    Explanation: The longest substring is "leetminicowor" which contains two
    each of the vowels: e, i and o and zero of the vowels: a and u.

    --- Example 2 ---
    Input: s = "leetcodeisgreat"
    Output: 5
    Explanation: The longest substring is "leetc" which contains two e's.

    --- Example 3 ---
    Input: s = "bcbcbc"
    Output: 6
    Explanation: In this case, the given string "bcbcbc" is the longest because
                 all vowels: a, e, i, o and u appear zero times.


    *** Constraints ***
    1 <= s.length <= 5 x 10^5
    s contains only lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 76.51% */
/* Space Beats: 75.12% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findTheLongestSubstring(string s)
    {
        vector<int> position(32, -2);
        position[0] = -1;

        int max_len = 0;
        int mask = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            char ch = s[i];

            switch (ch)
            {
                case 'a':
                    mask ^= 1;
                    break;

                case 'e':
                    mask ^= 2;
                    break;

                case 'i':
                    mask ^= 4;
                    break;

                case 'o':
                    mask ^= 8;
                    break;

                case 'u':
                    mask ^= 16;
                    break;
            }

            int prev = position[mask];

            if (prev == -2)
                position[mask] = i;
            else
                max_len = max(max_len, i - prev);
        }

        return max_len;
    }
};
