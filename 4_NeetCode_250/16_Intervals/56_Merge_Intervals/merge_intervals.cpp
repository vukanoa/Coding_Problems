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

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Elegant {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end()); // Default by first val

        vector<vector<int>> results;
        results.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++)
        {
            int res_size = results.size();
            if (results[res_size - 1][1] >= intervals[i][0])
            {
                results[res_size - 1][0] = min(results[res_size - 1][0], intervals[i][0]);
                results[res_size - 1][1] = max(results[res_size - 1][1], intervals[i][1]);
            }
            else
                results.push_back(intervals[i]);
        }

        return results;
    }
};
