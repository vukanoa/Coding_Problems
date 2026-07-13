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

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is the most FUNDAMENTAL "Digit DP" problem.

    If you don't understand this code, make sure to understand the basics of
    the "Digit DP" first, then come back to read it again.

    Prerequisite knowledge is that you're VERY good with "Memoization"
    technique, i.e. "Top-Down Dynamic Programming".

    Once you're comfortable with that, come back here and this'll be a breeze.
    It's not that bad.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  28.02% */

/* Time  Complexity: O(D * 2 * sum) --> O(logN * 2 * (logN * 9)) --> O(log(n)^2) */ // D is the number of digits in the largest numbers
/* Time  Complexity: O(D * 2 * sum) --> O(logN * 2 * (logN * 9)) --> O(log(n)^2) */ // "sum" is the maximal sum, which is: D * 9, i.e. logN * 9.
class Solution_Digit_DP {
private:
    int memo[10][2][10];

public:
    int countDigitOne(int n)
    {
        string str_num = to_string(n);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(str_num, 0, 1, 0);
    }

private:
    int solve(string& str_num, int idx, int tight, int count_of_ones)
    {
        const int N = str_num.size();

        if (idx == N)
            return count_of_ones;

        if (memo[idx][tight][count_of_ones] != -1)
            return memo[idx][tight][count_of_ones];

        int limit_digit = tight ? str_num[idx] - '0' : 9;

        int result = 0;
        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int next_tight            = tight && (curr_digit == limit_digit);
            int updated_count_of_ones = count_of_ones + (curr_digit == 1);

            result += solve(str_num, idx+1, next_tight, updated_count_of_ones);
        }

        return memo[idx][tight][count_of_ones] = result;
    }
};
