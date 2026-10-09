/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    4071) Minimum Rotations to Dial a Number II
    ===========================================

    ============
    Description:
    ============

    You are given an integer n and a string s of length n consisting of digits.

    The dial contains the digits 0 through 9 in order and is circular, so 0 and
    9 are adjacent. The pointer initially points to 0.

    To dial each digit of s in order, rotate the pointer until it points to
    that digit. Each rotation moves the pointer to an adjacent digit, and you
    may rotate in either direction. Dialing a digit that the pointer already
    points to requires no rotations.

    Before dialing, you may perform the following operation at most once:

        + Choose an index k such that 0 <= k < n and reverse the
          suffix s[k..n - 1].

    Return the minimum total number of rotations needed to dial the string
    after optimally choosing whether to perform the operation and which suffix
    to reverse.

    ============================================
    FUNCTION: int minRotations(int n, string s);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, s = "1502"
    Output: 9
    Explanation:
    Reverse the suffix starting at k = 1 to obtain "1205", then dial it.

    --- Example 2 ---
    Input: n = 4, s = "2916"
    Output: 12

    --- Example 3 ---
    Input: n = 4, s = "4219"
    Output: 6


    *** Constraints ***
    1 <= n == s.length <= 10^5
    s consists only of digits '0' to '9'

*/

#include <climits>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.38% */
/* Space Beats: 99.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minRotations(int n, string s)
    {
        const int N = s.size();
        int result = 0;

        int max_gain = INT_MIN;

        char pointer = '0';
        for (int i = 0; i < N; i++)
        {
            int to_left  = 10 - abs(pointer - s[i]);
            int to_right = abs(pointer - s[i]);

            int curr_dist = min(to_left, to_right);

            result += curr_dist;

            int to_last_left  = 10 - abs(pointer - s.back());
            int to_last_right = abs(pointer - s.back());

            max_gain = max(max_gain, curr_dist - min(to_last_left, to_last_right));

            pointer = s[i];
        }

        return result - max_gain;
    }
};
