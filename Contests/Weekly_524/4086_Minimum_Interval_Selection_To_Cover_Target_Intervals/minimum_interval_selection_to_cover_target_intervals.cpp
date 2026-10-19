/*
    ============
    === HARD ===
    ============

    ==========================================================
    4086) Minimum Interval Selection to Cover Target Intervals
    ==========================================================

    ============
    Description:
    ============

    You are given two 2D integer arrays, availableIntervals and
    targetIntervals, each representing a list of closed intervals.

    Select a subset of intervals from availableIntervals so that every real
    point contained in any interval in targetIntervals belongs to at least one
    selected interval.

    Points outside the target intervals do not need to be covered. Selected
    intervals may overlap or extend beyond the target intervals.

    Return the minimum number of intervals you need to select. If it is
    impossible to cover all the target intervals, return -1.

    ==========================================================================================================
    FUNCTION: int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals);
    ==========================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: availableIntervals = [[1,4],[1,7],[3,9],[5,10],[10,15]], targetIntervals = [[1,3],[2,5],[7,8],[10,13],[11,15],[12,13]]
    Output: 3
    Explanation:
    The target intervals cover the ranges [1, 5], [7, 8], and [10, 15]. By
    selecting [1, 4], [3, 9], and [10, 15] from availableIntervals, all target
    intervals can be fully covered with three intervals.

    --- Example 2 ---
    Input: availableIntervals = [[4,6],[1,4],[2,5]], targetIntervals = [[3,4],[2,5],[6,7]]
    Output: -1
    Explanation:
    It is impossible to select intervals from availableIntervals to cover all the intervals in targetIntervals.

    --- Example 3 ---
    Input: availableIntervals = [[1,2],[3,4]], targetIntervals = [[1,4]]
    Output: -1
    Explanation:
    Selecting both available intervals leaves every real point strictly between 2 and 3 uncovered. For example, 2.5 belongs to the target interval but to neither available interval.


    *** Constraints ***
    1 <= availableIntervals.length, targetIntervals.length <= 5 * 10^4
    availableIntervals[i].length == targetIntervals[j].length == 2
    1 <= availableIntervals[i][0] <= availableIntervals[i][1] <= 10^5
    1 <= targetIntervals[j][0] <= targetIntervals[j][1] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 71.60% */
/* Space Beats: 73.78% */

/* Time  Complexity: O(N * logN  +  M * logM) */
/* Space Complexity: O(M)                     */
class Solution {
public:
    int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals)
    {
        const int N = availableIntervals.size();

        /* Sort BOTH by start, then by end in ASCENDING order */
        sort(availableIntervals.begin(), availableIntervals.end());
        sort(targetIntervals.begin(),    targetIntervals.end());

        /* Merge TARGET intervals into DISJOINT SEGMENTS */
        vector<vector<int>> merged_target_intervals = merge_intervals(targetIntervals);
        const int NEW_M = merged_target_intervals.size();

        int result = 0;
        int reach  = -1; // Rightmost required point that IS covered so far

        int i = 0; // idx in availableIntervals
        int j = 0; // idx in merged_target_intervals
        while (j < NEW_M)
        {
            /* Leftmost still-uncovered required point */
            const int target_start = max(merged_target_intervals[j][0], reach);
            const int target_end   = merged_target_intervals[j][1];

            /* TAKE: extend coverage with every interval starting AT OR BEFORE target_start */
            int best_end = reach;
            while (i < N && availableIntervals[i][0] <= target_start)
            {
                const int& end = availableIntervals[i][1];
                best_end = max(best_end, end);
                ++i;
            }

            /* No interval can cover the leftmost uncovered point */
            if (best_end <= reach)
                return -1;

            ++result;
            reach = best_end;

            /* SKIP target segments thta are now FULLY COVERED */
            while (j < NEW_M && merged_target_intervals[j][1] <= reach)
                ++j;
        }

        return result;
    }

private:
    vector<vector<int>> merge_intervals(vector<vector<int>>& targetIntervals)
    {
        const int M = targetIntervals.size();

        vector<vector<int>> merged_intervals;
        merged_intervals.reserve(M); // To prevent repeated reallocations

        int prev_start = targetIntervals[0][0];
        int prev_end   = targetIntervals[0][1];
        for (int i = 1; i < M; i++)
        {
            const int& curr_start = targetIntervals[i][0];
            const int& curr_end   = targetIntervals[i][1];

            if (prev_end >= curr_start)
            {
                prev_end = max(prev_end, curr_end);
            }
            else
            {
                merged_intervals.push_back( {prev_start, prev_end} );

                prev_start = curr_start;
                prev_end   = curr_end;
            }
        }
        merged_intervals.push_back( {prev_start, prev_end} ); // Trailing one

        return merged_intervals;
    }
};
