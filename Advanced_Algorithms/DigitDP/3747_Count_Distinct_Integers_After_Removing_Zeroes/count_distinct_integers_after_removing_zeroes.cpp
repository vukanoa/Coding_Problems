/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3747) Count Distinct Integers After Removing Zeroes
    ===================================================

    ============
    Description:
    ============

    You are given a positive integer n.

    For every integer x from 1 to n, we write down the integer obtained by
    removing all zeros from the decimal representation of x.

    Return an integer denoting the number of distinct integers written down.

    ===============================================
    FUNCTION: long long countDistinct(long long n);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: 9
    Explanation:
    The integers we wrote down are 1, 2, 3, 4, 5, 6, 7, 8, 9, 1. There are 9
    distinct integers (1, 2, 3, 4, 5, 6, 7, 8, 9).

    --- Example 2 ---
    Input: n = 3
    Output: 3
    Explanation:
    The integers we wrote down are 1, 2, 3. There are 3 distinct integers (1,
    2, 3).


    *** Constraints ***
    1 <= n <= 10^15

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 15.51% */
/* Space Beats: 69.52% */

/* Time  Complexity: O(16 * 2 * 11) */
/* Space Complexity: O(16 * 2 * 11) */
class Solution {
private:
    // 16 --> because there are at most 16 digits in 10^15. N=10^15 --> log(N)=16
    //  2 --> because it's EITHER tight   or NOT tight
    // 11 --> because there are exactly 10 digits, which is always a CONSTANT!
    long long memo[16][2][11];

public:
    long long countDistinct(long long n)
    {
        return count_distinct_integers(n);
    }

private:
    long long count_distinct_integers(long long number)
    {
        string str_num = to_string(number);

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        return solve(str_num, 0, true, -1);
    }

    long long solve(string& str_num, int idx, int tight, int prev_digit)
    {
        const int N = str_num.size();

        if (idx == N)
            return prev_digit != -1 ? 1 : 0; // prev_digit != -1 --> Started 

        if (memo[idx][tight][prev_digit + 1] != -1)
            return memo[idx][tight][prev_digit + 1];


        int limit_digit = tight ? str_num[idx] - '0' : 9;

        long long result = 0LL;
        for (int curr_digit = 0; curr_digit <= limit_digit; curr_digit++)
        {
            int new_tight = tight && (curr_digit == limit_digit);

            if (curr_digit == 0)
            {
                if (prev_digit != -1) // Started
                    continue; // "remove this 0 from decimal"

                // Skip LEADING zero
                result += solve(str_num, idx + 1, new_tight, -1);
            }
            else // Take
            {
                result += solve(str_num, idx + 1, new_tight, curr_digit);
            }
        }

        return memo[idx][tight][prev_digit + 1] = result;
    }
};
