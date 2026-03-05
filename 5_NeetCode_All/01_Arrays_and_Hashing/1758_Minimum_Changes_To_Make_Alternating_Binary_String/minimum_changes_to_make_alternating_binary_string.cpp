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

#include <string>
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

    We don't need two passes where we check how many differences are there with
    the first desired string and how many with the other.

    We can only go through once and and conclude that the second amount of
    differences will certainly be:

        N - previous_difference

    
    That means we'll only have a single pass and we'll return:

        return min(previous_difference, N - previous_difference);
*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(string s)
    {
        const int N = s.size();
        unsigned long count = 0; // Operations if string s starts with 0

        for (int i = 0; i < N; i++)
        {
            if (i & 1) // Odd
                count += (s[i] == '0') ? 1 : 0;
            else
                count += (s[i] == '1') ? 1 : 0;
        }

        return min(count, N - count);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Essentially the same as above, however it's much more explicit and I
    believe it's much more easier to read and grasp.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.63% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int minOperations(string s)
    {
        const int N = s.size();

        int start_0_count = 0;
        int start_1_count = 0;

        for (int i = 0; i < N; i++)
        {
            if (i % 2 == 0)
            {
                start_0_count += s[i] == '0' ? 0 : 1;
                start_1_count += s[i] == '1' ? 0 : 1;
            }
            else
            {
                start_0_count += s[i] == '1' ? 0 : 1;
                start_1_count += s[i] == '0' ? 0 : 1;
            }
        }

        return min(start_0_count, start_1_count);
    }
};
