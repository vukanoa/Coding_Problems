#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =======================================
    387) First Unique Character in a String
    =======================================

    ============
    Description:
    ============

    Given a string s, find the first non-repeating character in it and return
    its index. If it does not exist, return -1.

    ======================================
    FUNCTION: int firstUniqChar(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcode"
    Output: 0

    --- Example 2 ---
    Input: s = "loveleetcode"
    Output: 2

    --- Example 3 ---
    Input: s = "aabb"
    Output: -1

    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only lowercase English letters.

*/

using namespace std;

/* Time  Beats: 95.56% */
/* Space Beats: 57.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int firstUniqChar(string s)
    {
        vector<int> freq(26, 0);

        for (char& chr : s)
            freq[chr - 'a']++;

        for (int i = 0; i < s.length(); i++)
        {
            if (1 == freq[s[i] - 'a'])
                return i;
        }

        return -1;
    }
};
