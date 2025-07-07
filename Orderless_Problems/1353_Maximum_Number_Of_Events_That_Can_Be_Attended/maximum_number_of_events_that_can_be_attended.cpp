/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    1353) Maximum Number of Events That Can Be Attended
    ===================================================

    ============
    Description:
    ============

    You are given an array of events where events[i] = [startDayi, endDayi].
    Every event i starts at startDayi and ends at endDayi.

    You can attend an event i at any day d where startTimei <= d <= endTimei.
    You can only attend one event at any time d.

    Return the maximum number of events you can attend.

    =====================================================
    FUNCTION: int maxEvents(vector<vector<int>>& events);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: events = [[1,2],[2,3],[3,4]]
    Output: 3
    Explanation: You can attend all the three events.
    One way to attend them all is as shown.
    Attend the first event on day 1.
    Attend the second event on day 2.
    Attend the third event on day 3.

    --- Example 2 ---
    Input: events= [[1,2],[2,3],[3,4],[1,2]]
    Output: 4


    *** Constraints ***
    1 <= events.length <= 10^5
    events[i].length == 2
    1 <= startDayi <= endDayi <= 10^5

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Unconventional use of DSU's "find" functionality with path compression.

*/

/* Time  Beats: 98.63% */
/* Space Beats: 25.49% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int maxEvents(vector<vector<int>>& events)
    {
        /* Sort */
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1]; // ASCENDING by end_time value
        });

        int max_day = 0;
        for (const auto& ev : events)
            max_day = max(max_day, ev[1]);

        vector<int> next_free_day(max_day + 2);

        for (unsigned d = 0; d < next_free_day.size(); ++d)
            next_free_day[d] = d;

        int result = 0;
        for (const auto& ev : events)
        {
            int start_day_of_this_event = ev[0];
            int end_day_of_this_event   = ev[1];

            int curr_first_free_day = find_next_free_day(start_day_of_this_event, next_free_day);
            if (curr_first_free_day <= end_day_of_this_event)
            {
                result++;
                next_free_day[curr_first_free_day] = find_next_free_day(curr_first_free_day+1, next_free_day);
            }
        }

        return result;
    }

private:
    int find_next_free_day(int day, vector<int>& next_free_day)
    {
        while (day != next_free_day[day])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            next_free_day[day] = next_free_day[next_free_day[day]];

            day = next_free_day[day];
        }

        return day;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.32% */
/* Space Beats: 64.45% */

/* Time  Complexity: O(N * logN + max_end * logN) */
/* Space Complexity: O(N)                    */
class Solution_Greedy {
public:
    int maxEvents(vector<vector<int>>& events)
    {
        const int N = events.size();
        int result = 0;

        int max_day = 0;
        for (int i = 0; i < events.size(); i++)
            max_day = max(max_day, events[i][1]);

        priority_queue<int, vector<int>, greater<>> min_heap;

        /* Sort in ASCENDING */
        sort(events.begin(), events.end());

        for (int i = 0, j = 0; i <= max_day; i++)
        {
            while (j < N && events[j][0] <= i)
            {
                min_heap.emplace(events[j][1]);
                j++;
            }

            while ( ! min_heap.empty() && min_heap.top() < i)
                min_heap.pop();

            if ( ! min_heap.empty())
            {
                min_heap.pop();
                result++;
            }
        }

        return result;
    }
};
