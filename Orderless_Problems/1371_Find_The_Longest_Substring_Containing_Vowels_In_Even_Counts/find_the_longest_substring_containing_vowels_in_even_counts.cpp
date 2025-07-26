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

/* Time  Beats: 87.11% */
/* Space Beats: 92.27% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */

class Solution {
public:
    int findTheLongestSubstring(string s)
    {
        const int N = s.length();

        int prefix_xor = 0;
        int character_map[26] = {0};
        character_map['a' - 'a'] = 1;
        character_map['e' - 'a'] = 2;
        character_map['i' - 'a'] = 4;
        character_map['o' - 'a'] = 8;
        character_map['u' - 'a'] = 16;
        vector<int> map(32, -1);
        int longest_substring = 0;

        for (int i = 0; i < N; i++)
        {
            prefix_xor ^= character_map[s[i] - 'a'];
            if (map[prefix_xor] == -1 and prefix_xor != 0)
                map[prefix_xor] = i;

            longest_substring = max(longest_substring, i - map[prefix_xor]);
        }

        return longest_substring;
    }
};
