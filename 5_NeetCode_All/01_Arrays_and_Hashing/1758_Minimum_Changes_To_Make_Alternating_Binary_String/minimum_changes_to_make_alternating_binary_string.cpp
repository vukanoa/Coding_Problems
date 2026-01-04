#include <iostream>

/*
    ============
    === EASY ===
    ============

    ========================================================
    1758) Minimum Changes to Makes Alternating Binary String
    ========================================================

    ============
    Description:
    ============

    You are given a string s consisting only of the characters '0' and '1'. In
    one operation, you can change any '0' to '1' or vice versa.

    The string is called alternating if no two adjacent characters are equal.
    For example, the string "010" is alternating, while the string "0100" is
    not.

    Return the minimum number of operations needed to make s alternating.

    ======================================
    FUNCTION: int minOperations(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "0100"
    Output: 1
    Explanation: If you change the last character to '1', s will be "0101",
                 which is alternating.

    --- Example 2 ---
    Input: s = "10"
    Output: 0
    Explanation: s is already alternating.

    --- Example 3 ---
    Input: s = "1111"
    Output: 2
    Explanation: You need two operations to reach "0101" or "1010".


    *** Constraints ***
    1 <= s.length <= 10^4
    s[i] is either '0' or '1'.

*/

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Imagine any example:

        01001010

    What is the desired string?

    It's either:

        01010101 

            or

        10101010

    We can just compare both of these to our Input and see how many differences
    are there.

    However, the answer will always be one or the other.

    Let's look at even simpler example:

        0100

    The desired string is either:
        
        0101

            or

        1010

    So it's either 1 or 3 differences. But do you notice something?

    We don't have to have two passes where we check how many differences are
    there with the first desired string and how many with the other.

    We can only go through and and conclude that the second amount of
    differences will certainly be:

        s.length() - previous_difference

    
    That means we'll only have a single pass and we'll return:

        return min(previous_difference, s.length() - previous_difference);

    (Note that in C++ s.length is "unsigned long", therefore
     "previous_difference" also has to be of that type so that we can put both
     in std::min)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(string s)
    {
        unsigned long count = 0; // Operations if string s starts with 0

        for (int i = 0; i < s.length(); i++)
        {
            if (i & 1) // Odd
                count += (s[i] == '0') ? 1 : 0;
            else
                count += (s[i] == '1') ? 1 : 0;
        }

        return min(count, s.length() - count);
    }
};
