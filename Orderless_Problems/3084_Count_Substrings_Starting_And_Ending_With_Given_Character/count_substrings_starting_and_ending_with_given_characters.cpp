/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================================
    3084) Count Substrings Starting and Ending with Given Character
    ===============================================================

    ============
    Description:
    ============

    You are given a string s and a character c. Return the total number of
    substrings of s that start and end with c.

    ======================================================
    FUNCTION: long long countSubstrings(string s, char c);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abada", c = "a"
    Output: 6
    Explanation: Substrings starting and ending with "a" are:
    "abada", "abada", "abada", "abada", "abada", "abada".

    --- Example 2 ---
    Input: s = "zzz", c = "z"
    Output: 6
    Explanation: There are a total of 6 substrings in s and all start and end
    with "z".


    *** Constraints ***
    1 <= s.length <= 10^5
    s and c consist only of lowercase English letters.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic "Counting Sliding Window" technique.

*/

/* Time  Beats: 27.71% */
/* Space Beats:  8.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long countSubstrings(string s, char c)
    {
        const int N = s.size();
        long long result = 0;

        int add = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == c)
            {
                add++;
                result += add;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's a famous "sum of the first N natural numbers".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  22.29% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    long long countSubstrings(string s, char c)
    {
        int count = 0;
        for (const char& chr : s)
        {
            if (chr == c)
                count++;
        }

        return 1LL * count * (count + 1) / 2;
    }
};
