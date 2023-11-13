#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2405) Optimal Partition of String
    =================================

    ============
    Description:
    ============

    Given a string s, partition the string into one or more substrings such
    that the characters in each substring are unique. That is, no letter
    appears in a single substring more than once.

    Return the minimum number of substrings in such a partition.

    Note that each character should belong to exactly one substring in a
    partition.

    ========================================
    FUNCTION: int partitionString(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abacaba"
    Output: 4
    Explanation:
    Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
    It can be shown that 4 is the minimum number of substrings needed.


    --- Example 2 ---
    Input: s = "ssssss"
    Output: 6
    Explanation:
    The only valid partition is ("s","s","s","s","s","s").



    *** Constraints ***
    1 <= s.length <= 105
    s consists of only English lowercase letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 73.04% */
/* Space Beats: 80.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int partitionString(string s)
    {
        int count = 0;
        std::vector<int> letters(26, 0);
        std::vector<int> empty(26, 0);

        for (int i = 0; i < s.length(); i++)
        {
            if (letters[s[i] - 'a'] > 0)
            {
                count++;
                letters = empty;
                letters[s[i] - 'a']++;
            }
            else
                letters[s[i] - 'a']++;
        }
        count++;

        return count;
    }
};
