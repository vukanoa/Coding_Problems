/*
    ============
    === EASY ===
    ============

    =============================
    4030) Check ASCII Palindromic
    =============================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters.

    Construct a binary string by replacing each character in s with the 8-bit
    binary representation of its ASCII value, including leading zeros, while
    preserving the original order of the characters.

    Return true if the resulting binary string is a palindrome. Otherwise,
    return false.

    =======================================
    FUNCTION: bool isPalindromic(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ff"
    Output: true
    Explanation:
        The ASCII value of f is 102, whose 8-bit binary representation is 01100110.
        Thus, the binary string is 0110011001100110.
        Since this binary string is a palindrome, the output is true.

    --- Example 2 ---
    Input: s = "leet"
    Output: false
    Explanation:
        The ASCII values of l, e, e, and t are 108, 101, 101, and 116, respectively.
        Their 8-bit binary representations are 01101100, 01100101, 01100101, and 01110100.
        Thus, the binary string is 01101100011001010110010101110100.
        Since this binary string is not a palindrome, the output is false.


    *** Constraints ***
    1 <= s.length <= 100
    s consists of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  35.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isPalindromic(string s)
    {
        const int N = s.size();

        string bin_str;
        bin_str.reserve(N * 8);

        for (const char& chr : s)
        {
            for (int bit = 7; bit >= 0; bit--)
            {
                if (chr & (1 << bit))
                    bin_str += '1';
                else
                    bin_str += '0';
            }
        }

        int L = 0;
        int R = bin_str.size() - 1;
        while (L < R)
        {
            if (bin_str[L] != bin_str[R])
                return false;

            ++L;
            --R;
        }

        return true;
    }
};
