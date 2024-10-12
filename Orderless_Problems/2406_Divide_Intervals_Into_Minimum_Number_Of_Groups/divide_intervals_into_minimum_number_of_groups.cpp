#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    2406) Divide Intervals Into Minimum Number of Groups
    ====================================================

    ============
    Description:
    ============

    You are given a 2D integer array intervals where intervals[i] = [lefti,
    righti] represents the inclusive interval [lefti, righti].

    You have to divide the intervals into one or more groups such that each
    interval is in exactly one group, and no two intervals that are in the same
    group intersect each other.

    Return the minimum number of groups you need to make.

    Two intervals intersect if there is at least one common number between
    them. For example, the intervals [1, 5] and [5, 8] intersect.

    ========================================================
    FUNCTION: int minGroups(vector<vector<int>>& intervals);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
    Output: 3
    Explanation: We can divide the intervals into the following groups:
    - Group 1: [1, 5], [6, 8].
    - Group 2: [2, 3], [5, 10].
    - Group 3: [1, 10].
    It can be proven that it is not possible to divide the intervals into fewer than 3 groups.

    --- Example 2 ---
    Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
    Output: 1
    Explanation: None of the intervals overlap, so we can put all of them in one group.


    *** Constraints ***
    1 <= intervals.length <= 10^5
    intervals[i].length == 2
    1 <= lefti <= righti <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.50% */
/* Space Beats: 68.69% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int minGroups(vector<vector<int>>& intervals)
    {
        vector<int> start_times, end_times;

        // Extract start and end times
        for (const auto& interval : intervals)
        {
            start_times.push_back(interval[0]);
            end_times.push_back(interval[1]);
        }

        // Sort start and end times
        sort(start_times.begin(), start_times.end());
        sort(end_times.begin(), end_times.end());

        int end_ptr = 0, group_count = 0;

        // Traverse through the start times
        for (int start : start_times)
        {
            if (start > end_times[end_ptr])
                end_ptr++;
            else
                group_count++;
        }

        return group_count;
    }
};
