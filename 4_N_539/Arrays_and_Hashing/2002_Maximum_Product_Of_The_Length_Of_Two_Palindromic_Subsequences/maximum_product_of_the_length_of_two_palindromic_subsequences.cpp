#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    2002) Maximum Product of the Length of Two Palindromic Subsequences
    ===================================================================

    ============
    Description:
    ============

    Given a string s, find two disjoint palindromic subsequences of s such that
    the product of their lengths is maximized. The two subsequences are
    disjoint if they do not both pick a character at the same index.

    Return the maximum possible product of the lengths of the two palindromic
    subsequences.

    A subsequence is a string that can be derived from another string by
    deleting some or no characters without changing the order of the remaining
    characters. A string is palindromic if it reads the same forward and
    backward.

    ===================================
    FUNCTION: int maxProduct(string s);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "leetcodecom"
    Output: 9
    Explanation: An optimal solution is to choose "ete" for the 1st subsequence
                 and "cdc" for the 2nd subsequence.  The product of their
                 lengths is: 3 * 3 = 9.


    --- Example 2 ---
    Input: s = "bb"
    Output: 1
    Explanation: An optimal solution is to choose "b" (the first character) for
                 the 1st subsequence and "b" (the second character) for the 2nd
                 subsequence.  The product of their lengths is: 1 * 1 = 1.


    --- Example 3 ---
    Input: s = "accbcaxxcxx"
    Output: 25
    Explanation: An optimal solution is to choose "accca" for the 1st
                 subsequence and "xxcxx" for the 2nd subsequence.  The product
                 of their lengths is: 5 * 5 = 25.


    *** Constraints ***
    2 <= s.length <= 12
    s consists of lowercase English letters only.

*/

/*
    ------------
    --- IDEA ---
    ------------

    In the "Constraints", they're hinting that we can and should do a
    Brute force, since: 2 <= s.length <= 12

*/

/* Time  Beats: 68.59% */
/* Space Beats: 28.30% */

/* Time  Complexity: O(4^n) */
/* Space Complexity: O(4^n) */
class Solution {
public:
    int maxProduct(string s)
    {
        int N = s.length();

        std::unordered_map<int, int> umap;

        for (int mask = 1; mask < (1 << N); mask++)
        {
            std::ostringstream out;
            int shifting_one = 1;

            for (int x = 0; x < N; x++)
            {
                if (mask & (1 << x))
                    out << s[N - x - 1]; // It also works with: out << s[x];
            }

            std::string orig = out.str();
            std::string rev  = out.str();
            std::reverse(rev.begin(), rev.end());

            if (orig == rev) // If it is a palindrome
                umap.insert( {mask, orig.length()} );
        }

        int result = 0;
        for (auto& entry_1 : umap)
        {
            int mask_1 = entry_1.first;
            int len_1  = entry_1.second;

            for (auto& entry_2 : umap)
            {
                int mask_2 = entry_2.first;
                int len_2  = entry_2.second;

                if ((mask_1 & mask_2) == 0)
                    result = std::max(result, len_1 * len_2);
            }
        }

        return result;
    }
};
