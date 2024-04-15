#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    926) Flip String to Montone Increasing
    ======================================

    ============
    Description:
    ============

    A binary string is monotone increasing if it consists of some number of 0's
    (possibly none), followed by some number of 1's (also possibly none).

    You are given a binary string s. You can flip s[i] changing it from 0 to 1
    or from 1 to 0.

    Return the minimum number of flips to make s monotone increasing.

    =========================================
    FUNCTION: int minFlipsMonoIncr(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "00110"
    Output: 1
    Explanation: We flip the last digit to get 00111.

    --- Example 2 ---
    Input: s = "010110"
    Output: 2
    Explanation: We flip to get 011111, or alternatively 000111.

    --- Example 3 ---
    Input: s = "00011000"
    Output: 2
    Explanation: We flip to get 00000000.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    1. Traverse the string from left to right

    2. Whenever you encounter a '1' there are 2 possible cases:

         + You can keep this as '1', then all the chars at right should be '1'
           to make it increasing, so flip all the '0's (towards right) to '1's,

           or

         +  Flip the curr '1' to '0' and move on


*/

/* Time  Beats: 96.42% */
/* Space Beats: 44.86% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minFlipsMonoIncr(string s)
    {
        const int n = s.size();
        std::vector<int> post(n); // Count of number of '0's to the right

        post[n - 1] = (s[n - 1] == '0') ? 1 : 0;

        for (int i = n-2; i >= 0; i--)
            post[i] = post[i + 1] + (s[i] == '0' ? 1 : 0);

        int curr_flips = 0;
        int result = n;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
            {
                int to_flip = (i+1 == n) ? 0 : post[i+1];

                /* Make all the 0's to 1's towards right */
                int total_flips = curr_flips + to_flip;

                result = std::min(result, total_flips);
                curr_flips++; // Just flip the current '1' to '0' and move
            }
        }

        result = std::min(result, curr_flips);

        return result;
    }
};
