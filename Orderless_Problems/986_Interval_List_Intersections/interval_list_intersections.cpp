/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    986) Interval List Intersections
    ================================

    ============
    Description:
    ============

    You are given two lists of closed intervals, firstList and secondList,
    where firstList[i] = [starti, endi] and secondList[j] = [startj, endj].
    Each list of intervals is pairwise disjoint and in sorted order.

    Return the intersection of these two interval lists.

    A closed interval [a, b] (with a <= b) denotes the set of real numbers x
    with a <= x <= b.

    The intersection of two closed intervals is a set of real numbers that are
    either empty or represented as a closed interval. For example, the
    intersection of [1, 3] and [2, 4] is [2, 3].

    ====================================================================================================================
    FUNCTION: vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList);
    ====================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList = [[1,5],[8,12],[15,24],[25,26]]
    Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]

    --- Example 2 ---
    Input: firstList = [[1,3],[5,9]], secondList = []
    Output: []


    *** Constraints ***
    0 <= firstList.length, secondList.length <= 1000
    firstList.length + secondList.length >= 1
    0 <= starti < endi <= 10^9
    endi < starti+1
    0 <= startj < endj <= 10^9
    endj < startj+1

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only important part here is this:

        int start = max(firstList[i][0] , secondList[j][0]);
        int end   = min(firstList[i][1] , secondList[j][1]);


    Pick a  LATER   start.
    Pick an EARLIER end.

    If (start <= end)
        // That's an intersection {start, end}

    Then just increment the correct index based upon which of the two have an
    earlier end.

    That's it.

*/

/* Time  Beats: 36.16% */
/* Space Beats: 62.79% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList)
    {
        vector<vector<int>> result;
        const int N = firstList.size();
        const int M = secondList.size();

        int i = 0;
        int j = 0;

        while (i < N && j < M)
        {
            int start = max(firstList[i][0] , secondList[j][0]);
            int end   = min(firstList[i][1] , secondList[j][1]);

            if (start <= end)
                result.push_back( {start , end} );

            if (firstList[i][1] < secondList[j][1])
                i++;
            else
                j++;
        }

        return result;
    }
};
