#include <iostream>

/*
    ============
    === EASY ===
    ============

    ======================================================
    28) Find The Index Of The First Occurrence In A String
    ======================================================

    ============
    Description:
    ============

    Given two strings needle and haystack, return the index of the first
    occurrence of needle in haystack, or -1 if needle is not part of haystack.

    =====================================================
    FUNCTION: int strStr(string haystack, string needle);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: haystack = "sadbutsad", needle = "sad"
    Output: 0
    Explanation: "sad" occurs at index 0 and 6.
    The first occurrence is at index 0, so we return 0.

    --- Example 2 ---
    Input: haystack = "leetcode", needle = "leeto"
    Output: -1
    Explanation: "leeto" did not occur in "leetcode", so we return -1.


    *** Constraints ***
    1 <= haystack.length, needle.length <= 10^4
    haystack and needle consist of only lowercase English characters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:   100% */
/* Space Beats: 26.40% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int strStr(std::string haystack, std::string needle)
    {
        if (needle.length() > haystack.length())
            return -1;

        int j = 0;
        int start = 0;
        for (int i = 0; i < haystack.length(); i++)
        {
            if (haystack[i] == needle[j])
            {
                if (j == needle.length() - 1)
                    return i - needle.length() + 1;

                j++;
            }
            else
            {
                j = 0;
                i = start++;
            }
        }

        return -1;
    }
};
