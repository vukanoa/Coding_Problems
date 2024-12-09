#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    2054) Two Best Non-Overlapping Events
    =====================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D integer array of events where events[i] =
    [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends
    at endTimei, and if you attend this event, you will receive a value of
    valuei. You can choose at most two non-overlapping events to attend such
    that the sum of their values is maximized.

    Return this maximum sum.


    =====
    Note: that the start time and end time is inclusive: that is, you cannot
          attend two events where one of them starts and the other ends at the
          same time. More specifically, if you attend an event with end time t,
          the next event must start at or after t + 1.
    =====

    ========================================================
    FUNCTION: int maxTwoEvents(vector<vector<int>>& events);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: events = [[1,3,2],[4,5,2],[2,4,3]]
    Output: 4
    Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.

    --- Example 2 ---
    Input: events = [[1,3,2],[4,5,2],[1,5,5]]
    Output: 5
    Explanation: Choose event 2 for a sum of 5.

    --- Example 3 ---
    Input: events = [[1,5,3],[1,5,1],[6,6,5]]
    Output: 8
    Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.


    *** Constraints ***
    2 <= events.length <= 10^5
    events[i].length == 3
    1 <= startTimei <= endTimei <= 10^9
    1 <= valuei <= 10^6

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is fairly simple if you understand two concepts:
        1. Binary Search
        2. LeetCode 1299: Replace Elements With Greatest Element On Right Side

    i)  Sort 2D vector "events" by the starting time, i.e. 0th value.

    ii) Start iterating through this sorted 2D vector and for each vector try
        to find a vector, to the right(since it's sorted), that has the
        starting (time curr_end_time +1) or higher.

        This is where we can use "lower_bound" function from C++.
        (It finds the first, leftmost, EQUAL OR GREATHER THAN target value)

        Once we find that vector(that has starting time (time curr_end_time +1)
        or higher) we need to check if curr_value + value from that vector is
        the new maximum.

        But here we would make a mistake.
        Why?

        Because what if that value(of that newly found vector) is NOT the
        biggest one of all the remaining ones that are also NOT overlapping
        with curr_end time?

        Because of that, we can use a DynamicProgramming approach to
        precalculate all of those.

        But, we need to use another vector, with only such values that
        correspond to same indices as the SORTED events.

        We need this additional structure because curr_value needs to be
        UNCHANGED when we're calculating it.

*/

/* Time  Beats: 94.83% */
/* Space Beats: 99.35% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        const int n = events.size();
        int result = 0;

        // std::sort(events.begin(), events.begin());
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        vector<int> dp(n, 0); 
        dp[n-1] = events[n-1][2]; // Biggest value from this starting time, onwards

        for (int i = n-2; i >= 0; i--)
            dp[i] = max(events[i][2], dp[i+1]);


        for (int i = 0; i < events.size(); i++)
        {
            auto it = lower_bound(events.begin() + i, events.end(), events[i][1]+1, [](const vector<int>& a, int val) {
                return a[0] < val;
            });

            int idx = it - events.begin();

            if (it != events.end() && (*it)[0] >= events[i][1]+1)
                result = max(result, events[i][2] + dp[idx]);
            else
                result = max(result, events[i][2]);
        }

        return result;
    }
};
