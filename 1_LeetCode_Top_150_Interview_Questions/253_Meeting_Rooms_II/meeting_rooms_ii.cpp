/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    253) Meeting Rooms II
    ===========================

    ============
    Description:
    ============

    Given an array of meeting time intervals consisting of start and end times
    [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference
    rooms required.

    ==============================================================
    FUNCTION: int minMeetingRooms(vector<vector<int>> &intervals);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: [[0, 30],[5, 10],[15, 20]]
    Output: 2
    Explanation:
    We need two conference rooms.
    room1: (0, 30)
    room2: (5, 10), (15, 20)

    --- Example 2 ---
    Input: [[7,10],[2,4]]
    Output: 1

    *** Constraints ***

*/

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    In the Description, when they've said: 
        "Find the minimum number of conference rooms required"
    what they really mean is:
        "What is the maximum number of overlapping meetings at any give point
         in time"

    It's kind of difficult to come up with the code if you look at the example
    in "vector" representation.

    So let's draw it:

            [[0, 30], [5, 10], [15, 20]]

            0                                30
            |--------------------------------|

                5    10
                |-----|    15    20
                            |-----|
    
    Again, let's emphasize the right question:
        "What is the maximum number of overlapping meetings at any give point
         in time"

    Now if we just go from left to right we'll see:
        Okay, 0 is the first meeting that starts. If we keep going then we're
        going to stumble upon a 5, which is also the beginning(of a conference)
        it's not that the first meeting is ending.

        So what does that tell us?
        It tells us that two meeting have started so far but none has ended.

        So at this point in time:
               |____
                   |
                   v

                   |
            0      |                         30
            |------|-------------------------|
                   |
                5  | 10
                |--|--|    15    20
                           |-----|


        We have 2 meetings that are going on at the same amount of time.

        So we're going to be maintaining a variable "count", which tells us at
        any given point in time, what is the number of meetings going on.

        Right now it's 2, but we're going to be returning whatever the max
        value of it happened to be.

        Next is the point 10, which is the first ending point.
        So what does that tell us?
        That tells us that a meeting has just ended. So what are we going to do
        with our "count"?

        We knew we have 2 meetings going on at the same time, but now, after
        this point:
             |
             |_________
                      |
                      v

                      |
            0         |                      30
            |---------|----------------------|
                      |
                5    1|0
                |-----|    15    20
                      |     |-----|

        
        We're only going to have one meeting going on, therefore we're going
        to see the number of meetings to 1.

        Next one is 15 and it happens to be the starting point.
        So now, once again, there are two meeting going on at the same time.
        We increment one count.

        Next is 20, which is an ending point. We know a meeting is ending, but
        we don't know which one. But that's not even important. The only thing
        that is important is the we are tracking how many meeting are going on
        at the same time. After this 20, it's 1.

        And the last point is 30, it's an ending point, again decrement the
        "count".

        At the end we return the maximum value of count at any given time.
        In our case, it was 2.

*/

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        int result = 0; // Max number of rooms at any given time

        vector<int> starts;
        vector<int> ends;

        for (int i = 0; i < N; i++)
        {
            starts.push_back(intervals[i][0]);
            ends.push_back(intervals[i][1]);
        }

        /* Sort */
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());


        int rooms = 0;

        int start_idx = 0;
        int end_idx   = 0;

        while (start_idx < N)
        {
            if (starts[start_idx] < ends[end_idx])
            {
                start_idx++;
                rooms++;
            }
            else
            {
                end_idx++;
                rooms--;
            }

            result = max(result, rooms);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If there are multiple points at some time, then we want ending points to be
    BEFORE the starting points.

    To achieve that we can associate -1 within the pairs of ending times and
    that also helps us with the remaining part of the Solution since we want to
    decrement rooms anytime we hit an ending point.

    Similarly, when we hit a starting point we want to increment the current
    number of rooms, so it works boths ways and the code because very concise.

*/

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Greedy {
public:
    int minMeetingRooms(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        int result = 0; // Max number of rooms at any given time

        vector<pair<int,int>> points;
        points.reserve(2 * N); // To prevent reallocations

        for (int i = 0; i < N; i++)
        {
            points.push_back( {intervals[i][0], +1} );
            points.push_back( {intervals[i][1], -1} );
        }

        /* Sort */
        sort(points.begin(), points.end());

        int rooms = 0;
        for (const auto& [time_point, room_delta] : points)
        {
            rooms += room_delta;
            result = max(result, rooms);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This approach could be done either with:

        Sorted MultiSet + BinarySearch
                
            or

        MinHeap

    I chose the former option since many Solutions online already show the
    MinHeap Solution.

*/

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_MultiSet__and__Binary_Search { // Or just Min-Heap
public:
    int minMeetingRooms(vector<vector<int>>& intervals)
    {
        if (intervals.empty())
            return 0;

        const int N = intervals.size();

        if (N == 1)
            return 1;

        /* Sort by start in ASCENDING order */
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b){
            if (a[0] == b[0])
                return a[1] < b[1];

            return a.start < b.start;
        });

        multiset<int> multiset_of_ends;
        multiset_of_ends.insert(intervals[0][1]);

        for (int i = 1; i < N; i++)
        {
            int& curr_start = intervals[i][0];
            int& curr_end   = intervals[i][1];

            /* Binary Search */
            auto iter = multiset_of_ends.upper_bound(curr_start);

            if (iter != multiset_of_ends.begin())
            {
                iter--;
                multiset_of_ends.erase(iter); // Detete only ONE instance!
            }

            multiset_of_ends.insert(curr_end);
        }

        return multiset_of_ends.size();
    }
};
