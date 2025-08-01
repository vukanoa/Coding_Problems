/*
    ============
    === HARD ===
    ============

    ======================================================
    1751) Maximum Number of Events That Can Be Attended II
    ======================================================

    ============
    Description:
    ============

    You are given an array of events where

        events[i] = [startDayi, endDayi, valuei].

    The ith event starts at startDayi and ends at endDayi, and if you attend
    this event, you will receive a value of valuei. You are also given an
    integer k which represents the maximum number of events you can attend.

    You can only attend one event at a time. If you choose to attend an event,
    you must attend the entire event. Note that the end day is inclusive: that
    is, you cannot attend two events where one of them starts and the other
    ends on the same day.

    Return the maximum sum of values that you can receive by attending events.

    ===========================================================
    FUNCTION: int maxValue(vector<vector<int>>& events, int k);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
    Output: 7
    Explanation: Choose the green events, 0 and 1 (0-indexed) for a total
                 value of 4 + 3 = 7.

    --- Example 2 ---
    Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
    Output: 10
    Explanation: Choose event 2 for a total value of 10.
    Notice that you cannot attend any other event as they overlap, and that you
    do not have to attend k events.

    --- Example 3 ---
    Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
    Output: 9
    Explanation: Although the events do not overlap, you can only attend 3
                 events. Pick the highest valued three.


    *** Constraints ***
    1 <= k <= events.length
    1 <= k * events.length <= 10^6
    1 <= startDayi <= endDayi <= 10^9
    1 <= valuei <= 10^6

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Skip-Take Memoization.

*/

/* Time  Beats: 58.38% */
/* Space Beats:  8.82% */

/* Time  Complexity: O(k * N * logN) */
/* Space Complexity: O(k * N)        */
class Solution_Memoization {
private:
    vector<vector<int>> memo;
    int N;

    static bool compare_events(const vector<int>& event_a, const vector<int>& event_b)
    {
        return event_a[0] < event_b[0]; // ASCENDING by 0th element, i.e. "start"
    }

