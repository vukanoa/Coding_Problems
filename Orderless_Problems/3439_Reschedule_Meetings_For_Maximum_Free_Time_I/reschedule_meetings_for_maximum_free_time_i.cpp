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

*/

/* Time  Beats: 83.33% */
/* Space Beats: 58.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_1 {
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
            int last_to_move = min(i + k, N-1);
            int end_of_moving_part = startTime[i] + prefix_sum[last_to_move] - (i == 0 ? 0 : prefix_sum[i-1]);

            int first_fixed_position = (min(i + k + 1, N) == N ? eventTime : startTime[i + k + 1]);

            result = max(result, first_fixed_position - end_of_moving_part);
        }

        /* Backward */
        for (int i = N-1; i >= 0; i--)
        {
            int last_to_move = max(0, i - k);
            int end_of_moving_part = endTime[i] - postfix_sum[last_to_move] + (i == N-1 ? 0 : postfix_sum[i+1]);

            int first_fixed_position = (max(-1, i - k - 1) == -1 ? 0 : endTime[i - k - 1]);

            result = max(result, end_of_moving_part - first_fixed_position);
        }

        return result;
    }
};
