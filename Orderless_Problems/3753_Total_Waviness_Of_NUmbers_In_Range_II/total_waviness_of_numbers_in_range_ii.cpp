/*
    ============
    === HARD ===
    ============

    ===========================================
    3753) Total Waviness of Numbers in Range II
    ===========================================

    ============
    Description:
    ============

    You are given two integers num1 and num2 representing an inclusive range
    [num1, num2].

    The waviness of a number is defined as the total count of its peaks and
    valleys:

        + A digit is a peak if it is strictly greater than both of its
          immediate neighbors.

        + A digit is a valley if it is strictly less than both of its immediate
          neighbors.

        + The first and last digits of a number cannot be peaks or valleys.

        + Any number with fewer than 3 digits has a waviness of 0.

    Return the total sum of waviness for all numbers in the range [num1, num2]. 

    ==================================================================
    FUNCTION: long long totalWaviness(long long num1, long long num2);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num1 = 120, num2 = 130
    Output: 3
    Explanation:
    In the range [120, 130]:
        120: middle digit 2 is a peak, waviness = 1.
        121: middle digit 2 is a peak, waviness = 1.
        130: middle digit 3 is a peak, waviness = 1.
        All other numbers in the range have a waviness of 0.
    Thus, total waviness is 1 + 1 + 1 = 3.

    --- Example 2 ---
    Input: num1 = 198, num2 = 202
    Output: 3
    Explanation:
    In the range [198, 202]:
        198: middle digit 9 is a peak, waviness = 1.
        201: middle digit 0 is a valley, waviness = 1.
        202: middle digit 0 is a valley, waviness = 1.
        All other numbers in the range have a waviness of 0.
    Thus, total waviness is 1 + 1 + 1 = 3.

    --- Example 3 ---
    Input: num1 = 4848, num2 = 4848
    Output: 2
    Explanation:
    Number 4848: the second digit 8 is a peak, and the third digit 4 is a
                 valley, giving a waviness of 2.


    *** Constraints ***
    1 <= num1 <= num2 <= 10^15

*/

#include <cstring>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Digit DP)

*/

/* Time  Beats: 72.88% */
/* Space Beats: 90.68% */

/* Time  Complexity: O(16 * 2 * 2 * 11 * 11 * 10) */
/* Space Complexity: O(16 * 2 * 2 * 11 * 11)      */
class Solution {
public:
    struct Node {
        long long waviness;
        long long count;
    };

    string s;

    Node    memo[17][2][2][11][11];
    bool visited[17][2][2][11][11];
    long long totalWaviness(long long num1, long long num2)
    {
        return solve(num2) - solve(num1 - 1);
    }

private:
    /*
        tight   = Are we still equal to N's prefix?
        started = Have we started building a number yet?

        prev_2  = 2nd digit to the left of the current one
        prev_1  = 1st digit to the left of the current one
    */
    Node dfs(int idx, int tight, int started, int prev2, int prev1)
    {
        // Base case: we have processed all digits
        if (idx == s.size())
            return {0, 1};

        if (visited[idx][tight][started][prev2][prev1])
            return memo[idx][tight][started][prev2][prev1];

        visited[idx][tight][started][prev2][prev1] = true;

        long long total_waviness = 0;
        long long total_count    = 0;

        // If tight=1 then limit will be digit at the idx else limit can be 9
        int limit = tight ? s[idx] - '0' : 9;

        for (int d = 0; d <= limit; d++) // d <==> digit
        {
            // If we were tight and we chose max allowed digit then we remain
            // tight
            int next_tight = tight && (d == limit);

            if ( ! started && d == 0) // Skipping leading zeroes
            {
                Node child = dfs(idx + 1, next_tight, 0, 10, 10);

                total_waviness += child.waviness;
                total_count    += child.count;
            }
            else // Non-leading zero case
            {
                int prev_2;
                int prev_1;
                long long add = 0;

                if ( ! started)
                {
                    prev_2 = 10;
                    prev_1 = d;
                }
                else
                {
                    if (prev2 != 10) // Checking peak or valley
                    {
                        bool peak   = (prev1 > prev2 && prev1 > d);
                        bool valley = (prev1 < prev2 && prev1 < d);

                        if (peak || valley)
                            add = 1;
                    }

                    prev_2 = prev1;
                    prev_1 = d;
                }

                Node child = dfs(idx + 1, next_tight, 1, prev_2, prev_1);

                total_waviness += child.waviness + add * child.count;
                total_count    += child.count;
            }
        }

        return memo[idx][tight][started][prev2][prev1] = {total_waviness, total_count};
    }

    long long solve(long long n)
    {
        if (n <= 0)
            return 0;

        s = to_string(n);

        /* Memset */
        memset(visited, 0, sizeof(visited));

        return dfs(0, 1, 0, 10, 10).waviness;
    }
};
