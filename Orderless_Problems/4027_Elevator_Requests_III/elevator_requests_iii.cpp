/*
    ============
    === HARD ===
    ============

    ===========================
    4027) Elevator Requests III
    ===========================

    ============
    Description:
    ============

    You are given an integer n denoting the number of floors in a building,
    where the floors are numbered from 0 to n - 1.

    You are also given an integer start and a 2D integer array requests, where
    requests[i] = [arrivali, floori] indicates that a request for floori is
    made at time arrivali.

    At time 0, the elevator is at floor start.

    At each second, the elevator may move up by 1 floor, move down by 1 floor,
    or remain on its current floor.

    A request can be fulfilled only at or after its arrival time; it is
    fulfilled instantly when the elevator is on its requested floor at any time
    from its arrival time onward.

    Return the minimum time needed to fulfill all requests.

    ======================================================================================
    FUNCTION: long long elevatorRequests(int n, int start, vector<vector<int>>& requests);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 9, start = 0, requests = [[0,8],[6,5]]
    Output: 9
    Explanation:
        + Move from floor 0 (start) to floor 5 (requests[1][1]) in 5 seconds,
          reaching at time 5. Since requests[1][0] = 6, wait until time 6 to
          fulfill it.

        + Move from floor 5 to floor 8 (requests[0][1]) in 3 seconds,
          fulfilling it at time 9.

    Thus, all requests are fulfilled by time 9.


    --- Example 2 ---
    Input: n = 8, start = 5, requests = [[1,7],[7,3]]
    Output: 7
    Explanation:
        + Move from floor 5 (start) to floor 7 (requests[0][1]) in 2 seconds,
          reaching at time 2. Since requests[0][0] = 1 has already passed,
          floor 7 is fulfilled at time 2.

        + Move from floor 7 to floor 3 (requests[1][1]) in 4 seconds, reaching
          at time 6. Since requests[1][0] = 7, wait until time 7.

    Thus, all requests are fulfilled by time 7.


    --- Example 3 ---
    Input: n = 7, start = 3, requests = [[0,5],[0,1],[6,3]]
    Output: 8
    Explanation:
        + Move from floor 3 (start) to floor 5 (requests[0][1]) in 2 seconds,
          fulfilling it at time 2.

        + Move from floor 5 to floor 1 (requests[1][1]) in 4 seconds,
          fulfilling it at time 6.

        + Move from floor 1 to floor 3 (requests[2][1]) in 2 seconds, reaching
          at time 8. Its request arrived at requests[2][0] = 6, so floor 3 is
          fulfilled at time 8.

    Thus, all requests are fulfilled by time 8.


    *** Constraints ***
    1 <= n <= 10^9
    1 <= requests.length <= 16
    requests[i] == [arrivali, floori]
    0 <= arrivali <= 109
    0 <= start, floori <= n - 1

*/

#include <climits>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 22.94% */
/* Space Beats: 95.91% */

/* Time  Complexity: O(2^M * M^2) */
/* Space Complexity: O(2^M * M^2) */
class Solution_Top_Down__Memoization {
private:
    long long memo[1 << 16][16];

public:
    long long elevatorRequests(int n, int start, vector<vector<int>>& requests)
    {
        const int M = requests.size();
        const int FULL_MASK = (1 << M) - 1;

        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        long long result = LLONG_MAX;

        for (int last = 0; last < M; last++)
            result = min(result, solve(FULL_MASK, last, start, requests));

        return result;
    }

private:
    long long solve(int mask, int last, int start, vector<vector<int>>& requests)
    {
        const int M = requests.size();

        if (memo[mask][last] != -1)
            return memo[mask][last];

        long long result = LLONG_MAX;

        if (mask == (1 << last))
        {
            long long travel = llabs(1LL * start - requests[last][1]);

            return memo[mask][last] = max(travel, 1LL * requests[last][0]);
        }

        int prev_mask = mask ^ (1 << last);
        for (int prev = 0; prev < M; prev++)
        {
            if ( ! (prev_mask & (1 << prev)))
                continue;

            long long prev_time = solve(prev_mask, prev, start, requests);
            long long distance  = llabs(1LL * requests[prev][1] - requests[last][1]);

            long long arrival = max(prev_time + distance, 1LL * requests[last][0]);
            result = min(result, arrival);
        }

        return memo[mask][last] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but written in a Bottom-Up, i.e. "Tabulation" way.

*/

/* Time  Beats: 69.58% */
/* Space Beats: 30.48% */

/* Time  Complexity: O(M^2 * 2^M) */
/* Space Complexity: O(M   * 2^M) */
class Solution_Bottom_Up__Tabulation {
public:
    long long elevatorRequests(int n, int start, vector<vector<int>>& requests)
    {
        const int M = requests.size();
        const int FULL_MASK = (1 << M) - 1;

        long long result = LLONG_MAX;

        vector<vector<long long>> dp(1 << M, vector<long long>(M, LLONG_MAX));

        for (int i = 0; i < M; i++)
        {
            long long arrival = requests[i][0];
            long long floor   = requests[i][1];

            long long travel = llabs(1LL * start - floor);

            dp[1 << i][i] = max(travel, arrival);
        }

        for (int mask = 1; mask < (1 << M); mask++)
        {
            for (int i = 0; i < M; i++)
            {
                if ( ! (mask & (1 << i)))
                    continue;

                if (dp[mask][i] == LLONG_MAX)
                    continue;

                for (int j = 0; j < M; j++)
                {
                    if (mask & (1 << j))
                        continue;

                    long long distance   = llabs(1LL * requests[i][1] - requests[j][1]);
                    long long reach_time = dp[mask][i] + distance;

                    long long new_time = max(reach_time, 1LL * requests[j][0]);

                    int new_mask = mask | (1 << j);

                    dp[new_mask][j] = min(dp[new_mask][j], new_time);
                }
            }
        }

        for (int i = 0; i < M; i++)
            result = min(result, dp[FULL_MASK][i]);

        return result;
    }
};
