/*
    ============
    === EASY ===
    ============

    ======================================
    1796) Second Largest Digit in a String
    ======================================

    ============
    Description:
    ============

    Given an alphanumeric string s, return the second largest numerical digit
    that appears in s, or -1 if it does not exist.

    An alphanumeric string is a string consisting of lowercase English letters
    and digits.

    ======================================
    FUNCTION: int secondHighest(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "dfa12321afd"
    Output: 2
    Explanation: The digits that appear in s are [1, 2, 3]. The second largest
                 digit is 2.

    --- Example 2 ---
    Input: s = "abc1111"
    Output: -1
    Explanation: The digits that appear in s are [1]. There is no second
                 largest digit. 


    *** Constraints ***
    1 <= s.length <= 500
    s consists of only lowercase English letters and digits.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.65% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int secondHighest(string s)
    {
        const int N = s.length();

        vector<bool> seen_digit(10, false); // O(1) Space

        for (const char& chr : s) // O(N)
        {
            if (isdigit(chr))
            {
                int digit = chr - '0'; // '0' is 48 in ASCII

                seen_digit[digit] = true;
            }
        }

        bool used_largest = false;

        for (int i = 9; i >= 0; i--) // O(1)
        {
            if (seen_digit[i])
            {
                if (used_largest == true)
                    return i;

                used_largest = true;
            }
        }

        return -1;
    }
};
