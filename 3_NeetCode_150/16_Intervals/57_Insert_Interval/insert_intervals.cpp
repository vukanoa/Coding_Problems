/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    57) Insert Interval
    ===========================

    ============
    Description:
    ============

    You are given an array of non-overlapping intervals intervals where
    intervals[i] = [starti, endi] represent the start and the end of the ith
    interval and intervals is sorted in ascending order by starti. You are also
    given an interval newInterval = [start, end] that represents the start and
    end of another interval.

    Insert newInterval into intervals such that intervals is still sorted in
    ascending order by starti and intervals still does not have any overlapping
    intervals (merge overlapping intervals if necessary).

    Return intervals after the insertion.

    ===============================================================================================
    FUNCTION: vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval);
    ===============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
    Output: [[1,5],[6,9]]

    --- Example 2 ---
    Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
    Output: [[1,2],[3,10],[12,16]]
    Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

    *** Constraints ***
    0 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 105
    intervals is sorted by starti in ascending order.
    newInterval.length == 2
    0 <= start <= end <= 105

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There are 3 possibilities:
            1. It's before the first interval
            2. It's after  the last  interval
            3. It's overlapping
            4. It's a separate new interval that needs to be pushed somewhere in the middle

    Consider this example:
            intervals = [[3, 5], [8, 10], [15, 18]]

    All the possible cases:
            1.  [0, 1]   // Before the first interval
            2.  [0, 4]   // Overlapping
            3.  [0, 16]  // Overlapping
            4.  [0, 19]  // Overlapping
            5.  [3, 8]   // Overlapping
            6.  [3, 15]  // Overlapping
            7.  [6, 7]   // New separate interval
            8.  [6, 17]  // Overlapping
            9.  [6, 19]  // Overlapping
            10. [16, 20] // Overlapping
            11. [19, 20] // After the last interval

    It's pretty much self-explanatory, especially with comments.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  12.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_1 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
    {
        const int N = intervals.size();

        if (intervals.empty())
            return {newInterval};

        vector<vector<int>> result;
        result.reserve(N+1); // To prevent reallocations

        int start = newInterval[0];
        int end   = newInterval[1];

        for (int i = 0; i < N; i++)
        {
            if (end < intervals[i][0]) // We're DONE
            {
                // Push newInterval that is potentially merged with other intervals
                // aka "potentially_merged_new_interval"
                result.push_back( {start, end} );

                // Push remaining intervals that come AFTER the end of the "potentially_merged_new_interval"
                result.insert(result.end(), intervals.begin() + i, intervals.end());

                return result;
            }



            // If an interval ends BEFORE the newInterval, push it and continue
            if (intervals[i][1] < start)
            {
                result.push_back( {intervals[i]} );
            }
            else // Potentially merge newInterval
            {
                start = min(start, intervals[i][0]);
                end   = max(end  , intervals[i][1]);
            }
        }

        result.push_back( {start, end} ); // Push "potentially_merged_new_interval"

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way to implement it. This is maybe a bit more clean.

*/

/* Time  Beats: 98.73% */
/* Space Beats: 51.03% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
    {
        const int N = intervals.size();

        if (intervals.empty())
            return {newInterval};

        vector<vector<int>> result;
        result.reserve(N+1); // To prevent reallocations

        int start = newInterval[0];
        int end   = newInterval[1];

        int i = 0;

        // Case 1: Intervals that end STRICTLY BEFORE the start of newInterval
        while (i < N && intervals[i][1] < start)
        {
            result.push_back(intervals[i]);

            // Increment
            i++;
        }

        // Case 2: Keep extending(merging) "potentially_merged_new_interval" in
        //         both directions as long as there is an overlap
        while (i < N && intervals[i][0] <= end)
        {
            start = min(start, intervals[i][0]);
            end   = max(end  , intervals[i][1]);

            // Increment
            i++;
        }
        result.push_back( {start, end} );

        // Case 3: Intervals that begin STRICTLY AFTER "potentially_merged_new_interval"
        while (i < N)
        {
            result.push_back(intervals[i]);

            // Increment
            i++;
        }

        return result;
    }
};
