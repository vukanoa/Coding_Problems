#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    2370) Longest Ideal Subsequence
    ===============================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase letters and an integer k.
    We call a string t ideal if the following conditions are satisfied:

        + t is a subsequence of the string s.

        + The absolute difference in the alphabet order of every two adjacent
          letters in t is less than or equal to k.

    Return the length of the longest ideal string.

    A subsequence is a string that can be derived from another string by
    deleting some or no characters without changing the order of the remaining
    characters.

    Note that the alphabet order is not cyclic. For example, the absolute
    difference in the alphabet order of 'a' and 'z' is 25, not 1.

    ==================================================
    FUNCTION: int longestIdealString(string s, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "acfgbd", k = 2
    Output: 4
    Explanation: The longest ideal string is "acbd". The length of this string
                 is 4, so 4 is returned.  Note that "acfgbd" is not ideal
                 because 'c' and 'f' have a difference of 3 in alphabet order.


    --- Example 2 ---
    Input: s = "abcd", k = 3
    Output: 4
    Explanation: The longest ideal string is "abcd". The length of this string
                 is 4, so 4 is returned.


    *** Constraints ***
    1 <= s.length <= 10^5
    0 <= k <= 25
    s consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.94% */
/* Space Beats: 59.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestIdealString(string s, int k)
    {
        vector<int> counts(26, 0);
        int result = 0;

        for (int i = 0; i < s.size(); i++)
        {
            int idx = s[i]-'a';

            // Update count of current character based on surrounding characters
            counts[idx] = check_count(idx, k, counts)+1;
        }

        for (int i = 0; i < counts.size(); i++)
            result = max(result, counts[i]);

        return result;
    }

private:
    // Function to check the count of consecutive characters within a range
    int check_count(int idx, int k, vector<int>& counts)
    {
        int result = 0;
        int count = 0;

        int curr_idx = idx;

        // Count consecutive characters to the left
        while (curr_idx >= 0 && count <= k)
        {
            result = max(result, counts[curr_idx]);
            curr_idx--;
            count++;
        }

        curr_idx = idx;
        count = 0;

        // Count consecutive characters to the right
        while (curr_idx < 26 && count <= k)
        {
            result = max(result, counts[curr_idx]);
            curr_idx++;
            count++;
        }

        return result;
    }
};
