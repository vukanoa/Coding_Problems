/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    56) Merge Intervals
    ===========================

    ============
    Description:
    ============

    Given an array of "intervals" where intervals[i] = [start_i, end_i],
    merge all overlapping intervals, and return an array of the non-overlapping
    intervals that cover all the intervals in the input.

    ====================================================================
    FUNCTION: vector<vector<int>> merge(vector<vector<int>>& intervals);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
    Output: [[1, 6], [8, 10], [15, 18]]

    --- Example 2 ---
    Input:  intervals = [[1, 4], [4, 5]]
    Output: [[1, 5]]

    *** Constraints ***
    1 <= intervals.lenght <= 10^4
    intervals[i].lenght == 2
    0 <= start_i <= end_i <= 10^4

*/

#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.03% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Sorting {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();

        vector<vector<int>> result;
        result.reserve(N); // To prevent reallocations

        /* Sort in ASCENDING order by start */
        sort(intervals.begin(), intervals.end());

        int start = intervals[0][0];
        int end   = intervals[0][1];

        for (int i = 1; i < N; i++)
        {
            if (end >= intervals[i][0])
            {
                end = max(end, intervals[i][1]);
            }
            else
            {
                result.push_back( {start, end} );

                start = intervals[i][0];
                end   = intervals[i][1];
            }
        }
        result.push_back( {start, end} );

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (SweepLine)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  21.77% */

/* Time  Complexity: O(N * RANGE) */
/* Space Complexity: O(RANGE)     */
class Solution_Sweep_Line {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();

        vector<vector<int>> result;
        result.reserve(N); // To prevent reallocations

        int min_start = INT_MAX;
        int max_end   = INT_MIN;

        // Find the absolute bounds of our timeline
        for (int i = 0; i < N; i++)
        {
            min_start = min(min_start, intervals[i][0]);
            max_end   = max(max_end,   intervals[i][1]);
        }

        const int RANGE = max_end - min_start + 1;

        // Initialize frequency arrays sized exactly to our range
        vector<int> sweep_line_start(RANGE, 0);
        vector<int> sweep_line_end  (RANGE, 0);

        int start;
        int end;

        for (int i = 0; i < N; i++)
        {
            start = intervals[i][0];
            end   = intervals[i][1];

            ++sweep_line_start[start - min_start];
            ++sweep_line_end[end - min_start];
        }

        int i = 0;
        int sum = 0;

        // Sweep the timeline to merge overlapping active zones
        while (i < RANGE)
        {
            while (i < RANGE && sum == 0)
            {
                sum += sweep_line_start[i];
                i++;
            }
            i--; // Rewind 1 step to process the current valid coordinate
            sum -= sweep_line_end[i];

            // Edge case: Handle isolated point intervals [x, x]
            if (sum == 0)
            {
                result.push_back( {i + min_start, i + min_start});
                i++;
                continue;
            }

            start = i + min_start;
            i++;

            // Fast-forward through the active merged interval
            while (i < RANGE && sum != 0)
            {
                sum -= sweep_line_end[i];   // Subtract ends
                sum += sweep_line_start[i]; // Add starts (bounces sum back up if touching)
                i++;
            }

            // The active interval has fully closed
            end = i + min_start - 1;
            result.push_back( {start, end} );
        }

        return result;
    }
};
