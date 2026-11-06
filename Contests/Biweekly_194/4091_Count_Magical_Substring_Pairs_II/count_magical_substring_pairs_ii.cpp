/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    4091) Count Magical Substring Pairs II
    ======================================

    ============
    Description:
    ============

    You are given a string s of length n consisting of lowercase English
    letters.

    For every triplet of indices (i, j, k) satisfying 0 <= i <= j < k < n,
    define:

        s1 = s[i..j]
        s2 = s[j + 1..k]

    A pair of substrings (s1, s2) is called magical if the number of distinct
    characters in s1 is equal to the number of distinct characters in s2.

    Return the number of triplets (i, j, k) for which (s1, s2) is a magical
    pair.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ==========================================
    FUNCTION: int countMagicalPairs(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aba"
    Output: 2
    Explanation:
    There are 2 valid triplets:
    No.    (i, j, k)    s1    s2    distinct(s1)    distinct(s2)
    1      (0, 0, 1)    "a"    "b"       1               1
    2      (1, 1, 2)    "b"    "a"       1               1


    --- Example 2 ---
    Input: s = "kkk"
    Output: 4
    Explanation:
    There are 4 valid triplets:
    No.    (i, j, k)    s1     s2    distinct(s1)    distinct(s2)
    1      (0, 0, 1)    "k"    "k"       1               1
    2      (0, 0, 2)    "k"    "kk"      1               1
    3      (0, 1, 2)    "kk"   "k"       1               1
    4      (1, 1, 2)    "k"    "k"       1               1


    --- Example 3 ---
    Input: s = "abcac"
    Output: 7
    Explanation:
    There are 7 valid triplets:
    No.    (i, j, k)    s1     s2    distinct(s1)    distinct(s2)
    1      (0, 0, 1)    "a"    "b"       1               1
    2      (1, 1, 2)    "b"    "c"       1               1
    3      (2, 2, 3)    "c"    "a"       1               1
    4      (3, 3, 4)    "a"    "c"       1               1
    5      (0, 1, 3)    "ab"   "ca"      2               2
    6      (0, 1, 4)    "ab"   "cac"     2               2
    7      (1, 2, 4)    "bc"   "ac"      2               2


    *** Constraints ***
    2 <= s.length <= 10^5
    s consists of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 33.54% */
/* Space Beats: 15.99% */

/* Time  Complexity: O(N * 26 * log(26)) */
/* Space Complexity: O(N * 27)           */
class Solution_Linear {
public:
    long long countMagicalPairs(string s)
    {
        const int N = s.size();
        long long result = 0LL;

        vector<vector<int>> L_subarrays_count_with(N, vector<int>(27, 0));
        vector<vector<int>> R_subarrays_count_with(N, vector<int>(27, 0));

        vector<int> last_idx(26);

        /* Build L_subarrays_count_with */
        fill(last_idx.begin(), last_idx.end(), -1);

        for (int i = 0; i < N; i++)
        {
            last_idx[s[i] - 'a'] = i;

            vector<int> distinct_char_indices;
            int L_distinct = 0;

            for (const int& idx : last_idx)
            {
                if (idx != -1)
                {
                    distinct_char_indices.push_back(idx);
                    ++L_distinct;
                }
            }

            /* Sort in DESCENDING order */
            sort(distinct_char_indices.begin(), distinct_char_indices.end(), greater<int>());

            for (int distinct = 1; distinct <= L_distinct; distinct++)
            {
                L_subarrays_count_with[i][distinct] = distinct_char_indices[distinct - 1];

                if (distinct < L_distinct)
                    L_subarrays_count_with[i][distinct] -= distinct_char_indices[distinct];
                else
                    L_subarrays_count_with[i][distinct] -= -1;
            }
        }

        /* Build R_subarrays_count_with */
        fill(last_idx.begin(), last_idx.end(), N);

        for (int i = N-1; i >= 0; i--)
        {
            last_idx[s[i] - 'a'] = i;

            vector<int> distinct_char_indices;
            int R_distinct = 0;

            for (const int& idx : last_idx)
            {
                if (idx != N)
                {
                    distinct_char_indices.push_back(idx);
                    ++R_distinct;
                }
            }

            /* Sort in ASCENDING order */
            sort(distinct_char_indices.begin(), distinct_char_indices.end());

            for (int distinct = 1; distinct <= R_distinct; distinct++)
            {
                if (distinct < R_distinct)
                    R_subarrays_count_with[i][distinct] = distinct_char_indices[distinct];
                else
                    R_subarrays_count_with[i][distinct] = N;

                R_subarrays_count_with[i][distinct] -= distinct_char_indices[distinct - 1];
            }
        }

        /* Count Magical Pairs */
        for (int j = 0; j < N-1; j++)
        {
            for (int distinct = 1; distinct <= 26; distinct++)
            {
                result += 1LL * L_subarrays_count_with[j  ][distinct] *
                                R_subarrays_count_with[j+1][distinct];
            }
        }

        return result;
    }
};
