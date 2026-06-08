/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    435) Non-Overlapping Intervals
    ==============================

    ============
    Description:
    ============

    Given an array of intervals intervals where intervals[i] = [starti, endi],
    return the minimum number of intervals you need to remove to make the rest
    of the intervals non-overlapping.

    ====================================================================
    FUNCTION: int eraseOverlapIntervals(vector<vector<int>>& intervals);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
    Output: 1
    Explanation: [1,3] can be removed and the rest of the intervals are
                 non-overlapping.

    --- Example 2 ---
    Input: intervals = [[1,2],[1,2],[1,2]]
    Output: 2
    Explanation: You need to remove two [1,2] to make the rest of the intervals
                 non-overlapping.

    --- Example 3 ---
    Input: intervals = [[1,2],[2,3]]
    Output: 0
    Explanation: You don't need to remove any of the intervals since they're
                 already non-overlapping.

    *** Constraints ***
    1 <= intervals.length <= 105
    intervals[i].length == 2
    -5 * 104 <= starti < endi <= 5 * 104

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First, as in most interval problems - Sort by starting point.

    1--------3
         2---3
    1----2
             3---4


    Here are some examples that make this solution obvious:

    I)
         1----------5  7--------9


    II)
               3-------7
         1----------6     8---------10


    III)
               3----------8
         1----------6  7------------10


    IV)
             2----5    7------------10
         1-----------------8


    Each time two adjacent intervals are overlapping, continue with the one
    that has a smaller ending point.
    (That ensures that we'll have MINIMUM amount of removals)

*/

/* Time  Beats: 32.74% */
/* Space Beats: 90.03% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Space Complexity of C++'s Intro Sort
class Solution_Sort_By_start_time {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        int result = 0;

        /* Sort by start in ASCENDING order */
        sort(intervals.begin(), intervals.end());

        int prev_end = intervals[0][1];

        for (int i = 1; i < N; i++)
        {
            int& curr_start = intervals[i][0];
            int& curr_end   = intervals[i][1];

            if (prev_end > curr_start)
            {
                prev_end = min(prev_end, curr_end);
                result++;
            }
            else
            {
                prev_end = curr_end;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent idea to the one above, however once we sort by end_time
    instead, the code becomes a bit more clean.

    You should be aware of this "trick" for interval problem. Sorting by
    end_time is very handy at times in interval problems.

*/

/* Time  Beats: 67.77% */
/* Space Beats: 68.16% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Space Complexity of C++'s Intro Sort
class Solution_Sort_By_end_time {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        int result = 0;

        /* Sort */
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b){
            return a[1] < b[1]; // Sort by end_time
        });

        int prev_end = intervals[0][1];

        for (int i = 1; i < N; i++)
        {
            int& curr_start = intervals[i][0];
            int& curr_end   = intervals[i][1];

            if (prev_end > curr_start)
                result++;
            else
                prev_end = curr_end;
        }

        return result;
    }
};
