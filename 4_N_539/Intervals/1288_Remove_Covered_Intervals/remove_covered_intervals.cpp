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
    Sort by 1st element in Ascending by 2nd in Descending.

*/

/* Time  Beats: 13.80% */
/* Space Beats: 99.77% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort it can be O(n)
class Solution_1 {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    This one doesn't use "custom sort".

*/

/* Time  Beats: 60.86% */
/* Space Beats: 89.59% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort it can be O(n)
class Solution_2 {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals)
    {
        int result = 0;

        std::sort(intervals.begin(), intervals.end());

        int left  = -1;
        int right = -1;

        for (auto& inter : intervals)
        {
            if (inter[0] > left && inter[1] > right)
            {
                left = inter[0];
                result++;
            }

            right = std::max(right, inter[1]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.46% */
/* Space Beats:  9.15% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals)
    {
        std::sort(intervals.begin(),intervals.end());

        int x1 = intervals[0][0];
        int x2 = intervals[0][1];

        int result = 1;

        for(int i = 1; i < intervals.size(); i++)
        {
            if(intervals[i][0] > x1 && intervals[i][1] > x2)
                result++;

            if(intervals[i][1] > x2)
            {
                x1 = intervals[i][0];
                x2 = intervals[i][1];
            }
        }

        return result;
    }
};