    static bool compare_target_with_start_day(int target_day, const vector<int>& event)
    {
        return target_day < event[0];
    }

public:
    int maxValue(vector<vector<int>>& events, int k)
    {
        N = events.size();

        /* Sort in ASCENDING by start_day */
        sort(events.begin(), events.end(), compare_events);

        // Allocate and initialize "memo"
        memo = vector<vector<int>>(k + 1, vector<int>(N, -1));

        return solve(0, k, events);
    }

private:
    int solve(int curr_idx, int remaining_count, const vector<vector<int>>& events)
    {
        if (curr_idx == N || remaining_count == 0)
            return 0;

        if (memo[remaining_count][curr_idx] != -1)
            return memo[remaining_count][curr_idx];

        /* Reference Aliasing */
        const int& start_day  = events[curr_idx][0];
        const int& end_day    = events[curr_idx][1];
        const int& curr_value = events[curr_idx][2];

        /* Binary Search */
        int target = end_day;
        auto iter  = upper_bound(events.begin(), events.end(), target, compare_target_with_start_day);

        // Leftmost index of an event that has a start_day STRICTLY GREATER than "target"(i.e. current end_day)
        int next_valid_event_idx = distance(events.begin(), iter);

        /* Classic Skip-Take Memoization */
        int skip =     0      + solve(curr_idx + 1        , remaining_count    , events);
        int take = curr_value + solve(next_valid_event_idx, remaining_count - 1, events);


        return memo[remaining_count][curr_idx] = max(skip, take);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    In terms of Big O notation it has the same Time and Space Complexities as
    the two Solutions above, however this one practically runs faster,
    especially on bigger Inputs.

*/

/* Time  Beats: 96.19% */
/* Space Beats:  8.57% */

/* Time  Complexity: O(k * N * logN) */
/* Space Complexity: O(k * N)        */
class Solution_Memoization_Plus_Cached_Binary_Search {
private:
    vector<vector<int>> memo;
    vector<int> next_non_overlapping_event_idx_after;
    int N;

    static bool compare_events(const vector<int>& event_a, const vector<int>& event_b)
    {
        return event_a[0] < event_b[0]; // ASCENDING by 0th element, i.e. "start"
    }

    static bool compare_target_with_start_day(int target_day, const vector<int>& event)
    {
        return target_day < event[0];
    }

public:
    int maxValue(vector<vector<int>>& events, int k)
    {
        N = events.size();

        /* Sort in ASCENDING by start_day */
        sort(events.begin(), events.end(), compare_events);

        // Precompute "next valid event idx" for each event
        next_non_overlapping_event_idx_after.resize(N);
        for (int event_idx = 0; event_idx < N; event_idx++)
        {
            int target_day = events[event_idx][1];
            auto iter = upper_bound(events.begin(), events.end(), target_day, compare_target_with_start_day);

            next_non_overlapping_event_idx_after[event_idx] = distance(events.begin(), iter);
        }

        memo = vector<vector<int>>(k + 1, vector<int>(N, -1));

        return solve(0, k, events);
    }

private:
    int solve(int curr_idx, int remaining_count, const vector<vector<int>>& events)
    {
        if (curr_idx == N || remaining_count == 0)
            return 0;

        if (memo[remaining_count][curr_idx] != -1)
            return memo[remaining_count][curr_idx];

        /* Reference Aliasing */
        const int& start_day  = events[curr_idx][0];
        const int& end_day    = events[curr_idx][1];
        const int& curr_value = events[curr_idx][2];

        int skip =          0 + solve(curr_idx + 1                                  , remaining_count    , events);
        int take = curr_value + solve(next_non_overlapping_event_idx_after[curr_idx], remaining_count - 1, events);

        return memo[remaining_count][curr_idx] = max(skip, take);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Bottom-up implementation. It's very beneficial to know both since sometimes
    Memoization is too costly because of the Stack-call.

    However, to me Memoizaiton i much more straightforward for writing,
    therefore it's good to know how to convert your Memoization Solution to a
    Bottom-Up Dynamic Programming one.

*/

/* Time  Beats: 8.73% */
/* Space Beats: 9.68% */

/* Time  Complexity: O(k * N * logN) */
/* Space Complexity: O(k * N) */
class Solution_Bottom_Up {
private:
    static bool compare_events(const vector<int>& event_a, const vector<int>& event_b)
    {
        return event_a[0] < event_b[0]; // ASCENDING by 0th element, i.e. "start"
    }

    static bool compare_target_with_start_day(int target_day, const vector<int>& event)
    {
        return target_day < event[0];
    }

public:
    int maxValue(vector<vector<int>>& events, int k)
    {
        const int N = events.size();

        /* Sort in ASCENDING by start_day */
        sort(events.begin(), events.end(), compare_events);

        vector<vector<int>> dp(k + 1, vector<int>(N + 1, 0));

        for (int curr_idx = N-1; curr_idx >= 0; curr_idx--)
        {
            for (int remaining_count = 1; remaining_count <= k; remaining_count++)
            {
                /* Reference Aliasing */
                const int& start_day   = events[curr_idx][0];
                const int& end_day     = events[curr_idx][1];
                const int& event_value = events[curr_idx][2];

                /* Binary Search */
                auto iter                = upper_bound(events.begin(), events.end(), end_day, compare_target_with_start_day);
                int next_valid_event_idx = distance(events.begin(), iter);

                int skip =     0       + dp[remaining_count    ][curr_idx + 1        ];
                int take = event_value + dp[remaining_count - 1][next_valid_event_idx];

                dp[remaining_count][curr_idx] = max(skip, take);
            }
        }

        return dp[k][0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A small optimization that makes a huge difference in practice.

*/

/* Time  Beats: 91.92% */
/* Space Beats:  5.02% */

/* Time  Complexity: O(k * N * logN) */
/* Space Complexity: O(k * N)        */
class Solution_Bottom_Up_Plus_Cached_Binary_Search {
private:
    static bool compare_events(const vector<int>& event_a, const vector<int>& event_b)
    {
        return event_a[0] < event_b[0]; // Sort by start_day
    }

    static bool compare_target_with_start_day(int target_day, const vector<int>& event)
    {
        return target_day < event[0];
    }

public:
    int maxValue(vector<vector<int>>& events, int k)
    {
        const int N = events.size();

        /* Sort in ASCENDING by start_day */
        sort(events.begin(), events.end(), compare_events);

        vector<vector<int>> dp(k + 1, vector<int>(N + 1, 0));

        for (int curr_idx = N-1; curr_idx >= 0; curr_idx--)
        {
            /* Reference Aliasing */
            const int& start_day   = events[curr_idx][0];
            const int& end_day     = events[curr_idx][1];
            const int& event_value = events[curr_idx][2];

            int target_day = end_day;
            auto iter      = upper_bound(events.begin(), events.end(), target_day, compare_target_with_start_day);

            int next_valid_event_idx = distance(events.begin(), iter);

            for (int remaining_count = 1; remaining_count <= k; remaining_count++)
            {
                int skip =     0       + dp[remaining_count    ][curr_idx + 1   ];
                int take = event_value + dp[remaining_count - 1][next_valid_event_idx];

                dp[remaining_count][curr_idx] = max(skip, take);
            }
        }

        return dp[k][0];
    }
};
