#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    539) Minimum Time Difference
    ============================

    ============
    Description:
    ============

    Given a list of 24-hour clock time points in "HH:MM" format, return the
    minimum minutes difference between any two time-points in the list.

    ============================================================
    FUNCTION: int findMinDifference(vector<string>& timePoints);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: timePoints = ["23:59","00:00"]
    Output: 1

    --- Example 2 ---
    Input: timePoints = ["00:00","23:59","00:00"]
    Output: 0


    *** Constraints ***
    2 <= timePoints.length <= 2 * 10^4
    timePoints[i] is in the format "HH:MM".

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.82% */
/* Space Beats: 98.24% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int findMinDifference(vector<string>& timePoints)
    {
        vector<int> minutes(timePoints.size());

        // Convert times to minutes
        for (int i = 0; i < timePoints.size(); ++i)
        {
            int h = stoi(timePoints[i].substr(0, 2));
            int m = stoi(timePoints[i].substr(3));

            minutes[i] = h * 60 + m;
        }

        // Sort times in ascending order
        sort(minutes.begin(), minutes.end());

        // Find minimum difference across adjacent elements
        int minDiff = INT_MAX;
        for (int i = 0; i < minutes.size() - 1; ++i)
            minDiff = min(minDiff, minutes[i + 1] - minutes[i]);

        // Consider the circular difference between last and first element
        minDiff = min(minDiff, 24 * 60 - minutes.back() + minutes.front());

        return minDiff;
    }
};
