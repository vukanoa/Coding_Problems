#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    2516) Take K of Each Character From Left and Right
    ==================================================

    ============
    Description:
    ============

    You are given a string s consisting of the characters 'a', 'b', and 'c' and
    a non-negative integer k. Each minute, you may take either the leftmost
    character of s, or the rightmost character of s.

    Return the minimum number of minutes needed for you to take at least k of
    each character, or return -1 if it is not possible to take k of each
    character.

    ==============================================
    FUNCTION: int takeCharacters(string s, int k);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aabaaaacaabc", k = 2
    Output: 8
    Explanation:
    Take three characters from the left of s. You now have two 'a' characters,
    and one 'b' character.
    Take five characters from the right of s. You now have four 'a' characters,
    two 'b' characters, and two 'c' characters.
    A total of 3 + 5 = 8 minutes is needed.
    It can be proven that 8 is the minimum number of minutes needed.


    --- Example 2 ---
    Input: s = "a", k = 1
    Output: -1
    Explanation: It is not possible to take one 'b' or 'c' so return -1.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only the letters 'a', 'b', and 'c'.
    0 <= k <= s.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Always try to INVERT the problem!)

*/

/* Time  Beats: 38.54% */
/* Space Beats: 56.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int takeCharacters(string s, int k)
    {
        vector<int> counter(3, 0);

        for (const char& chr : s)
            counter[chr - 'a']++;

        if (*min_element(counter.begin(), counter.end()) < k)
            return -1;

        const int n = s.length();
        int result = n + 1; // Or INT_MAX

        int left  = 0;
        int right = 0;
        while (right < n)
        {
            counter[s[right] - 'a']--;

            // If "left" pointer reaches "right" our Sliding_Window is VALID!
            while (*min_element(counter.begin(), counter.end()) < k)
            {
                counter[s[left] - 'a']++;
                left++;
            }

            // At this point, Sliding_Window is guaranteed to be VALID!
            result = min(result, n - (right - left + 1));

            // Post-loop Increment
            right++;
        }

        return result;
    }
};
