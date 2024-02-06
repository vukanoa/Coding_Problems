#include <iostream>

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

/*
    ------------
    --- IDEA ---
    ------------

    Once left and right pointer point to different characters, check:
        1. Substring [left, right] without the char "left"  pointers points to.
        2. Substring [left, right] without the char "right" pointers points to.

    Note that we are not checking the entire remaining of the string, only the
    substring between "left" and "right" pointer, inclusive.

    Example:
        a b x d e d t b a

    Since prefix "ab" and suffix "ba" are the same, we do NOT consider them.

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                                s = "a b x d e d t b a"

-------------------------------------------------------------------------------

    1) s = "a b x d e d t b a"  // S[L] == S[R] --> L++; R--;
            L               R

-------------------------------------------------------------------------------

    2) s = "a b x d e d t b a"  // S[L] == S[R] --> L++; R--;
              L           R

-------------------------------------------------------------------------------

    3) s = "a b x d e d t b a"  // S[L] != S[R] --> Check w/o s[L] and w/o s[R]
                L       R

            without_left  = "dedt" // s.substr(L+1, R - L);
            without_right = "xded" // s.substr(L  , R - L);

        If either of these two substrings IS INDEED a palindrome - return true.
        Else, return false;

-------------------------------------------------------------------------------

*/

/* Time  Beats: 84.72% */
/* Space Beats: 79.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Neat {
public:
    bool validPalindrome(std::string s)
    {
        if (palindrome(s))
            return true;

        int left  = 0;
        int right = s.length() - 1;

        while(left < right)
        {
            if (s[left] != s[right])
            {
                std::string without_left  = s.substr(left+1, right - left);
                std::string without_right = s.substr(left  , right - left);

                return palindrome(without_left) || palindrome(without_right);
            }

            left++;
            right--;
        }

        return false;
    }

private:
    bool palindrome(std::string s)
    {
        int left  = 0;
        int right = s.length() - 1;

        while (left < right)
        {
            if (s[left] != s[right])
                return false;

            left++;
            right--;
        }

        return true;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    This implementation got better results on LeetCode. I have no idea why.
    Maaaybe because we do not call a function, however compiler should optimize
    for that.

    Anyway, this one is faster on LeetCode even if both Time and Space
    Complexities are the same.

*/

/* Time  Beats: 93.93% */
/* Space Beats: 90.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool validPalindrome(string s)
    {
        int left  = 0;
        int right = s.length() - 1;

        while (left < right)
        {
            if (s[left] != s[right])
            {
                // Skip left
                int l = left + 1;
                int r = right;

                bool palindrome = true;
                while (l < r)
                {
                    if (s[l] != s[r])
                    {
                        palindrome = false;
                        break;
                    }

                    l++;
                    r--;
                }

                if (palindrome)
                    return true;

                palindrome = true;

                // Skip Right
                l = left;
                r = right - 1;

                while (l < r)
                {
                    if (s[l] != s[r])
                    {
                        palindrome = false;
                        break;
                    }

                    l++;
                    r--;
                }

                if (palindrome)
                    return true;

                return false;
            }

            left++;
            right--;
        }

        return true;
    }
};
