#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1288) Remove Covered Intervals
    ==============================

    ============
    Description:
    ============

    Given an array intervals where intervals[i] = [li, ri] represent the
    interval [li, ri), remove all intervals that are covered by another
    interval in the list.

    The interval [a, b) is covered by the interval [c, d) if and only if c <= a
    and b <= d.

    Return the number of remaining intervals.

    =====================================================================
    FUNCTION: int removeCoveredIntervals(vector<vector<int>>& intervals);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,4],[3,6],[2,8]]
    Output: 2
    Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

    --- Example 2 ---
    Input: intervals = [[1,4],[2,3]]
    Output: 1

    *** Constraints ***
    1 <= intervals.length <= 1000
    intervals[i].length == 2
    0 <= li < ri <= 10^5
    All the given intervals are unique.

*/

bool comparator(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a[0] != b[0])
        return (a[0] < b[0]);
    else
        return (a[1] > b[1]);
}

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 13.80% */
/* Space Beats: 99.77% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort it can be O(n)
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals)
    {
        int remaining = intervals.size();

        std::sort(intervals.begin(), intervals.end(), comparator);

        int left  = 0;
        int right = 1;
        while (right < intervals.size())
        {
            while (left != right && intervals[left][1] < intervals[right][1])
                left++;

            if (left != right)
                remaining--;

            right++;
        }

        return remaining;
    }
};
