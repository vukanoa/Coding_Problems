/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3440) Reschedule Meetings for Maximum Free Time II
    ==================================================

    ============
    Description:
    ============

    You are given an integer eventTime denoting the duration of an event. You
    are also given two integer arrays startTime and endTime, each of length n.

    These represent the start and end times of n non-overlapping meetings that
    occur during the event between time t = 0 and time t = eventTime, where the
    ith meeting occurs during the time [startTime[i], endTime[i]].

    You can reschedule at most one meeting by moving its start time while
    maintaining the same duration, such that the meetings remain
    non-overlapping, to maximize the longest continuous period of free time
    during the event.

    Return the maximum amount of free time possible after rearranging the
    meetings.

    Note that the meetings can not be rescheduled to a time outside the event
    and they should remain non-overlapping.

    =====
    Note: In this version, it is valid for the relative ordering of the meetings
          to change after rescheduling one meeting.
    =====

    =======================================================================================
    FUNCTION: int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime);
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
    Output: 2
    Explanation: Reschedule the meeting at [1, 2] to [2, 3], leaving no
                 meetings during the time [0, 2].

    --- Example 2 ---
    Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
    Output: 7
    Explanation: Reschedule the meeting at [0, 1] to [8, 9], leaving no
                 meetings during the time [0, 7].

    --- Example 3 ---
    Input: eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
    Output: 6
    Explanation: Reschedule the meeting at [3, 4] to [8, 9], leaving no
                 meetings during the time [1, 7].

    --- Example 4 ---
    Input: eventTime = 5, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
    Output: 0
    Explanation:
    There is no time during the event not occupied by meetings.


    *** Constraints ***
    1 <= eventTime <= 10^9
    n == startTime.length == endTime.length
    2 <= n <= 10^5
    0 <= startTime[i] < endTime[i] <= eventTime
    endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.71% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime)
    {
        const int N = startTime.size();
        int result = 0;

        /* Holes */
        int big   = INT_MIN;
        int mid   = INT_MIN;
        int small = INT_MIN;

        // Leftmost hole
        if (startTime[0] > 0)
            big = startTime[0]; // Since this is certainly the biggest so far

        for (int i = 0; i < N; i++)
        {
            int diff = difference_between(endTime[i], (i+1 == N ? eventTime : startTime[i+1]));

            if (diff == 0) // If there is NOT a hole to the right of endTime[i]
                continue;

            if (diff > big)
            {
                small = mid;
                mid = big;
                big = diff;
            }
            else if (diff > mid)
            {
                small = mid;
                mid = diff;
            }
            else if (diff > small)
            {
                small = diff;
            }
        }

        for (int i = 0; i < N; i++)
        {
            int L_hole = startTime[i] - (i == 0 ? 0 : endTime[i-1]);
            int R_hole = (i+1 == N ? eventTime : startTime[i+1]) - endTime[i];

            // You can always "slide" current block to the left or to the right
            result = max(result, L_hole + R_hole);

            int prev_big   = -1;
            int prev_mid   = -1;
            int prev_small = -1;

            /* Left Hole */
            if (L_hole == big)
            {
                prev_big = big;
                big = INT_MIN;
            }
            else if (L_hole == mid)
            {
                prev_mid = mid;
                mid = INT_MIN;
            }
            else if (L_hole == small)
            {
                prev_small = small;
                small = INT_MIN;
            }

            /* Right Hole */
            if (R_hole == big)
            {
                prev_big = big;
                big = INT_MIN;
            }
            else if (R_hole == mid)
            {
                prev_mid = mid;
                mid = INT_MIN;
            }
            else if (R_hole == small)
            {
                prev_small = small;
                small = INT_MIN;
            }


            int duration = difference_between(startTime[i], endTime[i]);

            if (big >= duration || mid >= duration || small >= duration)
                result = max(result, L_hole + duration + R_hole);

            if (prev_big != -1)
                big = prev_big;

            if (prev_mid != -1)
                mid = prev_mid;

            if (prev_small != -1)
                small = prev_small;
        }

        return result;
    }

private:
    int difference_between(int& left_position, int& right_position)
    {
        return right_position - left_position;
    }
};
