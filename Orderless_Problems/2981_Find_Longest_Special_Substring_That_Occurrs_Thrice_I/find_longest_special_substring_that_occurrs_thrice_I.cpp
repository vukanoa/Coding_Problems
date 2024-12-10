#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2981) Find Longest Special Substring that Occurs Thrice I
    =========================================================

    ============
    Description:
    ============

    You are given a string s that consists of lowercase English letters.

    A string is called special if it is made up of only a single character. For
    example, the string "abc" is not special, whereas the strings "ddd", "zz",
    and "f" are special.

    Return the length of the longest special substring of s which occurs at
    least thrice, or -1 if no special substring occurs at least thrice.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ======================================
    FUNCTION: int maximumLength(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaaa"
    Output: 2
    Explanation: The longest special substring which occurs thrice is "aa":
                 substrings "aaaa", "aaaa", and "aaaa". It can be shown that
                 the maximum length achievable is 2.

    --- Example 2 ---
    Input: s = "abcdef"
    Output: -1
    Explanation: There exists no special substring which occurs at least
                 thrice. Hence return -1.


    --- Example 3 ---
    Input: s = "abcaba"
    Output: 1
    Explanation: The longest special substring which occurs thrice is "a":
                 substrings "abcaba", "abcaba", and "abcaba". It can be shown
                 that the maximum length achievable is 1.


    *** Constraints ***
    3 <= s.length <= 50
    s consists of only lowercase English letters.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.09% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int maximumLength(string s)
    {
        const int N = s.length();
        const int THRICE = 3;

        int result = -1;

        vector<int> subsequence_length(N, 1);

        int upper_bound = 1;
        for (int i = N-2; i >= 0; i--)
        {
            if (s[i] == s[i+1])
                subsequence_length[i] = 1 + subsequence_length[i+1];

            upper_bound = max(upper_bound, subsequence_length[i]);
        }

        int left  = 1;
        int right = upper_bound;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            int max_occurr = 0;
            vector<int> counter(26, 0);
            for (int i = 0; i < N; i++)
            {
                if (subsequence_length[i] >= mid)
                {
                    counter[s[i] - 'a']++;
                    max_occurr = max(max_occurr, counter[s[i] - 'a']);
                }
            }

            if (max_occurr >= THRICE)
            {
                result = max(result, mid);
                left = mid + 1;
            }
            else
                right = mid-1;
        }

        return result;
    }
};
