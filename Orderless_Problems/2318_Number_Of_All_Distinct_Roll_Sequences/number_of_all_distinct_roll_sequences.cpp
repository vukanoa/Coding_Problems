/*
    ============
    === HARD ===
    ============

    =======================================
    2318) Number of Distinct Roll Sequences
    =======================================

    ============
    Description:
    ============

    You are given an integer n. You roll a fair 6-sided dice n times. Determine
    the total number of distinct sequences of rolls possible such that the
    following conditions are satisfied:

        + The greatest common divisor of any adjacent values in the sequence is
          equal to 1.

        + There is at least a gap of 2 rolls between equal valued rolls. More
          formally, if the value of the ith roll is equal to the value of the
          jth roll, then abs(i - j) > 2.

    Return the total number of distinct sequences possible. Since the answer
    may be very large, return it modulo 109 + 7.

    Two sequences are considered distinct if at least one element is different.

    =======================================
    FUNCTION: int distinctSequences(int n);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: 184
    Explanation: Some of the possible sequences are (1, 2, 3, 4), (6, 1, 2, 3), (1, 2, 3, 1), etc.
    Some invalid sequences are (1, 2, 1, 3), (1, 2, 3, 6).
    (1, 2, 1, 3) is invalid since the first and third roll have an equal value and abs(1 - 3) = 2 (i and j are 1-indexed).
    (1, 2, 3, 6) is invalid since the greatest common divisor of 3 and 6 = 3.
    There are a total of 184 distinct sequences possible, so we return 184.

    --- Example 2 ---
    Input: n = 2
    Output: 22
    Explanation: Some of the possible sequences are (1, 2), (2, 1), (3, 2).
    Some invalid sequences are (3, 6), (2, 4) since the greatest common divisor is not equal to 1.
    There are a total of 22 distinct sequences possible, so we return 22.


    *** Constraints ***
    1 <= n <= 10^4

*/


#include <cstring>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 67.81% */
/* Space Beats: 58.54% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    const int MOD = 1e9 + 7;
    long long memo[7][7][10001];

public:
    int distinctSequences(int n)
    {
        if (n == 1)
            return 6;

        /* Memset, i.e. Allocate  */
        memset(memo, -1, sizeof(memo));

        vector<pair<int,int>> starts = {{1,2}, {1,3}, {1,4}, {1,5}, {1,6},
                                        {2,3}, {2,5},
                                        {3,4}, {3,5},
                                        {4,5},
                                        {5,6}};

        unordered_map<int, vector<int>> allowed_for_num;

        for (int a = 1; a <= 6; a++)
        {
            for (int b = 1; b <= 6; b++)
            {
                if (gcd(a, b) == 1)
                    allowed_for_num[a].push_back(b);
            }
        }

        long long result = 0LL;

        for (const auto& pair : starts)
        {
            result += solve(pair.first, pair.second, n - 2, allowed_for_num);
            result %= MOD;

            result += solve(pair.second, pair.first, n - 2, allowed_for_num);
            result %= MOD;
        }

        return static_cast<int>(result);
    }

private:
    int solve(int second_prev, int first_prev, int rolls_left, unordered_map<int, vector<int>>& allowed_for_num)
    {
        if (rolls_left == 0)
            return 1;

        if (memo[second_prev][first_prev][rolls_left] != -1)
            return memo[second_prev][first_prev][rolls_left];


        long long result = 0LL;
        for (const int& allowed : allowed_for_num[first_prev])
        {
            if (allowed == second_prev)
                continue;

            if (allowed == first_prev)
                continue;

            result += solve(first_prev, allowed, rolls_left - 1, allowed_for_num);
            result %= MOD;
        }

        return memo[second_prev][first_prev][rolls_left] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, implemented using Bottom-Up approach.
    This is VERY unintuitive to me. Memoization is so much easier to grasp.

*/

/* Time  Beats: 47.31% */
/* Space Beats:  5.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
private:
    const int MOD = 1e9 + 7;

public:
    int distinctSequences(int n)
    {
        if (n == 1)
            return 6;

        vector<vector<vector<long long>>> dp(7, vector<vector<long long>>(7, vector<long long>(10001, 0)));

        unordered_map<int, vector<int>> allowed_for_num;
        for (int a = 1; a <= 6; a++)
        {
            for (int b = 1; b <= 6; b++)
            {
                if (gcd(a, b) == 1)
                    allowed_for_num[a].push_back(b);
            }
        }

        vector<pair<int, int>> starts = {{1,2}, {1,3}, {1,4}, {1,5}, {1,6},
                                         {2,3}, {2,5},
                                         {3,4}, {3,5},
                                         {4,5},
                                         {5,6}};


        // Base case: with 0 rolls left, there's exactly 1 sequence
        for (int second_prev = 1; second_prev <= 6; second_prev++)
        {
            for (int first_prev = 1; first_prev <= 6; first_prev++)
            {
                dp[second_prev][first_prev][0] = 1;
            }
        }

        // Build DP Bottom-Up
        for (int rolls_left = 1; rolls_left <= n-2; rolls_left++)
        {
            for (int second_prev = 1; second_prev <= 6; second_prev++)
            {
                for (int first_prev = 1; first_prev <= 6; first_prev++)
                {
                    long long local_result = 0LL;

                    for (int allowed : allowed_for_num[first_prev])
                    {
                        if (allowed == second_prev)
                            continue;

                        if (allowed == first_prev)
                            continue;

                        local_result += dp[first_prev][allowed][rolls_left - 1];
                        local_result %= MOD;
                    }

                    dp[second_prev][first_prev][rolls_left] = local_result;
                }
            }
        }

        long long result = 0LL;
        for (const auto& pair : starts)
        {
            result += dp[pair.first][pair.second][n - 2];
            result %= MOD;

            result += dp[pair.second][pair.first][n - 2];
            result %= MOD;
        }

        return static_cast<int>(result);
    }
};
