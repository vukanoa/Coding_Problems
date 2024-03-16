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




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  24.28% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int strStr(string haystack, string needle)
    {
        if (needle.length() > haystack.length())
            return -1;

        int x = 0;
        int i = 0;
        while (i < haystack.length())
        {
            if (haystack[i] != needle[x])
            {
                i = i - x + 1;
                x = 0;
                continue;
            }
            else
                x++;

            if (x == needle.length())
                return i - needle.length() + 1;

            i++;
        }

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.03% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int strStr(std::string haystack, std::string needle)
    {
        int x = needle.size(); // Get the size of the needle

        // Iterate through the characters of the haystack
        for (int i = 0; i < haystack.size(); i++)
        {
            // Check if the substring of haystack starting at index i and of
            // length x is equal to the needle
            if (needle == haystack.substr(i, x))
                return i; // If true, return the current index i
        }

        return -1; // If no match is found, return -1
    }
};
