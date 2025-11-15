/*
    ==============
    === MEDIUM ===
    ==============

    =======================================================
    3234) Count the Number of Substrings With Dominant Ones
    =======================================================

    ============
    Description:
    ============

    You are given a binary string s.

    Return the number of substrings with dominant ones.

    A string has dominant ones if the number of ones in the string is greater
    than or equal to the square of the number of zeros in the string.

    ===========================================
    FUNCTION: int numberOfSubstrings(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "00011"
    Output: 5
    Explanation:
    The substrings with dominant ones are shown in the table below.
        i    j    s[i..j]    Number of Zeros    Number of Ones
        3    3       1              0              1
        4    4       1              0              1
        2    3       01             1              1
        3    4       11             0              2
        2    4       011            1              2


    --- Example 2 ---
    Input: s = "101101"
    Output: 16
    Explanation:
    The substrings with non-dominant ones are shown in the table below.
    Since there are 21 substrings total and 5 of them have non-dominant ones,
    it follows that there are 16 substrings with dominant ones.
    i    j    s[i..j]    Number of Zeros    Number of Ones
    1    1       0              1                  0
    4    4       0              1                  0
    1    4       0110           2                  2
    0    4       10110          2                  3
    1    5       01101          2                  3


    *** Constraints ***
    1 <= s.length <= 4 * 10^4
    s consists only of characters '0' and '1'.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    I would advise you to skip over this problem. It's not worth it. It' way
    too difficult for a MEDIUM problem.

    There are waaaaay too many edge-cases and it's just not a good problem.
    Unless you know this specific problem, it's almost impossible to solve it
    in a interview-context if you've never seen it before.

*/

/* Time  Beats: 84.56% */
/* Space Beats: 28.86% */

/* Time  Complexity: O(N * sqrt(N)) */
/* Space Complexity: O(N)           */
class Solution {
public:
    int numberOfSubstrings(string s)
    {
        const int N = s.length();

        vector<int> last_zero_prefix(N + 1);
        last_zero_prefix[0] = -1;

        // Build prefix links that jump over contiguous sequences of zeros
        for (int idx = 0; idx < N; idx++)
        {
            if (idx == 0 || (idx > 0 && s[idx - 1] == '0'))
            {
                last_zero_prefix[idx + 1] = idx;
            }
            else
            {
                last_zero_prefix[idx + 1] = last_zero_prefix[idx];
            }
        }

        int resut = 0;

        for (int end_pos = 1; end_pos <= N; end_pos++)
        {
            int zero_count = (s[end_pos - 1] == '0');

            int jump_pos = end_pos;
            while (jump_pos > 0 && zero_count * zero_count <= N)
            {
                // Count ones inside the substring ending at end_pos,
                // starting after last sequence of zeros
                int one_count = (end_pos - last_zero_prefix[jump_pos]) - zero_count;

                if (zero_count * zero_count <= one_count)
                {
                    resut += min(
                        jump_pos - last_zero_prefix[jump_pos],
                        one_count - zero_count * zero_count + 1
                    );
                }

                jump_pos = last_zero_prefix[jump_pos];
                zero_count++;
            }
        }

        return resut;
    }
};
