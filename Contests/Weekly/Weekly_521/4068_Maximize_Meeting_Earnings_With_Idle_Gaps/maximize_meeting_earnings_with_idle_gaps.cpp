/*
    ============
    === HARD ===
    ============

    ==============================================
    4068) Maximize Meeting Earnings with Idle Gaps
    ==============================================

    ============
    Description:
    ============

    You are given a 2D integer array meetings, where meetings[i] = [starti,
    endi, revenuei] represents a meeting starting at time starti, ending at
    time endi, with revenue revenuei.

    All meetings use half-open intervals [start, end), so meetings that only
    touch at endpoints do not overlap.

    You may select any non-empty of meetings such that no two selected meetings
    overlap. You earn the revenue of each selected meeting.

    Arrange the selected meetings in increasing order of their start times. For
    each pair of adjacent meetings in this order, you also earn 1 unit of
    revenue per unit of idle time between them. This idle time equals the later
    meeting's start time minus the earlier meeting's end time.

    No idle revenue is earned before the earliest selected meeting starts or
    after the latest selected meeting ends. If only one meeting is selected, no
    idle revenue is earned.

    Return the maximum total earnings achievable.

    ===============================================================
    FUNCTION: long long maxEarnings(vector<vector<int>>& meetings);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: meetings = [[2,5,4],[6,8,3]]
    Output: 8
    Explanation:
        Select both meetings. They do not overlap and earn 4 + 3 = 7 units of
        meeting revenue.
        The first meeting ends at time 5, and the second starts at time 6. This
        idle gap earns 6 - 5 = 1 additional unit.
        The maximum total earnings are 7 + 1 = 8.

    --- Example 2 ---
    Input: meetings = [[3,5,4],[4,7,8],[8,10,3]]
    Output: 12
    Explanation:
        Select the meetings at indices 1 and 2. They do not overlap and earn 8
        + 3 = 11 units of meeting revenue.
        In chronological order, these meetings run from time 4 to 7 and from
        time 8 to 10. The idle gap earns 8 - 7 = 1 additional unit.
        The maximum total earnings are 11 + 1 = 12.

    --- Example 3 ---
    Input: meetings = [[1,2,2],[4,5,2],[7,9,3]]
    Output: 11
    Explanation:
        Select all three meetings. They do not overlap and earn 2 + 2 + 3 = 7
        units of meeting revenue.
        The idle gap from time 2 to 4 earns 4 - 2 = 2 additional units.
        The idle gap from time 5 to 7 earns 7 - 5 = 2 additional units.
        The maximum total earnings are 7 + 2 + 2 = 11.


    *** Constraints ***
    1 <= meetings.length <= 10^5
    meetings[i] = [starti, endi, revenuei]
    0 <= starti < endi <= 10^9
    1 <= revenuei <= 10^9

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 71.89% */
/* Space Beats: 84.02% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maxEarnings(vector<vector<int>>& meetings)
    {
        long long result = 0;

        /* Sort */
        sort(meetings.begin(), meetings.end());

        priority_queue<pair<long long, long long>,
                       vector<pair<long long, long long>>,
                       greater<pair<long long, long long>>> min_heap;

        long long max_prev_revenue = -1e18;
        long long curr_revenue;

        for (const vector<int>& meeting : meetings)
        {
            const int& start   = meeting[0];
            const int& end     = meeting[1];
            const int& revenue = meeting[2];

            while ( ! min_heap.empty() && min_heap.top().first <= start)
            {
                max_prev_revenue = max(max_prev_revenue, min_heap.top().second);
                min_heap.pop();
            }

            curr_revenue = revenue;
            if (max_prev_revenue != -1e18)
                curr_revenue = max(curr_revenue, revenue + max_prev_revenue + start);

            result = max(result, curr_revenue);

            min_heap.push( {end, curr_revenue - end} );
        }

        return result;
    }
};
