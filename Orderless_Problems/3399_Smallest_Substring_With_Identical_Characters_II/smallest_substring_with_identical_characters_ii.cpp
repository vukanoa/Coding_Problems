/*
    ============
    === HARD ===
    ============

    =====================================================
    3399) Smallest Substring With Identical Characters II
    =====================================================

    ============
    Description:
    ============

    You are given a binary string s of length n and an integer numOps.

    You are allowed to perform the following operation on s at most numOps
    times:

        + Select any index i (where 0 <= i < n) and flip s[i]. If s[i] == '1',
          change s[i] to '0' and vice versa.

    You need to minimize the length of the longest

    of s such that all the characters in the substring are identical.

    Return the minimum length after the operations.

    ==============================================
    FUNCTION: int minLength(string s, int numOps);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "000001", numOps = 1
    Output: 2
    Explanation: By changing s[2] to '1', s becomes "001001". The longest
                 substrings with identical characters are s[0..1] and s[3..4].

    --- Example 2 ---
    Input: s = "0000", numOps = 2
    Output: 1
    Explanation:  By changing s[0] and s[2] to '1', s becomes "1010".

    --- Example 3 ---
    Input: s = "0101", numOps = 0
    Output: 1


    *** Constraints ***
    1 <= n == s.length <= 10^5
    s consists only of '0' and '1'.
    0 <= numOps <= n

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.91% */
/* Space Beats: 81.88% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minLength(string s, int numOps)
    {
        const int N = s.size();

        int flips_needed = 0;

        int left  = 2;
        int right = N;

        // Count flips to make string alternate starting with '0' or '1'
        for (int i = 0; i < N; i++)
            flips_needed += (s[i] - '0') != (i % 2);

        if (min(flips_needed, N - flips_needed) <= numOps)
            return 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2; // Prevent Overflow

            int operations_used = 0;
            int curr_run_len = 1;
            int previous_char = s[0] - '0';

            for (int i = 1; i < N; ++i)
            {
                if (s[i] - '0' == previous_char)
                    curr_run_len++;
                else
                    curr_run_len = 1;

                if (curr_run_len > mid)
                {
                    operations_used++;

                    if (i + 1 < N && s[i] == s[i + 1])
                        previous_char = !previous_char;

                    curr_run_len = 1;
                }
                else
                {
                    previous_char = s[i] - '0';
                }
            }

            if (operations_used <= numOps)
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};
