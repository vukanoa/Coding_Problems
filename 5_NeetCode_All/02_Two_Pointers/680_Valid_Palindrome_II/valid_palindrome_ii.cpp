/*
    ============
    === EASY ===
    ============

    ===========================
    680) Valid Palindrome II
    ===========================

    ============
    Description:
    ============

    Given a string s, return true if the s can be palindrome after deleting at
    most one character from it.

    =========================================
    FUNCTION: bool validPalindrome(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aba"
    Output: true

    --- Example 2 ---
    Input: s = "abca"
    Output: true
    Explanation: You could delete the character 'c'.

    --- Example 3 ---
    Input: s = "abc"
    Output: false

    *** Constraints ***
    1 <= s.length <= 105
    s consists of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Keep two pointers at two opposing sides. If at any point we see that two
    characters are NOT equals, then check to see if the remaining INNER part
    of the string without s[L] OR without s[R] is a palindrome.

    We're allowed to remove at most ONE character, therefore if a remaining
    INNER string(i.e. the one without s[L] or the one without s[R]) is NOT
    a palindorme, we return false.

    Otherwise we return true.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.11% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool validPalindrome(string s)
    {
        const int N = s.size();

        int L = 0;
        int R = N-1;

        // O(N) (entire block)
        while (L < R)
        {
            if (s[L] != s[R])
            {
                return is_palindrome(s, L+1, R  ) || // Remove chr s[L]
                       is_palindrome(s, L  , R-1);   // Remove chr s[R]
            }

            L++; // Increment
            R--; // Decrement
        }

        return true;
    }

private:
    bool is_palindrome(string s, int L, int R)
    {
        while (L < R)
        {
            if (s[L] != s[R])
                return false;

            L++; // Increment
            R--; // Decrement
        }

        return true;
    }
};
