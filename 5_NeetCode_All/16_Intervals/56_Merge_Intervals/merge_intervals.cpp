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
class Solution {
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
