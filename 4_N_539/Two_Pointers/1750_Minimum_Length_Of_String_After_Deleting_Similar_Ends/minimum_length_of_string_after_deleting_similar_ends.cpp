#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    1750) Minimum Length of String After Deleting Similar Ends
    ==========================================================

    ============
    Description:
    ============

    Given a string s consisting only of characters 'a', 'b', and 'c'. You are
    asked to apply the following algorithm on the string any number of times:

        + Pick a non-empty prefix from the string s where all the characters in
          the prefix are equal.

        + Pick a non-empty suffix from the string s where all the characters in
          this suffix are equal.

        + The prefix and the suffix should not intersect at any index.

        + The characters from the prefix and suffix must be the same.

        + Delete both the prefix and the suffix.

    Return the minimum length of s after performing the above operation any
    number of times (possibly zero times).

    ======================================
    FUNCTION: int minimumLength(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ca"
    Output: 2
    Explanation: You can't remove any characters, so the string stays as is.

    --- Example 2 ---
    Input: s = "cabaabac"
    Output: 0
    Explanation: An optimal sequence of operations is:
    - Take prefix = "c" and suffix = "c" and remove them, s = "abaaba".
    - Take prefix = "a" and suffix = "a" and remove them, s = "baab".
    - Take prefix = "b" and suffix = "b" and remove them, s = "aa".
    - Take prefix = "a" and suffix = "a" and remove them, s = "".

    --- Example 3 ---
    Input: s = "aabccabba"
    Output: 3
    Explanation: An optimal sequence of operations is:
    - Take prefix = "aa" and suffix = "a" and remove them, s = "bccabb".
    - Take prefix = "b" and suffix = "bb" and remove them, s = "cca".


    *** Constraints ***
    1 <= s.length <= 10^5
    s only consists of characters 'a', 'b', and 'c'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.87% */
/* Space Beats: 86.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumLength(string s)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        const int n = s.length();

        if (n == 1)
            return 1;

        int left  = 0;
        int right = n-1;

        while (left < n-1)
        {
            int curr_len = right - left + 1;

            while (left < n-1 && s[left] == s[left+1])
                left++;

            while (right > 0 && s[right-1] == s[right])
                right--;

            if (s[left] != s[right])
                return curr_len;

            if (left == right)
                return 1;

            if (left > right)
                return 0;

            left++;
            right--;
        }

        return 0;
    }
};
