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
        1. The remaining string without the char "left"  pointers points to
        2. The remaining string without the char "right" pointers points to

    If either of them is a palindrome - return true.

    Otherwise, return false.

    These two examples are important:
        1. a b d f g g f d b c a
        2. a b c f g g f c b c a

*/

/* Time  Beats: 84.72% */
/* Space Beats: 79.03% */

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
                if (is_palindrome(s, left+1, right))
                    return true;

                // Skip Right
                return is_palindrome(s, left, right-1);
            }

            left++;
            right--;
        }

        return true;
    }

private:
    bool is_palindrome(std::string& s, int left, int right)
    {
        bool palindrome = true;

        while (left < right)
        {
            if (s[left] != s[right])
            {
                palindrome = false;
                break;
            }

            left++;
            right--;
        }

        return palindrome;
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
