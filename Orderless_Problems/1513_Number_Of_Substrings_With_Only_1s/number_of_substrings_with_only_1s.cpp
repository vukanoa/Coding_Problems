/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    1513) Number of Substrings With Only 1s
    =======================================

    ============
    Description:
    ============

    Given a binary string s, return the number of substrings with all
    characters 1's.

    Since the answer may be too large, return it modulo 10^9 + 7.

    ===============================
    FUNCTION: int numSub(string s);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "0110111"
    Output: 9
    Explanation: There are 9 substring in total with only 1's characters.
    "1" -> 5 times.
    "11" -> 3 times.
    "111" -> 1 time.

    --- Example 2 ---
    Input: s = "101"
    Output: 2
    Explanation: Substring "1" is shown 2 times in s.

    --- Example 3 ---
    Input: s = "111111"
    Output: 21
    Explanation: Each substring contains only 1's characters.


    *** Constraints ***
    1 <= s.length <= 10^5
    s[i] is either '0' or '1'.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You needed to know only 2 basic things in order to solve this problem:

        1. If you have X amount of 1s, then the total number of substrings is:
            X * (X+1) / 2

        2. How to avoid Overflow and how to MOD properly.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numSub(string s)
    {
        const int N = s.length();
        const int MOD = 1e9 + 7;

        int result = 0;

        int L = 0;
        int R = 0;
        while (R < N)
        {
            while (R < N && s[R] == '1')
                R++;

            int ones = R - L; // Consecutive ones
            unsigned long long new_substrings = (1ULL * ones * (ones + 1) / 2) % MOD;

            result = (result + new_substrings) % MOD;

            if (L == R)
            {
                L++;
                R++;
            }
            else
            {
                L = R;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is another neat-trick you should know when it comes to counting the
    number of substrings of "consecutive groups".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int numSub(string s)
    {
        const int N = s.length();
        const int MOD = 1e9 + 7;

        unsigned long long result = 0;
        unsigned long long consecutive_ones = 0;

        for (const char& chr : s)
        {
            if (chr == '0')
                consecutive_ones = 0; // Reset
            else
                result += ++consecutive_ones;
        }

        return result % MOD;
    }
};
