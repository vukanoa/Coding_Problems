/*
    ============
    === HARD ===
    ============

    ==========================================================
    3445) Maximum Difference Between Even and Odd Frequency II
    ==========================================================

    ============
    Description:
    ============

    You are given a string s and an integer k. Your task is to find the maximum
    difference between the frequency of two characters, freq[a] - freq[b], in a
    substrings subs of s, such that:

        + subs has a size of at least k.
        + Character a has an odd frequency in subs.
        + Character b has an even frequency in subs.

    Return the maximum difference.

    =====
    Note: that subs can contain more than 2 distinct characters.
    =====

    =============================================
    FUNCTION: int maxDifference(string s, int k);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "12233", k = 4
    Output: -1
    Explanation: For the substring "12233", the frequency of '1' is 1 and the
                 frequency of '3' is 2. The difference is 1 - 2 = -1.

    --- Example 2 ---
    Input: s = "1122211", k = 3
    Output: 1
    Explanation: For the substring "11222", the frequency of '2' is 3 and the
                 frequency of '1' is 2. The difference is 3 - 2 = 1.

    --- Example 3 ---
    Input: s = "110", k = 3
    Output: -1


    *** Constraints ***
    3 <= s.length <= 3 * 10^4
    s consists only of digits '0' to '4'.
    The input is generated that at least one substring has a character with an
    even frequency and a character with an odd frequency.
    1 <= k <= s.length

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

/* Time  Beats: 96.15% */
/* Space Beats: 97.44% */

/* Time  Complexity: O(N * 20)  -->  O(N) */
/* Space Complexity: O(1)                 */
class Solution {
public:
    int maxDifference(string s, int k)
    {
        auto get_status = [](int cnt_a, int cnt_b) -> int
        {
            return ((cnt_a & 1) << 1) | (cnt_b & 1);
        };

        const int N = s.size();
        int result = INT_MIN;

        for (char a = '0'; a <= '4'; a++)
        {
            for (char b = '0'; b <= '4'; b++)
            {
                if (a == b)
                    continue;

                int best[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
                int cnt_a = 0;
                int cnt_b = 0;

                int prev_a = 0;
                int prev_b = 0;

                int left = -1;
                for (int right = 0; right < N; right++)
                {
                    cnt_a += (s[right] == a);
                    cnt_b += (s[right] == b);

                    while (right - left >= k && cnt_b - prev_b >= 2)
                    {
                        int left_status = get_status(prev_a, prev_b);
                        best[left_status] = min(best[left_status], prev_a - prev_b);

                        left++;

                        prev_a += (s[left] == a);
                        prev_b += (s[left] == b);
                    }

                    int right_status = get_status(cnt_a, cnt_b);

                    if (best[right_status ^ 0b10] != INT_MAX)
                        result = max(result, cnt_a - cnt_b - best[right_status ^ 0b10]);
                }
            }
        }

        return result;
    }
};
