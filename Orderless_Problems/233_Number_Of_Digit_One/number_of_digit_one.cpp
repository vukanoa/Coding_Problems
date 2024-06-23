#include <iostream>

/*
    ============
    === HARD ===
    ============

    ===========================
    233) Number of Digit One
    ===========================

    ============
    Description:
    ============

    Given an integer n, count the total number of digit 1 appearing in all
    non-negative integers less than or equal to n.

    ===================================
    FUNCTION: int countDigitOne(int n); 
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13
    Output: 6

    --- Example 2 ---
    Input: n = 0
    Output: 0


    *** Constraints ***
    0 <= n <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.04% */
/* Space Beats: 52.44% */

/* Time  Complexity: O(len(n)^2) */ // 'len(n)' is the number of digits in n
/* Space Complexity: O(len(n)^2) */ // 'len(n)' is the number of digits in n
class Solution_Memoization {
public:
    int dp[11][11][2];

    int countDigitOne(int n)
    {
        string s = to_string(n);
        memset(dp, -1, sizeof dp);

        return dfs(s, 0, 0, true);
    }

private:
    int dfs(string &s, int idx, int cnt, bool flag)
    {
        if(idx == s.size())
            return cnt;

        if (dp[idx][cnt][flag] != -1)
            return dp[idx][cnt][flag];

        char upper_bound = '9'; // upper bound of position i

        if (flag)
            upper_bound = s[idx];

        int count = 0;
        for(char x = '0'; x <= upper_bound; x++)
        {
            bool new_flag = flag & (x == upper_bound);
            int  new_cnt  = cnt;

            if(x == '1')
                new_cnt++;

            count += dfs(s, idx+1, new_cnt, new_flag);
        }

        return dp[idx][cnt][flag] = count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Go through the digit positions one at a time, find out how often a "1"
    appears at each position, and sum those up. 

*/

/* Time  Beats: 100%   */
/* Space Beats: 99.90% */

/* Time  Complexity: O(log10(n)) */
/* Space Complexity: O(1)        */
class Solution_Efficient {
public:
    int countDigitOne(int n)
    {
        int ones = 0;

        for (long long m = 1; m <= n; m *= 10)
            ones += (n/m + 8) / 10 * m + (n/m % 10 == 1) * (n % m + 1);

        return ones;
    }
};
