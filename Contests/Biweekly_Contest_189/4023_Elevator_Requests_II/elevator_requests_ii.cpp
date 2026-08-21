/*
    ============
    === HARD ===
    ============

    ===========================
    4023) Elevator Requests II
    ===========================

    ============
    Description:
    ============

    You are given an integer n denoting the number of floors in a building,
    where the floors are numbered from 0 to n - 1.

    You are also given an integer start, representing the floor where the
    elevator begins, and an integer array requests, where requests[i] is a
    floor that the elevator is requested to reach. All floors in requests are
    distinct.

    At time 0, the elevator is on floor start, and all requests are made
    simultaneously.

    During each second before all requests are fulfilled, the elevator moves
    exactly one floor, either up or down. A request is fulfilled instantly when
    the elevator reaches its requested floor. If start appears in requests,
    that request is fulfilled at time 0.

    For each second that a request remains unfulfilled, you receive 1 penalty.
    Equivalently, a request fulfilled at time t contributes t to the total
    penalty.

    Return the minimum total penalty required to fulfill all requests.

    ==============================================================================
    FUNCTION: long long elevatorRequests(int n, int start, vector<int>& requests);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, start = 4, requests = [1,5]
    Output: 6
    Explanation:
        Move from floor 4 (start) to floor 5 in 1 second. Penalty for floor 5 is 1.
        Move from floor 5 to floor 1 in 4 seconds. Penalty for floor 1 is 5.
    Thus, the total penalty is 1 + 5 = 6.

    --- Example 2 ---
    Input: n = 8, start = 3, requests = [3,7,1]
    Output: 10
    Explanation:
        Floor 3 (start) is fulfilled instantly. Penalty for floor 3 is 0.
        Move from floor 3 to floor 1 in 2 seconds. Penalty for floor 1 is 2.
        Move from floor 1 to floor 7 in 6 seconds. Penalty for floor 7 is 8.
    Thus, the total penalty is 0 + 2 + 8 = 10.

    --- Example 3 ---
    Input: n = 10, start = 5, requests = [0,2,9]
    Output: 22
    Explanation:
        Move from floor 5 (start) to floor 2 in 3 seconds. Penalty for floor 2 is 3.
        Move from floor 2 to floor 0 in 2 seconds. Penalty for floor 0 is 5.
        Move from floor 0 to floor 9 in 9 seconds. Penalty for floor 9 is 14.
    Thus, the total penalty is 3 + 5 + 14 = 22.


    *** Constraints ***
    1 <= n <= 10^9
    1 <= requests.length <= 1500
    0 <= start, requests[i] <= n - 1
    All values in requests are distinct.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  5.00% */
/* Space Beats: 22.24% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
public:
    long long elevatorRequests(int n, int start, vector<int>& requests)
    {
        constexpr long long INF = 1e18;

        bool start_already_requested = false;
        for (const int& requested_floor : requests)
        {
            if (requested_floor == start)
            {
                start_already_requested = true;
                break;
            }
        }

        if ( ! start_already_requested)
            requests.push_back(start);

        /* Sort */
        sort(requests.begin(), requests.end());

        const int REQUEST_LEN = requests.size();
        int start_idx = lower_bound(requests.begin(), requests.end(), start) - requests.begin();

        vector<vector<vector<long long>>> dp(REQUEST_LEN, vector<vector<long long>>(REQUEST_LEN, vector<long long>(2, INF)));

        dp[start_idx][start_idx][0] = 0;
        dp[start_idx][start_idx][1] = 0;

        for (int range_len = 1; range_len < REQUEST_LEN; range_len++)
        {
            for (int L = 0; L + range_len - 1 < REQUEST_LEN; L++)
            {
                int R = L + range_len - 1;
                int remaining_requests = REQUEST_LEN - range_len;

                if (L > 0)
                {
                    dp[L-1][R][0] = min(dp[L-1][R][0],
                                        dp[L  ][R][0] + 1LL*(requests[L] - requests[L-1]) * remaining_requests);

                    dp[L-1][R][0] = min(dp[L-1][R][0],
                                        dp[L  ][R][1] + 1LL*(requests[R] - requests[L-1]) * remaining_requests);
                }

                if (R < REQUEST_LEN-1)
                {
                    dp[L][R+1][1] = min(dp[L][R+1][1],
                                        dp[L][R  ][0] + 1LL*(requests[R+1] - requests[L]) * remaining_requests);

                    dp[L][R+1][1] = min(dp[L][R+1][1],
                                        dp[L][R  ][1] + 1LL*(requests[R+1] - requests[R]) * remaining_requests);
                }
            }
        }

        return min(dp[0][REQUEST_LEN-1][0],
                   dp[0][REQUEST_LEN-1][1]);
    }
};
