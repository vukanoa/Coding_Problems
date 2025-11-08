/*
    ============
    === EASY ===
    ============

    =====================================================
    1893) Check if All the Inegers in a Range Are Covered
    =====================================================

    ============
    Description:
    ============

    You are given a 2D integer array ranges and two integers left and right.
    Each ranges[i] = [starti, endi] represents an inclusive interval between
    starti and endi.

    Return true if each integer in the inclusive range [left, right] is covered
    by at least one interval in ranges. Return false otherwise.

    An integer x is covered by an interval ranges[i] = [starti, endi] if starti
    <= x <= endi.

    ===========================================================================
    FUNCTION: bool isCovered(vector<vector<int>>& ranges, int left, int right);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
    Output: true
    Explanation: Every integer between 2 and 5 is covered:
    - 2 is covered by the first range.
    - 3 and 4 are covered by the second range.
    - 5 is covered by the third range.

    --- Example 2 ---
    Input: ranges = [[1,10],[10,20]], left = 21, right = 21
    Output: false
    Explanation: 21 is not covered by any range.


    *** Constraints ***
    1 <= ranges.length <= 50
    1 <= starti <= endi <= 50
    1 <= left <= right <= 50

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental Line Sweep.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right)
    {
        const int N = ranges.size();
        int min_start = left;

        int line_sweep[52] = {}; // On the Stack
        for (const auto& entry : ranges)
        {
            const int& start = entry[0];
            const int& end   = entry[1];

            min_start = min(min_start, start);

            line_sweep[start]++;
            line_sweep[end + 1]--;
        }

        int covered_by = 0;
        for (int i = min_start; i <= right; i++)
        {
            covered_by += line_sweep[i];

            if (i >= left && covered_by <= 0)
                return false;
        }

        return true;
    }
};
