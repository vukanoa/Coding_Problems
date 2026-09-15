/*
    ============
    === HARD ===
    ============

    =============================================================
    2472) Maximum Number of Non-Overlapping Palindrome Substrings 
    =============================================================

    ============
    Description:
    ============

    You are given a string s and a positive integer k.

    Select a set of non-overlapping substrings from the string s that satisfy
    the following conditions:

        + The length of each substring is at least k.
        + Each substring is a palindrome.

    Return the maximum number of substrings in an optimal selection.

    A substring is a contiguous sequence of characters within a string.

    =============================================
    FUNCTION: int maxPalindromes(string s, int k)
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abaccdbbd", k = 3
    Output: 2
    Explanation: We can select the substrings underlined in s = "abaccdbbd".
    Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
    It can be shown that we cannot find a selection with more than two valid
    substrings.

    --- Example 2 ---
    Input: s = "adbcda", k = 2
    Output: 0
    Explanation: There is no palindrome substring of length at least 2 in the
                 string.


    *** Constraints ***
    1 <= k <= s.length <= 2000
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

/* Time  Beats: 77.49% */
/* Space Beats: 73.56% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int maxPalindromes(string s, int k)
    {
        const int N = s.size();

        vector<pair<int,int>> intervals;

        /////////////////////////////////////////////////////////////////////////////
        /// Generate Intervals from each palindromic substring of length k or k+1 ///
        /////////////////////////////////////////////////////////////////////////////

        /* ODD length palindromes */
        for (int start = 0; start < N; start++)
        {
            int L = start;
            int R = start;

            bool found_palindrome_of_at_least_size_k = false;
            int substr_len;
            while (L >= 0 && R < N && s[L] == s[R])
            {
                substr_len = R - L + 1;

                if (substr_len >= k)
                {
                    found_palindrome_of_at_least_size_k = true;
                    break;
                }

                --L;
                ++R;
            }

            if (found_palindrome_of_at_least_size_k)
                intervals.push_back( {L, R} );
        }

        /* EVEN length palindromes */
        for (int start = 0; start < N-1; start++)
        {
            int L = start;
            int R = start + 1;

            bool found_palindrome_of_at_least_size_k = false;
            int substr_len;
            while (L >= 0 && R < N && s[L] == s[R])
            {
                substr_len = R - L + 1;

                if (substr_len >= k)
                {
                    found_palindrome_of_at_least_size_k = true;
                    break;
                }

                --L;
                ++R;
            }

            if (found_palindrome_of_at_least_size_k)
                intervals.push_back( {L, R} );
        }


        if (intervals.empty())
            return 0;


        /* Sort */
        sort(intervals.begin(), intervals.end());
        const int M = intervals.size();

        vector<int> dp(2005, 0);
        for (auto it = intervals.rbegin(); it != intervals.rend(); it++)
        {
            auto& [start, end] = *it;

            int target = end + 1;
            auto interval_after_end = lower_bound(intervals.begin(), intervals.end(), target, [](const auto& interval, int target){
                return interval.first < target;
            });

            target = start + 1;
            auto interval_after_start = lower_bound(intervals.begin(), intervals.end(), target, [](const auto& interval, int target){
                return interval.first < target;
            });

            int start_of_interval_after_end   = interval_after_end   == intervals.end() ? 2001 : interval_after_end->first;
            int start_of_interval_after_start = interval_after_start == intervals.end() ? 2001 : interval_after_start->first;

            dp[start] = max(dp[start_of_interval_after_end  ] + 1,   // Take
                            dp[start_of_interval_after_start]     ); // Skip
        }

        return dp[intervals.begin()->first];
    }
};
