/*
    ============
    === HARD ===
    ============

    ==================================================
    1520) Maximum Number of Non-Overlapping Substrings
    ==================================================

    ============
    Description:
    ============

    Given a string s of lowercase letters, you need to find the maximum number
    of non-empty substrings of s that meet the following conditions:

        1. The substrings do not overlap, that is for any two substrings
           s[i..j] and s[x..y], either j < x or i > y is true.

        2. A substring that contains a certain character c must also contain
           all occurrences of c.

    Find the maximum number of substrings that meet the above conditions. If
    there are multiple solutions with the same number of substrings, return the
    one with minimum total length. It can be shown that there exists a unique
    solution of minimum total length.

    Notice that you can return the substrings in any order.

    ======================================================
    FUNCTION: vector<string> maxNumOfSubstrings(string s);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "adefaddaccc"
    Output: ["e","f","ccc"]
    Explanation: The following are all the possible substrings that meet the conditions:
    [
      "adefaddaccc"
      "adefadda",
      "ef",
      "e",
      "f",
      "ccc",
    ]
    If we choose the first string, we cannot choose anything else and we'd get
    only 1. If we choose "adefadda", we are left with "ccc" which is the only
    one that doesn't overlap, thus obtaining 2 substrings. Notice also, that
    it's not optimal to choose "ef" since it can be split into two. Therefore,
    the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings.
    No other solution of the same number of substrings exist.


    --- Example 2 ---
    Input: s = "abbaccd"
    Output: ["d","bb","cc"]
    Explanation: Notice that while the set of substrings ["d","abba","cc"] also
                 has length 3, it's considered incorrect since it has larger
                 total length.



    *** Constraints ***
    1 <= s.length <= 10^5
    s contains only lowercase English letters.

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

/* Time  Beats: 96.02% */
/* Space Beats: 71.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<string> maxNumOfSubstrings(string s)
    {
        const int N = s.size();

        int start_idx[26];
        int end_idx  [26];

        fill(start_idx, start_idx + 26, -1);
        fill(end_idx  , end_idx   + 26, -1);

        for (int i = 0; i < N; i++)
        {
            const char& chr = s[i];

            if (start_idx[chr - 'a'] == -1)
                start_idx[chr - 'a'] = i;

            end_idx[chr - 'a'] = i;
        }

        vector<tuple<int,int,char,int>> intervals;

        for (int i = 0; i < 26; i++)
        {
            if (start_idx[i] == -1)
                continue;

            int start = start_idx[i];
            int end   = end_idx[i];

            bool valid = true;

            for (int j = start; j <= end; j++)
            {
                const int chr_idx = s[j] - 'a';

                if (start_idx[chr_idx] < start)
                {
                    valid = false;
                    break;
                }

                end = max(end, end_idx[chr_idx]);
            }

            if (valid)
            {
                intervals.push_back( {start,
                                      end,
                                      static_cast<char>(i + 'a'),
                                      end - start + 1});
            }
        }

        /* Sort in ASCENDING order by END!! */
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            return get<1>(a) < get<1>(b);
        });

        vector<string> result;
        int prev_end = -1;

        for (const auto& [start, end, chr, len] : intervals)
        {
            if (prev_end < start)
            {
                result.push_back(s.substr(start, len));
                prev_end = end;
            }
        }

        return result;
    }
};
