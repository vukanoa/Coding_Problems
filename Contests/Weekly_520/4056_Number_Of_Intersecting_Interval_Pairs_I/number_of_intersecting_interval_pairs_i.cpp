/*
    ============
    === EASY ===
    ============

    =============================================
    4056) Number Of Intersecting Interval Pairs I
    =============================================

    ============
    Description:
    ============

    You are given a 2D integer array intervals of n elements, where
    intervals[i] = [starti, endi] represents the closed interval from starti to
    endi.

    Return the number of pairs of indices (i, j) such that 0 <= i < j < n and
    intervals[i] and intervals[j] intersect.

    Two intervals intersect if they have at least one point in common,
    including when they only share an endpoint.

    =========================================================================
    FUNCTION: int countIntersectingIntervals(vector<vector<int>>& intervals);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,2],[2,3],[3,4]]
    Output: 2
    Explanation:
    There are 2 intersecting interval pairs:
        Intervals [1, 2] and [2, 3] intersect at the point 2.
        Intervals [2, 3] and [3, 4] intersect at the point 3.

    --- Example 2 ---
    Input: intervals = [[1,5],[2,4],[3,6]]
    Output: 3
    Explanation:
    There are 3 intersecting interval pairs:
        The intersection of [1, 5] and [2, 4] is [2, 4].
        The intersection of [1, 5] and [3, 6] is [3, 5].
        The intersection of [2, 4] and [3, 6] is [3, 4].


    --- Example 3 ---
    Input: intervals = [[1,2],[3,4],[5,6]]
    Output: 0
    Explanation:
    There are no intersecting interval pairs. Hence, the answer is 0.


    *** Constraints ***
    2 <= n == intervals.length <= 100
    intervals[i] = [starti, endi]
    0 <= starti <= endi <= 100

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple sort + Binary Search.

*/

/* Time  Beats: 75.00% */
/* Space Beats: 37.50% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Space Complexity of C++"s Intro Sort
class Solution {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        int result = 0;

        /* Sort */
        sort(intervals.begin(), intervals.end());
        
        for (int i = 0; i < N; i++)
        {
            const int& start = intervals[i][0];
            const int& end   = intervals[i][1];

            auto it = upper_bound(intervals.begin() + i + 1, intervals.end(), end, [](int value, const auto& interval) {
                return value < interval[0];
            });

            --it; // Move back by one
            int last_intersection_idx = it - intervals.begin();

            result += last_intersection_idx - i;
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

/* Time  Beats: 56.25% */
/* Space Beats: 12.50% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */
class Solution_Without_Using_Binary_Search {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        long long result = 1LL * N * (N - 1) / 2;

        vector<pair<int, bool>> positions;
        for (const auto& interval : intervals)
        {
            positions.push_back( {interval[0], false} ); // start
            positions.push_back( {interval[1], true}  ); // end
        }

        /* Sort */
        sort(positions.begin(), positions.end());

        long long ended_interval_count = 0;
        for (const auto& [point, is_end_point] : positions)
        {
            if ( ! is_end_point)
                result -= ended_interval_count;

            ended_interval_count += is_end_point;
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

/* Time  Complexity: O(N + M) */ // M is the maximum endpoint value
/* Space Complexity: O(M)     */
class Solution_Linear {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals)
    {
        int intersecting_pair_count = 0;
        int active_interval_count   = 0;
        int max_end        = 0;

        int interval_start_count[101] = {};
        int interval_end_count[101]   = {};

        for (const auto& interval : intervals)
        {
            ++interval_start_count[interval[0]];
            ++interval_end_count[interval[1]];

            max_end = max(max_end, interval[1]);
        }

        for (int point = 0; point <= max_end; point++)
        {
            int intervals_starting_here = interval_start_count[point];

            intersecting_pair_count += active_interval_count * intervals_starting_here + intervals_starting_here * (intervals_starting_here - 1) / 2;
            active_interval_count   += intervals_starting_here - interval_end_count[point];
        }

        return intersecting_pair_count;
    }
};
