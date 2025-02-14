/*
    ============
    === HARD ===
    ============

    ===================================================
    3261) Count Substrings That Satisfy K-Constraint II
    ===================================================

    ============
    Description:
    ============

    You are given a binary string s and an integer k.

    You are also given a 2D integer array queries, where queries[i] = [li, ri].

    A binary string satisfies the k-constraint if either of the following
    conditions holds:

        The number of 0's in the string is at most k.
        The number of 1's in the string is at most k.

    Return an integer array answer, where answer[i] is the number of substrings
    of s[li..ri] that satisfy the k-constraint.

    ======================================================================================================
    FUNCTION: vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries);
    ======================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "0001111", k = 2, queries = [[0,6]]
    Output: [26]
    Explanation:
    For the query [0, 6], all substrings of s[0..6] = "0001111" satisfy the
    k-constraint except for the substrings s[0..5] = "000111" and s[0..6] =
    "0001111".

    --- Example 2 ---
    Input: s = "010101", k = 1, queries = [[0,5],[1,4],[2,3]]
    Output: [15,9,3]
    Explanation:
    The substrings of s with a length greater than 3 do not satisfy the
    k-constraint.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.
    1 <= k <= s.length
    1 <= queries.length <= 10^5
    queries[i] == [li, ri]
    0 <= li <= ri < s.length
    All queries are distinct.

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

/* Time  Beats: 52.38% */
/* Space Beats: 79.05% */

/* Time  Complexity: O(N + Q * logN) */
/* Space Complexity: O(N + Q)        */
class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries)
    {
        int N = s.size();

        vector<long long> result;
        vector<long long> prefix_sum(N);
        vector<int> previous(N);

        int ones  = 0;
        int zeroes = 0;

        int L = 0;
        for (int R = 0; R < N; R++)
        {
            s[R] == '1' ? ones++ : zeroes++;

            while (zeroes > k && ones > k)
            {
                s[L] == '1' ? ones-- : zeroes--;
                L++;
            }

            previous[R] = L;
        }

        prefix_sum[0] = 1;
        for (int i = 1; i < N; i++)
            prefix_sum[i] = prefix_sum[i-1] + i - previous[i] + 1;

        for (auto& entry : queries)
        {
            int left  = entry[0];
            int right = entry[1];
            int original_right = right;  // Store the original right value

            long long curr  = 0;
            int index = right + 1;

            /* Binary Search */
            while (left <= right)
            {
                int mid = (left + right) / 2;

                if (previous[mid] >= entry[0])
                {
                    index = mid;
                    right = mid - 1;
                }
                else
                    left = mid + 1;
            }

            // If there exists such index
            if (index <= original_right)
            {
                curr += prefix_sum[original_right];

                if (index > 0)
                    curr -= prefix_sum[index - 1];
            }

            curr += (1LL * (index - entry[0]) * (index - entry[0] + 1)) / 2;
            result.push_back(curr);
        }

        return result;
    }
};
