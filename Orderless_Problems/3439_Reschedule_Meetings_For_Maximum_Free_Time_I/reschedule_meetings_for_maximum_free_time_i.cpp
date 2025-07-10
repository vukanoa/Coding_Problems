/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    3439) Reschedule Meetings for Maximum Free Time I
    =================================================

    ============
    Description:
    ============

    You are given an integer eventTime denoting the duration of an event, where
    the event occurs from time t = 0 to time t = eventTime.

    You are also given two integer arrays startTime and endTime, each of length
    n. These represent the start and end time of n non-overlapping meetings,
    where the ith meeting occurs during the time [startTime[i], endTime[i]].

    You can reschedule at most k meetings by moving their start time while
    maintaining the same duration, to maximize the longest continuous period of
    free time during the event.

    The relative order of all the meetings should stay the same and they should
    remain non-overlapping.

    Return the maximum amount of free time possible after rearranging the
    meetings.

    =====
    Note: that the meetings can not be rescheduled to a time outside the event.
    =====

    ==============================================================================================
    FUNCTION: int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime);
    ==============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
    Output: 2
    Explanation: Reschedule the meeting at [1, 2] to [2, 3], leaving no
                 meetings during the time [0, 2].

    --- Example 2 ---
    Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
    Output: 6
    Explanation: Reschedule the meeting at [2, 4] to [1, 3], leaving no
                 meetings during the time [3, 9].

    --- Example 3 ---
    Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
    Output: 0
    Explanation:
    There is no time during the event not occupied by meetings.


    *** Constraints ***
    1 <= eventTime <= 10^9
    n == startTime.length == endTime.length
    2 <= n <= 10^5
    1 <= k <= n
    0 <= startTime[i] < endTime[i] <= eventTime
    endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Be aware of the fact that "idx" refers to indices of startTime and endTime.

    However, the term "position" refers to either:
        1) startTime[some_idx], or
        2) endTime[some_idx],   or
        3) 0, or
        4) eventTime


               0           1                 // These are indices of intervals
               |           |
               |           |
               v           v
           ________      _____
           |      |      |   |
    X------       -------    --------X
    ^      ^      ^      ^   ^       ^
    |      |      |      |   |       |
    0      2      4      6   7    eventTime   // These are POSITIONS(or points)

*/

/* Time  Beats: 83.33% */
/* Space Beats: 58.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime)
    {
        const int N = startTime.size();
        int result = 0;

        vector<int> prefix_sum (N, 0);
        vector<int> postfix_sum(N, 0);

        prefix_sum [0]   = endTime[0]   - startTime[0];
        postfix_sum[N-1] = endTime[N-1] - startTime[N-1];
        for (int i = 1; i < N; i++)
        {
            prefix_sum [i]       = prefix_sum [i-1]       + endTime[i]       - startTime[i];
            postfix_sum[N-1 - i] = postfix_sum[N-1 - i+1] + endTime[N-1 - i] - startTime[N-1 - i];
        }

        if (k == N) // Then it's eventTime - len_of_merged_all_intervals
        {
            result = max(result, eventTime - prefix_sum[N-1]);
            return result;
        }

        /* Forward */
        for (int i = 0; i < N; i++)
        {
            int idx_of_last_interval_to_move_to_the_left = min(i + k, N-1);
            int len_of_k_merged_intervals                = prefix_sum[idx_of_last_interval_to_move_to_the_left] - (i == 0 ? 0 : prefix_sum[i-1]);
            int last_position_of_k_merged_intervals      = startTime[i] + len_of_k_merged_intervals;

            int first_position_after_last_interval_to_move_to_the_left = (i + k+1 >= N ? eventTime : startTime[i + k+1]);

            /* Easier to read */
            int left_position  = last_position_of_k_merged_intervals;
            int right_position = first_position_after_last_interval_to_move_to_the_left;

            int diff = difference_between(left_position, right_position);

            result = max(result, diff);
        }

        /*
            Since down here we're going backwards, think of it like this:

                      (After)    (Before)
                       Last       First
                         |         |
                         |         |
                         v         v
                         0  1  2   3
            startTime = [0, 4, 7, 11]
              endTime = [2, 5, 9, 13]

            Examples:
                1) Before position 5 is a position 7
                2) After  position 4 is a position 2
                3) First  position is eventTime
                4) Last   position is 0
                5) First  position after position 11 is 9

        */
        /* Backward */
        for (int i = N-1; i >= 0; i--)
        {
            int idx_of_last_interval_to_move_to_the_right = max(0, i - k);
            int len_of_k_merged_intervals                 = postfix_sum[idx_of_last_interval_to_move_to_the_right] - (i+1 == N ? 0 : postfix_sum[i+1]);
            int last_position_of_k_merged_intervals       = endTime[i] - len_of_k_merged_intervals;

            int first_position_after_last_interval_to_move_to_the_right = ((i - k-1) <= -1 ? 0 : endTime[i - k-1]);

            /* Easier to read */
            int left_position  = first_position_after_last_interval_to_move_to_the_right;
            int right_position = last_position_of_k_merged_intervals;

            int diff = difference_between(left_position, right_position);

            result = max(result, difference_between(left_position, right_position));
        }

        return result;
    }

private:
    int difference_between(int& left_position, int& right_position)
    {
        return right_position - left_position;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Much more concise way of implementing it.

*/

/* Time  Beats: 32.46% */
/* Space Beats: 49.77% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Greedy_plus_Prefix_Sum {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime)
    {
        int N = startTime.size();
        int result = 0;

        vector<int> prefix_sum(N + 1);

        for (int i = 0; i < N; i++)
            prefix_sum[i + 1] = prefix_sum[i] + endTime[i] - startTime[i];

        for (int i = k - 1; i < N; i++)
        {
            int L = i == k - 1 ?     0     : endTime[i - k];
            int R = i == N - 1 ? eventTime : startTime[i + 1];

            result = max(result, R - L - (prefix_sum[i + 1] - prefix_sum[i - k + 1]));
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We do NOT have to use prefix_sum, instead we can only use a single variable
    named "curr_window_total_event_time" and thus optimize Space Complexity.

    Pretty standard technique for "Sliding Window".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy_plus_Sliding_Window {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime)
    {
        int N = startTime.size();
        int result = 0;
        int curr_window_total_event_time = 0;

        for (int i = 0; i < N; i++)
        {
            curr_window_total_event_time += endTime[i] - startTime[i];

            int L = i <= k - 1 ?     0     : endTime[i - k];
            int R = i == N - 1 ? eventTime : startTime[i + 1];

            result = max(result, R - L - curr_window_total_event_time);

            if (i >= k - 1)
                curr_window_total_event_time -= endTime[i - k + 1] - startTime[i - k + 1];
        }

        return result;
    }
};
