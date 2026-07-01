/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3951) Minimum Energy to Maintain Brightness
    ===========================================

    ============
    Description:
    ============

    You are given an integer n, representing n light bulbs arranged in a line
    and indexed from 0 to n - 1.

    You are also given an integer brightness and a 2D integer array intervals,
    where intervals[i] = [starti, endi] represents an inclusive time interval
    during which the lighting requirement must be satisfied.

    At each time unit, every bulb can independently be either on or off. A bulb
    that is on illuminates its own position and its adjacent positions, if they
    exist.

    The total illumination at a time unit is the number of illuminated
    positions. Each position is counted at most once.

    For every integer time unit covered by at least one interval in intervals,
    the total illumination must be at least brightness. At time units not
    covered by any interval, all bulbs may remain off. Each bulb that is on
    consumes 1 unit of energy for that time unit.

    Return an integer denoting the minimum total energy required.

    =====================================================================================
    FUNCTION: long long minEnergy(int n, int brightness, vector<vector<int>>& intervals);
    =====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, brightness = 5, intervals = [[6,12]]
    Output: 14
    Explanation:
        Turn on the light bulbs at positions 1 and 4.
        Current state of line: 0 1 0 0 1.
        All 5 positions are illuminated, so the required brightness is reached.
        The active interval has length 12 - 6 + 1 = 7, so the total energy is 2 * 7 = 14.

    --- Example 2 ---
    Input: n = 2, brightness = 1, intervals = [[0,0],[2,2]]
    Output: 2
    Explanation:
        Turn on one light bulb during each active interval.
        Each interval has length 1, so the total active time is 1 + 1 = 2.
        The total energy is 1 * 2 = 2.

    --- Example 3 ---
    Input: n = 4, brightness = 2, intervals = [[1,3],[2,4]]
    Output: 4
    Explanation:
        Turn on one light bulb. It can illuminate at least 2 positions. The
        active intervals overlap, so the total active time is the length of
        [1,4], which is 4. The total energy is 1 * 4 = 4.


    *** Constraints ***
    1 <= n <= 10^6
    1 <= brightness <= n
    1 <= intervals.length <= 10^5
    intervals[i] == [starti, endi]
    0 <= starti <= endi <= 10^9

*/

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    A variation on the "Merge Intervals" problem.

    If you know how to "Merge Intervals", then the rest is a simulation.

*/

/* Time  Beats: 33.71% */
/* Space Beats: 36.75% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_By_the_Book {
public:
    long long minEnergy(int n, int brightness, vector<vector<int>>& intervals)
    {
        const int SIZE = intervals.size();
        long long result = 0;

        vector<vector<int>> non_overlapping_intervals = merge_overlapping_intervals(intervals);
        long long energy = static_cast<long long>(ceil(1.0 * brightness / 3));

        for (const vector<int>& interval : non_overlapping_intervals)
        {
            const int& start = interval[0];
            const int& end   = interval[1];

            result += (end - start + 1) * energy;
        }

        return result;
    }

private:
    vector<vector<int>> merge_overlapping_intervals(vector<vector<int>>& intervals)
    {
        const int SIZE = intervals.size();

        vector<vector<int>> new_intervals;
        new_intervals.reserve(SIZE); // To prevent reallocations

        /* Sort */
        sort(intervals.begin(), intervals.end());

        int start = intervals[0][0];
        int end   = intervals[0][1];

        for (int i = 1; i < SIZE; i++)
        {
            if (end >= intervals[i][0])
            {
                end = max(end, intervals[i][1]);
            }
            else
            {
                new_intervals.push_back( {start, end} );

                start = intervals[i][0];
                end   = intervals[i][1];
            }
        }
        new_intervals.push_back( {start, end} );

        return new_intervals;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though for this specific problem we do not need to merge
    intervals explicitly and then do an additional processing. We can do these
    two things at the same time, as we go.

*/

/* Time  Beats: 51.80% */
/* Space Beats: 53.45% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // SC of C++'s Intro Sort
class Solution_Shorter {
public:
    long long minEnergy(int n, int brightness, vector<vector<int>>& intervals)
    {
        const int SIZE = intervals.size();
        long long result = 0;

        long long energy = static_cast<long long>(ceil(1.0 * brightness / 3));

        /* Sort */
        sort(intervals.begin(), intervals.end());

        int start = intervals[0][0];
        int end   = intervals[0][1];

        int time_units = 0;
        for (int i = 1; i < SIZE; i++)
        {
            if (end >= intervals[i][0])
            {
                end = max(end, intervals[i][1]);
            }
            else
            {
                time_units += end - start + 1;

                start = intervals[i][0];
                end   = intervals[i][1];
            }
        }
        time_units += end - start + 1;

        return energy * time_units;
    }
};
