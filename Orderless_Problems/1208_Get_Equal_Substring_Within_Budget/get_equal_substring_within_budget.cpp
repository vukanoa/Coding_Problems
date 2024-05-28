#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    1208) Get Equal Substrings within Budget
    ========================================

    ============
    Description:
    ============

    You are given two strings s and t of the same length and an integer maxCost.

    You want to change s to t. Changing the ith character of s to ith character
    of t costs |s[i] - t[i]| (i.e., the absolute difference between the ASCII
    values of the characters).

    Return the maximum length of a substring of s that can be changed to be the
    same as the corresponding substring of t with a cost less than or equal to
    maxCost. If there is no substring from s that can be changed to its
    corresponding substring from t, return 0.

    ==============================================================
    FUNCTION: int equalSubstring(string s, string t, int maxCost);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcd", t = "bcdf", maxCost = 3
    Output: 3
    Explanation: "abc" of s can change to "bcd".
    That costs 3, so the maximum length is 3.


    --- Example 2 ---
    Input: s = "abcd", t = "cdef", maxCost = 3
    Output: 1
    Explanation: Each character in s costs 2 to change to character in t,  so
                 the maximum length is 1.


    --- Example 3 ---
    Input: s = "abcd", t = "acde", maxCost = 0
    Output: 1
    Explanation: You cannot make any change, so the maximum length is 1.


    *** Constraints ***
    1 <= s.length <= 10^5
    t.length == s.length
    0 <= maxCost <= 10^6
    s and t consist of only lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is a Sliding Window problem.

    1. Initialize Variables

        + "start" is a beginning of a Sliding Window.

        + "current_cost" keeps track of the total transformation cost of the
           current window.

        + "max_length" to store maximum length of a valid window found.

    2. Iterate through the String:

        + Use end as the current end of the window.
        + For each character at end, compute the cost to convert s[end] to
          t[end] and add it to current_cost.

    3. Adjust the Window:

        If "current_cost" exceeds "maxCost", increment start to shrink the
        window from the left, subtracting the cost of the character at "start"
        from "current_cost", until the total cost is within the allowed limit.

    4. Update the Maximum Length:

        After adjusting the window, compare its size (end - start + 1) with
        "max_length" and update "max_length" if the current window is larger.

    5. Return the Result:

        The maximum valid window length found during the iteration is returned
        as the result.

*/

/* Time  Beats: 63.98% */
/* Space Beats: 93.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int equalSubstring(std::string s, std::string t, int maxCost)
    {
        const int N = s.size();

        int start = 0;
        int current_cost = 0;
        int max_length = 0;

        for (int end = 0; end < N; end++)
        {
            current_cost += abs(s[end] - t[end]);

            while (current_cost > maxCost)
            {
                current_cost -= std::abs(s[start] - t[start]);
                start++;
            }

            max_length = std::max(max_length, end - start + 1);
        }

        return max_length;
    }
};
