#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ===========================
    2402) Meeting Rooms III
    ===========================

    ============
    Description:
    ============

    You are given an integer n. There are n rooms numbered from 0 to n - 1.

    You are given a 2D integer array meetings where meetings[i] = [starti,
    endi] means that a meeting will be held during the half-closed time
    interval [starti, endi). All the values of starti are unique.

    Meetings are allocated to rooms in the following manner:

        1. Each meeting will take place in the unused room with the lowest number.

        2. If there are no available rooms, the meeting will be delayed until a
           room becomes free. The delayed meeting should have the same duration
           as the original meeting.

        3. When a room becomes unused, meetings that have an earlier original
           start time should be given the room.

    Return the number of the room that held the most meetings. If there are
    multiple rooms, return the room with the lowest number.

    A half-closed interval [a, b) is the interval between a and b including a
    and not including b.

    ===============================================================
    FUNCTION: int mostBooked(int n, vector<vector<int>>& meetings);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
    Output: 0
    Explanation:
    - At time 0, both rooms are not being used. The first meeting starts in
      room 0.
    - At time 1, only room 1 is not being used. The second meeting starts in
      room 1.
    - At time 2, both rooms are being used. The third meeting is delayed.
    - At time 3, both rooms are being used. The fourth meeting is delayed.
    - At time 5, the meeting in room 1 finishes. The third meeting starts in
      room 1 for the time period [5,10).
    - At time 10, the meetings in both rooms finish. The fourth meeting starts
      in room 0 for the time period [10,11).
    Both rooms 0 and 1 held 2 meetings, so we return 0.


    --- Example 2 ---
    Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
    Output: 1
    Explanation:
    - At time 1, all three rooms are not being used. The first meeting starts
      in room 0.
    - At time 2, rooms 1 and 2 are not being used. The second meeting starts in
      room 1.
    - At time 3, only room 2 is not being used. The third meeting starts in
      room 2.
    - At time 4, all three rooms are being used. The fourth meeting is delayed.
    - At time 5, the meeting in room 2 finishes. The fourth meeting starts in
      room 2 for the time period [5,10).
    - At time 6, all three rooms are being used. The fifth meeting is delayed.
    - At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting
      starts in room 1 for the time period [10,12).

    Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we
    return 1.


    *** Constraints ***
    1 <= n <= 100
    1 <= meetings.length <= 10^5
    meetings[i].length == 2
    0 <= starti < endi <= 5 * 10^5
    All the values of starti are unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 67.55% */
/* Space Beats: 46.72% */

// N - number of rooms
// M - number of meetings

/* Time  Complexity: O(M + logM) */
/* Space Complexity: O(N + M)   */
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings)
    {
        vector<int> freq(n, 0);

        sort(meetings.begin(), meetings.end());

        // min_heap stores the current meetings going on with lowest end time at top
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> curr_meetings;

        // Mean Heap
        priority_queue<int, vector<int>, greater<int>> available_rooms;

        // Initially all rooms are available
        for (int i = 0; i < n; i++)
            available_rooms.push(i);

        int i = 0;

        while (i<meetings.size())
        {
            // Remove all meetings from the curr_meetings that are over when current meeting starts
            while ( ! curr_meetings.empty() && curr_meetings.top().first <= meetings[i][0])
            {
                available_rooms.push(curr_meetings.top().second);
                freq[curr_meetings.top().second]++;
                curr_meetings.pop();
            }

            // If all rooms full, delay the current meeting and add it
            if (curr_meetings.size() == n)
            {
                long long end_time = curr_meetings.top().first;
                long long room = curr_meetings.top().second;

                curr_meetings.pop();
                freq[room]++;
                curr_meetings.push({end_time-meetings[i][0]+meetings[i][1], room});
            }

            // Otherwise add the current meeting
            else
            {
                curr_meetings.push({meetings[i][1], available_rooms.top()});
                available_rooms.pop();
            }
            i++;
        }

        // Empty all the ongoing meetings
        while ( ! curr_meetings.empty())
        {
            freq[curr_meetings.top().second]++;
            curr_meetings.pop();
        }

        // Matrix to store multiple rooms of same frequency

        vector<vector<int>> result(meetings.size()+1);

        for (int i = 0; i < freq.size(); i++)
            result[freq[i]].push_back(i);

        for (int i = result.size()-1; i >= 0; i--)
        {
            if (result[i].size() > 0)
                return result[i][0];
        }

        return -1;
    }
};
