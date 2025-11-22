/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    436) Find Right Interval
    ===========================

    ============
    Description:
    ============

    You are given an array of intervals, where intervals[i] = [starti, endi]
    and each starti is unique.

    The right interval for an interval i is an interval j such that startj >=
    endi and startj is minimized. Note that i may equal j.

    Return an array of right interval indices for each interval i. If no right
    interval exists for interval i, then put -1 at index i.

    ========================================================================
    FUNCTION: vector<int> findRightInterval(vector<vector<int>>& intervals);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,2]]
    Output: [-1]
    Explanation: There is only one interval in the collection, so it outputs -1

    --- Example 2 ---
    Input: intervals = [[3,4],[2,3],[1,2]]
    Output: [-1,0,1]
    Explanation: There is no right interval for [3,4].
    The right interval for [2,3] is [3,4] since start0 = 3 is the smallest start that is >= end1 = 3.
    The right interval for [1,2] is [2,3] since start1 = 2 is the smallest start that is >= end2 = 2.

    --- Example 3 ---
    Input: intervals = [[1,4],[2,3],[3,4]]
    Output: [-1,2,-1]
    Explanation: There is no right interval for [1,4] and [3,4].
    The right interval for [2,3] is [3,4] since start2 = 3 is the smallest
    start that is >= end1 = 3.


    *** Constraints ***
    1 <= intervals.length <= 2 * 10^4
    intervals[i].length == 2
    -10^6 <= starti <= endi <= 10^6
    The start point of each interval is unique.

*/

#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.90% */
/* Space Beats: 36.64% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        vector<int> result(N, -1);

        map<int,int> map_start_to_idx; // Red-Black Tree

        for (int i = 0; i < N; i++)
            map_start_to_idx.insert( {intervals[i][0], i} );

        for (int i = 0; i < N; i++)
        {
            auto it = map_start_to_idx.lower_bound(intervals[i][1]);

            if (it != map_start_to_idx.end()) // It exists
                result[i] = it->second;
        }

        return result;
    }
};
