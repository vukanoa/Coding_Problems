/*
    ============
    === HARD ===
    ============

    ===============================
    4081) Prime Subset Selection II
    ===============================

    ============
    Description:
    ============

    You are given two integers n and s.

    Consider all prime  numbers less than or equal to n. Select a subset of
    these primes such that:

        + Each prime can be selected at most once.

        + The sum of the selected primes is as large as possible while
          remaining less than or equal to s.

        + Among subsets with the maximum sum, select one containing the fewest
          primes.

        + If multiple subsets remain tied, select the one whose elements,
          written in increasing order, form the array.

    Return an integer array containing the selected primes in increasing order.
    If no valid non-empty subset exists, return an empty array.

    ===================================================
    FUNCTION: vector<int> maxPrimeSubset(int n, int s);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 7, s = 20
    Output: [2, 3, 5, 7]
    Explanation:
        The prime numbers less than or equal to n = 7 are 2, 3, 5, and 7.
        The sum of all these primes is 2 + 3 + 5 + 7 = 17, which is less than or equal to s = 20.
        Thus, the answer is [2, 3, 5, 7].

    --- Example 2 ---
    Input: n = 15, s = 18
    Output: [5,13]
    Explanation:
        The prime numbers less than or equal to 15 are 2, 3, 5, 7, 11, and 13.
        The subsets with sum 18 are [5, 13], [7, 11], [2, 3, 13], and [2, 5, 11]. Since this sum equals s, it is the maximum possible sum.
        Among these subsets, [5, 13] and [7, 11] contain the fewest primes: two.
        Between these two subsets, [5, 13] is lexicographically smaller because its first element, 5, is smaller than 7. Thus, the answer is [5, 13].


    --- Example 3 ---
    Input: n = 5, s = 1
    Output: []
    Explanation:
        The smallest prime number is 2, which is greater than s = 1.
        Thus, no prime can be selected, so the answer is an empty array.

    *** Constraints ***
    1 <= n <= 1000
    1 <= s <= 1000

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Sieve + 2D Top-Down Memoization.

*/

/* Time  Beats: 47.71% */
/* Space Beats: 93.14% */

/* Time  Complexity: O(N * S  +  N * loglogN) */
/* Space Complexity: O(N * S)                 */
class Solution {
private:
    static constexpr int MAX_N   = 1000;
    static constexpr int MAX_SUM = 1000;
    static constexpr int INF = INT_MAX / 2;

    int max_sum_memo  [MAX_N + 1][MAX_SUM + 1];
    int min_count_memo[MAX_N + 1][MAX_SUM + 1];

public:
    vector<int> maxPrimeSubset(int n, int s)
    {
        /* Sieve of Eratosthenes */
        vector<bool> is_prime(n+1, true);
        is_prime[0] = false;
        is_prime[1] = false;

        for (int num = 2; num * num <= n; num++)
        {
            if ( ! is_prime[num])
                continue;

            for (int j = num * num; j <= n; j += num)
                is_prime[j] = false;
        }

        /* Get Primes */
        vector<int> primes;
        for (int num = 2; num <= n; num++)
        {
            if (is_prime[num])
                primes.push_back(num);
        }

        const int N = primes.size();

        /* Memset */
        memset(max_sum_memo,   0xff, sizeof(max_sum_memo));
        memset(min_count_memo, 0xff, sizeof(min_count_memo));

        /* Solve */
        int max_sum = solve_max_sum(0, 0, s, primes);
        if (max_sum == INT_MIN)
            return {};

        int min_count = solve_min_count(0, 0, max_sum, primes);
        if (min_count >= INF)
            return {};

        /* Build Result */
        vector<int> result;
        int curr_sum = 0;

        for (int idx = 0; idx < N && curr_sum <= max_sum; idx++)
        {
            int take = solve_min_count(idx+1, curr_sum + primes[idx], max_sum, primes);
            int skip = solve_min_count(idx+1, curr_sum              , max_sum, primes);

            if (curr_sum + primes[idx] <= max_sum &&
                take < INF                        &&
                1 + take == solve_min_count(idx, curr_sum, max_sum, primes))
            {
                result.push_back(primes[idx]);
                curr_sum += primes[idx];
            }
        }

        return result;
    }

private:
    int solve_max_sum(int idx, int curr_sum, int target, vector<int>& primes)
    {
        const int N = primes.size();

        if (curr_sum > target)
            return INT_MIN;

        if (idx == N)
            return curr_sum;

        if (max_sum_memo[idx][curr_sum] != -1)
            return max_sum_memo[idx][curr_sum];

        int take = solve_max_sum(idx+1, curr_sum + primes[idx], target, primes);
        int skip = solve_max_sum(idx+1, curr_sum              , target, primes);

        return max_sum_memo[idx][curr_sum] = max(take, skip);
    }

    int solve_min_count(int idx, int curr_sum, int target, vector<int>& primes)
    {
        const int N = primes.size();

        if (curr_sum > target)
            return INF;

        if (idx == N)
            return curr_sum == target ? 0 : INF;

        if (min_count_memo[idx][curr_sum] != -1)
            return min_count_memo[idx][curr_sum];

        int take = 1 + solve_min_count(idx+1, curr_sum + primes[idx], target, primes);
        int skip = 0 + solve_min_count(idx+1, curr_sum              , target, primes);

        return min_count_memo[idx][curr_sum] = min(take, skip);
    }
};
