/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    3169) Count Days Without Meetings
    =================================

    ============
    Description:
    ============

    You are given a positive integer days representing the total number of days
    an employee is available for work (starting from day 1). You are also given
    a 2D array meetings of size n where, meetings[i] = [start_i, end_i]
    represents the starting and ending days of meeting i (inclusive).

    Return the count of days when the employee is available for work but no
    meetings are scheduled.

    =====
    Note: The meetings may overlap.
    =====

    =================================================================
    FUNCTION: int countDays(int days, vector<vector<int>>& meetings);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
    Output: 2
    Explanation:
    There is no meeting scheduled on the 4th and 8th days.

    --- Example 2 ---
    Input: days = 5, meetings = [[2,4],[1,3]]
    Output: 1
    Explanation:
    There is no meeting scheduled on the 5th day.

    --- Example 3 ---
    Input: days = 6, meetings = [[1,6]]
    Output: 0
    Explanation:
    Meetings are scheduled for all working days.


    *** Constraints ***
    1 <= days <= 10^9
    1 <= meetings.length <= 10^5
    meetings[i].length == 2
    1 <= meetings[i][0] <= meetings[i][1] <= days

*/

#include <algorithm>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    This would be a by-the-book line-sweep algorithm were it not for these
    Constraints.

    Since days are:

        1 <= days <= 10^9

    Making an array of (days + 2) elements exceeds Memory Limit, therefore we
    get MLE(Memory Limit Exceeded).

    However, the Constraints SCREAM what to do. Since "meetings" is:

        1 <= meetings.length <= 10^5

    Which is LESS than the maximum "days", that highly suggest we should do
    something with "meetings".

    As you'll see in the Correct Solution(All the way down), we needed to sort
    the meetings and then solve it that way.

    Always look at the Constraints!

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // This is too much for N = 10^9
class Solution_MLE {
public:
    int countDays(int days, vector<vector<int>>& meetings)
    {
        const int N = meetings.size();
        int busy = 0;

        vector<int> line_sweep(days + 2, 0);

        for (const auto& entry : meetings)
        {
            line_sweep[entry[0]]++;
            line_sweep[entry[1] + 1]--;
        }

        int meetings_today = 0;
        for (int i = 0; i <= days; i++)
        {
            meetings_today += line_sweep[i];

            if (meetings_today > 0)
                busy++;
        }

        return days - busy;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    As we've said, because of the Constraints, they are hinting at us to try
    and do something with meetings.

    The first thing that comes to mind is--Sorting.

    Also, since we're dealing with some kind of range, that also suggests that
    sorting would definitely help.

    Once you figure that our, the remaining part is intuitive. It's no more
    difficult than a basic EASY problem.

    Sorting was the crux that you could figure out ONLY by looking at the
    Constraints, otherwise you'd go down the "Line Sweep" path and would get a
    MLE.

*/

/* Time  Beats: 64.63% */
/* Space Beats: 59.18% */

/* Time  Complexity: O(M * logM) */
/* Space Complexity: O(1)        */ // Depending on the Sort
class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings)
    {
        const int N = meetings.size();

        sort(meetings.begin(), meetings.end());

        int no_meetings = meetings[0][0] - 1; // Before the first start_meeting
        int prev_end    = meetings[0][1];

        for (int i = 1; i < N; i++)
        {
            int curr_start = meetings[i][0];
            int curr_end   = meetings[i][1];

            if ((prev_end + 1) <= curr_start)
                no_meetings += curr_start - (prev_end + 1);

            prev_end = max(prev_end, curr_end);
        }

        if (prev_end < days)                // After the furthermost end_meetin
            no_meetings += days - prev_end;

        return no_meetings;
    }
};
