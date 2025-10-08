/*
    ==============
    === MEDIUM ===
    ==============

    =============================================================
    1689) Partitioning Into Minimum Number Of Deci-Binary Numbers
    =============================================================

    ============
    Description:
    ============

    A decimal number is called deci-binary if each of its digits is either 0 or
    1 without any leading zeros. For example, 101 and 1100 are deci-binary,
    while 112 and 3001 are not.

    Given a string n that represents a positive decimal integer, return the
    minimum number of positive deci-binary numbers needed so that they sum up
    to n.

    ======================================
    FUNCTION: int minPartitions(string n);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = "32"
    Output: 3
    Explanation: 10 + 11 + 11 = 32

    --- Example 2 ---
    Input: n = "82734"
    Output: 8

    --- Example 3 ---
    Input: n = "27346209830709182346"
    Output: 9

    *** Constraints ***
    1 <= n.length <= 10^5
    n consists of only digits.
    n does not contain any leading zeros and represents a positive integer.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.75% */
/* Space Beats: 51.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minPartitions(string n)
    {
        const int N = n.length();
        int max_digit_in_string = 0;
        
        for (const auto& element : n)
        {
            // convert the string number into integer number by subtracting the
            // ascii value.
            int digit = element - '0';
            max_digit_in_string = max(max_digit_in_string, digit);
        }
        
        return max_digit_in_string;
    }
};
