/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3458) Select K Disjoint Special Susbstrings
    ===========================================

    ============
    Description:
    ============

    Given a string s of length n and an integer k, determine whether it is
    possible to select k disjoint special substrings.

    A special substring is a substring where:

        + Any character present inside the substring should not appear outside
          it in the string.

        + The substring is not the entire string s.

    Note that all k substrings must be disjoint, meaning they cannot overlap.

    Return true if it is possible to select k such disjoint special substrings;
    otherwise, return false.

    ===================================================
    FUNCTION: bool maxSubstringLength(string s, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcdbaefab", k = 2
    Output: true
    Explanation:
    We can select two disjoint special substrings: "cd" and "ef".
    "cd" contains the characters 'c' and 'd', which do not appear elsewhere
    in s.

    "ef" contains the characters 'e' and 'f', which do not appear elsewhere
    in s.


    --- Example 2 ---
    Input: s = "cdefdc", k = 3
    Output: false
    Explanation:
    There can be at most 2 disjoint special substrings: "e" and "f".
    Since k = 3, the output is false.

    --- Example 3 ---
    Input: s = "abeabe", k = 0
    Output: true


    *** Constraints ***
    2 <= n == s.length <= 5 * 10^4
    0 <= k <= 26
    s consists only of lowercase English letters.

*/

#include <algorithm>
#include <climits>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.73% */
/* Space Beats: 86.48% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool maxSubstringLength(string s, int k)
    {
        const int N = s.size();

        vector<int> first(26, -1);
        vector<int>  last(26, -1);

        for (int i = 0; i < N; i++)
        {
            int chr = s[i] - 'a';

            if (first[chr] == -1)
                first[chr] = i;

            last[chr] = i;
        }

        vector<pair<int,int>> intervals;
        for (int i = 0; i < N; i++)
        {
            int chr = s[i] - 'a';

            if (i != first[chr])
                continue;

            int j = last[chr];
            for (int k = i; k <= j; k++)
                j = max(j, last[s[k] - 'a']);

            bool flag = true;
            for (int k = i; k <= j; k++)
            {
                if (first[s[k]-'a'] < i)
                {
                    flag = false;
                    break;
                }
            }

            if ( ! flag)
                continue;

            if (i == 0 && j == N - 1)
                continue;

            intervals.push_back({i, j});
        }

        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            return a.second < b.second;
        });


        int count = 0;
        int curr = -1;
        for (const auto &i : intervals)
        {
            const int& begin = i.first;
            const int& end   = i.second;

            if (begin > curr)
            {
                count++;
                curr = end;
            }
        }

        return count >= k;
    }
};
