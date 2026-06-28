/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    3975) Filter Occupied Intervals
    ===============================

    ============
    Description:
    ============

    You are given a 2D integer array occupiedIntervals, where
    occupiedIntervals[i] = [starti, endi] represents a time interval during
    which you are occupied. Each interval starts at starti and ends at endi,
    inclusive. These intervals may overlap.

    You are also given two integers freeStart and freeEnd, which define a free
    time interval from freeStart to freeEnd, inclusive.

    Your task is to merge all occupied intervals that overlap or touch, then
    remove all integer points in the free interval from the merged occupied
    intervals.

    Two intervals touch if the second interval starts immediately after the
    first one ends. For example, [1, 1] and [2, 2] touch and should be merged
    into [1, 2].

    Return the remaining occupied intervals in sorted order. The returned
    intervals must be non-overlapping and must contain the minimum number of
    intervals possible. If there are no remaining occupied points, return an
    empty list.

    ==========================================================================================================================
    FUNCTION: vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd);
    ==========================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: occupiedIntervals = [[2,6],[4,8],[10,10],[10,12],[14,16]], freeStart = 7, freeEnd = 11
    Output: [[2,6],[12,12],[14,16]]
    Explanation:
        After merging, the occupied intervals are [2, 8], [10, 12], and [14, 16].
        Excluding the free interval [7, 11] results in [2, 6], [12, 12], and [14, 16].

    --- Example 2 ---
    Input: occupiedIntervals = [[1,5],[2,3]], freeStart = 3, freeEnd = 8
    Output: [[1,2]]
    Explanation:
        After merging, the occupied interval is [1, 5].
        Excluding the free interval [3, 8] results in [1, 2].


    *** Constraints ***
    1 <= occupiedIntervals.length <= 5 * 10^4
    occupiedIntervals[i].length == 2
    1 <= starti <= endi <= 10^9
    1 <= freeStart <= freeEnd <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Merge Intervals + Trim Intervals.

*/

/* Time  Beats: 94.85% */
/* Space Beats: 92.69% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd)
    {
        const int N = occupiedIntervals.size();
        vector<vector<int>> intervals;
        vector<vector<int>> result;
        result.reserve(N); // To prevent reallocations

        /* Sort */
        sort(occupiedIntervals.begin(), occupiedIntervals.end());

        intervals = merge_intervals(occupiedIntervals);

        /* Trim Intervals */
        for (const vector<int>& interval : intervals)
        {
            const int& start = interval[0];
            const int& end   = interval[1];

            // No overlap
            if (end < freeStart || freeEnd < start)
            {
                result.push_back(interval);
                continue;
            }

            // Left piece
            if (start < freeStart)
                result.push_back( {start,       freeStart - 1} );

            // Right piece
            if (freeEnd < end)
                result.push_back( {freeEnd + 1, end          } );
        }

        return result;
    }

private:
    /* Merge Intervals */
    vector<vector<int>> merge_intervals(vector<vector<int>>& occupied)
    {
        const int N = occupied.size();
        vector<vector<int>> intervals;
        intervals.reserve(N); // To prevent reallocations

        int start = occupied[0][0];
        int end   = occupied[0][1];

        for (int i = 1; i < N; i++)
        {
            if (end >= (occupied[i][0] - 1))
            {
                end = max(end, occupied[i][1]);
            }
            else
            {
                intervals.push_back( {start, end} );

                start = occupied[i][0];
                end   = occupied[i][1];
            }
        }
        intervals.push_back( {start, end} );

        return intervals;
    }
};
