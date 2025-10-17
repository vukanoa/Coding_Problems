/*
    ============
    === HARD ===
    ============

    ========================================================
    3003) Maximize the Number of Partitions After Operations
    ========================================================

    ============
    Description:
    ============

    You are given a string s and an integer k.

    First, you are allowed to change at most one index in s to another
    lowercase English letter.

    After that, do the following partitioning operation until s is empty:

        + Choose the longest prefix of s containing at most k distinct
          characters.

        + Delete the prefix from s and increase the number of partitions by
          one. The remaining characters (if any) in s maintain their initial
          order.

    Return an integer denoting the maximum number of resulting partitions after
    the operations by optimally choosing at most one index to change.

    ============================================================
    FUNCTION: int maxPartitionsAfterOperations(string s, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "accca", k = 2
    Output: 3
    Explanation:
    The optimal way is to change s[2] to something other than a and c, for example, b. then it becomes "acbca".
    Then we perform the operations:
        The longest prefix containing at most 2 distinct characters is "ac", we remove it and s becomes "bca".
        Now The longest prefix containing at most 2 distinct characters is "bc", so we remove it and s becomes "a".
        Finally, we remove "a" and s becomes empty, so the procedure ends.
    Doing the operations, the string is divided into 3 partitions, so the answer is 3.

    --- Example 2 ---
    Input: s = "aabaab", k = 3
    Output: 1
    Explanation:
    Initially s contains 2 distinct characters, so whichever character we
    change, it will contain at most 3 distinct characters, so the longest
    prefix with at most 3 distinct characters would always be all of it,
    therefore the answer is 1.

    --- Example 3 ---
    Input: s = "xxyz", k = 1
    Output: 4
    Explanation:
    The optimal way is to change s[0] or s[1] to something other than
    characters in s, for example, to change s[0] to w.
    Then s becomes "wxyz", which consists of 4 distinct characters, so as k is
    1, it will divide into 4 partitions.

    *** Constraints ***
    1 <= s.length <= 10^4
    s consists only of lowercase English letters.
    1 <= k <= 26

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Not worth your time)

*/

/* Time  Beats: 81.15% */
/* Space Beats: 83.61% */

/* Time  Complexity: O(26 * N) --> O(N) */
/* Space Complexity: O(N)               */
class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k)
    {
        const int N = s.length();
        vector<vector<int>> left (N, vector<int>(3));
        vector<vector<int>> right(N, vector<int>(3));

        int num = 0;
        int mask = 0;
        int count = 0;
        for (int i = 0; i < N-1; i++)
        {
            int binary = 1 << (s[i] - 'a');

            if ( ! (mask & binary))
            {
                count++;

                if (count <= k)
                {
                    mask |= binary;
                }
                else
                {
                    num++;
                    mask = binary;
                    count = 1;
                }
            }

            left[i + 1][0] = num;
            left[i + 1][1] = mask;
            left[i + 1][2] = count;
        }

        num = 0;
        mask = 0;
        count = 0;
        for (int i = N-1; i > 0; i--)
        {
            int binary = 1 << (s[i] - 'a');

            if ( ! (mask & binary))
            {
                count++;

                if (count <= k)
                {
                    mask |= binary;
                }
                else
                {
                    num++;
                    mask = binary;
                    count = 1;
                }
            }

            right[i - 1][0] = num;
            right[i - 1][1] = mask;
            right[i - 1][2] = count;
        }

        int max_value = 0;
        for (int i = 0; i < N; i++)
        {
            int segment     = left[i][0] + right[i][0] + 2;
            int total_mask  = left[i][1] | right[i][1];
            int total_count = 0;

            while (total_mask)
            {
                total_mask = total_mask & (total_mask - 1);
                total_count++;
            }

            if (left[i][2] == k && right[i][2] == k && total_count < 26)
            {
                segment++;
            }
            else if (min(total_count + 1, 26) <= k)
            {
                segment--;
            }

            max_value = max(max_value, segment);
        }

        return max_value;
    }
};
