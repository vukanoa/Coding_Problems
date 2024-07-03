#include <iostream>

/*
    ============
    === HARD ===
    ============

    ====================================
    1542) Find Longest Awesome Substring
    ====================================

    ============
    Description:
    ============

    You are given a string s. An awesome substring is a non-empty substring of
    s such that we can make any number of swaps in order to make it a
    palindrome.

    Return the length of the maximum length awesome substring of s.

    =======================================
    FUNCTION: int longestAwesome(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "3242415"
    Output: 5
    Explanation: "24241" is the longest awesome substring, we can form the
                 palindrome "24142" with some swaps.


    --- Example 2 ---
    Input: s = "12345678"
    Output: 1


    --- Example 3 ---
    Input: s = "213123"
    Output: 6
    Explanation: "213123" is the longest awesome substring, we can form the
                 palindrome "231132" with some swaps.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of digits.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Hint: It's very similar to:
        1371. Find the Longest Substring Containing Vowels in Even Counts.

*/

/* Time  Beats: 92.36% */
/* Space Beats: 71.34% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(2^k)   */
class Solution {
public:
    int longestAwesome(std::string s)
    {
        std::vector<int> dp(1024, s.size());

        int result = 0;
        int mask = 0;

        dp[0] = -1;

        for (auto i = 0; i < s.size(); i++)
        {
            mask ^= 1 << (s[i] - '0');

            result = std::max(result, i - dp[mask]);

            for (auto j = 0; j <= 9; ++j)
                result = max(result, i - dp[mask ^ (1 << j)]);

            dp[mask] = min(dp[mask], i);
        }

        return result;
    }
};
